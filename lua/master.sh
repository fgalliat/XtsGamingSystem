# XtsConsole main start script

mkdir /vm_mnt/lock 2>/dev/null
rm /vm_mnt/lock/XtsConsole.lock 2>/dev/null

./lua script/boot.lua

