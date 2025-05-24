import tkinter as tk
from tkinter import messagebox
import subprocess
import os

ARCHIVO = "bluetooth.sh"

def leer_vinculados():
    if not os.path.isfile(ARCHIVO):
        return []
    with open(ARCHIVO, "r") as f:
        lineas = f.readlines()
    vinculados = []
    for linea in lineas:
        if linea.startswith("sudo rfcomm bind"):
            partes = linea.strip().split()
            if len(partes) == 5:
                vinculados.append((partes[3], partes[4]))
    return vinculados

def esta_bind(puerto):
    try:
        salida = subprocess.check_output(["rfcomm"], universal_newlines=True)
        for linea in salida.splitlines():
            if puerto in linea:
                return True
    except subprocess.CalledProcessError:
        pass
    return False

def ejecutar_bind(puerto, mac):
    subprocess.call(["sudo", "rfcomm", "bind", puerto, mac])

def ejecutar_unbind(puerto):
    subprocess.call(["sudo", "rfcomm", "release", puerto])

def borrar_y_refrescar(puerto):
    with open(ARCHIVO, "r") as f:
        lineas = f.readlines()
    with open(ARCHIVO, "w") as f:
        for linea in lineas:
            if not (linea.startswith("sudo rfcomm bind") and puerto in linea):
                f.write(linea)
    reorganizar_archivo()
    refrescar_lista()

def reorganizar_archivo():
    with open(ARCHIVO, "r") as f:
        lineas = f.readlines()

    primera_linea = ""
    if lineas and lineas[0].strip() == "#!/bin/bash":
        primera_linea = lineas.pop(0)

    comandos = [linea for linea in lineas if linea.startswith("sudo rfcomm bind")]
    comandos.sort(key=lambda x: int(x.split()[3].replace("/dev/rfcomm", "")))

    nuevos_comandos = []
    for i, linea in enumerate(comandos):
        partes = linea.strip().split()
        if len(partes) == 5:
            mac = partes[4]
            nuevos_comandos.append(f"sudo rfcomm bind /dev/rfcomm{i} {mac}\n")

    with open(ARCHIVO, "w") as f:
        if primera_linea:
            f.write(primera_linea + "\n")
        f.writelines(nuevos_comandos)

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
                         fg=color_estado, bg="#333", font=("Arial", 10), anchor="w")
        label.pack(side="left", fill="x", expand=True, padx=5)

        frame_botones = tk.Frame(frame_disp, bg="#333")
        frame_botones.pack(side="right", padx=5)

        ancho_boton = 10  # ancho uniforme para todos los botones

        if estado == "Inactivo":
            btn_bind = tk.Button(frame_botones, text="Bind", width=ancho_boton,
                                 font=("Arial", 9), bg="#28a745", fg="white",
                                 command=lambda p=puerto, m=mac: (ejecutar_bind(p, m), refrescar_lista()))
            btn_bind.pack(side="left", padx=2)

        btn_unbind = tk.Button(frame_botones, text="Unbind", width=ancho_boton,
                               font=("Arial", 9), bg="#dc3545", fg="white",
                               command=lambda p=puerto: (ejecutar_unbind(p), refrescar_lista()))
        btn_unbind.pack(side="left", padx=2)

        btn_borrar = tk.Button(frame_botones, text="Borrar", width=ancho_boton,
                               font=("Arial", 9), bg="#6c757d", fg="white",
                               command=lambda p=puerto: borrar_y_refrescar(p))
        btn_borrar.pack(side="left", padx=2)

# Interfaz
root = tk.Tk()
root.title("Gestor Bluetooth")
root.geometry("600x400")  # Tamaño fijo
root.configure(bg="#222")

frame_resultados = tk.Frame(root, bg="#222")
frame_resultados.pack(fill="both", expand=True, padx=10, pady=10)

resultado_text = tk.StringVar()
resultado_label = tk.Label(root, textvariable=resultado_text, bg="#222", fg="white", font=("Arial", 10))
resultado_label.pack()

refrescar_lista()
root.mainloop()
