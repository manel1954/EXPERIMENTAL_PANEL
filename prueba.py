import tkinter as tk
import subprocess
from PIL import Image, ImageTk
import os

# Ruta del archivo PNG
image_path = "/home/pi/A108/triangulo.png"

# Ruta para guardar posición
pos_file = "/home/pi/A108/posicion.txt"

def cerrar_qt():
    try:
        subprocess.run(['killall', 'qt_menu_superior'], check=True)
    except Exception as e:
        print(f"Error al cerrar qt_menu_superior: {e}")

def start_move(event):
    root.x = event.x
    root.y = event.y

def do_move(event):
    deltax = event.x - root.x
    deltay = event.y - root.y
    x = root.winfo_x() + deltax
    y = root.winfo_y() + deltay
    root.geometry(f"+{x}+{y}")
    guardar_posicion(x, y)

def guardar_posicion(x, y):
    try:
        with open(pos_file, "w") as f:
            f.write(f"{x},{y}")
    except Exception as e:
        print(f"Error al guardar posición: {e}")

def cargar_posicion():
    if os.path.exists(pos_file):
        try:
            with open(pos_file, "r") as f:
                contenido = f.read()
                x, y = map(int, contenido.strip().split(","))
                return x, y
        except:
            pass
    return 50, 50  # posición por defecto

# Cargar posición guardada
x_pos, y_pos = cargar_posicion()

# Crear ventana
root = tk.Tk()
root.overrideredirect(True)
root.geometry(f"64x64+{x_pos}+{y_pos}")
root.attributes("-topmost", True)
root.attributes("-alpha", 0.8)

# Cargar imagen
image = Image.open(image_path).convert("RGBA")
image_tk = ImageTk.PhotoImage(image)

# Mostrar en label
label = tk.Label(root, image=image_tk, bg='black')
label.pack()

# Asignar acciones
label.bind("<Button-1>", lambda e: cerrar_qt())      # botón izquierdo: matar qt
label.bind("<ButtonPress-3>", start_move)            # botón derecho: iniciar movimiento
label.bind("<B3-Motion>", do_move)                   # mientras arrastra: mover y guardar

root.mainloop()
