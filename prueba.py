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

def start_move(event):
    root.x = event.x
    root.y = event.y

def do_move(event):
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

def on_single_click(event):
    # Esperar un poco para detectar si es doble clic
    def callback():
        if not single_click_cancelled[0]:
            cerrar_qt()
    single_click_cancelled[0] = False
    root.after(250, callback)

def on_double_click(event):
    single_click_cancelled[0] = True
    toggle_minimize()

# Flag para controlar la ejecución del click simple
single_click_cancelled = [False]

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

# Bindings
label.bind("<Button-1>", on_single_click)          # clic izquierdo simple (con delay)
label.bind("<Double-Button-1>", on_double_click)   # doble clic izquierdo
label.bind("<ButtonPress-3>", start_move)          # iniciar mover con botón derecho
label.bind("<B3-Motion>", do_move)                  # mover ventana con botón derecho arrastrando
label.bind("<ButtonRelease-3>", guardar_posicion)  # guardar posición al soltar botón derecho

# También restaurar ventana con clic derecho simple cuando está minimizada
root.bind("<Button-3>", lambda e: toggle_minimize() if root.state() == "iconic" else None)

root.mainloop()
