#!/bin/bash

PANEL_FILE="$HOME/.config/lxpanel/LXDE-pi/panels/panel"
BACKUP_FILE="$PANEL_FILE.bak_$(date +%Y%m%d%H%M%S)"

echo "🔧 Corrigiendo lxpanel..."

# Verificar existencia del archivo
if [ ! -f "$PANEL_FILE" ]; then
  echo "❌ Archivo de panel no encontrado en: $PANEL_FILE"
  exit 1
fi

# Copia de seguridad
cp "$PANEL_FILE" "$BACKUP_FILE"
echo "✅ Copia de seguridad creada: $BACKUP_FILE"

# Eliminar el bloque del plugin 'tray'
awk '
  BEGIN { inside=0 }
  /Plugin[[:space:]]*{/ { inside=1; buffer=$0; next }
  inside && /type=tray/ { skipping=1 }
  inside && /}/ {
    if (skipping) {
      inside=0; skipping=0; next
    } else {
      print buffer; inside=0
    }
  }
  !inside { print }
' "$BACKUP_FILE" > "$PANEL_FILE"

echo "✅ Plugin 'tray' eliminado del panel."

# Reiniciar entorno gráfico
echo "♻️ Reiniciando entorno gráfico..."
lxpanelctl restart

echo "✅ Panel corregido. Si aún no aparece, reinicia con: sudo reboot"
∫