#ifndef CLIPS_CPUINTERFACE_H 
#define CLIPS_CPUINTERFACE_H 

extern void RegisterCPUFeaturesFunctions(void *theEnv);
//Begin Android Specific Functions
//TODO: Insert defines if we are on an android platform
extern void* Android_GetCPUArch(void* theEnv);
extern int Android_GetCPUCount(void* theEnv);
extern void* Android_IsARMCPU(void* theEnv);
extern void* Android_ARMCPUIsV7(void* theEnv);
extern void* Android_ARMCPUSupportsNEON(void* theEnv);
extern void* Android_ARMCPUSupportsVFPv3(void* theEnv);
extern void* Android_IsMIPSCPU(void* theEnv);
extern void* Android_IsX86CPU(void* theEnv);
extern void* Android_X86CPUSupportsSSSE3(void* theEnv);
extern void* Android_X86CPUSupportsPOPCNT(void* theEnv);
extern void* Android_X86CPUSupportsMOVBE(void* theEnv);

#endif
