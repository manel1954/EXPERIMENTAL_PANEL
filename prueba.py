import tkinter as tk
import subprocess
from PIL import Image, ImageTk

def cerrar_qt():
    try:
        subprocess.run(['killall', 'qt_menu_superior'], check=True)
    except Exception as e:
        print(f"Error al cerrar qt_menu_superior: {e}")

# Cargar imagen desde archivo
image_path = "/home/pi/A108/triangulo.png"
image = Image.open(image_path).convert("RGBA")

# Crear ventana
root = tk.Tk()
root.overrideredirect(True)
root.geometry("64x64+50+50")
root.attributes("-topmost", True)
root.attributes("-alpha", 0.8)

# Mostrar imagen
image_tk = ImageTk.PhotoImage(image)
label = tk.Label(root, image=image_tk, bg='black')
label.pack()

# Click cierra QT
label.bind("<Button-1>", lambda e: cerrar_qt())

root.mainloop()
