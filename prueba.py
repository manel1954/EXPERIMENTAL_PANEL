import tkinter as tk
from tkinter import messagebox
import os
import shutil

INI_PATH = '/home/pi/MMDVMHost/MMDVM.ini'

def cargar_valores():
    if not os.path.exists(INI_PATH):
        messagebox.showerror("Error", f"No se encuentra el archivo {INI_PATH}")
        return "", ""

    callsign = ""
    dmr_id = ""
    in_general = False

    with open(INI_PATH, 'r') as f:
        for line in f:
            stripped = line.strip()
            if stripped.startswith("["):
                in_general = stripped.lower() == "[general]"
            elif in_general:
                if stripped.lower().startswith("callsign"):
                    callsign = stripped.split("=", 1)[1].strip()
                elif stripped.lower().startswith("id"):
                    dmr_id = stripped.split("=", 1)[1].strip()

    return callsign, dmr_id

def guardar_valores(nuevo_callsign, nuevo_id):
    if not os.path.exists(INI_PATH):
        messagebox.showerror("Error", f"No se encuentra el archivo {INI_PATH}")
        return

    backup = INI_PATH + ".bak"
    shutil.copy(INI_PATH, backup)

    lines = []
    in_general = False

    with open(INI_PATH, 'r') as f:
        for line in f:
            original_line = line
            stripped = line.strip()
            if stripped.startswith("["):
                in_general = stripped.lower() == "[general]"
            elif in_general:
                if stripped.lower().startswith("callsign"):
                    line = f"Callsign={nuevo_callsign}\n"
                elif stripped.lower().startswith("id"):
                    line = f"Id={nuevo_id}\n"
            lines.append(line)

    with open(INI_PATH, 'w') as f:
        f.writelines(lines)

    messagebox.showinfo("Guardado", "Cambios guardados.\nSe creó una copia de seguridad.")

def on_guardar():
    nuevo_callsign = entry_callsign.get().strip().upper()
    nuevo_id = entry_id.get().strip()

    if not nuevo_callsign or not nuevo_id:
        messagebox.showwarning("Campos vacíos", "Callsign e ID son obligatorios.")
        return

    guardar_valores(nuevo_callsign, nuevo_id)

def on_cargar():
    callsign, dmr_id = cargar_valores()
    entry_callsign.delete(0, tk.END)
    entry_callsign.insert(0, callsign)
    entry_id.delete(0, tk.END)
    entry_id.insert(0, dmr_id)

# Interfaz Tkinter
root = tk.Tk()
root.title("Editor MMDVM.ini (Seguro)")
root.geometry("360x200")
root.resizable(False, False)

frame = tk.Frame(root, padx=20, pady=20)
frame.pack()

tk.Label(frame, text="Callsign:").grid(row=0, column=0, sticky="e")
entry_callsign = tk.Entry(frame, width=25)
entry_callsign.grid(row=0, column=1)

tk.Label(frame, text="DMR ID:").grid(row=1, column=0, sticky="e")
entry_id = tk.Entry(frame, width=25)
entry_id.grid(row=1, column=1)

tk.Button(frame, text="Cargar", command=on_cargar).grid(row=2, column=0, pady=20)
tk.Button(frame, text="Guardar", command=on_guardar).grid(row=2, column=1)

on_cargar()
root.mainloop()
