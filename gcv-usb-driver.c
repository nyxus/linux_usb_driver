/*
 * USB driver for my hobby project, build from scratch
*/

#include <linux/module.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/init.h>
#include <linux/slab.h>
#include <linux/cdev.h>


#define USB_DRV_NAME "usb-drv-gcv"


static char *ramdisk;
#define ramdisk_size (size_t) (128*PAGE_SIZE)

static dev_t first;
static unsigned int count = 1;
static int usb_drv_major = 500;
static int usb_drv_minor = 0;
static struct cdev *usb_drv_cdev;

static int usb_drv_open(struct inode* inode, struct file* file) 
{
	pr_info("Opening device: %s: \n\n", USB_DRV_NAME);
	return 0;
}

static int usb_drv_release(struct inode *inode, struct file *file) 
{
	pr_info("Closing  device: %s: \n\n", USB_DRV_NAME);
	return 0;
}

static ssize_t usb_drv_read(struct file *file, char __user* buf, size_t lbuf, loff_t* ppos)
{
	 int nbytes;
	 // TODO [versloot]: fix because it is stub
	 if ((lbuf + *ppos) > ramdisk_size){
		 pr_info("Trying to read past the end of device, "
				 "aborting because this is just a stub");
		 return 0;
	 }
	 nbytes = lbuf - copy_to_user(buf, ramdisk + *ppos, lbuf);
	 *ppos += nbytes;
	 pr_info("\n Reading function, nbytes=%d, pos=%d", nbytes, (int)*ppos);
	 return nbytes;
}

static ssize_t usb_drv_write(struct file* file, const char __user* buf, size_t lbuf, loff_t* ppos)
{
	 int nbytes;
	 // TODO [versloot]: fix because it is stub
	 if ((lbuf + *ppos) > ramdisk_size){
		 pr_info("Trying to write past the end of device, "
				 "aborting because this is just a stub");
		 return 0;
	 }
	 nbytes = lbuf - copy_from_user(ramdisk + *ppos, buf,  buf,lbuf);
	 *ppos += nbytes;
	 pr_info("\n Writing function, nbytes=%d, pos=%d", nbytes, (int)*ppos);
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

static int __init usb_drv_init(void)
{
	ramdisk = kmalloc(ramdisk_size, GFP_KERNEL);
	first = MKDEV(usb_drv_major, usb_drv_minor);
	register_chrdev_region(first, count, USB_DRV_NAME);
	usb_drv_cdev = cdev_alloc();
	cdev_add(usb_drv_cdev, first, count);
	pr_info("Succeeded in registering character device %s\n", USB_DRV_NAME);
	return 0;
}


static void __exit usb_drv_exit(void)
{
	cdev_del(usb_drv_cdev);
	unregister_chrdev_region(first, count);
	pr_info("Device unregistered: %s\n", USB_DRV_NAME);
}

module_init(usb_drv_init);
module_exit(usb_drv_exit);

MODULE_AUTHOR("Gerco Versloot");
MODULE_LICENSE("GPL v2");

