#ifndef CLIPS_CPUINTERFACE_H 
#define CLIPS_CPUINTERFACE_H 

extern void RegisterCPUFeaturesFunctions(void *theEnv);
//Begin Android Specific Functions
//TODO: Insert defines if we are on an android platform
extern void* AndroidGetCPUArch(void* theEnv);
extern void* AndroidIsARMCPU(void* theEnv);
extern void* AndroidIsARMV7CPU(void* theEnv);
extern void* AndroidCPUSupportsNEON(void* theEnv);
extern void* AndroidIsMIPSCPU(void* theEnv);
extern void* AndroidIsX86CPU(void* theEnv);

#endif
