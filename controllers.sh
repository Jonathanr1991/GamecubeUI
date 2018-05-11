#!/bin/bash
[ "$UID" -eq 0 ] || { echo "This script must be run as root. Use sudo."; exit 1;}
modprobe uinput
/home/user/wii-u-gc-adapter/wii-u-gc-adapter &
exit
