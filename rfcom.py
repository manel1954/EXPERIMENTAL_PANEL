import tkinter as tk
from tkinter import messagebox, simpledialog
import subprocess
import os

BLUETOOTH_SCRIPT = "/home/pi/.local/bluetooth.sh"

def scan_devices():
    output_text.delete(1.0, tk.END)
    output_text.insert(tk.END, "<<<< ESCANEANDO DISPOSITIVOS BLUETOOTH >>>>\n\n")
    try:
        result = subprocess.check_output(["sudo", "hcitool", "scan"], stderr=subprocess.STDOUT).decode()
        output_text.insert(tk.END, result)
        bind_button.config(state=tk.NORMAL)
    except subprocess.CalledProcessError as e:
        output_text.insert(tk.END, "Error al escanear dispositivos:\n" + e.output.decode())
        bind_button.config(state=tk.DISABLED)

def bind_mac():
    mac = simpledialog.askstring("MAC Bluetooth", "Pega la MAC aquí y pulsa OK")
    if mac:
        try:
            # Modificar el archivo de script bluetooth.sh
            with open(BLUETOOTH_SCRIPT, 'r') as file:
                lines = file.readlines()
            lines[1] = f"sudo rfcomm bind /dev/rfcomm0 {mac}\n"
            with open(BLUETOOTH_SCRIPT, 'w') as file:
                file.writelines(lines)
            
            # Ejecutar el bind
            subprocess.check_call(["sudo", "rfcomm", "bind", "/dev/rfcomm0", mac])
            output_text.delete(1.0, tk.END)
            output_text.insert(tk.END, "  ********************************************************************\n")
            output_text.insert(tk.END, "  *                   MAC ENLAZADA CORRECTAMENTE                     *\n")
            output_text.insert(tk.END, "  ********************************************************************\n")
        except Exception as e:
            messagebox.showerror("Error", f"Fallo al enlazar la MAC:\n{e}")
    else:
        messagebox.showwarning("MAC no ingresada", "No se ha ingresado ninguna dirección MAC.")

# Ventana principal
root = tk.Tk()
root.title("Enlazar Dispositivo Bluetooth")
root.geometry("600x400")

output_text = tk.Text(root, wrap=tk.WORD, font=("Courier", 10), bg="black", fg="lightgreen")
output_text.pack(expand=True, fill=tk.BOTH, padx=10, pady=10)

scan_button = tk.Button(root, text="Escanear Bluetooth", command=scan_devices, bg="cyan")
scan_button.pack(side=tk.LEFT, padx=10, pady=5)

bind_button = tk.Button(root, text="Enlazar MAC", command=bind_mac, bg="orange", state=tk.DISABLED)
bind_button.pack(side=tk.RIGHT, padx=10, pady=5)

root.mainloop()
