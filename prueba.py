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
click_threshold = 5  # pixeles para considerar drag
start_mouse_x = 0
start_mouse_y = 0
start_win_x = 0
start_win_y = 0

def on_left_button_press(event):
    global dragging, start_mouse_x, start_mouse_y, start_win_x, start_win_y
    dragging = False
    start_mouse_x = event.x_root
    start_mouse_y = event.y_root
    start_win_x = root.winfo_x()
    start_win_y = root.winfo_y()

def on_left_button_motion(event):
    global dragging
    dx = event.x_root - start_mouse_x
    dy = event.y_root - start_mouse_y
    if abs(dx) > click_threshold or abs(dy) > click_threshold:
        dragging = True
        new_x = start_win_x + dx
        new_y = start_win_y + dy
        root.geometry(f"+{new_x}+{new_y}")

def on_left_button_release(event):
    if not dragging:
        cerrar_qt()
    else:
        guardar_posicion()

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

label.bind("<ButtonPress-1>", on_left_button_press)
label.bind("<B1-Motion>", on_left_button_motion)
label.bind("<ButtonRelease-1>", on_left_button_release)
label.bind("<Double-Button-1>", toggle_minimize)

root.bind("<Button-3>", lambda e: toggle_minimize() if root.state() == "iconic" else None)

root.mainloop()
