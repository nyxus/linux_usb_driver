# linux_usb_driver
Hobby project to create a usb driver in the linux kernel

# Requirements 
* Make
* Linux source 

## Optional   
* Bear: `sudo apt install bear`: 
  * Creates compile_commands.json from makefiles, needed by YCM
  * [YCM for kernel development](https://stackoverflow.com/questions/30180064/how-to-setup-youcompleteme-for-kernel-and-device-driver-development/61914280#61914280)


# Build & insert
`bear make` or `make`
`sudo rmmod gcv_usb_driver; sudo insmod gcv-usb-driver.ko`

# Usage
`sudo chmod 666 /dev/usb-drv-gcv`
`sudo echo "message 42" > /dev/usb-drv-gcv`
`sudo cat /dev/usb-drv-gcv`

