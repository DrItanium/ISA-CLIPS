#include "setup.h"
#include "argacces.h"
#include "envrnmnt.h"
#include "extnfunc.h"
#include "router.h"

#include "binary_operations.h"

extern void BinaryOperationsFunctionDefinitions(void* theEnv) {
	EnvDefineFunction2(theEnv, "right-shift", 'i', PTIEF RightShiftFunction, "RightShiftFunction", "22i");
	EnvDefineFunction2(theEnv, "left-shift", 'i', PTIEF LeftShiftFunction, "LeftShiftFunction", "22i");
	EnvDefineFunction2(theEnv, "binary-and", 'i', PTIEF BinaryAndFunction, "BinaryAndFunction", "22i");
	EnvDefineFunction2(theEnv, "binary-or", 'i', PTIEF BinaryOrFunction, "BinaryOrFunction", "22i");
	EnvDefineFunction2(theEnv, "binary-xor", 'i', PTIEF BinaryXorFunction, "BinaryXorFunction", "22i");
	EnvDefineFunction2(theEnv, "binary-not", 'i', PTIEF BinaryNotFunction, "BinaryNotFunction", "11i");
   EnvDefineFunction2(theEnv, "slice", 'i', PTIEF SliceFunction, "SliceFunction", "33i");
}
//use unsigned long long to ensure that logical shift is used instead of
//arithmetic shift
typedef unsigned long long longlong;
typedef long long clipslonglong;
extern long long RightShiftFunction(void* theEnv) {
	DATA_OBJECT arg0, arg1;
	longlong a, b;
	if(EnvArgCountCheck(theEnv,"right-shift",EXACTLY,2) == -1) {
		return 0LL;
	} 
	if(EnvArgTypeCheck(theEnv,"right-shift",1,INTEGER,&arg0) == FALSE) {
		return 0LL;
	}

	if(EnvArgTypeCheck(theEnv,"right-shift",2,INTEGER,&arg1) == FALSE) {
		return 0LL;
	}
	a = DOToLong(arg0);
	b = DOToLong(arg1);
	return (longlong)(a >> b);
}
extern long long LeftShiftFunction(void* theEnv) {

	DATA_OBJECT arg0, arg1;
	longlong a, b;
	if(EnvArgCountCheck(theEnv,"left-shift",EXACTLY,2) == -1) {
		return 0LL;
	} 
	if(EnvArgTypeCheck(theEnv,"left-shift",1,INTEGER,&arg0) == FALSE) {
		return 0LL;
	}

	if(EnvArgTypeCheck(theEnv,"left-shift",2,INTEGER,&arg1) == FALSE) {
		return 0LL;
	}
	a = DOToLong(arg0);
	b = DOToLong(arg1);
	return (longlong)(a << b);

}
extern long long BinaryAndFunction(void* theEnv) {
	DATA_OBJECT arg0, arg1;
	longlong a, b;
	if(EnvArgCountCheck(theEnv,"binary-and",EXACTLY,2) == -1) {
		return 0LL;
	} 
	if(EnvArgTypeCheck(theEnv,"binary-and",1,INTEGER,&arg0) == FALSE) {
		return 0LL;
	}

	if(EnvArgTypeCheck(theEnv,"binary-and",2,INTEGER,&arg1) == FALSE) {
		return 0LL;
	}
	a = DOToLong(arg0);
	b = DOToLong(arg1);
	return (longlong)(a & b);

}
extern long long BinaryOrFunction(void* theEnv) {
	DATA_OBJECT arg0, arg1;
	longlong a, b;
	if(EnvArgCountCheck(theEnv,"binary-or",EXACTLY,2) == -1) {
		return 0LL;
	} 
	if(EnvArgTypeCheck(theEnv,"binary-or",1,INTEGER,&arg0) == FALSE) {
		return 0LL;
	}

	if(EnvArgTypeCheck(theEnv,"binary-or",2,INTEGER,&arg1) == FALSE) {
		return 0LL;
	}
	a = DOToLong(arg0);
	b = DOToLong(arg1);
	return (longlong)(a | b);

}
extern long long BinaryXorFunction(void* theEnv) {
	DATA_OBJECT arg0, arg1;
	longlong a, b;
	if(EnvArgCountCheck(theEnv,"binary-xor",EXACTLY,2) == -1) {
		return 0LL;
	} 
	if(EnvArgTypeCheck(theEnv,"binary-xor",1,INTEGER,&arg0) == FALSE) {
		return 0LL;
	}

	if(EnvArgTypeCheck(theEnv,"binary-xor",2,INTEGER,&arg1) == FALSE) {
		return 0LL;
	}
	a = DOToLong(arg0);
	b = DOToLong(arg1);
	return (longlong)(a ^ b);
}
extern long long BinaryNotFunction(void* theEnv) {
	DATA_OBJECT arg0;
	longlong a;
	if(EnvArgCountCheck(theEnv,"binary-not",EXACTLY,1) == -1) {
		return 0LL;
	} 
	if(EnvArgTypeCheck(theEnv,"binary-not",1,INTEGER,&arg0) == FALSE) {
		return 0LL;
	}
	a = DOToLong(arg0);
	return (longlong)(~a);
}
extern long long SliceFunction(void* theEnv) {
   DATA_OBJECT arg0, arg1, arg2;
   longlong w, s, e;
   if(EnvArgCountCheck(theEnv, "slice", EXACTLY, 3) == -1) {
      return 0LL;
   }
   if(EnvArgTypeCheck(theEnv, "slice", 1, INTEGER, &arg0) == FALSE) {
      return 0LL;
   }
   if(EnvArgTypeCheck(theEnv, "slice", 2, INTEGER, &arg1) == FALSE) {
      return 0LL;
   }
   if(EnvArgTypeCheck(theEnv, "slice", 3, INTEGER, &arg2) == FALSE) {
      return 0LL;
   }
    
   w = DOToLong(arg0);
   s = DOToLong(arg1);
   e = DOToLong(arg2);
   //TODO: fix this code so that it takes the underlying platform into account
   if(s == 0LL && e == 64LL) {
      return w;
   } else if(s >= 0LL && s <= 64LL && e >= 0LL && e <= 64LL && e > s) {
      longlong width, ff, fb;
#ifdef DEBUG
      longlong result;
#endif
      width = e - s;
      ff = 64LL - e;
      fb = 64LL - width;
#ifdef DEBUG
      result = (w << ff) >> fb; 
      printf("(%lld << %lld) >> %lld = %lld\n", w, ff, fb, result);
      return (clipslonglong)result;
#else
      return (clipslonglong)((w << ff) >> fb);
#endif
   } else {
      return 0LL;
   }
}
