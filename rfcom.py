import tkinter as tk
from tkinter import messagebox
import subprocess
import re
import os

RUTA_FICHERO = "/home/pi/.local/bluetooth.sh"

def leer_vinculados():
    """Leer el fichero bluetooth.sh y devolver lista de tuples (rfcommN, mac)"""
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
    """Reescribe el archivo bluetooth.sh respetando la primera línea #!/bin/bash"""
    lineas = []
    if os.path.exists(RUTA_FICHERO):
        with open(RUTA_FICHERO, "r") as f:
            todas = f.readlines()
        if todas:
            # Primera línea es #!/bin/bash (o similar)
            lineas.append(todas[0].rstrip('\n') + '\n')
    else:
        # Si no existe, crea la línea bin bash por defecto
        lineas.append("#!/bin/bash\n")

    # Ahora las vinculaciones, ordenadas según el número de rfcomm
    # ordena por el número después de rfcomm
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
    """Detectar si el rfcomm está vinculado en el sistema"""
    try:
        salida = subprocess.check_output(["rfcomm", "show"], text=True)
        patron = re.compile(rf"^{puerto}:", re.MULTILINE)
        if patron.search(salida):
            return True
    except subprocess.CalledProcessError:
        pass
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

        label = tk.Label(frame_disp, text=f"{puerto} - {mac} [{estado}]",
                         fg=color_estado, bg="#333", font=("Arial", 10))
        label.pack(side="left", padx=5)

        if estado == "Inactivo":
            btn_bind = tk.Button(frame_disp, text="Bind",
                                command=lambda p=puerto, m=mac: (ejecutar_bind(p, m), refrescar_lista()),
                                bg="#28a745", fg="white")
            btn_bind.pack(side="right", padx=5)
        else:
            btn_unbind = tk.Button(frame_disp, text="Unbind",
                                  command=lambda p=puerto: (ejecutar_unbind(p), refrescar_lista()),
                                  bg="#dc3545", fg="white")
            btn_unbind.pack(side="right", padx=5)

        btn_borrar = tk.Button(frame_disp, text="Borrar",
                               command=lambda p=puerto: (borrar_vinculado(p), refrescar_lista()),
                               bg="#6c757d", fg="white")
        btn_borrar.pack(side="right", padx=5)

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
root.geometry("550x450")
root.configure(bg="#121212")

tk.Button(root, text="Refrescar lista", command=refrescar_lista,
          bg="#007bff", fg="white", font=("Arial", 10, "bold")).pack(pady=10)

frame_resultados = tk.Frame(root, bg="#222222")
frame_resultados.pack(fill="both", expand=True, padx=10, pady=10)

resultado_text = tk.StringVar()
tk.Label(root, textvariable=resultado_text, bg="#121212", fg="white",
         font=("Arial", 10)).pack()

tk.Button(root, text="Ejecutar script completo", command=ejecutar_script_completo,
          bg="#17a2b8", fg="white", font=("Arial", 10, "bold")).pack(pady=10)

refrescar_lista()

root.mainloop()
