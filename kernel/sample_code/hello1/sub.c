#include <linux/module.h>
#include <linux/kernel.h>

MODULE_LICENSE("GPL");

void sub(void) { 
printk("%s: sub() called\n", __func__); 
} 

