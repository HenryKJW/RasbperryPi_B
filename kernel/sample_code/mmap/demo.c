/*
說明：1.如果是透過kmalloc(),get_free_pages()等分配的，這種內存頁是不能直接使用remap_pfn_range()映射出去的
	     要對每個頁面用SetPageReserverd()標記“保留”才可以，virt_to_phys()函式只是得到其物理地址，
	     remap_pfn_range()中的第三個參數是要求物理頁即pfn,所以phys還要做">> PAGE_SHIFT”操作
*/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/errno.h>
#include <linux/types.h>
#include <linux/fcntl.h>
#include <linux/cdev.h>
#include <linux/version.h>
#include <linux/vmalloc.h>
#include <linux/ctype.h>
#include <linux/pagemap.h>
#include <linux/mm.h>
#include <linux/slab.h>
#include "demo.h"

MODULE_DESCRIPTION("mmap demo driver");
MODULE_LICENSE("Dual BSD/GPL");

struct simple_dev *simple_devices;
static unsigned char simple_inc=0;
static char*buffer=NULL;
static char*buffer_area=NULL;

int simple_open(struct inode *inode, struct file *filp)
{
	 struct simple_dev *dev;
	 simple_inc++;

	 dev = container_of(inode->i_cdev, struct simple_dev, cdev);
	 filp->private_data = dev;

	 return 0;
}

int simple_release(struct inode *inode, struct file *filp)
{
	 simple_inc--;
	 return 0;
}

static int simple_mmap(struct file *filp, struct vm_area_struct *vma)
{
	 int ret;
	 ret = remap_pfn_range(vma,
	     vma->vm_start,
	     virt_to_phys((void*)((unsigned long)buffer_area)) >> PAGE_SHIFT,
	//這個地方由於我們是將一段虛擬內存buffer_area虛擬為物理內存，所以這裡要使用virt_to_phys
	//第三個參數是要求物理頁即pfn,所以phys還要做">> PAGE_SHIFT”操作
	     vma->vm_end-vma->vm_start,
	     PAGE_SHARED);
	 if(ret != 0) {
	 	return -EAGAIN;
	 }
	 return 0;
}

struct file_operations simple_fops = {
 .owner =    THIS_MODULE,
 .open =     simple_open,
 .mmap =    simple_mmap,
 .release =  simple_release,
};

/*******************************************************
                MODULE ROUTINE
*******************************************************/
void simple_cleanup_module(void)
{
	 dev_t devno = MKDEV(simple_MAJOR, simple_MINOR);
	 unsigned long virt_addr;
	 if (simple_devices) 
	 {
		  cdev_del(&simple_devices->cdev);
		  kfree(simple_devices);
	 }
	 for(virt_addr=(unsigned long)buffer_area; virt_addr<(unsigned long)buffer_area+4096;
	 virt_addr+=PAGE_SIZE)
	 {
		   SetPageReserved(virt_to_page(virt_addr));
	 }
	 if (buffer)
		   kfree(buffer);
	 unregister_chrdev_region(devno,1);
}

int simple_init_module(void)
{
	 int result;
	 dev_t dev = 0;
	 int i;
	 unsigned long virt_addr;
 
	 dev = MKDEV(simple_MAJOR, simple_MINOR);
	 result = register_chrdev_region(dev, 1, "demo");
	 if (result < 0) 
	 {
		  printk(KERN_WARNING "DEMO: can't get major %d\n", simple_MAJOR);
		  goto out_free;
	 }

	 simple_devices = kmalloc(sizeof(struct simple_dev), GFP_KERNEL);
 
	 if (!simple_devices)
	 {
		  result = -ENOMEM;
		  goto out_free;
	 }
	 memset(simple_devices, 0, sizeof(struct simple_dev));

	 sema_init(&simple_devices->sem,1);
	 cdev_init(&simple_devices->cdev, &simple_fops);
	 simple_devices->cdev.owner = THIS_MODULE;
	 simple_devices->cdev.ops = &simple_fops;
	 result = cdev_add (&simple_devices->cdev, dev, 1);
 
	 if(result)
	 {
		  printk(KERN_NOTICE "Error %d adding DEMO\n", result);
		  goto out_free;
	 }
 
	 buffer = kmalloc(4096, GFP_KERNEL);
	 printk(" mmap buffer = %p\n",buffer);
	 buffer_area=(int *)(((unsigned long)buffer + PAGE_SIZE -1) & PAGE_MASK);
	 printk(" mmap buffer_area = %p virt_to_phys=%p \n",buffer, (void*)virt_to_phys((void*)((unsigned long)buffer_area)));
	 for (virt_addr=(unsigned long) buffer_area; virt_addr<(unsigned long) buffer_area+4096; virt_addr+=PAGE_SIZE)
	 {
	  	/* reserve all pages to make them remapable */
	  	SetPageReserved(virt_to_page(virt_addr));//將頁配置為保留，防止映射到用戶空間的頁面被swap out出去；
	 }
	 memset(buffer,'C',100);
	 return 0;

	 out_free:
	 simple_cleanup_module();

	 return result;
}

module_init(simple_init_module);
module_exit(simple_cleanup_module);