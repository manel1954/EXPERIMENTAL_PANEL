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
            # Ejemplo: sudo rfcomm bind /dev/rfcomm0 AA:BB:CC:DD:EE:FF
            partes = linea.split()
            if len(partes) >= 5:
                puerto = partes[3].replace("/dev/", "")
                mac = partes[4]
                vinculados.append((puerto, mac))
    return vinculados

def esta_bind(puerto):
    """Detectar si el rfcomm está vinculado en el sistema (comando rfcomm show)"""
    try:
        salida = subprocess.check_output(["rfcomm", "show"], text=True)
        # Busca líneas que contengan el puerto, ejemplo: rfcomm0: ...
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
            btn = tk.Button(frame_disp, text="Bind",
                            command=lambda p=puerto, m=mac: (ejecutar_bind(p, m), refrescar_lista()),
                            bg="#28a745", fg="white")
        else:
            btn = tk.Button(frame_disp, text="Unbind",
                            command=lambda p=puerto: (ejecutar_unbind(p), refrescar_lista()),
                            bg="#dc3545", fg="white")
        btn.pack(side="right", padx=5)

def ejecutar_script_completo():
    try:
        subprocess.check_call(["sudo", "sh", RUTA_FICHERO])
        messagebox.showinfo("Ejecutar script", "Script ejecutado correctamente.")
    except subprocess.CalledProcessError as e:
        messagebox.showerror("Error script", f"No se pudo ejecutar el script:\n{e}")

# --- Interfaz gráfica ---

root = tk.Tk()
root.title("Gestión Bluetooth rfcomm")
root.geometry("500x400")
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

# Inicializa la lista al iniciar
refrescar_lista()

root.mainloop()
