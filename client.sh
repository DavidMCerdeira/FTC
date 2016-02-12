#!/bin/bash

modprobe uinput
./touchpad.elf /dev/hidraw0 &
modprobe evdev
export TSLIB_TSDEVICE=/dev/input/event0

modprobe gspca_zc3xx
modprobe uvcvideo




#./nome_da_app -plugin tslib:/dev/input/event0
