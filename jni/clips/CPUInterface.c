#include "CPUInterface.h"
//Android code
#include <cpu-features.h>
#include "clips.h"

extern void RegisterCPUFeaturesFunctions(void* theEnv) {

}
#define msg(x) (char*)x
extern void* Android_GetCPUArch(void* theEnv) {
	if(EnvArgCountCheck(theEnv,msg("android-get-cpu-arch"),EXACTLY,0) == -1) {
		EnvPrintRouter(theEnv, msg("werror"), msg("ERROR: android-get-cpu-arch takes in zero arguments\n"));
		return FalseSymbol();
	} 
	AndroidCpuFamily cpu = android_getCpuFamily();
	switch(cpu) {
		case ANDROID_CPU_FAMILY_ARM:
			return msg("arm");
		case ANDROID_CPU_FAMILY_MIPS:
			return msg("mips");
		case ANDROID_CPU_FAMILY_X86:
			return msg("x86");
		default:
			return msg("Unknown");
	}
}
extern int Android_GetCPUCount(void* theEnv) {
	if(EnvArgCountCheck(theEnv,msg("android-get-cpu-count"),EXACTLY,0) == -1) {
		EnvPrintRouter(theEnv, msg("werror"), msg("ERROR: android-get-cpu-count takes in zero arguments\n"));
		return FalseSymbol();
	} 
	return android_getCpuCount();
}
extern void* Android_IsARMCPU(void* theEnv) {
	if(EnvArgCountCheck(theEnv,msg("android-is-arm-cpu"),EXACTLY,0) == -1) {
		EnvPrintRouter(theEnv, msg("werror"), msg("ERROR: android-is-arm-cpu takes in zero arguments\n"));
		return FalseSymbol();
	} 
	if(android_getCpuFamily() == ANDROID_CPU_FAMILY_ARM) {
		return TrueSymbol();
	} else {
		return FalseSymbol();
	}
}
extern void* Android_ARMCPUIsV7(void* theEnv) {
	if(EnvArgCountCheck(theEnv,msg("android-arm-cpu-is-v7"),EXACTLY,0) == -1) {
		EnvPrintRouter(theEnv, msg("werror"), msg("ERROR: android-arm-cpu-is-v7 takes in zero arguments\n"));
		return FalseSymbol();
	} 
	uint64_t features = android_getCpuFeatures();
	if((features & ANDROID_CPU_ARM_FEATURE_ARMv7) == 0) {
		return FalseSymbol();
	} else {
		return TrueSymbol();
	}
}
extern void* Android_ARMCPUSupportsNEON(void* theEnv) {
	if(EnvArgCountCheck(theEnv,msg("android-arm-cpu-supports-neon"),EXACTLY,0) == -1) {
		EnvPrintRouter(theEnv, msg("werror"), msg("ERROR: android-arm-cpu-supports-neon takes in zero arguments\n"));
		return FalseSymbol();
	} 
	uint64_t features = android_getCpuFeatures();
	if((features & ANDROID_CPU_ARM_FEATURE_NEON) == 0) {
		return FalseSymbol();
	} else {
		return TrueSymbol();
	}
}
extern void* Android_ARMCPUSupportsVFPv3(void* theEnv) {
	if(EnvArgCountCheck(theEnv,msg("android-arm-cpu-supports-vfpv3"),EXACTLY,0) == -1) {
		EnvPrintRouter(theEnv, msg("werror"), msg("ERROR: android-arm-cpu-supports-vfpv3 takes in zero arguments\n"));
		return FalseSymbol();
	} 
	uint64_t features = android_getCpuFeatures();
	if((features & ANDROID_CPU_ARM_FEATURE_VFPv3) == 0) {
		return FalseSymbol();
	} else {
		return TrueSymbol();
	}

}
extern void* Android_IsMIPSCPU(void* theEnv) {

	if(EnvArgCountCheck(theEnv,msg("android-is-mips-cpu"),EXACTLY,0) == -1) {
		EnvPrintRouter(theEnv, msg("werror"), msg("ERROR: android-is-mips-cpu takes in zero arguments\n"));
		return FalseSymbol();
	} 
	if(android_getCpuFamily() == ANDROID_CPU_FAMILY_MIPS) {
		return TrueSymbol();
	} else {
		return FalseSymbol();
	}
}
extern void* Android_IsX86CPU(void* theEnv) {

	if(EnvArgCountCheck(theEnv,msg("android-is-x86-cpu"),EXACTLY,0) == -1) {
		EnvPrintRouter(theEnv, msg("werror"), msg("ERROR: android-is-x86-cpu takes in zero arguments\n"));
		return FalseSymbol();
	} 
	if(android_getCpuFamily() == ANDROID_CPU_FAMILY_X86) {
		return TrueSymbol();
	} else {
		return FalseSymbol();
	}
}
extern void* Android_X86CPUSupportsSSSE3(void* theEnv) {
	if(EnvArgCountCheck(theEnv,msg("android-x86-cpu-supports-ssse3"),EXACTLY,0) == -1) {
		EnvPrintRouter(theEnv, msg("werror"), msg("ERROR: android-x86-cpu-supports-ssse3 takes in zero arguments\n"));
		return FalseSymbol();
	} 
	uint64_t features = android_getCpuFeatures();
	if((features & ANDROID_CPU_X86_FEATURE_SSSE3) == 0) {
		return FalseSymbol();
	} else {
		return TrueSymbol();
	}

}
extern void* Android_X86CPUSupportsPOPCNT(void* theEnv) {
	if(EnvArgCountCheck(theEnv,msg("android-x86-cpu-supports-popcnt"),EXACTLY,0) == -1) {
		EnvPrintRouter(theEnv, msg("werror"), msg("ERROR: android-x86-cpu-supports-popcnt takes in zero arguments\n"));
		return FalseSymbol();
	} 
	uint64_t features = android_getCpuFeatures();
	if((features & ANDROID_CPU_X86_FEATURE_POPCNT) == 0) {
		return FalseSymbol();
	} else {
		return TrueSymbol();
	}

}
extern void* Android_X86CPUSupportsMOVBE(void* theEnv) {
	if(EnvArgCountCheck(theEnv,msg("android-x86-cpu-supports-movbe"),EXACTLY,0) == -1) {
		EnvPrintRouter(theEnv, msg("werror"), msg("ERROR: android-x86-cpu-supports-movbe takes in zero arguments\n"));
		return FalseSymbol();
	} 
	uint64_t features = android_getCpuFeatures();
	if((features & ANDROID_CPU_X86_FEATURE_MOVBE) == 0) {
		return FalseSymbol();
	} else {
		return TrueSymbol();
	}
}
#undef msg
