#include <jni.h>
#include "clips.h"
#include "bionic-workarounds.h"

char* bionic_setlocale(void* theEnv, int value, char* input) {
	JNIEnv* env = (JNIEnv*)GetEnvironmentContext(theEnv);	
		
}
