import tkinter as tk
import subprocess

def cerrar_qt():
    try:
        subprocess.run(['killall', 'qt_menu_superior'], check=True)
    except:
        pass

# Crear ventana principal sin bordes
root = tk.Tk()
root.overrideredirect(1)  # Quitar barra de título
root.geometry("60x60+50+50")  # Tamaño y posición (opcional)
root.wm_attributes('-topmost', True)  # Siempre al frente
root.config(bg='magenta')  # Color que usaremos como transparente
root.attributes('-transparentcolor', 'magenta')  # Hacer transparente ese color

# Crear canvas con fondo transparente
canvas = tk.Canvas(root, width=60, height=60, bg='magenta', highlightthickness=0)
canvas.pack()

# Dibujar triángulo apuntando a la izquierda
triangle = canvas.create_polygon(45, 10, 45, 50, 15, 30, fill="red", outline="black")

# Clic sobre el triángulo
canvas.tag_bind(triangle, '<Button-1>', lambda e: cerrar_qt())

root.mainloop()
