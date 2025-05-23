import tkinter as tk
from tkinter import messagebox
import subprocess
import re
import os

RUTA_FICHERO = "/home/pi/.local/bluetooth.sh"

def escribir_comando_en_fichero(mac, linea):
    comando = f"sudo rfcomm bind /dev/rfcomm{linea} {mac}\n"

    os.makedirs(os.path.dirname(RUTA_FICHERO), exist_ok=True)

    try:
        if os.path.exists(RUTA_FICHERO):
            with open(RUTA_FICHERO, "r") as f:
                lineas = f.readlines()
        else:
            lineas = []

        # Asegurar que hay suficientes líneas
        while len(lineas) <= linea:
            lineas.append("\n")

        # Escribir en la línea correspondiente
        lineas[linea] = comando

        with open(RUTA_FICHERO, "w") as f:
            f.writelines(lineas)

        messagebox.showinfo("Hecho", f"Comando guardado en línea {linea+1}:\n{comando.strip()}")

    except Exception as e:
        messagebox.showerror("Error", f"No se pudo escribir en el archivo:\n{str(e)}")

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
            for i, (mac, nombre) in enumerate(dispositivos):
                boton = tk.Button(
                    frame_resultados,
                    text=f"{nombre} ({mac})",
                    bg="#28a745", fg="white",
                    command=lambda m=mac, n=i: escribir_comando_en_fichero(m, n)
                )
                boton.pack(fill="x", padx=10, pady=2)
    except subprocess.CalledProcessError as e:
        resultado_text.set("Error al escanear Bluetooth.")
        messagebox.showerror("Error", f"No se pudo escanear: {e}")
    except Exception as ex:
        resultado_text.set("Error inesperado.")
        messagebox.showerror("Error", str(ex))

# Interfaz gráfica
root = tk.Tk()
root.title("Escaneo Bluetooth")
root.geometry("420x450")
root.configure(bg="white")

tk.Button(root, text="Escanear Bluetooth", command=escanear_bluetooth, bg="#007bff", fg="white", font=("Arial", 10, "bold")).pack(pady=10)

resultado_text = tk.StringVar()
tk.Label(root, textvariable=resultado_text, bg="white", fg="black", font=("Arial", 10)).pack()

frame_resultados = tk.Frame(root, bg="white")
frame_resultados.pack(fill="both", expand=True, padx=10, pady=10)

root.mainloop()
