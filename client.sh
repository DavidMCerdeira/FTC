#!/bin/sh

modprobe uinput
./touchpad.elf /dev/hidraw0 &
modprobe evdev
export TSLIB_TSDEVICE=/dev/input/event0

modprobe gspca_zc3xx
modprobe uvcvideo

export QT_QPA_EGLFS_PHYSICAL_WIDTH=142
export QT_QPA_EGLFS_PHYSICAL_HEIGHT=79


#./nome_da_app -plugin tslib:/dev/input/event0
