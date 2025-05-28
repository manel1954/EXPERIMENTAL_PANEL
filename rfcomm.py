import tkinter as tk
from tkinter import messagebox
import subprocess
import os

ARCHIVO = "bluetooth.sh"

def estado_bluetooth():
    try:
        with open("/boot/config.txt", "r") as f:
            lineas = f.readlines()
        if len(lineas) >= 57:
            return lineas[56].strip().startswith("#")
        return False
    except:
        return False

def cambiar_estado_bluetooth(activar):
    comando = (
        ["sudo", "sed", "-i", "57c #dtoverlay=pi3-disable-bt", "/boot/config.txt"]
        if activar else
        ["sudo", "sed", "-i", "57c dtoverlay=pi3-disable-bt", "/boot/config.txt"]
    )
    try:
        subprocess.check_call(comando)
        messagebox.showinfo("Bluetooth", "Cambio aplicado. Reinicia la Raspberry para que surta efecto.")
    except subprocess.CalledProcessError:
        messagebox.showerror("Error", "No se pudo cambiar el estado del Bluetooth.")

def abrir_formulario_importante():
    ventana = tk.Toplevel()
    ventana.title("Descripción")
    ventana.configure(bg="black")

    texto = tk.Text(ventana, wrap="word", font=("Arial", 10), bg="black", fg="white", width=60, height=20)
    texto.insert(tk.END, """
    GESTIÓN BLUETOOTH RFCOMM\n
    Este programa permite:
    • Escanear dispositivos Bluetooth disponibles.
    • Añadir un dispositivo y asignarle un número rfcomm.
    • Eliminar un dispositivo previamente añadido.
    • Ejecutar todos los comandos rfcomm bind desde el script bluetooth.sh.
    • Ver el estado de las vinculaciones actuales del sistema.
    • Realizar unrelease individual de cada rfcomm activo.
    • Cambiar el estado del Bluetooth en el sistema (activar/desactivar).
    
    El archivo bluetooth.sh contiene los comandos:
    sudo rfcomm bind /dev/rfcommN MAC
    
    Las líneas se mantienen ordenadas por rfcommN.
    Si se elimina un dispositivo, su número se reutiliza en futuras vinculaciones.
    
    El botón de ejecución aplicará todos los comandos listados.
    El botón de estado permitirá gestionar el Bluetooth de la Raspberry Pi.
    
    IMPORTANTE: Cambios en el estado del Bluetooth requieren reinicio para aplicarse.
    """)
    texto.configure(state="disabled")
    texto.pack(padx=10, pady=10)

    # Estado actual del Bluetooth
    estado_actual = estado_bluetooth()

    label_estado = tk.Label(
        ventana, text="ESTADO DEL BLUETOOTH:",
        bg="#5007ed", fg="white", font=("Arial", 10, "bold"),
        bd=0, highlightthickness=0
    )
    label_estado.pack(pady=5)

    if estado_actual:
        boton_bt = tk.Button(
            ventana, text="DESACTIVADO  (click para ACTIVARLO)",
            command=lambda: cambiar_estado_bluetooth(True),
            bg="#dc3545", fg="white", font=("Arial", 10, "bold"),
            bd=0, highlightthickness=0
        )
    else:
        boton_bt = tk.Button(
            ventana, text="ACTIVADO  (click para DESACTIVARLO)",
            command=lambda: cambiar_estado_bluetooth(False),
            bg="#28a745", fg="white", font=("Arial", 10, "bold"),
            bd=0, highlightthickness=0
        )

    boton_bt.pack(pady=(0, 10))

def ejecutar_bluetooth_sh():
    os.system("sudo sh bluetooth.sh")
    messagebox.showinfo("Bluetooth", "Script ejecutado.")

def mostrar_rfcomm_activos():
    try:
        resultado = subprocess.check_output("rfcomm", shell=True, text=True)
        messagebox.showinfo("Vinculaciones Activas", resultado if resultado else "No hay vinculaciones activas.")
    except subprocess.CalledProcessError:
        messagebox.showerror("Error", "No se pudo obtener el estado de rfcomm.")

root = tk.Tk()
root.title("Gestor de Bluetooth RFCOMM")
root.geometry("400x300")
root.configure(bg="black")

# Botones principales
tk.Button(root, text="Descripción / Información",
          command=abrir_formulario_importante,
          bg="#17a2b8", fg="white", font=("Arial", 10, "bold"),
          bd=0, highlightthickness=0).pack(pady=10)

tk.Button(root, text="Ejecutar Script Bluetooth",
          command=ejecutar_bluetooth_sh,
          bg="#007bff", fg="white", font=("Arial", 10, "bold"),
          bd=0, highlightthickness=0).pack(pady=10)

tk.Button(root, text="Mostrar rfcomm activos",
          command=mostrar_rfcomm_activos,
          bg="#6c757d", fg="white", font=("Arial", 10, "bold"),
          bd=0, highlightthickness=0).pack(pady=10)

root.mainloop()
