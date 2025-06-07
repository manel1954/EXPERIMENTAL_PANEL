import tkinter as tk
from tkinter import filedialog, messagebox, Toplevel
from PIL import Image, ImageTk
import os

directorio_origen = "/home/pi/uploads"

def mostrar_imagen_en_ventana_nueva(ruta_imagen):
    # Crear ventana nueva
    ventana_imagen = Toplevel(root)
    ventana_imagen.title(f"Imagen: {os.path.basename(ruta_imagen)}")
    
    try:
        img = Image.open(ruta_imagen)
        img = img.resize((600, 400), Image.Resampling.LANCZOS)  # Ajusta tamaño aquí si quieres
        foto = ImageTk.PhotoImage(img)

        etiqueta = tk.Label(ventana_imagen, image=foto)
        etiqueta.image = foto  # evitar que el garbage collector borre la imagen
        etiqueta.pack()

        ventana_imagen.geometry("620x420")  # Tamaño ventana un poco mayor que la imagen
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
