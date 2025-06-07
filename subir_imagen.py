import tkinter as tk
from tkinter import filedialog, messagebox
from PIL import Image, ImageTk
import shutil
import os

directorio_destino = "/home/pi"
imagen_seleccionada = None

def mostrar_imagen(ruta):
    global imagen_seleccionada
    try:
        img = Image.open(ruta)
        img = img.resize((300, 200), Image.Resampling.LANCZOS)
        foto = ImageTk.PhotoImage(img)
        etiqueta_imagen.config(image=foto, text='')
        etiqueta_imagen.image = foto
        imagen_seleccionada = ruta
    except Exception as e:
        messagebox.showerror("Error", f"No se pudo mostrar la imagen:\n{e}")
        etiqueta_imagen.config(image='', text="No hay imagen para mostrar")
        imagen_seleccionada = None

def elegir_imagen():
    # Sin initialdir para que abra en carpeta por defecto o última usada del sistema
    archivo = filedialog.askopenfilename(
        title="Selecciona un archivo JPG",
        filetypes=[("Archivos JPG", "*.jpg;*.jpeg;*.JPG;*.JPEG")]
    )
    if archivo:
        mostrar_imagen(archivo)

def guardar_imagen():
    global imagen_seleccionada
    if not imagen_seleccionada:
        messagebox.showwarning("Atención", "No has seleccionado ninguna imagen para guardar.")
        return
    try:
        nombre_archivo = os.path.basename(imagen_seleccionada)
        destino = os.path.join(directorio_destino, nombre_archivo)
        shutil.copy2(imagen_seleccionada, destino)
        messagebox.showinfo("Éxito", f"Imagen guardada en:\n{destino}")
    except Exception as e:
        messagebox.showerror("Error", f"No se pudo guardar la imagen:\n{e}")

root = tk.Tk()
root.title("Elegir y guardar imagen JPG")
root.geometry("350x350")

btn_elegir = tk.Button(root, text="Elegir imagen JPG", command=elegir_imagen)
btn_elegir.pack(pady=10)

btn_guardar = tk.Button(root, text="Guardar imagen en /home/pi", command=guardar_imagen)
btn_guardar.pack(pady=10)

etiqueta_imagen = tk.Label(root, text="No hay imagen seleccionada")
etiqueta_imagen.pack(pady=10)

root.mainloop()
