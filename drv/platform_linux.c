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
#include <linux/smp.h>
#include <linux/miscdevice.h>

#include "platform.h"
#include "hypervisor.h"

MODULE_LICENSE("Dual MIT/GPL");
MODULE_AUTHOR("Ryan Salsamendi <rsalsamendi@hotmail.com>");
MODULE_DESCRIPTION("A simple hypervisor");

#define HYPERVISOR_MINOR	1

bool PlatformRunOnAllCpus(PlatformOnAllCpusFunc func, void* data)
{
	int cpu;
	for_each_online_cpu(cpu)
		if (!func(data))
			return false;
	return true;
}

uint32_t PlatformGetCpuCount(void)
{
	uint32_t cpuCount;
	int cpu;

	cpuCount = 0;
	for_each_online_cpu(cpu)
		cpuCount++;
	return cpuCount;
}

void PlatformDisableSchedulerInterrupts(void)
{
	get_cpu();
}

void PlatformEnableSchedulerInterrupts(void)
{
	put_cpu();
}

void PlatformPrint(const char* msg)
{
	printk(KERN_WARNING "hypervisor: %s\n", msg);
}

static int __init hypervisor_init_module(void)
{
	if (!HypervisorInit())
		return -1;
	return 0;
}

static void __exit hypervisor_exit_module(void)
{
	HypervisorCleanup();
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

