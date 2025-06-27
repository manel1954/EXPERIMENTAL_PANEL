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

# Paso 3: Restaurar autostart
echo "📝 Restaurando archivo autostart..."
mkdir -p ~/.config/lxsession/LXDE-pi/
cat > ~/.config/lxsession/LXDE-pi/autostart <<EOF
@lxpanel --profile LXDE-pi
@pcmanfm --desktop --profile LXDE-pi
@xscreensaver -no-splash
EOF

# Paso 4: Crear configuración básica del panel
echo "🛠️  Generando configuración básica del panel..."
mkdir -p ~/.config/lxpanel/LXDE-pi/panels

cat > ~/.config/lxpanel/LXDE-pi/panels/panel <<EOF
Global {
  edge=top
  allign=left
  margin=0
  widthtype=percent
  width=100
  height=26
  transparent=0
  tintcolor=#000000
  alpha=0
  autohide=0
  heightwhenhidden=2
  setdocktype=1
  setpartialstrut=1
  usefontcolor=1
  fontsize=10
  fontcolor=#ffffff
  background=1
  backgroundfile=/usr/share/lxpanel/images/background.png
}

Plugin {
  type=menu
}

Plugin {
  type=launchbar
  Config {
    Button {
      id=lxterminal.desktop
    }
    Button {
      id=pcmanfm.desktop
    }
  }
}

Plugin {
  type=taskbar
}

Plugin {
  type=pager
}

Plugin {
  type=tray
}

Plugin {
  type=dclock
}
EOF

# Paso 5: Reiniciar entorno gráfico
echo "♻️ Iniciando panel..."
lxpanel --profile LXDE-pi &

echo "✅ Panel superior restaurado. Si aún no se muestra, reinicia con:"
echo "sudo reboot"
