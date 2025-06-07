import tkinter as tk
from tkinter import filedialog, messagebox
import subprocess
import os
import shutil

pos_file = "/home/pi/A108/posicion.txt"

# ... (tu clase ToolTip y otras funciones siguen igual) ...

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

# --- Nueva función para elegir foto y mostrarla ---
def elegir_foto_y_mostrar():
    # Abrimos diálogo para elegir imagen
    ruta_imagen = filedialog.askopenfilename(
        title="Elige una foto",
        filetypes=[("Archivos de imagen", "*.png;*.jpg;*.jpeg;*.gif;*.bmp")]
    )
    if ruta_imagen:
        try:
            destino = "/home/pi/foto_guardada" + os.path.splitext(ruta_imagen)[1]  # mantener extensión
            shutil.copy2(ruta_imagen, destino)
            print(f"Foto guardada en {destino}")

            # Cargar y mostrar la imagen en el botón
            # Para jpg/jpeg o bmp necesitamos PIL (Pillow), para png/gif funciona PhotoImage de Tkinter.
            try:
                from PIL import Image, ImageTk
                img = Image.open(destino)
                img = img.resize((btn.winfo_width(), btn.winfo_height()), Image.ANTIALIAS)
                foto = ImageTk.PhotoImage(img)
            except ImportError:
                # Solo PNG/GIF nativos con PhotoImage
                foto = tk.PhotoImage(file=destino)

            btn.config(image=foto, text="")
            btn.image = foto  # Referencia para evitar que se recoja el GC

            # Cerrar ventana emergente de selección automáticamente (ya cerró al seleccionar archivo)
            # No hay ventana extra abierta aparte de filedialog, así que no hay que destruir nada.

        except Exception as e:
            messagebox.showerror("Error", f"No se pudo guardar la foto: {e}")

def on_left_button_release(event):
    global dragging
    if not dragging:
        current_text = btn['text']
        if current_text == '<':
            cerrar_qt()
            btn.config(text='>')

            # Abrir ventana para elegir foto y mostrarla
            elegir_foto_y_mostrar()

        else:
            iniciar_qt()
            btn.config(text='<')
    else:
        guardar_posicion()

# ... resto de código igual ...

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

ToolTip(btn, get_tooltip_text)

root.mainloop()
