#include "platform.h"
#include "arch.h"
#include "vmx.h"

typedef enum VmxVmExit
{
	VMX_VMEXIT_EXCEPTION = 0,
	VMX_VMEXIT_EXTERNAL_INT = 1,
	VMX_VMEXIT_TRIPLE_FAULT = 2,
	VMX_VMEXIT_INIT = 3,
	VMX_VMEXIT_SIPI = 4,
	VMX_VMEXIt_IO_SMI = 5,
	VMX_VMEXIT_OTHER_SMI = 6,
	VMX_VMEXIT_INTERRUPT_WINDOW = 7,
	VMX_VMEXIT_NMI_WINDOW = 8,
	VMX_VMEXIT_TASK_SWITCH = 9,
	VMX_VMEXIT_CPUID = 10,
	VMX_VMEXIT_GETSEC = 11,
	VMX_VMEXIT_HLT = 12,
	VMX_VMEXIT_INVD = 13,
	VMX_VMEXIT_INVLPG = 14,
	VMX_VMEXIT_RDPMC = 15,
	VMX_VMEXIT_RDTSC = 16,
	VMX_VMEXIT_RSM = 17,	
	VMX_VMEXIT_VMCALL = 18,
	VMX_VMEXIT_VMCLEAR = 19,
	VMX_VMEXIT_VMLAUNCH = 20,
	VMX_VMEXIT_VMPTRLD = 21,
	VMX_VMEXIT_VMPTRST = 22,
	VMX_VMEXIT_VMREAD = 23,
	VMX_VMEXIT_VMRESUME = 24,
	VMX_VMEXIT_VMWRITE = 25,
	VMX_VMEXIT_VMXOFF = 26,
	VMX_VMEXIT_VMXON = 27,
	VMX_VMEXIT_CR_ACCESS = 28,
	VMX_VMEXIT_MOV_DR = 29,
	VMX_VMEXIT_IO = 30,
	VMX_VMEXIT_RDMSR = 31,
	VMX_VMEXIT_WRMSR = 32,
	VMX_VMEXIT_VMENTRY_FAIL_INVALID_GUEST_STATE = 33,
	VMX_VMEXIT_VMENTRY_FAIL_MSR_LOAD = 34,
	// VMX_VMEXIT_RESERVED1 = 35,
	VMX_VMEXIT_MWAIT = 36,
	VMX_VMEXIT_MONITOR_TRAP_FLAG = 37,
	// VMX_VMEXIT_RESERVED2 = 37,
	// VMX_VMEXIT_RESERVED3 = 38,
	VMX_VMEXIT_MONITOR = 39,
	VMX_VMEXIT_PAUSE = 40,
	VMX_VMEXIT_VMENTRY_MACHINE_CHECK = 41,
	// VMX_VMEXIT_RESERVED4 = 42,
	VMX_VMEXIt_TPR_BELOW_THRESHOLD = 43,
	VMX_VMEXIT_APIC_ACCESS = 44,
	VMX_VMEXIT_VIRTUALIZED_EOI = 45,
	VMX_VMEXIT_GDTR_IDTR = 46,
	VMX_VMEXIT_LDTR_TR = 47,
	VMX_VMEXIT_EPT_VIOLATION = 48,
	VMX_VMEXIT_EPT_MISCONFIGURATION = 49,
	VMX_VMEXIT_INVEPT = 50,
	VMX_VMEXIT_RDTSCP = 51,
	VMX_VMEXIT_PREEMPTION_TIMER = 52,
	VMX_VMEXIT_INVVPID = 53,
	VMX_VMEXIT_WBINVD = 54,
	VMX_VMEXIT_XSETBV = 55,
	VMX_VMEXIT_APIC_WRITE = 56,
	VMX_VMEXIT_RDRAND = 57,
	VMX_VMEXIT_INVPCID = 58,
	VMX_VMEXIT_VMFUNC = 59,
	// VMX_VMEXIT_RESERVED5-7
	VMX_VMEXIT_XSAVES = 63,
	VMX_VMEXIt_XRSTORS = 64
} VmxVmExit;

typedef enum VmxVmcsFields
{
	// 16bit control fields
	VMX_VMCS_VPID = 0x0000,
	VMX_VMCS_POSTED_INT_NOTIFICATION_VECTOR	= 0x0002,
	VMX_VMCS_EPTP_INDEX = 0x0004
} VmxVmcsFields;


static bool TryEnableVmxFeature(void)
{
	uint64_t featureCtrlMsr;
	bool result;

	featureCtrlMsr = ArchReadMsr(IA32_FEATURE_CTL);
	if ((featureCtrlMsr & 5) != 1)
	{
		featureCtrlMsr |= 5;
		ArchWriteMsr(IA32_FEATURE_CTL, featureCtrlMsr);
		result = true;
	}
	else
	{
		result = false;
	} 
	return true;
}

static bool DetectVmxSupportFunc(void* data)
{
	CpuidRegs cpuidRegs;

	(void)data;

	// VMX support is CPUID.1:ECX.VMX[bit 5]
	ArchCpuid(1, &cpuidRegs);
	if ((cpuidRegs.ecx & (1 << 5)) == 0)
	{
		PlatformPrint("VMX is not supported on this CPU.");
		return false;
	}	

	// Ensure that VMX is enabled by the BIOS
	if (!TryEnableVmxFeature())
	{
		PlatformPrint("VMX is disabled by the BIOS.");
		return false;
	}

	return true;
}

bool DetectVmxSupport(void)
{
	PlatformPrint("Detecting VMX support.");
	if (!PlatformRunOnAllCpus(DetectVmxSupportFunc, NULL))
		return false;
	PlatformPrint("VMX is supported and enabled in the BIOS.");
	return true;
}
