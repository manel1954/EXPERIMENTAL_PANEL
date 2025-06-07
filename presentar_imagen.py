import tkinter as tk
from tkinter import filedialog, messagebox, Toplevel
from PIL import Image, ImageTk
import os

directorio_origen = "/home/pi/uploads"

def redimensionar_con_aspect_ratio(imagen, max_width, max_height):
    ancho_original, alto_original = imagen.size
    ratio = min(max_width / ancho_original, max_height / alto_original)
    nuevo_ancho = int(ancho_original * ratio)
    nuevo_alto = int(alto_original * ratio)
    return imagen.resize((nuevo_ancho, nuevo_alto), Image.Resampling.LANCZOS)

def mostrar_imagen_en_ventana_nueva(ruta_imagen):
    ventana_imagen = Toplevel(root)
    ventana_imagen.title(f"Imagen: {os.path.basename(ruta_imagen)}")
    
    try:
        img = Image.open(ruta_imagen)
        img = redimensionar_con_aspect_ratio(img, 600, 400)  # Mantiene proporción
        foto = ImageTk.PhotoImage(img)

        etiqueta = tk.Label(ventana_imagen, image=foto)
        etiqueta.image = foto
        etiqueta.pack()

        # Ajustamos ventana al tamaño de la imagen + un margen
        ventana_imagen.geometry(f"{img.width + 20}x{img.height + 20}")
    except Exception as e:
        messagebox.showerror("Error", f"No se pudo mostrar la imagen:\n{e}")
        ventana_imagen.destroy()

def elegir_imagen():
    archivo = filedialog.askopenfilename(
        title="Selecciona una imagen",
        initialdir=directorio_origen,
        filetypes=[
            ("Archivos de imagen", "*.jpg *.jpeg *.png *.gif *.bmp *.tiff"),
            ("Todos los archivos", "*.*")
        ]
    )
    if archivo:
        mostrar_imagen_en_ventana_nueva(archivo)

root = tk.Tk()
root.title("Selector de imágenes")
root.geometry("300x150")

btn_elegir = tk.Button(root, text="Elegir imagen de /home/pi/uploads", command=elegir_imagen)
btn_elegir.pack(expand=True)

root.mainloop()
