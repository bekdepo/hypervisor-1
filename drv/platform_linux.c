/*
	Copyright (c) 2014 Ryan Salsamendi

	Permission is hereby granted, free of charge, to any person obtaining a copy
	of this software and associated documentation files (the "Software"), to deal
	in the Software without restriction, including without limitation the rights
	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
	copies of the Software, and to permit persons to whom the Software is
	furnished to do so, subject to the following conditions:

	The above copyright notice and this permission notice shall be included in
	all copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
	THE SOFTWARE.
*/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/types.h>
#include <linux/fs.h>
#include <linux/miscdevice.h>

#include "platform.h"
#include "hypervisor.h"

MODULE_LICENSE("Dual MIT/GPL");
MODULE_AUTHOR("Ryan Salsamendi <rsalsamendi@hotmail.com>");
MODULE_DESCRIPTION("A simple hypervisor");

#define HYPERVISOR_MINOR	1

void PlatformPrint(const char* msg)
{
	printk(KERN_WARNING "hypervisor: %s\n", msg);
}

uint64_t PlatformReadCR0(void)
{
	uint64_t cr0;

	__asm__ __volatile__
	(
		"movq %%cr0, %%rax\r\n"
		: "=a" (cr0)
		:
		:
	);

	return cr0;
}

uint64_t PlatformReadCR4(void)
{
	uint64_t cr4;

	__asm__ __volatile__
	(
		"movq %%cr4, %%rax\r\n"
		: "=a" (cr4)
		:
		:
	);

	return cr4;
}

void PlatformCpuid(uint64_t leaf, CpuidRegs* const cpuid)
{
	__asm__ __volatile__
	(
		"cpuid\r\n"
		: "=a" (cpuid->rax), "=c" (cpuid->rcx),
		  "=d" (cpuid->rdx), "=b" (cpuid->rbx)
		: "a" (leaf)
		:
	);
}

static int __init hypervisor_init_module(void)
{
	printk(KERN_INFO "hypervisor driver loaded\n");

	if (!HVInit())
		printk(KERN_INFO "vmx not supported\n");

	return 0;
}

static void __exit hypervisor_exit_module(void)
{
	printk(KERN_INFO "hypervisor driver unloaded\n");
}

module_init(hypervisor_init_module);
module_exit(hypervisor_exit_module);

static long hypervisor_ioctl(struct file* filp, unsigned int ioctl, unsigned long arg)
{
	return 0;
}

static int hypervisor_open(struct inode* inodep, struct file* filep)
{
	return 0;
}

static int hypervisor_release(struct inode* inodep, struct file* filep)
{
	return 0;
}

static const struct file_operations hypervisor_device_ops =
{
	// .owner =  ?
	.unlocked_ioctl = hypervisor_ioctl,
#ifdef CONFIG_COMPAT
	.compat_ioctl = hypervisor_ioctl,
#endif /* CONFIG_COMPAT */
	.open = hypervisor_open,
	.release = hypervisor_release
};

static const struct miscdevice hypervisor_device =
{
	HYPERVISOR_MINOR,
	"hypervisor",
	&hypervisor_device_ops
};

