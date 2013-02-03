/*
Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in 
the Software without restriction, including without limitation the rights to 
use, copy, modify, merge, publish, distribute, and/or sell copies of the 
Software, and to permit persons to whom the Software is furnished to do so.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT OF THIRD PARTY RIGHTS. IN NO EVENT 
SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, OR ANY SPECIAL INDIRECT OR 
CONSEQUENTIAL DAMAGES, OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, 
DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS
ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS 
SOFTWARE.

*/
/*
 * Written by Joshua Scoggins 
 * Started on February 3, 2013
 *
 * Contains workaround methods for features missing from Android's bionic
 */
#ifndef _BIONIC_WORKAROUNDS_H
#define _BIONIC_WORKAROUNDS_H
/* 
 * Calls the Java version of setlocale. This is necessary since bionic doesn't
 * actually implement setlocale. We use the environment as a way to get the JNI
 * context out so it's usable.
 */
char* bionic_setlocale(void* theEnv, int value, char* value);
#endif
