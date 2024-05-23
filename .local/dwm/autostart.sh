#!/usr/bin/bash
xrandr --output DP-1 --mode 1920x1080 --pos 2560x0 --rotate normal --output HDMI-1 --mode 2560x1080 --pos 0x0 --rotate normal --output DVI-D-1 --off --output DVI-D-2 --off
xsetroot -cursor_name left_ptr &
nitrogen --restore & 
dwmblocks &
numlockx &
dunst &
picom -b &
xset -dpms &
xset s off &
xfce4-power-manager &
/usr/lib/polkit-gnome/polkit-gnome-authentication-agent-1 &



