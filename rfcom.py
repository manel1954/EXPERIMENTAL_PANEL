import tkinter as tk
from tkinter import messagebox
import subprocess
import re
import os

RUTA_FICHERO = "/home/pi/.local/bluetooth.sh"

def leer_vinculaciones():
    vinculaciones = []
    if os.path.exists(RUTA_FICHERO):
        with open(RUTA_FICHERO, "r") as f:
            lineas = f.readlines()
            for i, linea in enumerate(lineas):
                if i == 0 or not linea.strip():
                    continue
                match = re.match(r"sudo rfcomm bind /dev/rfcomm(\d+) ([0-9A-F:]{17})", linea.strip())
                if match:
                    rfcomm = int(match.group(1))
                    mac = match.group(2)
                    vinculaciones.append((rfcomm, mac))
    return vinculaciones

def escribir_vinculaciones(vinculaciones):
    vinculaciones.sort()
    with open(RUTA_FICHERO, "w") as f:
        f.write("#!/bin/bash\n")
        for rfcomm, mac in vinculaciones:
            f.write(f"sudo rfcomm bind /dev/rfcomm{rfcomm} {mac}\n")

def obtener_rfcomm_activos():
    activos = set()
    try:
        output = subprocess.check_output(["rfcomm"], text=True)
        for line in output.strip().split("\n"):
            match = re.match(r"/dev/rfcomm(\d+):", line)
            if match:
                activos.add(int(match.group(1)))
    except subprocess.CalledProcessError:
        pass
    return activos

def eliminar_vinculacion(rfcomm):
    vinculaciones = leer_vinculaciones()
    vinculaciones = [(r, m) for r, m in vinculaciones if r != rfcomm]
    escribir_vinculaciones(vinculaciones)
    actualizar_lista()

def hacer_bind_individual(rfcomm, mac):
    activos = obtener_rfcomm_activos()
    if rfcomm in activos:
        messagebox.showinfo("Info", f"rfcomm{rfcomm} ya está vinculado.")
        return
    try:
        subprocess.run(["sudo", "rfcomm", "bind", f"/dev/rfcomm{rfcomm}", mac], check=True)
        messagebox.showinfo("Bind", f"rfcomm{rfcomm} vinculado correctamente.")
    except subprocess.CalledProcessError as e:
        messagebox.showerror("Error", f"No se pudo vincular rfcomm{rfcomm}:\n{e}")
    actualizar_lista()

def hacer_unbind(rfcomm):
    activos = obtener_rfcomm_activos()
    if rfcomm not in activos:
        messagebox.showinfo("Info", f"rfcomm{rfcomm} no está vinculado.")
        return
    try:
        subprocess.run(["sudo", "rfcomm", "release", f"/dev/rfcomm{rfcomm}"], check=True)
        messagebox.showinfo("Unbind", f"rfcomm{rfcomm} liberado.")
    except subprocess.CalledProcessError as e:
        messagebox.showerror("Error", f"No se pudo liberar rfcomm{rfcomm}:\n{e}")
    actualizar_lista()

def actualizar_lista():
    for widget in frame_lista.winfo_children():
        widget.destroy()
    vinculaciones = leer_vinculaciones()
    activos = obtener_rfcomm_activos()
    for rfcomm, mac in vinculaciones:
        estado = " (activo)" if rfcomm in activos else " (inactivo)"
        frame = tk.Frame(frame_lista, bg="black")
        frame.pack(fill="x", padx=5, pady=2)
        lbl = tk.Label(frame, text=f"rfcomm{rfcomm} → {mac}{estado}", fg="white", bg="black")
        lbl.pack(side="left", padx=5)

        # Botón bind (solo si está inactivo)
        if rfcomm not in activos:
            tk.Button(frame, text="Bind", command=lambda r=rfcomm, m=mac: hacer_bind_individual(r, m)).pack(side="right", padx=5)
        else:
            # Botón unbind (solo si está activo)
            tk.Button(frame, text="Unbind", command=lambda r=rfcomm: hacer_unbind(r)).pack(side="right", padx=5)

        tk.Button(frame, text="Eliminar", command=lambda r=rfcomm: eliminar_vinculacion(r)).pack(side="right")

def ejecutar_script():
    try:
        subprocess.run(["sudo", "sh", RUTA_FICHERO], check=True)
        messagebox.showinfo("Ejecutado", "Script ejecutado correctamente.")
        actualizar_lista()
    except subprocess.CalledProcessError as e:
        messagebox.showerror("Error", f"No se pudo ejecutar el script:\n{e}")

def escanear_bluetooth():
    resultado_text.set("Escaneando dispositivos Bluetooth...")
    try:
        resultado = subprocess.check_output(['hcitool', 'scan'], text=True)
        dispositivos = re.findall(r'((?:[0-9A-F]{2}:){5}[0-9A-F]{2})\s+(.+)', resultado, re.IGNORECASE)

        for widget in frame_resultados.winfo_children():
            widget.destroy()

        if not dispositivos:
            resultado_text.set("No se encontraron dispositivos.")
        else:
            resultado_text.set(f"{len(dispositivos)} dispositivo(s) encontrado(s):")
            vinculaciones = leer_vinculaciones()
            usados = set(rfcomm for rfcomm, _ in vinculaciones)
            disponibles = [i for i in range(256) if i not in usados]

            for mac, nombre in dispositivos:
                if any(mac == v[1] for v in vinculaciones):
                    continue  # ya vinculado
                if not disponibles:
                    continue
                nuevo_rfcomm = disponibles.pop(0)
                def vincular(m=mac, r=nuevo_rfcomm):
                    vinculaciones = leer_vinculaciones()
                    vinculaciones.append((r, m))
                    escribir_vinculaciones(vinculaciones)
                    actualizar_lista()
                boton = tk.Button(frame_resultados, text=f"{nombre} ({mac})", bg="#28a745", fg="white", command=vincular)
                boton.pack(fill="x", padx=10, pady=2)
    except subprocess.CalledProcessError:
        resultado_text.set("Error al escanear Bluetooth.")
        messagebox.showerror("Error", "No se pudo escanear.")
    except Exception as ex:
        resultado_text.set("Error inesperado.")
        messagebox.showerror("Error", str(ex))

# Interfaz
root = tk.Tk()
root.title("Gestor Bluetooth")
root.geometry("500x600")
root.configure(bg="black")

tk.Button(root, text="Escanear Bluetooth", command=escanear_bluetooth, bg="#007bff", fg="white").pack(pady=10)

resultado_text = tk.StringVar()
tk.Label(root, textvariable=resultado_text, fg="white", bg="black").pack()

frame_resultados = tk.Frame(root, bg="black")
frame_resultados.pack(fill="x", padx=10)

tk.Label(root, text="Dispositivos vinculados:", fg="white", bg="black", font=("Arial", 10, "bold")).pack(pady=(20,5))

frame_lista = tk.Frame(root, bg="black")
frame_lista.pack(fill="both", expand=True, padx=10)

tk.Button(root, text="Ejecutar script completo", command=ejecutar_script, bg="#17a2b8", fg="white", font=("Arial", 10, "bold")).pack(pady=10)

actualizar_lista()
root.mainloop()
