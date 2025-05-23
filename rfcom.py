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
            lineas = f.readlines()[1:]  # Saltar línea #!/bin/bash
            for linea in lineas:
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

def agregar_nuevo(mac):
    dispositivos = leer_dispositivos_guardados()
    ocupados = set(num for num, _ in dispositivos)
    for i in range(100):
        if i not in ocupados:
            dispositivos.append((i, mac))
            break
    guardar_dispositivos(dispositivos)
    actualizar_lista_guardados()

def escanear_bluetooth():
    resultado_text.set("Escaneando dispositivos Bluetooth...")
    try:
        resultado = subprocess.check_output(['hcitool', 'scan'], text=True)
        dispositivos_encontrados = re.findall(r'((?:[0-9A-F]{2}:){5}[0-9A-F]{2})\s+(.+)', resultado, re.IGNORECASE)

        for widget in frame_resultados.winfo_children():
            widget.destroy()

        dispositivos_guardados = leer_dispositivos_guardados()
        mac_guardadas = [m for _, m in dispositivos_guardados]
        activos = dispositivos_activos()

        # Sección Dispositivos vinculados
        label_vinculados = tk.Label(frame_resultados, text="Dispositivos Vinculados:",
                                    bg="#19181C", fg="white", font=("Arial", 10, "bold"))
        label_vinculados.pack(anchor="w", padx=5, pady=(0, 5))

        if dispositivos_guardados:
            for num, mac in dispositivos_guardados:
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
        else:
            label_no_vinculados = tk.Label(frame_resultados, text="No hay dispositivos vinculados.",
                                          bg="#19181C", fg="white")
            label_no_vinculados.pack(anchor="w", padx=5, pady=5)

        # Separador visual
        separator = tk.Frame(frame_resultados, height=2, bd=1, relief="sunken", bg="#888")
        separator.pack(fill="x", padx=5, pady=10)

        # Sección Dispositivos escaneados no vinculados
        label_encontrados = tk.Label(frame_resultados, text="Dispositivos Escaneados (no vinculados):",
                                    bg="#19181C", fg="white", font=("Arial", 10, "bold"))
        label_encontrados.pack(anchor="w", padx=5, pady=(0, 5))

        dispositivos_no_vinculados = [(mac, nombre) for mac, nombre in dispositivos_encontrados if mac not in mac_guardadas]
        if dispositivos_no_vinculados:
            for mac, nombre in dispositivos_no_vinculados:
                frame = tk.Frame(frame_resultados, bg="#444")
                frame.pack(fill="x", pady=2, padx=5)
                label = tk.Label(frame, text=f"{nombre} ({mac})", bg="#444", fg="white", width=30, anchor="w")
                label.pack(side="left", padx=(5, 0))

                btn_add = tk.Button(frame, text="Añadir", bg="#28a745", fg="white",
                                    command=lambda m=mac: agregar_nuevo(m))
                btn_add.pack(side="right", padx=5)
        else:
            label_no_nuevos = tk.Label(frame_resultados, text="No se encontraron dispositivos nuevos.",
                                      bg="#19181C", fg="white")
            label_no_nuevos.pack(anchor="w", padx=5, pady=5)

        resultado_text.set(f"{len(dispositivos_encontrados)} dispositivo(s) encontrado(s).")

    except subprocess.CalledProcessError as e:
        resultado_text.set("Error al escanear Bluetooth.")
        messagebox.showerror("Error", f"No se pudo escanear: {e}")
    except Exception as ex:
        resultado_text.set("Error inesperado.")
        messagebox.showerror("Error", str(ex))

def actualizar_lista_guardados():
    escanear_bluetooth()

root = tk.Tk()
root.title("Gestor Bluetooth")
root.geometry("420x480+1287+479")
root.configure(bg="#19181C")

btn_escanear = tk.Button(root, text="Escanear Bluetooth", command=escanear_bluetooth,
                         bg="#007bff", fg="white", activebackground="#0056b3", activeforeground="white",
                         font=("Arial", 10, "bold"))
btn_escanear.pack(pady=10)

resultado_text = tk.StringVar()
label_resultado = tk.Label(root, textvariable=resultado_text,
                          bg="#19181C", fg="white", font=("Arial", 10))
label_resultado.pack()

frame_resultados = tk.Frame(root, bg="#333")
frame_resultados.pack(fill="both", expand=True, padx=10, pady=10)

btn_ejecutar = tk.Button(root, text="Ejecutar Script", command=ejecutar_script,
                         bg="#28a745", fg="white", font=("Arial", 10, "bold"))
btn_ejecutar.pack(pady=10)

actualizar_lista_guardados()
root.mainloop()
