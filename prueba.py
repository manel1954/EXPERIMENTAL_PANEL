import tkinter as tk
import subprocess

class AudioStreamApp:
    def __init__(self, master):
        self.master = master
        master.title("Escuchar MMDVMHost")

        self.playing = False
        self.process = None

        self.button = tk.Button(master, text="🔊 Escuchar", command=self.toggle_audio, width=20)
        self.button.pack(padx=20, pady=20)

    def toggle_audio(self):
        if not self.playing:
            self.start_audio()
        else:
            self.stop_audio()

    def start_audio(self):
        try:
            # Reemplaza la URL con tu stream real
            stream_url = "http://localhost:8888/audio"
            self.process = subprocess.Popen(['ffplay', '-nodisp', '-autoexit', '-loglevel', 'quiet', stream_url])
            self.playing = True
            self.button.config(text="⏹️ Detener")
        except Exception as e:
            print("Error al reproducir el audio:", e)

    def stop_audio(self):
        if self.process:
            self.process.terminate()
            self.process = None
        self.playing = False
        self.button.config(text="🔊 Escuchar")

if __name__ == "__main__":
    root = tk.Tk()
    app = AudioStreamApp(root)
    root.mainloop()
