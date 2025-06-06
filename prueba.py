import tkinter as tk
import subprocess

class DVSwitchMonitor:
    def __init__(self, master):
        self.master = master
        master.title("DVSwitch RX Monitor")

        self.playing = False
        self.process = None

        self.button = tk.Button(master, text="🔊 Escuchar RX", command=self.toggle_audio, width=30)
        self.button.pack(padx=30, pady=30)

    def toggle_audio(self):
        if not self.playing:
            self.start_audio()
        else:
            self.stop_audio()

    def start_audio(self):
        try:
            # Dirección del stream RTP/UDP generado por AnalogBridge/DVSwitch
            stream_url = "udp://127.0.0.1:12345"  # Ajusta si es diferente
            self.process = subprocess.Popen(['ffplay', '-nodisp', '-autoexit', '-loglevel', 'quiet', stream_url])
            self.playing = True
            self.button.config(text="⏹️ Detener RX")
        except Exception as e:
            print("Error al iniciar audio:", e)

    def stop_audio(self):
        if self.process:
            self.process.terminate()
            self.process = None
        self.playing = False
        self.button.config(text="🔊 Escuchar RX")

if __name__ == "__main__":
    root = tk.Tk()
    app = DVSwitchMonitor(root)
    root.mainloop()
