#include <linux/module.h>
#include <linux/kernel.h>

MODULE_LICENSE("Dual MIT/GPL");

int init_module(void)
{
	printk(KERN_INFO "vice driver loaded\n");
	return 0;
}

void cleanup_module(void)
{
	printk(KERN_INFO "vice driver unloaded\n");
}
