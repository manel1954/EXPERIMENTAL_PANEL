import tkinter as tk
from tkinter import messagebox
import subprocess
import os
import re

script_file = "bluetooth.sh"

def get_bluetooth_status():
    try:
        output = subprocess.check_output(["rfkill", "list", "bluetooth"], text=True)
        if "Soft blocked: yes" in output or "Hard blocked: yes" in output:
            return False
        return True
    except subprocess.CalledProcessError:
        return False

def update_bt_status_label():
    status = get_bluetooth_status()
    status_label.config(text=f"Bluetooth {'ACTIVADO' if status else 'DESACTIVADO'}", bg="green" if status else "red")

def toggle_bluetooth(enable):
    try:
        subprocess.run(["rfkill", "unblock" if enable else "block", "bluetooth"], check=True)
        update_bt_status_label()
    except subprocess.CalledProcessError:
        messagebox.showerror("Error", f"No se pudo {'activar' if enable else 'desactivar'} el Bluetooth.")

def scan_devices():
    try:
        output = subprocess.check_output(["bluetoothctl", "scan", "on"], stderr=subprocess.STDOUT, timeout=5, text=True)
        output += subprocess.check_output(["bluetoothctl", "devices"], text=True)
    except subprocess.TimeoutExpired:
        output = subprocess.check_output(["bluetoothctl", "devices"], text=True)
    devices = re.findall(r'Device ([\w:]+) (.+)', output)
    device_list.delete(0, tk.END)
    for mac, name in devices:
        device_list.insert(tk.END, f"{name} ({mac})")

def load_bindings():
    if not os.path.exists(script_file):
        with open(script_file, "w") as f:
            f.write("#!/bin/bash\n")
    bindings_list.delete(0, tk.END)
    with open(script_file, "r") as f:
        lines = f.readlines()[1:]
        for line in lines:
            match = re.match(r'sudo rfcomm bind (/dev/rfcomm\d+) ([\w:]+)', line.strip())
            if match:
                bindings_list.insert(tk.END, f"{match.group(1)} -> {match.group(2)}")

def add_binding():
    selection = device_list.curselection()
    if not selection:
        return
    device = device_list.get(selection[0])
    mac = device.split("(")[-1].strip(")")
    with open(script_file, "r") as f:
        lines = f.readlines()
    used_rfcomm = {int(re.search(r'rfcomm(\d+)', line).group(1)) for line in lines[1:] if 'rfcomm' in line}
    available = next(i for i in range(10) if i not in used_rfcomm)
    new_line = f"sudo rfcomm bind /dev/rfcomm{available} {mac}\n"
    lines.append(new_line)
    lines[1:] = sorted(lines[1:], key=lambda x: int(re.search(r'rfcomm(\d+)', x).group(1)))
    with open(script_file, "w") as f:
        f.writelines(lines)
    load_bindings()

def remove_binding():
    selection = bindings_list.curselection()
    if not selection:
        return
    item = bindings_list.get(selection[0])
    rfcomm = re.search(r'rfcomm\d+', item).group(0)
    with open(script_file, "r") as f:
        lines = f.readlines()
    new_lines = [lines[0]] + [line for line in lines[1:] if rfcomm not in line]
    rfcomm_lines = sorted([line for line in new_lines[1:] if 'rfcomm' in line], key=lambda x: int(re.search(r'rfcomm(\d+)', x).group(1)))
    for i, line in enumerate(rfcomm_lines):
        mac = re.search(r'([\w:]+)$', line.strip()).group(1)
        rfcomm_lines[i] = f"sudo rfcomm bind /dev/rfcomm{i} {mac}\n"
    with open(script_file, "w") as f:
        f.write(lines[0])
        f.writelines(rfcomm_lines)
    load_bindings()

def run_script():
    subprocess.run(["sudo", "sh", script_file])
    update_rfcomm_status()

def release_binding():
    selection = bindings_list.curselection()
    if not selection:
        return
    item = bindings_list.get(selection[0])
    rfcomm = re.search(r'rfcomm\d+', item).group(0)
    subprocess.run(["sudo", "rfcomm", "release", rfcomm])
    update_rfcomm_status()

def update_rfcomm_status():
    try:
        output = subprocess.check_output(["rfcomm"], text=True)
        connected = re.findall(r"rfcomm\d+:", output)
        status_text = f"Dispositivos vinculados:\n" + "\n".join(connected) if connected else "No hay dispositivos vinculados."
    except subprocess.CalledProcessError:
        status_text = "No se pudo obtener el estado de rfcomm."
    rfcomm_status.config(text=status_text)

root = tk.Tk()
root.title("Gestor de Vinculaciones Bluetooth rfcomm")
root.geometry("600x500")

status_label = tk.Label(root, text="", font=("Arial", 12), width=25)
status_label.pack(pady=5)

btn_frame = tk.Frame(root)
btn_frame.pack()

tk.Button(btn_frame, text="Activar Bluetooth", command=lambda: toggle_bluetooth(True)).grid(row=0, column=0, padx=5)
tk.Button(btn_frame, text="Desactivar Bluetooth", command=lambda: toggle_bluetooth(False)).grid(row=0, column=1, padx=5)

tk.Label(root, text="Dispositivos detectados").pack()
device_list = tk.Listbox(root, width=50)
device_list.pack()

tk.Button(root, text="Escanear dispositivos", command=scan_devices).pack(pady=5)
tk.Button(root, text="Agregar vinculación", command=add_binding).pack()

tk.Label(root, text="Dispositivos vinculados").pack()
bindings_list = tk.Listbox(root, width=50)
bindings_list.pack()

action_frame = tk.Frame(root)
action_frame.pack(pady=5)
tk.Button(action_frame, text="Eliminar vinculación", command=remove_binding).grid(row=0, column=0, padx=5)
tk.Button(action_frame, text="Ejecutar script", command=run_script).grid(row=0, column=1, padx=5)
tk.Button(action_frame, text="Liberar rfcomm", command=release_binding).grid(row=0, column=2, padx=5)

rfcomm_status = tk.Label(root, text="", font=("Courier", 10), justify="left")
rfcomm_status.pack(pady=10)

update_bt_status_label()
load_bindings()
update_rfcomm_status()

root.mainloop()
