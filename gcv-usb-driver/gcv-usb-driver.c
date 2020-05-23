/*
 * USB driver for my hobby project, build from scratch
*/

#include <linux/module.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/sched.h>
#include <linux/init.h>
#include <linux/slab.h>
#include <linux/device.h>
#include <linux/cdev.h>
#include <linux/miscdevice.h>
#include <linux/oom.h>

#include <linux/errno.h>


#define USB_DRV_NAME "usb-drv-gcv"

static struct device *usb_drv_dev;
static char *ramdisk;
static size_t ramdisk_size = (16*PAGE_SIZE);


static int usb_drv_open(struct inode* inode, struct file* file) {
	static int counter;
	dev_info(usb_drv_dev, "Attempting to open device: %s\n", USB_DRV_NAME);
	dev_info(usb_drv_dev, "MAJOR: %d, MINOR: %d\n", imajor(inode), iminor(inode));

	counter++;

	dev_info(usb_drv_dev, "Successfully opened device: %s (times: %d, refs: %d)\n", 
			USB_DRV_NAME, counter, (int) module_refcount(THIS_MODULE));
	return 0;
}

static int usb_drv_release(struct inode *inode, struct file *file) 
{
	dev_info(usb_drv_dev, "Closing  device: %s: \n", USB_DRV_NAME);
	return 0;
}

static ssize_t usb_drv_read(struct file *file, char __user* buf, size_t lbuf, loff_t* ppos)
{
	int nbytes =
		simple_read_from_buffer(buf, lbuf, ppos, ramdisk, ramdisk_size);
	dev_info(usb_drv_dev, "Leaving the READ function; nbytes: %d, pos: %d\n", nbytes, (int)*ppos);
	return nbytes;
}

static ssize_t usb_drv_write(struct file* file, const char __user* buf, size_t lbuf, loff_t* ppos)
{
	int nbytes =
		simple_write_to_buffer(ramdisk, ramdisk_size, ppos, buf, lbuf);
	dev_info(usb_drv_dev, "Leaving the WRITE function; nbytes: %d, pos: %d\n", nbytes, (int)*ppos);
	return nbytes;
}

static const struct file_operations usb_drv_fops = 
{
	.owner = THIS_MODULE,
	.read = usb_drv_read,
	.write = usb_drv_write,
	.open = usb_drv_open,
	.release = usb_drv_release,
};

static struct miscdevice usb_drv_misc_dev = {
	.minor = MISC_DYNAMIC_MINOR,
	.name = USB_DRV_NAME,
	.fops = &usb_drv_fops,
};

static int __init usb_drv_init(void)
{
	ramdisk = kmalloc(ramdisk_size, GFP_KERNEL);
	if (misc_register(&usb_drv_misc_dev)) {
		pr_err("Coun't register misc device, "
				"%d,.\n", usb_drv_misc_dev.minor);
		kfree(ramdisk);
		return -EBUSY;
		
	}

	usb_drv_dev = usb_drv_misc_dev.this_device;
	dev_info(usb_drv_dev, "Succeeded in registering character device %s\n", USB_DRV_NAME);
	return 0;
}


static void __exit usb_drv_exit(void)
{
	dev_info(usb_drv_dev, "Unregistering character device %s\n", USB_DRV_NAME);
	misc_deregister(&usb_drv_misc_dev);
	kfree(ramdisk);
}

module_init(usb_drv_init);
module_exit(usb_drv_exit);

MODULE_AUTHOR("Gerco Versloot");
MODULE_LICENSE("GPL v2");

