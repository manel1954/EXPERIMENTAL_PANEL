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

# Imagen PNG en base64 (triángulo rojo apuntando a la izquierda, fondo transparente)
triangle_png_base64 = """
iVBORw0KGgoAAAANSUhEUgAAAEAAAABACAYAAACqaXHeAAABTElEQVR4nO3ZwQmEMBAF0RYjT+9/b8t2qViN
4tg2UbkqX6gbMcm++3cgMzMzMzMzMzMzMzMzM/PnlLXySdr8ErzVZTL3tuUOsnmpQ+S/eNdQh+fMZ7owNLLv
myiueVHPjmaZ9i3cvz5UdePHW7fdyrt1uH66uYP1nyzA+sxz+lHNeSfb19ZH8YTOsbcX/PcS/b/0bZMwcQ9F
MdcjRNqz0FvS1KehQ7mpXj/FCXmX3PzMzMzMzMzMzMzMzMz8zPYBBHFU3u9Mc+kAAAAASUVORK5CYII=
"""

# Decodificar la imagen
image_data = base64.b64decode(triangle_png_base64)
image = Image.open(io.BytesIO(image_data))

# Crear ventana flotante sin bordes
root = tk.Tk()
root.overrideredirect(True)
root.geometry("64x64+50+50")
root.wm_attributes("-topmost", True)
root.configure(bg='black')
root.wm_attributes("-transparentcolor", "black")  # En Tk 8.6.9+

# Crear imagen Tkinter
image_tk = ImageTk.PhotoImage(image)

# Crear etiqueta con la imagen
label = tk.Label(root, image=image_tk, bg='black')
label.pack()

# Ejecutar acción al hacer clic
label.bind("<Button-1>", lambda e: cerrar_qt())

root.mainloop()
