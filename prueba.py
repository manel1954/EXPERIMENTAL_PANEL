import tkinter as tk
from tkinter import messagebox
import configparser
import os
import shutil

INI_PATH = '/home/pi/MMDVMHost/MMDVM.ini'

def cargar_config():
    if not os.path.isfile(INI_PATH):
        messagebox.showerror("Error", f"No se encontró el archivo:\n{INI_PATH}")
        return None
    config = configparser.ConfigParser(strict=False)
    config.optionxform = str  # Respeta mayúsculas/minúsculas en las claves
    config.read(INI_PATH)
    return config

def guardar_config_si_cambia(nuevo_callsign, nuevo_id):
    config = cargar_config()
    if config is None:
        return

    cambiado = False

    callsign_actual = config.get('General', 'Callsign', fallback='')
    id_actual = config.get('DMR', 'Id', fallback='')

    if nuevo_callsign and nuevo_callsign != callsign_actual:
        config.set('General', 'Callsign', nuevo_callsign)
        cambiado = True

    if nuevo_id and nuevo_id != id_actual:
        config.set('DMR', 'Id', nuevo_id)
        cambiado = True

    if cambiado:
        # Backup
        backup_path = INI_PATH + '.bak'
        shutil.copy(INI_PATH, backup_path)
        with open(INI_PATH, 'w') as configfile:
            config.write(configfile)
        messagebox.showinfo("Guardado", "Se han aplicado los cambios.\nSe creó una copia de seguridad.")
    else:
        messagebox.showinfo("Sin cambios", "No se detectaron cambios para guardar.")

def guardar_datos():
    nuevo_callsign = entry_callsign.get().strip().upper()
    nuevo_id = entry_id.get().strip()
    
    if not nuevo_callsign and not nuevo_id:
        messagebox.showwarning("Campos vacíos", "Debes ingresar al menos un valor.")
        return

    guardar_config_si_cambia(nuevo_callsign, nuevo_id)

def cargar_datos():
    config = cargar_config()
    if config is None:
        return

    callsign = config.get('General', 'Callsign', fallback='')
    dmr_id = config.get('DMR', 'Id', fallback='')

    entry_callsign.delete(0, tk.END)
    entry_callsign.insert(0, callsign)

    entry_id.delete(0, tk.END)
    entry_id.insert(0, dmr_id)

# Interfaz
root = tk.Tk()
root.title("Editor MMDVM.ini")
root.geometry("350x200")
root.resizable(False, False)

frame = tk.Frame(root, padx=20, pady=20)
frame.pack()

tk.Label(frame, text="Callsign:").grid(row=0, column=0, sticky='e')
entry_callsign = tk.Entry(frame, width=25)
entry_callsign.grid(row=0, column=1)

tk.Label(frame, text="DMR ID:").grid(row=1, column=0, sticky='e')
entry_id = tk.Entry(frame, width=25)
entry_id.grid(row=1, column=1)

tk.Button(frame, text="Cargar valores", command=cargar_datos).grid(row=2, column=0, pady=20)
tk.Button(frame, text="Guardar cambios", command=guardar_datos).grid(row=2, column=1)

cargar_datos()
root.mainloop()
