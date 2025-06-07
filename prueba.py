import tkinter as tk
import subprocess
from PIL import Image, ImageTk
import os

image_path = "/home/pi/A108/triangulo.png"
pos_file = "/home/pi/A108/posicion.txt"

def cerrar_qt():
    try:
        subprocess.run(['killall', 'qt_menu_superior'], check=True)
        print("qt_menu_superior cerrado")
    except Exception as e:
        print(f"Error al cerrar qt_menu_superior: {e}")

def start_move_right(event):
    root.x = event.x
    root.y = event.y

def do_move_right(event):
    deltax = event.x - root.x
    deltay = event.y - root.y
    x = root.winfo_x() + deltax
    y = root.winfo_y() + deltay
    root.geometry(f"+{x}+{y}")

def guardar_posicion(event=None):
    try:
        x = root.winfo_x()
        y = root.winfo_y()
        with open(pos_file, "w") as f:
            f.write(f"{x},{y}")
        print(f"Posición guardada: {x},{y}")
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
    if root.state() == "normal":
        root.iconify()
    else:
        root.deiconify()

# Variables para detectar drag con botón izquierdo
dragging = False
drag_start_x = None
drag_start_y = None
click_threshold = 5  # píxeles para considerar drag

def on_left_button_press(event):
    global dragging, drag_start_x, drag_start_y
    dragging = False
    drag_start_x = event.x_root
    drag_start_y = event.y_root

def on_left_button_motion(event):
    global dragging
    dx = abs(event.x_root - drag_start_x)
    dy = abs(event.y_root - drag_start_y)
    if dx > click_threshold or dy > click_threshold:
        dragging = True
        # Mover ventana mientras arrastra con botón izquierdo
        x = root.winfo_x() + (event.x_root - drag_start_x)
        y = root.winfo_y() + (event.y_root - drag_start_y)
        root.geometry(f"+{x}+{y}")
        drag_start_x = event.x_root
        drag_start_y = event.y_root

def on_left_button_release(event):
    if not dragging:
        # Si no hubo drag, matar proceso
        cerrar_qt()
    else:
        # Si hubo drag, guardar posición
        guardar_posicion()

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

# Bindings para mover con botón derecho (opcional, si quieres también derecho)
label.bind("<ButtonPress-3>", lambda e: None)  # evita interferencias, no mueve con botón derecho ya que movemos con izquierdo ahora

# Bindings para mover y click kill con botón izquierdo
label.bind("<ButtonPress-1>", on_left_button_press)
label.bind("<B1-Motion>", on_left_button_motion)
label.bind("<ButtonRelease-1>", on_left_button_release)

# Doble click izquierdo para minimizar/restaurar
label.bind("<Double-Button-1>", toggle_minimize)

# Restaurar con clic derecho cuando minimizado
root.bind("<Button-3>", lambda e: toggle_minimize() if root.state() == "iconic" else None)

root.mainloop()
