# linux_usb_driver
Hobby project to create a usb driver in the linux kernel

# Build & insert

`./runmake gcv-usb-driver`
`sudo rmmod gcv_usb_driver; sudo insmod gcv-usb-driver.ko`

# Usage

`sudo chmod 666 /dev/usb-drv-gcv`
`sudo echo "message 42" > /dev/usb-drv-gcv`
`sudo cat /dev/usb-drv-gcv`

