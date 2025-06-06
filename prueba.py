import configparser
import os

# Ruta del archivo MMDVM.ini
INI_PATH = '/home/pi/MMDVMHost/MMDVM.ini'

def cargar_config(path):
    if not os.path.isfile(path):
        print(f"Error: El archivo {path} no existe.")
        return None
    config = configparser.ConfigParser(strict=False)
    config.read(path)
    return config

def guardar_config(config, path):
    with open(path, 'w') as configfile:
        config.write(configfile)
    print(f"Archivo guardado exitosamente en {path}")

def mostrar_datos_actuales(config):
    callsign = config.get('General', 'Callsign', fallback='No definido')
    dmr_id = config.get('DMR', 'Id', fallback='No definido')
    print(f"Callsign actual: {callsign}")
    print(f"DMR ID actual: {dmr_id}")

def editar_valores(config):
    nuevo_callsign = input("Nuevo Callsign: ").strip().upper()
    nuevo_id = input("Nuevo DMR ID: ").strip()

    if nuevo_callsign:
        config.set('General', 'Callsign', nuevo_callsign)
    if nuevo_id:
        config.set('DMR', 'Id', nuevo_id)

def main():
    config = cargar_config(INI_PATH)
    if config is None:
        return

    print("\n--- VALORES ACTUALES ---")
    mostrar_datos_actuales(config)

    print("\n--- MODIFICAR VALORES ---")
    editar_valores(config)

    print("\n--- NUEVOS VALORES ---")
    mostrar_datos_actuales(config)

    guardar_config(config, INI_PATH)

if __name__ == '__main__':
    main()
