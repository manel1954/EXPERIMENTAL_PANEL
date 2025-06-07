import tkinter as tk
import subprocess

def cerrar_qt():
    try:
        subprocess.run(['killall', 'qt_menu_superior'], check=True)
    except Exception as e:
        print(f"Error al cerrar qt_menu_superior: {e}")

# Crear ventana principal sin bordes
root = tk.Tk()
root.overrideredirect(True)  # Sin barra de título
root.geometry("80x80+50+50")  # Tamaño y posición (ajusta si quieres)
root.wm_attributes("-topmost", True)  # Siempre visible
root.wm_attributes("-transparentcolor", "magenta")  # Hacemos magenta transparente
root.configure(bg='magenta')  # Fondo del mismo color a ocultar

# Canvas con fondo también magenta (transparente)
canvas = tk.Canvas(root, width=80, height=80, bg='magenta', highlightthickness=0)
canvas.pack()

# Triángulo rojo apuntando a la izquierda
triangle = canvas.create_polygon(60, 15, 60, 65, 20, 40, fill="red", outline="black")

# Hacer que al hacer clic se ejecute el cierre
def on_click(event):
    cerrar_qt()

canvas.tag_bind(triangle, '<Button-1>', on_click)

root.mainloop()
