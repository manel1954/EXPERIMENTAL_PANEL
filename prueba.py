import tkinter as tk
import subprocess
from tkinter import messagebox

def cerrar_qt():
    try:
        subprocess.run(['killall', 'qt_menu_superior'], check=True)
        messagebox.showinfo("Éxito", "qt_menu_superior cerrado correctamente.")
    except subprocess.CalledProcessError:
        messagebox.showwarning("Aviso", "No se pudo cerrar qt_menu_superior. ¿Está en ejecución?")
    except Exception as e:
        messagebox.showerror("Error", f"Ocurrió un error: {e}")

# Crear ventana principal
root = tk.Tk()
root.title("Cerrar Qt")
root.geometry("100x100")
root.resizable(False, False)

# Dibujar triángulo apuntando a la izquierda
canvas = tk.Canvas(root, width=60, height=60)
canvas.pack(pady=10)

# Coordenadas del triángulo (punta hacia la izquierda)
triangle = canvas.create_polygon(45, 10, 45, 50, 15, 30, fill="red", outline="black")

# Hacer que al hacer clic se ejecute el cierre
def on_click(event):
    cerrar_qt()

canvas.tag_bind(triangle, '<Button-1>', on_click)

# Ejecutar la interfaz
root.mainloop()
