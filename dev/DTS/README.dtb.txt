dtc -I dtb -O dts -o ./gpio.dts /boot/acme-arietta.dtb
# modify it
dtc -I dts -O dtb -o ./acme-arietta.dtb gpio.dts
cp ./acme-arietta.dtb /boot/