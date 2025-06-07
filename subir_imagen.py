import tkinter as tk
from tkinter import filedialog, messagebox
import shutil
import os

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
        except Exception as e:
            messagebox.showerror("Error", f"No se pudo copiar el archivo:\n{e}")

root = tk.Tk()
root.title("Subir JPG a /home/pi")
root.geometry("300x100")

btn_subir = tk.Button(root, text="Subir JPG", command=subir_jpg)
btn_subir.pack(expand=True)

root.mainloop()
