import tkinter as tk
from tkinter import filedialog, messagebox
import subprocess
import os
import shutil

pos_file = "/home/pi/A108/posicion.txt"

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

def guardar_posicion(event=None):
    try:
        x = root.winfo_x()
        y = root.winfo_y()
        with open(pos_file, "w") as f:
            f.write(f"{x},{y}")
    except Exception as e:
        print(f"Error al guardar posición: {e}")

def cerrar_qt():
    try:
        subprocess.run(['killall', 'qt_menu_superior'], check=True)
    except Exception as e:
        print(f"Error al cerrar qt_menu_superior: {e}")

def iniciar_qt():
    try:
        subprocess.Popen(['/home/pi/A108/qt/./qt_menu_superior'])
    except Exception as e:
        print(f"Error al iniciar qt_menu_superior: {e}")

def elegir_foto_y_mostrar():
    ruta_imagen = filedialog.askopenfilename(
        title="Elige una foto",
        filetypes=[("Archivos de imagen", "*.png;*.jpg;*.jpeg;*.gif;*.bmp")]
    )
    if ruta_imagen:
        try:
            destino = "/home/pi/foto_guardada" + os.path.splitext(ruta_imagen)[1]
            shutil.copy2(ruta_imagen, destino)
            print(f"Foto guardada en {destino}")

            try:
                from PIL import Image, ImageTk
                img = Image.open(destino)
                img = img.resize((btn.winfo_width(), btn.winfo_height()), Image.ANTIALIAS)
                foto = ImageTk.PhotoImage(img)
            except ImportError:
                foto = tk.PhotoImage(file=destino)

            btn.config(image=foto, text="")
            btn.image = foto

        except Exception as e:
            messagebox.showerror("Error", f"No se pudo guardar la foto: {e}")

dragging = False
click_threshold = 5
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
    global dragging
    if not dragging:
        current_text = btn['text']
        if current_text == '<':
            cerrar_qt()
            btn.config(text='>')
            elegir_foto_y_mostrar()
        else:
            iniciar_qt()
            btn.config(text='<')
    else:
        guardar_posicion()

def toggle_minimize(event=None):
    if root.state() == "normal":
        root.iconify()
    else:
        root.deiconify()

def get_tooltip_text():
    return "CERRAR PANELES" if btn['text'] == '<' else "ABRIR PANELES"

x_pos, y_pos = cargar_posicion()

root = tk.Tk()
root.overrideredirect(True)
root.geometry(f"20x20+{x_pos}+{y_pos}")
root.attributes("-topmost", True)
root.attributes("-alpha", 0.8)
root.configure(bg='black')

btn = tk.Label(root, text="<", font=("Arial", 12), fg="black", bg="white", width=2, height=1, cursor="hand2")
btn.pack(expand=True, fill="both")

btn.bind("<ButtonPress-1>", on_left_button_press)
btn.bind("<B1-Motion>", on_left_button_motion)
btn.bind("<ButtonRelease-1>", on_left_button_release)
btn.bind("<Double-Button-1>", toggle_minimize)

# Tu clase ToolTip aquí o importada, si quieres
# Por simplicidad la omito en este ejemplo, añádela si la necesitas.

root.mainloop()
