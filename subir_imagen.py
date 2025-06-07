import tkinter as tk
from tkinter import filedialog, messagebox
from PIL import Image, ImageTk
import shutil
import os

# Cambia esto por el nombre exacto de tu archivo JPG en /home/pi/A108/
ruta_imagen_muestra = "/home/pi/A108/tuimagen.jpg"  

def mostrar_imagen(ruta):
    try:
        img = Image.open(ruta)
        img = img.resize((300, 200), Image.ANTIALIAS)  # Ajusta tamaño de la imagen
        foto = ImageTk.PhotoImage(img)
        etiqueta_imagen.config(image=foto, text='')
        etiqueta_imagen.image = foto
    except Exception as e:
        print(f"No se pudo cargar la imagen: {e}")
        etiqueta_imagen.config(image='', text="No hay imagen para mostrar")

def subir_jpg():
    archivo = filedialog.askopenfilename(
        title="Selecciona un archivo JPG",
        filetypes=[("Archivos JPG", "*.jpg;*.jpeg")]
    )
    if archivo:
        try:
            destino = "/home/pi/" + os.path.basename(archivo)
            shutil.copy2(archivo, destino)
            messagebox.showinfo("Éxito", f"Archivo copiado a:\n{destino}")
            mostrar_imagen(destino)
        except Exception as e:
            messagebox.showerror("Error", f"No se pudo copiar el archivo:\n{e}")

root = tk.Tk()
root.title("Subir y mostrar JPG")
root.geometry("320x300")

btn_subir = tk.Button(root, text="Subir JPG", command=subir_jpg)
btn_subir.pack(pady=10)

etiqueta_imagen = tk.Label(root, text="No hay imagen para mostrar")
etiqueta_imagen.pack(pady=10)

# Mostrar imagen si existe
if os.path.exists(ruta_imagen_muestra):
    mostrar_imagen(ruta_imagen_muestra)

root.mainloop()
