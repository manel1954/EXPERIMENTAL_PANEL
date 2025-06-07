import tkinter as tk
import subprocess
from PIL import Image, ImageTk
import os

image_path = "/home/pi/A108/triangulo.png"
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
    return 50, 50

def toggle_minimize(event=None):
    # Si está visible, minimizar (iconificar)
    if root.state() == "normal":
        root.iconify()
    else:
        root.deiconify()

# Cargar posición guardada
x_pos, y_pos = cargar_posicion()

root = tk.Tk()
root.overrideredirect(True)
root.geometry(f"64x64+{x_pos}+{y_pos}")
root.attributes("-topmost", True)
root.attributes("-alpha", 0.8)

image = Image.open(image_path).convert("RGBA")
image_tk = ImageTk.PhotoImage(image)
label = tk.Label(root, image=image_tk, bg='black')
label.pack()

label.bind("<Button-1>", lambda e: cerrar_qt())           # click izquierdo = cerrar qt_menu_superior
label.bind("<Double-Button-1>", toggle_minimize)           # doble click izquierdo = minimizar/mostrar
label.bind("<ButtonPress-3>", start_move)                  # click derecho presionar = iniciar mover
label.bind("<B3-Motion>", do_move)                          # mover con botón derecho arrastrando
label.bind("<ButtonRelease-3>", guardar_posicion)          # guardar posición al soltar botón derecho

# También permito restaurar con click derecho simple cuando está minimizado
root.bind("<Button-3>", toggle_minimize)

root.mainloop()
