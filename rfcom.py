import tkinter as tk
from tkinter import messagebox
import subprocess
import re
import os

RUTA_FICHERO = "/home/pi/.local/bluetooth.sh"

def leer_vinculados():
    if not os.path.exists(RUTA_FICHERO):
        return []
    with open(RUTA_FICHERO, "r") as f:
        lineas = f.readlines()
    vinculados = []
    for linea in lineas:
        linea = linea.strip()
        if linea.startswith("sudo rfcomm bind"):
            partes = linea.split()
            if len(partes) >= 5:
                puerto = partes[3].replace("/dev/", "")
                mac = partes[4]
                vinculados.append((puerto, mac))
    return vinculados

def escribir_vinculados(vinculados):
    lineas = []
    if os.path.exists(RUTA_FICHERO):
        with open(RUTA_FICHERO, "r") as f:
            todas = f.readlines()
        if todas:
            lineas.append(todas[0].rstrip('\n') + '\n')
    else:
        lineas.append("#!/bin/bash\n")

    def key_rfcomm(item):
        puerto = item[0]
        m = re.match(r"rfcomm(\d+)", puerto)
        return int(m.group(1)) if m else 9999
    vinculados_ordenados = sorted(vinculados, key=key_rfcomm)

    for puerto, mac in vinculados_ordenados:
        lineas.append(f"sudo rfcomm bind /dev/{puerto} {mac}\n")

    with open(RUTA_FICHERO, "w") as f:
        f.writelines(lineas)

def esta_bind(puerto):
    try:
        salida = subprocess.check_output(["rfcomm", "show"], text=True)
        patron = re.compile(rf"^{puerto}:", re.MULTILINE)
        return bool(patron.search(salida))
    except subprocess.CalledProcessError:
        return False

def ejecutar_bind(puerto, mac):
    try:
        subprocess.check_call(["sudo", "rfcomm", "bind", f"/dev/{puerto}", mac])
        messagebox.showinfo("Bind", f"{puerto} vinculado a {mac}")
    except subprocess.CalledProcessError as e:
        messagebox.showerror("Error Bind", f"No se pudo vincular {puerto}:\n{e}")

def ejecutar_unbind(puerto):
    try:
        subprocess.check_call(["sudo", "rfcomm", "unbind", f"/dev/{puerto}"])
        messagebox.showinfo("Unbind", f"{puerto} desvinculado correctamente")
    except subprocess.CalledProcessError as e:
        messagebox.showerror("Error Unbind", f"No se pudo desvincular {puerto}:\n{e}")

def borrar_vinculado(puerto):
    vinculados = leer_vinculados()
    nuevos = [v for v in vinculados if v[0] != puerto]
    if len(nuevos) == len(vinculados):
        messagebox.showwarning("Borrar", f"No se encontró {puerto} en la lista")
        return
    escribir_vinculados(nuevos)
    messagebox.showinfo("Borrar", f"{puerto} eliminado de la lista")
    refrescar_lista()

def refrescar_lista():
    for widget in frame_resultados.winfo_children():
        widget.destroy()

    vinculados = leer_vinculados()
    if not vinculados:
        resultado_text.set("No hay dispositivos vinculados en el archivo.")
        return

    resultado_text.set(f"{len(vinculados)} dispositivo(s) en la lista:")
    for puerto, mac in vinculados:
        estado = "Activo" if esta_bind(puerto) else "Inactivo"
        color_estado = "green" if estado == "Activo" else "red"
        frame_disp = tk.Frame(frame_resultados, bg="#333", pady=2)
        frame_disp.pack(fill="x", padx=5, pady=2)

        # Texto blanco + estado en color
        label_texto = tk.Label(frame_disp, text=f"{puerto} - {mac} ",
                               fg="white", bg="#333", font=("Arial", 10))
        label_texto.pack(side="left", padx=5)

        label_estado = tk.Label(frame_disp, text=f"[{estado}]",
                                fg=color_estado, bg="#333", font=("Arial", 10, "bold"))
        label_estado.pack(side="left")

        frame_botones = tk.Frame(frame_disp, bg="#333")
        frame_botones.pack(side="right", padx=5)

        if estado == "Inactivo":
            btn_bind = tk.Button(frame_botones, text="Bind",
                                command=lambda p=puerto, m=mac: (ejecutar_bind(p, m), refrescar_lista()),
                                bg="#28a745", fg="white")
            btn_bind.pack(side="left", padx=2)

        btn_unbind = tk.Button(frame_botones, text="Unbind",
                              command=lambda p=puerto: (ejecutar_unbind(p), refrescar_lista()),
                              bg="#dc3545", fg="white")
        btn_unbind.pack(side="left", padx=2)

        btn_borrar = tk.Button(frame_botones, text="Borrar",
                               command=lambda p=puerto: borrar_y_refrescar(p),
                               bg="#6c757d", fg="white")
        btn_borrar.pack(side="left", padx=2)

def borrar_y_refrescar(puerto):
    borrar_vinculado(puerto)
    refrescar_lista()

def escanear_bluetooth():
    resultado_text.set("Escaneando dispositivos Bluetooth...")
    try:
        resultado = subprocess.check_output(['hcitool', 'scan'], text=True)
        dispositivos = re.findall(r'((?:[0-9A-F]{2}:){5}[0-9A-F]{2})\s+(.+)', resultado, re.IGNORECASE)

        for widget in frame_escaneo.winfo_children():
            widget.destroy()

        if not dispositivos:
            resultado_text.set("No se encontraron dispositivos.")
            return

        resultado_text.set(f"{len(dispositivos)} dispositivo(s) encontrado(s):")
        vinculados = leer_vinculados()
        macs_existentes = {mac for _, mac in vinculados}

        for mac, nombre in dispositivos:
            if mac in macs_existentes:
                texto_btn = f"{nombre} ({mac}) - Ya vinculado"
                estado_btn = "disabled"
            else:
                texto_btn = f"{nombre} ({mac})"
                estado_btn = "normal"

            boton = tk.Button(
                frame_escaneo,
                text=texto_btn,
                bg="#28a745" if estado_btn == "normal" else "#6c757d",
                fg="white",
                activebackground="#218838",
                activeforeground="white",
                state=estado_btn,
                command=lambda m=mac: agregar_dispositivo(m)
            )
            boton.pack(fill="x", padx=10, pady=2)
    except subprocess.CalledProcessError as e:
        resultado_text.set("Error al escanear Bluetooth.")
        messagebox.showerror("Error", f"No se pudo escanear: {e}")
    except Exception as ex:
        resultado_text.set("Error inesperado.")
        messagebox.showerror("Error", str(ex))

def agregar_dispositivo(mac):
    vinculados = leer_vinculados()
    puertos_usados = {int(re.match(r"rfcomm(\d+)", p).group(1)) for p, _ in vinculados}
    nuevo_puerto_num = 0
    while nuevo_puerto_num in puertos_usados:
        nuevo_puerto_num += 1
    nuevo_puerto = f"rfcomm{nuevo_puerto_num}"
    vinculados.append((nuevo_puerto, mac))
    escribir_vinculados(vinculados)
    messagebox.showinfo("Agregar", f"Dispositivo {mac} agregado como {nuevo_puerto}")
    refrescar_lista()
    escanear_bluetooth()

def ejecutar_script_completo():
    try:
        subprocess.check_call(["sudo", "sh", RUTA_FICHERO])
        messagebox.showinfo("Ejecutar script", "Script ejecutado correctamente.")
        refrescar_lista()
    except subprocess.CalledProcessError as e:
        messagebox.showerror("Error script", f"No se pudo ejecutar el script:\n{e}")

# --- Interfaz gráfica ---

root = tk.Tk()
root.title("Gestión Bluetooth rfcomm")
root.geometry("420x450+835+585")
root.configure(bg="#121212")

# Botón para refrescar lista vinculados
tk.Button(root, text="Refrescar lista vinculados", command=refrescar_lista,
          bg="#007bff", fg="white", font=("Arial", 10, "bold")).pack(pady=5)

# Frame lista vinculados
frame_resultados = tk.Frame(root, bg="#222222")
frame_resultados.pack(fill="both", expand=True, padx=10, pady=5)

resultado_text = tk.StringVar()
tk.Label(root, textvariable=resultado_text, bg="#121212", fg="white",
         font=("Arial", 10)).pack()

# Botón para ejecutar script completo
tk.Button(root, text="Ejecutar script completo", command=ejecutar_script_completo,
          bg="#17a2b8", fg="white", font=("Arial", 10, "bold")).pack(pady=5)

# Sección de escaneo de nuevos dispositivos
tk.Label(root, text="Escanear dispositivos Bluetooth cercanos", bg="#121212", fg="white",
         font=("Arial", 12, "bold")).pack(pady=10)

tk.Button(root, text="Escanear Bluetooth", command=escanear_bluetooth,
          bg="#28a745", fg="white", font=("Arial", 10, "bold")).pack(pady=5)

frame_escaneo = tk.Frame(root, bg="#222222")
frame_escaneo.pack(fill="both", expand=True, padx=10, pady=5)

refrescar_lista()
root.mainloop()
