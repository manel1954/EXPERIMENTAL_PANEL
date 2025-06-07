import tkinter as tk
import subprocess
from PIL import Image, ImageTk
import base64
import io

def cerrar_qt():
    try:
        subprocess.run(['killall', 'qt_menu_superior'], check=True)
    except Exception as e:
        print(f"Error al cerrar qt_menu_superior: {e}")

# Imagen PNG en base64 (triángulo rojo con fondo transparente)
triangle_png_base64 = """
iVBORw0KGgoAAAANSUhEUgAAAEAAAABACAYAAACqaXHeAAABTElEQVR4nO3ZwQmEMBAF0RYjT+9/b8t2qViN
4tg2UbkqX6gbMcm++3cgMzMzMzMzMzMzMzMzM/PnlLXySdr8ErzVZTL3tuUOsnmpQ+S/eNdQh+fMZ7owNLLv
myiueVHPjmaZ9i3cvz5UdePHW7fdyrt1uH66uYP1nyzA+sxz+lHNeSfb19ZH8YTOsbcX/PcS/b/0bZMwcQ9F
MdcjRNqz0FvS1KehQ7mpXj/FCXmX3PzMzMzMzMzMzMzMzMz8zPYBBHFU3u9Mc+kAAAAASUVORK5CYII=
"""

# Decodificar imagen
image_data = base64.b64decode(triangle_png_base64)
image = Image.open(io.BytesIO(image_data))

# Crear ventana principal
root = tk.Tk()
root.overrideredirect(True)  # Sin barra ni bordes
root.geometry("64x64+50+50")  # Tamaño y posición
root.attributes("-topmost", True)
root.attributes("-alpha", 0.8)  # Transparencia total de la ventana

# Cargar imagen
image_tk = ImageTk.PhotoImage(image)

# Crear y mostrar imagen
label = tk.Label(root, image=image_tk, bg='black')
label.pack()

# Asociar clic
label.bind("<Button-1>", lambda e: cerrar_qt())

root.mainloop()
