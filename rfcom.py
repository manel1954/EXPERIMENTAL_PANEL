import os
import re
import tkinter as tk
from tkinter import messagebox
import subprocess

RUTA_FICHERO = "/home/pi/.local/bluetooth.sh"

def cargar_vinculaciones():
    vinculaciones = []
    if os.path.exists(RUTA_FICHERO):
        with open(RUTA_FICHERO, "r") as f:
            lineas = f.readlines()[1:]  # ignorar #!/bin/bash
        for linea in lineas:
            match = re.match(r'sudo rfcomm bind /dev/rfcomm(\d+) ([0-9A-F:]{17})', linea.strip(), re.IGNORECASE)
            if match:
                rfcomm_n = int(match.group(1))
                mac = match.group(2)
                vinculaciones.append((rfcomm_n, mac))
    return sorted(vinculaciones)

def guardar_vinculaciones(vinculaciones):
    vinculaciones_ordenadas = sorted(vinculaciones, key=lambda x: x[0])
    with open(RUTA_FICHERO, "w") as f:
        f.write("#!/bin/bash\n")
        for rfcomm_n, mac in vinculaciones_ordenadas:
            f.write(f"sudo rfcomm bind /dev/rfcomm{rfcomm_n} {mac}\n")

def obtener_siguiente_rfcomm(vinculaciones):
    ocupados = {rfcomm for rfcomm, _ in vinculaciones}
    n = 0
    while n in ocupados:
        n += 1
    return n

def eliminar_vinculacion(mac_objetivo):
    vinculaciones = cargar_vinculaciones()
    nuevas = [(rfcomm, mac) for rfcomm, mac in vinculaciones if mac != mac_objetivo]
    guardar_vinculaciones(nuevas)
    listar_vinculados()

def agregar_vinculacion(mac_nueva):
    vinculaciones = cargar_vinculaciones()
    if mac_nueva in [mac for _, mac in vinculaciones]:
        messagebox.showinfo("Info", f"{mac_nueva} ya está vinculada.")
        return
    nuevo_rfcomm = obtener_siguiente_rfcomm(vinculaciones)
    vinculaciones.append((nuevo_rfcomm, mac_nueva))
    guardar_vinculaciones(vinculaciones)
    listar_vinculados()
    messagebox.showinfo("Añadido", f"Vinculado: rfcomm{nuevo_rfcomm} → {mac_nueva}")

def listar_vinculados():
    for widget in frame_vinculados.winfo_children():
        widget.destroy()
    vinculaciones = cargar_vinculaciones()
    for rfcomm_n, mac in vinculaciones:
        fila = tk.Frame(frame_vinculados, bg="black")
        fila.pack(fill="x", pady=2)
        tk.Label(fila, text=f"/dev/rfcomm{rfcomm_n}: {mac}", fg="white", bg="black").pack(side="left", padx=5)
        tk.Button(fila, text="Eliminar", command=lambda m=mac: eliminar_vinculacion(m), bg="red", fg="white").pack(side="right", padx=5)

def escanear_bluetooth():
    resultado_text.set("Escaneando...")
    try:
        resultado = subprocess.check_output(['hcitool', 'scan'], text=True)
        dispositivos = re.findall(r'((?:[0-9A-F]{2}:){5}[0-9A-F]{2})\s+(.+)', resultado, re.IGNORECASE)
        for widget in frame_resultados.winfo_children():
            widget.destroy()
        if not dispositivos:
            resultado_text.set("No se encontraron dispositivos.")
        else:
            resultado_text.set(f"{len(dispositivos)} dispositivo(s) encontrado(s):")
            for mac, nombre in dispositivos:
                boton = tk.Button(
                    frame_resultados,
                    text=f"{nombre} ({mac})",
                    bg="#28a745", fg="white",
                    command=lambda m=mac: agregar_vinculacion(m)
                )
                boton.pack(fill="x", padx=5, pady=2)
    except Exception as ex:
        resultado_text.set("Error al escanear.")
        messagebox.showerror("Error", str(ex))

# Interfaz
root = tk.Tk()
root.title("Gestión Bluetooth")
root.geometry("500x600")
root.configure(bg="black")

tk.Button(root, text="Escanear Bluetooth", command=escanear_bluetooth, bg="#007bff", fg="white").pack(pady=10)

resultado_text = tk.StringVar()
tk.Label(root, textvariable=resultado_text, bg="black", fg="white").pack()

tk.Label(root, text="Dispositivos encontrados", bg="black", fg="white").pack()
frame_resultados = tk.Frame(root, bg="black")
frame_resultados.pack(fill="both", expand=False, padx=10)

tk.Label(root, text="Dispositivos vinculados", bg="black", fg="white").pack(pady=(10, 0))
frame_vinculados = tk.Frame(root, bg="black")
frame_vinculados.pack(fill="both", expand=True, padx=10)

listar_vinculados()
root.mainloop()
