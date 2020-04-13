# Makefile for linking kernel modules
# Assumes that MYMODULE is imported as shell variable

THISDIR = $(shell pwd)
KERNDIR = /lib/modules/$(shell uname -r)/build

obj-m   := $(MYMODULE).o

$(MYMODULE).ko: $(MYMODULE).c 
	echo start the make
	make -C $(KERNDIR) M=$(THISDIR) modules
