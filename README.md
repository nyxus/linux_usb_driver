# linux_usb_driver
Hobby project to create a usb driver in the linux kernel for the Velleman VM110N

# Requirements 
## Driver
* Make
* Linux source 

## Application
* Cmake: `sudo apt install cmake`

## Optional   
* Bear: `sudo apt install bear`: 
  * Creates compile_commands.json from makefiles, needed by YCM
  * [YCM for kernel development](https://stackoverflow.com/questions/30180064/how-to-setup-youcompleteme-for-kernel-and-device-driver-development/61914280#61914280)


# Build

## Driver
`cd gcv-usb-driver`
`bear make` or `make`

## Application
`cd gcv-usb-app`
`cmake -S . -B build && cmake --build build`

# Usage

## Driver: insert & test
`sudo rmmod gcv_usb_driver; sudo insmod gcv-usb-driver.ko`
`sudo chmod 666 /dev/usb-drv-gcv`
`sudo echo "message 42" > /dev/usb-drv-gcv`
`sudo cat /dev/usb-drv-gcv`

## Application
`./build/Gcv-usb-app`

