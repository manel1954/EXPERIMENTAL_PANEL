import tkinter as tk
from tkinter import messagebox
import subprocess
import os
import re

BLUETOOTH_SCRIPT = "/home/pi/.local/bluetooth.sh"

def scan_devices():
    output_text.delete(1.0, tk.END)
    output_text.insert(tk.END, "<<<< ESCANEANDO DISPOSITIVOS BLUETOOTH >>>>\n\n")
    try:
        result = subprocess.check_output(["sudo", "hcitool", "scan"], stderr=subprocess.STDOUT).decode()
        print("Resultado crudo de hcitool scan:\n", result)  # Debug opcional
        devices = []

        lines = result.splitlines()
        for line in lines[1:]:  # Ignorar "Scanning ..."
            line = line.strip()
            match = re.match(r"([0-9A-F:]{17})\s+(.+)", line)
            if match:
                mac, name = match.groups()
                devices.append((name.strip(), mac.strip()))

        if not devices:
            output_text.insert(tk.END, "No se encontraron dispositivos Bluetooth.\n")
            return

        for name, mac in devices:
            output_text.insert(tk.END, f"{mac} - {name}\n")

        select_mac(devices)

    except subprocess.CalledProcessError as e:
        output_text.insert(tk.END, "Error al escanear dispositivos:\n" + e.output.decode())

def select_mac(devices):
    def on_select(event):
        selection = listbox.curselection()
        if selection:
            idx = selection[0]
            name, mac = devices[idx]
            list_window.destroy()
            bind_mac(mac)

    list_window = tk.Toplevel(root)
    list_window.title("Selecciona un dispositivo Bluetooth")
    listbox = tk.Listbox(list_window, font=("Courier", 11), width=60, height=10)
    listbox.pack(padx=10, pady=10, fill=tk.BOTH, expand=True)

    for name, mac in devices:
        listbox.insert(tk.END, f"{name:30} {mac}")

    listbox.bind("<Double-Button-1>", on_select)

def bind_mac(mac):
    try:
        output_text.insert(tk.END, f"\nLiberando rfcomm0...\n")
        subprocess.call(["sudo", "rfcomm", "unbind", "/dev/rfcomm0"])  # No importa si falla

        # Actualizar el archivo bluetooth.sh
        if os.path.exists(BLUETOOTH_SCRIPT):
            with open(BLUETOOTH_SCRIPT, 'r') as file:
                lines = file.readlines()
            if len(lines) < 2:
                lines += ["\n"] * (2 - len(lines))
            lines[1] = f"sudo rfcomm bind /dev/rfcomm0 {mac}\n"
        else:
            lines = ["#!/bin/bash\n", f"sudo rfcomm bind /dev/rfcomm0 {mac}\n"]

        with open(BLUETOOTH_SCRIPT, 'w') as file:
            file.writelines(lines)

        subprocess.check_call(["sudo", "rfcomm", "bind", "/dev/rfcomm0", mac])

        output_text.insert(tk.END, "\n  ********************************************************************\n")
        output_text.insert(tk.END, "  *                   MAC ENLAZADA CORRECTAMENTE                     *\n")
        output_text.insert(tk.END, "  ********************************************************************\n")

    except Exception as e:
        messagebox.showerror("Error", f"Fallo al enlazar la MAC:\n{e}")

# Interfaz principal
root = tk.Tk()
root.title("Enlazar Dispositivo Bluetooth")
root.geometry("700x400")

output_text = tk.Text(root, wrap=tk.WORD, font=("Courier", 10), bg="black", fg="lightgreen")
output_text.pack(expand=True, fill=tk.BOTH, padx=10, pady=10)

scan_button = tk.Button(root, text="Escanear Bluetooth", command=scan_devices, bg="cyan")
scan_button.pack(pady=5)

root.mainloop()
