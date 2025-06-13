import tkinter as tk
import subprocess
import os
import signal

# -------------------------------
# Configuración: actualiza estas rutas
# -------------------------------
MMDVM_DIR = "/home/pi/MMDVMHost"
EXECUTABLE = "./MMDVMHost"
CONFIG_FILE = "MMDVM.ini"
# -------------------------------

# Variable para almacenar el proceso lanzado por este script (si lo crea)
terminal_process = None

def is_mmdvm_running():
    """
    Verifica si hay un proceso que incluya "MMDVMHost" en su línea de comando.
    """
    try:
        output = subprocess.check_output(["pgrep", "-f", "MMDVMHost"]).decode().strip()
        return bool(output)
    except subprocess.CalledProcessError:
        return False

def kill_mmdvm_processes():
    """
    Mata todos los procesos que contengan "MMDVMHost" en su línea de comando.
    """
    try:
        pids = subprocess.check_output(["pgrep", "-f", "MMDVMHost"]).decode().splitlines()
        for pid in pids:
            os.kill(int(pid), signal.SIGTERM)
    except Exception as e:
        print(f"Error al matar procesos: {e}")

def toggle_mmdvm():
    global terminal_process
    if not is_mmdvm_running():
        try:
            # Comando a ejecutar: se cambia de directorio y se lanza MMDVMHost con su .ini,
            # y al finalizar se abre bash para mantener abierta la terminal.
            cmd = f"cd {MMDVM_DIR} && {EXECUTABLE} {CONFIG_FILE}; bash"
            # Se lanza un terminal gráfico (ajusta el nombre si es necesario)
            terminal_process = subprocess.Popen([
                "x-terminal-emulator", "-e", f"bash -c '{cmd}'"
            ])
            button.config(text="Cerrar MMDVMHost", bg="red")
            status_label.config(text="Estado: EJECUTANDO", fg="green")
        except Exception as e:
            status_label.config(text=f"Error: {e}", fg="red")
    else:
        try:
            kill_mmdvm_processes()
            terminal_process = None
            button.config(text="Iniciar MMDVMHost", bg="green")
            status_label.config(text="Estado: DETENIDO", fg="black")
        except Exception as e:
            status_label.config(text=f"Error al cerrar: {e}", fg="red")

def update_status_at_startup():
    """
    Verifica al iniciar si MMDVMHost ya está en ejecución y actualiza la interfaz.
    """
    if is_mmdvm_running():
        button.config(text="Cerrar MMDVMHost", bg="red")
        status_label.config(text="Estado: EJECUTANDO", fg="green")
    else:
        button.config(text="Iniciar MMDVMHost", bg="green")
        status_label.config(text="Estado: DETENIDO", fg="black")

# -------------------------------
# Interfaz gráfica con tkinter
# -------------------------------
root = tk.Tk()
root.title("Control MMDVMHost (Terminal Visible)")

button = tk.Button(root, text="Iniciar MMDVMHost", command=toggle_mmdvm,
                   bg="green", font=("Arial", 14), width=30)
button.pack(pady=20)

status_label = tk.Label(root, text="Estado: DESCONOCIDO", font=("Arial", 12))
status_label.pack()

def on_close():
    """
    Al cerrar la ventana, se intenta detener MMDVMHost si está en ejecución.
    """
    if is_mmdvm_running():
        kill_mmdvm_processes()
    root.destroy()

root.protocol("WM_DELETE_WINDOW", on_close)

# Actualizar estado al iniciar la aplicación
update_status_at_startup()

root.mainloop()
