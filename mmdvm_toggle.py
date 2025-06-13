import tkinter as tk
import subprocess
import os
import signal
import threading
import time

# Configura tu ruta aquí
MMDVM_DIR = "/home/pi/MMDVMHost"
EXECUTABLE = "./MMDVMHost"
CONFIG_FILE = "MMDVM.ini"
LOG_FILE = "/home/pi/MMDVMHost/MMDVM.log"  # Asume que tienes activado el log en el .ini

mmdvm_process = None
stop_reading = threading.Event()

def toggle_mmdvm():
    global mmdvm_process, stop_reading
    if mmdvm_process is None:
        try:
            log_text.delete(1.0, tk.END)
            stop_reading.clear()

            mmdvm_process = subprocess.Popen(
                [EXECUTABLE, CONFIG_FILE],
                cwd=MMDVM_DIR,
                preexec_fn=os.setsid,
                stdout=subprocess.DEVNULL,
                stderr=subprocess.DEVNULL
            )

            button.config(text="Detener MMDVMHost", bg="red")
            status_label.config(text="Estado: EJECUTANDO", fg="green")

            threading.Thread(target=read_log, daemon=True).start()

        except Exception as e:
            status_label.config(text=f"Error: {e}", fg="red")
    else:
        try:
            os.killpg(os.getpgid(mmdvm_process.pid), signal.SIGTERM)
            mmdvm_process = None
            stop_reading.set()
            button.config(text="Iniciar MMDVMHost", bg="green")
            status_label.config(text="Estado: DETENIDO", fg="black")
        except Exception as e:
            status_label.config(text=f"Error al detener: {e}", fg="red")

def read_log():
    while not stop_reading.is_set():
        try:
            if os.path.exists(LOG_FILE):
                with open(LOG_FILE, "r") as f:
                    lines = f.readlines()[-20:]  # Últimas 20 líneas
                    log_text.delete(1.0, tk.END)
                    log_text.insert(tk.END, "".join(lines))
            time.sleep(1)
        except Exception as e:
            log_text.insert(tk.END, f"\nError leyendo log: {e}")
            break

# Ventana principal
root = tk.Tk()
root.title("Control MMDVMHost con Log")

button = tk.Button(root, text="Iniciar MMDVMHost", command=toggle_mmdvm, bg="green", font=("Arial", 14), width=25)
button.pack(pady=10)

status_label = tk.Label(root, text="Estado: DETENIDO", font=("Arial", 12))
status_label.pack()

log_text = tk.Text(root, height=20, width=80, font=("Courier", 10))
log_text.pack(pady=10)

# Salida limpia
def on_closing():
    if mmdvm_process:
        os.killpg(os.getpgid(mmdvm_process.pid), signal.SIGTERM)
    root.destroy()

root.protocol("WM_DELETE_WINDOW", on_closing)
root.mainloop()
