modprobe uinput
modprobe usbtouchscreen
modprobe evdev
#export TSLIB_FBDEVICE=/dev/fb0 
setsid ./tochpadRPi.elf /dev/hidraw0
export TSLIB_TSDEVICE=/dev/input/event0
./nome_da_app -plugin tslib:/dev/input/event0



