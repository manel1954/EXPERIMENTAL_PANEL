#!/bin/bash

echo "🔧 Restaurando configuración del panel superior LXPanel..."

# Paso 1: Asegurar que lxpanel está instalado
if ! command -v lxpanel &> /dev/null; then
    echo "📦 Instalando lxpanel..."
    sudo apt update
    sudo apt install -y lxpanel
else
    echo "✅ lxpanel ya está instalado."
fi

# Paso 2: Hacer copia de seguridad de la configuración actual
echo "📁 Haciendo copia de seguridad de la configuración actual..."
mkdir -p ~/.config_backup
mv -v ~/.config/lxpanel ~/.config_backup/lxpanel_$(date +%Y%m%d%H%M%S) 2>/dev/null
mv -v ~/.config/lxsession ~/.config_backup/lxsession_$(date +%Y%m%d%H%M%S) 2>/dev/null

# Paso 3: Regenerar configuración predeterminada reiniciando sesión
echo "📝 Restaurando archivo autostart..."
mkdir -p ~/.config/lxsession/LXDE-pi/
cat > ~/.config/lxsession/LXDE-pi/autostart <<EOF
@lxpanel --profile LXDE-pi
@pcmanfm --desktop --profile LXDE-pi
@xscreensaver -no-splash
EOF

# Paso 4: Reiniciar entorno gráfico
echo "♻️ Reiniciando entorno gráfico..."
lxpanel --profile LXDE-pi &
pcmanfm --desktop --profile LXDE-pi &

echo "✅ Panel superior restaurado. Si aún no aparece, reinicia el sistema con:"
echo "sudo reboot"
