import tkinter as tk
from tkinter import messagebox
import subprocess
import re
import os

RUTA_FICHERO = "/home/pi/.local/bluetooth.sh"
HEADER = "#!/bin/bash\n"

def leer_dispositivos_guardados():
    dispositivos = []
    if os.path.exists(RUTA_FICHERO):
        with open(RUTA_FICHERO, "r") as f:
            lineas = f.readlines()[1:]  # Saltar línea del #!/bin/bash
            for i, linea in enumerate(lineas):
                match = re.match(r"sudo rfcomm bind /dev/rfcomm(\d+) ([0-9A-F:]{17})", linea.strip())
                if match:
                    num, mac = match.groups()
                    dispositivos.append((int(num), mac))
    return sorted(dispositivos)

def guardar_dispositivos(dispositivos):
    with open(RUTA_FICHERO, "w") as f:
        f.write(HEADER)
        for num, mac in sorted(dispositivos):
            f.write(f"sudo rfcomm bind /dev/rfcomm{num} {mac}\n")

def ejecutar_script():
    try:
        subprocess.run(["sudo", "sh", RUTA_FICHERO], check=True)
        messagebox.showinfo("Éxito", "Script ejecutado correctamente.")
        actualizar_lista_guardados()
    except subprocess.CalledProcessError as e:
        messagebox.showerror("Error", f"No se pudo ejecutar el script:\n{e}")

def dispositivos_activos():
    try:
        resultado = subprocess.check_output(["rfcomm"], text=True)
        activos = re.findall(r"rfcomm(\d+):", resultado)
        return set(map(int, activos))
    except subprocess.CalledProcessError:
        return set()

def bind_rfcomm(num, mac):
    try:
        subprocess.run(["sudo", "rfcomm", "bind", f"/dev/rfcomm{num}", mac], check=True)
    except subprocess.CalledProcessError as e:
        messagebox.showerror("Error", f"No se pudo bind rfcomm{num}: {e}")
    actualizar_lista_guardados()

def unbind_rfcomm(num):
    try:
        subprocess.run(["sudo", "rfcomm", "unbind", f"/dev/rfcomm{num}"], check=True)
    except subprocess.CalledProcessError as e:
        messagebox.showerror("Error", f"No se pudo unbind rfcomm{num}: {e}")
    actualizar_lista_guardados()

def eliminar_dispositivo(num):
    dispositivos = leer_dispositivos_guardados()
    dispositivos = [d for d in dispositivos if d[0] != num]
    guardar_dispositivos(dispositivos)
    actualizar_lista_guardados()

def escanear_bluetooth():
    resultado_text.set("Escaneando dispositivos Bluetooth...")
    try:
        resultado = subprocess.check_output(['hcitool', 'scan'], text=True)
        dispositivos = re.findall(r'((?:[0-9A-F]{2}:){5}[0-9A-F]{2})\s+(.+)', resultado, re.IGNORECASE)
        
        if not dispositivos:
            resultado_text.set("No se encontraron dispositivos.")
        else:
            resultado_text.set(f"{len(dispositivos)} dispositivo(s) encontrado(s):")
            for mac, nombre in dispositivos:
                if any(m == mac for _, m in leer_dispositivos_guardados()):
                    continue  # Saltar ya guardados
                frame = tk.Frame(frame_resultados, bg="#444")
                frame.pack(fill="x", pady=2, padx=5)
                label = tk.Label(frame, text=f"{nombre} ({mac})", bg="#444", fg="white", width=30, anchor="w")
                label.pack(side="left", padx=(5, 0))

                btn_add = tk.Button(frame, text="Añadir", bg="#28a745", fg="white",
                                    command=lambda m=mac: agregar_nuevo(m))
                btn_add.pack(side="right", padx=5)
    except subprocess.CalledProcessError as e:
        resultado_text.set("Error al escanear Bluetooth.")
        messagebox.showerror("Error", f"No se pudo escanear: {e}")
    except Exception as ex:
        resultado_text.set("Error inesperado.")
        messagebox.showerror("Error", str(ex))

def agregar_nuevo(mac):
    dispositivos = leer_dispositivos_guardados()
    ocupados = set(num for num, _ in dispositivos)
    for i in range(100):
        if i not in ocupados:
            dispositivos.append((i, mac))
            break
    guardar_dispositivos(dispositivos)
    actualizar_lista_guardados()

def actualizar_lista_guardados():
    for widget in frame_resultados.winfo_children():
        widget.destroy()

    dispositivos = leer_dispositivos_guardados()
    activos = dispositivos_activos()

    if not dispositivos:
        resultado_text.set("No hay dispositivos vinculados.")
    else:
        resultado_text.set("Dispositivos vinculados:")
        for num, mac in dispositivos:
            estado = "Activo" if num in activos else "Inactivo"
            frame = tk.Frame(frame_resultados, bg="#555")
            frame.pack(fill="x", pady=2, padx=5)

            label = tk.Label(frame, text=f"rfcomm{num} - {mac}", bg="#555", fg="white", width=30, anchor="w")
            label.pack(side="left", padx=(5, 0))

            label_estado = tk.Label(frame, text=estado, fg="lime" if estado == "Activo" else "red", bg="#555")
            label_estado.pack(side="left", padx=5)

            btn_bind = tk.Button(frame, text="Bind", bg="#007bff", fg="white",
                                 command=lambda n=num, m=mac: bind_rfcomm(n, m))
            btn_bind.pack(side="left", padx=5)

            btn_unbind = tk.Button(frame, text="Unbind", bg="#6c757d", fg="white",
                                   command=lambda n=num: unbind_rfcomm(n))
            btn_unbind.pack(side="left", padx=5)

            btn_del = tk.Button(frame, text="Borrar", bg="red", fg="white",
                                command=lambda n=num: eliminar_dispositivo(n))
            btn_del.pack(side="right", padx=5)

# Interfaz gráfica
root = tk.Tk()
root.title("Gestor Bluetooth")
root.geometry("420x480+1287+479")
root.configure(bg="#19181C")

tk.Button(
    root, text="Escanear Bluetooth", command=escanear_bluetooth,
    bg="#007bff", fg="white", activebackground="#0056b3", activeforeground="white",
    font=("Arial", 10, "bold")
).pack(pady=10)

resultado_text = tk.StringVar()
tk.Label(
    root, textvariable=resultado_text,
    bg="#19181C", fg="white", font=("Arial", 10)
).pack()

frame_resultados = tk.Frame(root, bg="#333")
frame_resultados.pack(fill="both", expand=True, padx=10, pady=10)

tk.Button(
    root, text="Ejecutar Script", command=ejecutar_script,
    bg="#28a745", fg="white", font=("Arial", 10, "bold")
).pack(pady=10)

actualizar_lista_guardados()
root.mainloop()
