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

# Imagen PNG válida (triángulo rojo apuntando a la izquierda sobre fondo transparente)
triangle_png_base64 = (
    "iVBORw0KGgoAAAANSUhEUgAAAEAAAABACAYAAACqaXHeAAABr0lEQVR4nO3asU3DQBSA4W+pl7CwZLKwR3C"
    "cLJbcRdwbG8ZC8Bd0TawUSL4C6TKT93xspEpiwEBAQEBAQEBAQGBuT2T+0zAOef9y0gUnzlsHx7wb9Nn9Na"
    "np0CD9TltF81zE+y+0bh79POxRX1MZTVNXP2X19fUzRlaM2LwYUP9vvo4ZrYboeqbeNYPdUVXwT1P9PGVfq"
    "xNlmbfxszWdQ3foN9BddU85ajSnaCrf2UtW0b4aMeUl9FN7x+2XX9q62GzKz6xbFfaSpK+m+qHxUS2MdRRu"
    "pWw2uTdZ9Gmr3khrH3/2VF9V+Ut26OKc1jptPoA9OfNvOtHoWov2zGqzRdfS88fLwFydL0KfdScpcHn8cYl"
    "87Z7zjVv29nb98DEBAQEBAQEBAcHfgw7qnkZkYe3jAAAAAElFTkSuQmCC"
)

# Decodificar imagen y cargarla en Tkinter
image_data = base64.b64decode(triangle_png_base64)
image = Image.open(io.BytesIO(image_data)).convert("RGBA")  # Asegura canal alpha

# Crear ventana
root = tk.Tk()
root.overrideredirect(True)
root.geometry("64x64+50+50")
root.attributes("-topmost", True)
root.attributes("-alpha", 0.8)  # Transparente general

# Crear widget de imagen
image_tk = ImageTk.PhotoImage(image)
label = tk.Label(root, image=image_tk, bg='black')
label.pack()

# Acción al hacer clic
label.bind("<Button-1>", lambda e: cerrar_qt())

root.mainloop()
