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
#ifndef __ARCH_H__
#define __ARCH_H__

typedef struct CpuidRegs
{
	uint32_t eax;
	uint32_t ecx;
	uint32_t edx;
	uint32_t ebx;
} CpuidRegs;

typedef enum MachineSpecificRegister
{
	IA32_FEATURE_CTL = 0x3a,

	IA32_VMX_BASIC = 0x480,
	IA32_VMX_PINBASED_CTLS = 0x481,
	IA32_VMX_PROCBASED_CTLS = 0x482,
	IA32_VMX_EXIT_CTLS = 0x483,
	IA32_VMX_ENTRY_CTLS = 0x484,
	IA32_VMX_MISC = 0x485,
	IA32_VMX_CR0_FIXED0 = 0x486,
	IA32_VMX_CR0_FIXED1 = 0x487,
	IA32_VMX_CR4_FIXED0 = 0x488,
	IA32_VMX_CR4_FIXED1 = 0x489,
	IA32_VMX_VMCS_ENUM = 0x48a,
	IA32_VMX_PROCBASED_CTLS2 = 0x48b,
	IA32_VMX_EPT_VPID_CAP	 = 0x48c,
	IA32_VMX_TRUE_PINBASED_CTLS = 0x48d,
	IA32_VMX_TRUE_PROCBASED_CTLS = 0x48e,
	IA32_VMX_TRUE_EXIT_CTLS	 = 0x48f,
	IA32_VMX_TRUE_ENTRY_CTLS = 0x490,
	IA32_VMX_VMFUNC = 0x491
} MachineSpecificRegister;

uint64_t ArchReadMsr(uint32_t msr);
void ArchWriteMsr(uint32_t msr, uint64_t value);

uint64_t ArchReadCr0(void);
uint64_t ArchReadCr2(void);
uint64_t ArchReadCr3(void);
uint64_t ArchReadCr4(void);

void ArchWriteCr0(uint64_t cr0);
void ArchWriteCr2(uint64_t cr2);
void ArchWriteCr3(uint64_t cr3);
void ArchWriteCr4(uint64_t cr4);

uint64_t ArchReadDr0(void);
uint64_t ArchReadDr1(void);
uint64_t ArchReadDr2(void);
uint64_t ArchReadDr3(void);
uint64_t ArchReadDr6(void);
uint64_t ArchReadDr7(void);

void ArchWriteDr0(uint64_t dr0);
void ArchWriteDr1(uint64_t dr1);
void ArchWriteDr2(uint64_t dr2);
void ArchWriteDr3(uint64_t dr3);
void ArchWriteDr6(uint64_t dr6);
void ArchWriteDr7(uint64_t dr7);

void ArchCpuid(uint64_t leaf, CpuidRegs* const cpuid);


#endif /* __ARCH_H__ */
