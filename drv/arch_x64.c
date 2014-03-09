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
#include <linux/types.h>

#include "arch.h"

uint64_t ArchReadMsr(uint32_t msr)
{
	uint64_t value;

	__asm__
	(
		"rdmsr"
		: "=A" (value)
		: "c" (msr)
		:
	);

	return value;
}

void ArchWriteMsr(uint32_t msr, uint64_t value)
{
	__asm__ __volatile__
	(
		"wrmsr"
		:
		: "c" (msr), "A" (value)
		:
	);
}

uint64_t ArchReadCr0(void)
{
	uint64_t cr0;

	__asm__
	(
		"movq %%cr0, %%rax"
		: "=a" (cr0)
		:
		:
	);

	return cr0;
}

uint64_t ArchReadCr2(void)
{
	uint64_t cr2;

	__asm__
	(
		"movq %%cr2, %%rax"
		: "=a" (cr2)
		:
		:
	);

	return cr2;
}

uint64_t ArchReadCr3(void)
{
	uint64_t cr3;

	__asm__
	(
		"movq %%cr3, %%rax"
		: "=a" (cr3)
		:
		:
	);

	return cr3;
}

uint64_t ArchReadCr4(void)
{
	uint64_t cr4;

	__asm__
	(
		"movq %%cr4, %%rax"
		: "=a" (cr4)
		:
		:
	);

	return cr4;
}

void ArchWriteCr0(uint64_t cr0)
{
	__asm__ __volatile__
	(
		"movq %0, %%cr0"
		:
		: "r" (cr0)
		:
	);
}
		
void ArchWriteCr2(uint64_t cr2)
{
	__asm__ __volatile__
	(
		"movq %0, %%cr2"
		:
		: "r" (cr2)
		:
	);
}
	
void ArchWriteCr3(uint64_t cr3)
{
	__asm__ __volatile__
	(
		"movq %0, %%cr3"
		:
		: "r" (cr3)
		:
	);
}
	
void ArchWriteCr4(uint64_t cr4)
{
	__asm__ __volatile__
	(
		"movq %0, %%cr4"
		:
		: "r" (cr4)
		:
	);
}

uint64_t ArchReadDr0(void)
{
	uint64_t dr0;

	__asm__
	(
		"movq %%dr0, %%rax"
		: "=a" (dr0)
		:
		:
	);

	return dr0;
}
	
uint64_t ArchReadDr1(void)
{
	uint64_t dr1;

	__asm__
	(
		"movq %%dr1, %%rax"
		: "=a" (dr1)
		:
		:
	);

	return dr1;
}
	
uint64_t ArchReadDr2(void)
{
	uint64_t dr2;

	__asm__
	(
		"movq %%dr2, %%rax"
		: "=a" (dr2)
		:
		:
	);

	return dr2;
}

uint64_t ArchReadDr3(void)
{
	uint64_t dr3;

	__asm__
	(
		"movq %%dr3, %%rax"
		: "=a" (dr3)
		:
		:
	);

	return dr3;
}

uint64_t ArchReadDr6(void)
{
	uint64_t dr6;

	__asm__
	(
		"movq %%dr6, %%rax"
		: "=a" (dr6)
		:
		:
	);

	return dr6;
}

uint64_t ArchReadDr7(void)
{
	uint64_t dr7;

	__asm__
	(
		"movq %%dr7, %%rax"
		: "=a" (dr7)
		:
		:
	);

	return dr7;
}

void ArchWriteDr0(uint64_t dr0)
{
	__asm__ __volatile__
	(
		"movq %0, %%dr0"
		:
		: "r" (dr0)
		:
	);
}

void ArchWriteDr1(uint64_t dr1)
{
	__asm__ __volatile__
	(
		"movq %0, %%dr1"
		:
		: "r" (dr1)
		:
	);
}

void ArchWriteDr2(uint64_t dr2)
{
	__asm__ __volatile__
	(
		"movq %0, %%dr2"
		:
		: "r" (dr2)
		:
	);
}

void ArchWriteDr3(uint64_t dr3)
{
	__asm__ __volatile__
	(
		"movq %0, %%dr3"
		:
		: "r" (dr3)
		:
	);
}

void ArchWriteDr6(uint64_t dr6)
{
	__asm__ __volatile__
	(
		"movq %0, %%dr6"
		:
		: "r" (dr6)
		:
	);
}

void ArchWriteDr7(uint64_t dr7)
{
	__asm__ __volatile__
	(
		"movq %0, %%dr7"
		:
		: "r" (dr7)
		:
	);
}

void ArchCpuid(uint64_t leaf, CpuidRegs* const cpuid)
{
	__asm__
	(
		"cpuid"
		: "=a" (cpuid->rax), "=c" (cpuid->rcx),
		  "=d" (cpuid->rdx), "=b" (cpuid->rbx)
		: "a" (leaf)
		:
	);
}

