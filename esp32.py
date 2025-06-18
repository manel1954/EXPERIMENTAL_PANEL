# Programador esp32 by REM-ESP 2025 - Linux - MAC - Windows #
# Autor EA4AOJ @
import tkinter as tk
from tkinter import filedialog, messagebox, ttk
from PIL import Image, ImageTk
import subprocess
import sys
import os
import platform
import glob
import threading
import re

SCRIPT_DIR = os.path.abspath(os.path.dirname(__file__))
VENV_DIR = os.path.join(SCRIPT_DIR, "esp32_env")
VENV_PYTHON = os.path.join(VENV_DIR, "Scripts" if platform.system() == "Windows" else "bin", "python.exe" if platform.system() == "Windows" else "python3")

BG_COLOR = "#2b2b2b"
FG_COLOR = "#f0f0f0"
ENTRY_BG = "#3c3f41"
FONT = ("Segoe UI", 10)
BUTTON_FONT = ("Segoe UI", 10, "bold")

root = tk.Tk()
root.title("Programador ESP32 by REM-ESP")
root.geometry("600x650")
root.configure(bg=BG_COLOR)
root.resizable(False, False)

frame = tk.Frame(root, bg=BG_COLOR)
frame.pack(padx=20, pady=20, fill="both", expand=False)

# --- ESTILO MODERNO PARA BOTONES ---
style = ttk.Style()
style.theme_use('clam')

style.configure(
    "Rounded.TButton",
    font=BUTTON_FONT,
    padding=6,
    borderwidth=0,
    relief="flat",
    cursor="hand2"
)

def create_button_style(name, color):
    style.configure(f"{name}.TButton", background=color, foreground="white")
    style.map(
        f"{name}.TButton",
        background=[("active", darken_color(color))],
    )

def darken_color(hex_color):
    hex_color = hex_color.lstrip('#')
    r, g, b = tuple(int(hex_color[i:i+2], 16) for i in (0, 2, 4))
    r = max(r - 30, 0)
    g = max(g - 30, 0)
    b = max(b - 30, 0)
    return f"#{r:02x}{g:02x}{b:02x}"

create_button_style("borrar", "#d9534f")     # Rojo
create_button_style("programar", "#f0ad4e")  # Naranja
create_button_style("salir", "#5cb85c")      # Verde
create_button_style("seleccionar", "#4caf50")  # Verde oscuro para ...
create_button_style("ayuda", "#007acc")      # Azul ayuda

# --- FUNCIONES PRINCIPALES ---

def crear_entorno_virtual():
    label_estado.config(text="Creando entorno virtual...", fg="yellow")
    root.update_idletasks()
    if not os.path.exists(VENV_DIR):
        subprocess.check_call([sys.executable, "-m", "venv", VENV_DIR])
    label_estado.config(text="Entorno virtual listo", fg="lightgreen")
    root.update_idletasks()

def verificar_instalar_esptool():
    import importlib
    import sys
    label_estado.config(text="Verificando e instalando dependencias...", fg="yellow")
    root.update_idletasks()
    try:
        subprocess.check_output([VENV_PYTHON, "-m", "esptool"], stderr=subprocess.STDOUT)
    except subprocess.CalledProcessError as e:
        salida_error = e.output.decode('utf-8') if isinstance(e.output, bytes) else e.output
        if "No module named esptool" in salida_error or "usage:" in salida_error:
            subprocess.check_call([VENV_PYTHON, "-m", "pip", "install", "--upgrade", "pip"])
            subprocess.check_call([VENV_PYTHON, "-m", "pip", "install", "esptool", "pillow"])
        else:
            raise
    else:
        try:
            importlib.import_module("PIL")
        except ImportError:
            subprocess.check_call([VENV_PYTHON, "-m", "pip", "install", "pillow"])
    label_estado.config(text="Todo listo !", fg="lightgreen")
    root.update_idletasks()

def listar_puertos():
    sistema = platform.system()
    if sistema == "Windows":
        return [f"COM{i}" for i in range(1, 21)]
    elif sistema == "Darwin":
        return glob.glob("/dev/cu.*") + glob.glob("/dev/tty.*")
    else:
        return glob.glob("/dev/ttyUSB*") + glob.glob("/dev/ttyACM*")

def seleccionar_archivo(entry_destino):
    archivo = filedialog.askopenfilename(filetypes=[("Archivos binarios", "*.bin")])
    if archivo:
        entry_destino.delete(0, tk.END)
        entry_destino.insert(0, archivo)

def ejecutar_comando_esptool(args, actualizar_barra, callback_fin):
    try:
        proceso = subprocess.Popen(args, stdout=subprocess.PIPE, stderr=subprocess.STDOUT, text=True, bufsize=1)
        for linea in proceso.stdout:
            match = re.search(r"(\d{1,3})\s?%", linea)
            if match:
                porcentaje = int(match.group(1))
                porcentaje = min(max(porcentaje, 0), 100)
                actualizar_barra(porcentaje)
            consola.insert(tk.END, linea)
            consola.see(tk.END)
        proceso.wait()
        exito = proceso.returncode == 0
    except Exception as e:
        exito = False
        messagebox.showerror("Error", f"Error al ejecutar esptool:\n{e}")
    finally:
        callback_fin(exito)

def programar_todo_en_thread():
    puerto = entry_puerto.get()
    velocidad = entry_velocidad.get()
    firmware = entry_firmware.get()
    direccion_firmware = entry_direccion_firmware.get()
    bootloader = entry_bootloader.get()
    direccion_bootloader = entry_direccion_bootloader.get()
    particiones = entry_particiones.get()
    direccion_particiones = entry_direccion_particiones.get()
    if not all([puerto, velocidad, firmware, direccion_firmware]):
        messagebox.showerror("Error", "Faltan datos mínimos para programar el firmware.")
        return
    btn_salir.config(state="disabled")
    btn_programar.config(state="disabled")
    btn_borrar.config(state="disabled")
    label_estado.config(text="Programando...", fg="yellow")
    barra_progreso.grid()
    barra_progreso['value'] = 0
    root.update_idletasks()
    args = [
        VENV_PYTHON, "-m", "esptool",
        "--chip", "esp32",
        "--port", puerto,
        "--baud", velocidad,
        "write_flash",
        direccion_firmware, firmware
    ]
    if bootloader and direccion_bootloader:
        args += [direccion_bootloader, bootloader]
    if particiones and direccion_particiones:
        args += [direccion_particiones, particiones]
    def fin_programacion(exito):
        if exito:
            label_estado.config(text="✅ Programación completada", fg="lightgreen")
            messagebox.showinfo("Éxito", "ESP32 programado correctamente.")
        else:
            label_estado.config(text="❌ Error durante programación", fg="red")
        btn_salir.config(state="normal")
        btn_programar.config(state="normal")
        btn_borrar.config(state="normal")
        root.after(4000, lambda: barra_progreso.grid_remove())
        root.after(4000, lambda: label_estado.config(text=""))
    threading.Thread(
        target=ejecutar_comando_esptool,
        args=(args, lambda p: barra_progreso.config(value=p), fin_programacion),
        daemon=True
    ).start()

def borrar_esp32_en_thread():
    btn_salir.config(state="disabled")
    btn_programar.config(state="disabled")
    btn_borrar.config(state="disabled")
    label_estado.config(text="Borrando flash...", fg="yellow")
    root.update_idletasks()
    puerto = entry_puerto.get()
    velocidad = entry_velocidad.get()
    if not puerto or not velocidad:
        messagebox.showerror("Error", "Debe seleccionar puerto y velocidad para borrar.")
        btn_programar.config(state="normal")
        btn_borrar.config(state="normal")
        return
    args = [
        VENV_PYTHON, "-m", "esptool",
        "--chip", "esp32",
        "--port", puerto,
        "--baud", velocidad,
        "erase_flash"
    ]
    def fin_borrado(exito):
        if exito:
            label_estado.config(text="✅ Flash borrado", fg="lightgreen")
            messagebox.showinfo("Éxito", "Flash del ESP32 borrado correctamente.")
        else:
            label_estado.config(text="❌ Error al borrar flash", fg="red")
        btn_programar.config(state="normal")
        btn_borrar.config(state="normal")
        btn_salir.config(state="normal")
        root.after(4000, lambda: label_estado.config(text=""))
    threading.Thread(target=ejecutar_comando_esptool, args=(args, lambda p: barra_progreso.config(value=p), fin_borrado), daemon=True).start()

def confirmar_borrado():
    respuesta = messagebox.askyesno("Confirmar", "¿Estás seguro que deseas borrar el ESP32?")
    if respuesta:
        borrar_esp32_en_thread()

def mostrar_ayuda():
    btn_ayuda.config(state="disabled")
    ventana_ayuda = tk.Toplevel(root)
    ventana_ayuda.title("Ayuda - Instrucciones de uso")
    ventana_ayuda.geometry("500x500")
    ventana_ayuda.configure(bg=BG_COLOR)
    ventana_ayuda.resizable(False, False)
    ventana_ayuda.protocol("WM_DELETE_WINDOW", lambda: (btn_ayuda.config(state="normal"), ventana_ayuda.destroy()))
    texto = """\
INSTRUCCIONES DE USO:
1. Selecciona el archivo del firmware (.bin) y su dirección.
2. Si es la primera vez que programas el dispositivo selecciona el firmware, bootloader y particiones, con sus respectivas direcciones.
3. Escoge el puerto serie al que está conectado tu ESP32.
4. Selecciona la velocidad de comunicación (por defecto 921600).
5. Pulsa 'Programar' para cargar el firmware al ESP32.
6. Si deseas borrar la memoria flash antes de programar, pulsa 'Borrar'.
7. Salir para finalizar el programa.
Programador ESP32 by REM-ESP © 2025"""
    tk.Label(
        ventana_ayuda,
        text=texto,
        justify="left",
        bg=BG_COLOR,
        fg=FG_COLOR,
        font=FONT,
        wraplength=460
    ).pack(padx=20, pady=(70, 5), fill="both", expand=True)

# --- INTERFAZ GRÁFICA ---

entry_vars = {}

def agregar_entrada(label_texto, fila, var_key, archivo=False, valor_defecto=None):
    tk.Label(frame, text=label_texto, bg=BG_COLOR, fg=FG_COLOR, font=FONT).grid(row=fila, column=0, sticky="e", padx=5, pady=5)
    var = tk.StringVar()
    entry = tk.Entry(frame, textvariable=var, bg=ENTRY_BG, fg=FG_COLOR, insertbackground=FG_COLOR, font=FONT)
    entry.grid(row=fila, column=1, sticky="we", padx=5, pady=5)
    if valor_defecto:
        var.set(valor_defecto)
    if archivo:
        ttk.Button(frame, text=". . .", style="seleccionar.TButton", width=4, command=lambda: seleccionar_archivo(entry)).grid(row=fila, column=2, padx=5, pady=5)
    entry_vars[var_key] = var
    return entry

frame.columnconfigure(1, weight=1)

entry_firmware = agregar_entrada("Firmware .bin:", 0, "firmware", archivo=True)
entry_direccion_firmware = agregar_entrada("Dirección Firmware:", 1, "direccion_firmware", valor_defecto="0x10000")
entry_bootloader = agregar_entrada("Bootloader .bin:", 2, "bootloader", archivo=True)
entry_direccion_bootloader = agregar_entrada("Dirección Bootloader:", 3, "direccion_bootloader", valor_defecto="0x1000")
entry_particiones = agregar_entrada("Particiones .bin:", 4, "particiones", archivo=True)
entry_direccion_particiones = agregar_entrada("Dirección Particiones:", 5, "direccion_particiones", valor_defecto="0x8000")

# Puerto y velocidad
puertos_disponibles = listar_puertos()
entry_puerto = ttk.Combobox(frame, values=puertos_disponibles, font=FONT, width=15)
entry_puerto.grid(row=6, column=1, sticky="w", padx=5, pady=5)
if puertos_disponibles:
    entry_puerto.set(puertos_disponibles[0])

tk.Label(frame, text="Puerto serie:", bg=BG_COLOR, fg=FG_COLOR, font=FONT).grid(row=6, column=0, sticky="e", padx=5, pady=5)

entry_velocidad = ttk.Combobox(frame, values=["115200", "256000", "460800", "921600"], font=FONT, width=15)
entry_velocidad.grid(row=7, column=1, sticky="w", padx=5, pady=5)
entry_velocidad.set("921600")
tk.Label(frame, text="Velocidad (baudios):", bg=BG_COLOR, fg=FG_COLOR, font=FONT).grid(row=7, column=0, sticky="e", padx=5, pady=5)

# Botones
btn_borrar = ttk.Button(frame, text="Borrar", style="borrar.TButton", command=confirmar_borrado)
btn_borrar.grid(row=8, column=1, sticky="w", padx=5, pady=15)

btn_programar = ttk.Button(frame, text="Programar", style="programar.TButton", command=programar_todo_en_thread)
btn_programar.grid(row=8, column=1, padx=5, pady=15)

btn_salir = ttk.Button(frame, text="Salir", style="salir.TButton", command=root.destroy)
btn_salir.grid(row=8, column=1, sticky="e", padx=5, pady=15)

btn_ayuda = ttk.Button(root, text="AYUDA", style="ayuda.TButton", command=mostrar_ayuda)
btn_ayuda.pack(pady=(0, 10))

# Progreso y estado
barra_progreso = ttk.Progressbar(frame, orient="horizontal", length=600, mode="determinate")
barra_progreso.grid(row=9, column=0, columnspan=3, sticky="we", padx=5)
barra_progreso.grid_remove()

label_estado = tk.Label(root, text="", bg=BG_COLOR, fg=FG_COLOR, font=FONT)
label_estado.pack(pady=(0, 10))

# Consola salida
consola = tk.Text(root, height=15, bg="#222", fg="lightgreen", insertbackground="#eee", font=("Consolas", 8))
consola.pack(padx=20, pady=10, fill="both", expand=True)

# Iniciar aplicación
crear_entorno_virtual()
verificar_instalar_esptool()

root.mainloop()