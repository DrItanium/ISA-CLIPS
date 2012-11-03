#include "clips.h" 
#include "binary_operations.h"

//private definitions
typedef unsigned long long longlong;
typedef long long clipslonglong;

longlong Slice(longlong w, longlong s, longlong e);



extern void BinaryOperationsFunctionDefinitions(void* theEnv) {
	EnvDefineFunction2(theEnv, "right-shift", 'i', PTIEF RightShiftFunction, "RightShiftFunction", "22i");
	EnvDefineFunction2(theEnv, "left-shift", 'i', PTIEF LeftShiftFunction, "LeftShiftFunction", "22i");
	EnvDefineFunction2(theEnv, "binary-and", 'i', PTIEF BinaryAndFunction, "BinaryAndFunction", "22i");
	EnvDefineFunction2(theEnv, "binary-or", 'i', PTIEF BinaryOrFunction, "BinaryOrFunction", "22i");
	EnvDefineFunction2(theEnv, "binary-xor", 'i', PTIEF BinaryXorFunction, "BinaryXorFunction", "22i");
	EnvDefineFunction2(theEnv, "binary-not", 'i', PTIEF BinaryNotFunction, "BinaryNotFunction", "11i");
   EnvDefineFunction2(theEnv, "slice", 'i', PTIEF SliceFunction, "SliceFunction", "33i");
   EnvDefineFunction2(theEnv, "slice8", 'm', PTIEF Slice8Function, "Slice8Function", "11i");
   EnvDefineFunction2(theEnv, "slice4", 'm', PTIEF Slice4Function, "Slice4Function", "11i");
   EnvDefineFunction2(theEnv, "slice2", 'm', PTIEF Slice2Function, "Slice2Function", "11i");
}
//use unsigned long long to ensure that logical shift is used instead of
//arithmetic shift
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
longlong Slice(longlong w, longlong s, longlong e) {
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
      return result;
#else
      return ((w << ff) >> fb);
#endif
   } else {
      return 0LL;
   }
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
   return (clipslonglong)Slice(w,s,e);
}

#define SetMultifieldSlot(index, from, to) \
   SetMFType(multifield, index, INTEGER); \
   SetMFValue(multifield, index, EnvAddLong(theEnv, (clipslonglong)Slice(value, from, to)))

extern void Slice8Function(void* theEnv, DATA_OBJECT_PTR retVal) {
   DATA_OBJECT arg0;
   void* multifield;
   longlong value;
   if(EnvArgCountCheck(theEnv, "slice8", EXACTLY, 1) == -1) {
      EnvSetMultifieldErrorValue(theEnv, retVal);
      return;
   } 
   if(EnvArgTypeCheck(theEnv, "slice8", 1, INTEGER, &arg0) == FALSE) {
      EnvSetMultifieldErrorValue(theEnv, retVal);
      return;
   }
   value = DOToLong(arg0); 
   multifield = EnvCreateMultifield(theEnv, 8);
   SetMultifieldSlot(1, 0LL, 8LL);
   SetMultifieldSlot(2, 8LL, 16LL);
   SetMultifieldSlot(3, 16LL, 24LL);
   SetMultifieldSlot(4, 24LL, 32LL);
   SetMultifieldSlot(5, 32LL, 40LL);
   SetMultifieldSlot(6, 40LL, 48LL);
   SetMultifieldSlot(7, 48LL, 56LL);
   SetMultifieldSlot(8, 56LL, 64LL);
   
   SetpType(retVal, MULTIFIELD);
   SetpValue(retVal, multifield);

   SetpDOBegin(retVal, 1);
   SetpDOEnd(retVal, 8);
}

extern void Slice4Function(void* theEnv, DATA_OBJECT_PTR retVal) {
   DATA_OBJECT arg0;
   void* multifield;
   longlong value;
   if(EnvArgCountCheck(theEnv, "slice4", EXACTLY, 1) == -1) {
      EnvSetMultifieldErrorValue(theEnv, retVal);
      return;
   } 
   if(EnvArgTypeCheck(theEnv, "slice4", 1, INTEGER, &arg0) == FALSE) {
      EnvSetMultifieldErrorValue(theEnv, retVal);
      return;
   }
   value = DOToLong(arg0); 
   multifield = EnvCreateMultifield(theEnv, 4);
   SetMultifieldSlot(1, 0LL, 16LL);
   SetMultifieldSlot(2, 16LL, 32LL);
   SetMultifieldSlot(3, 32LL, 48LL);
   SetMultifieldSlot(4, 48LL, 64LL);
   
   SetpType(retVal, MULTIFIELD);
   SetpValue(retVal, multifield);

   SetpDOBegin(retVal, 1);
   SetpDOEnd(retVal, 4);
}
extern void Slice2Function(void* theEnv, DATA_OBJECT_PTR retVal) {
   DATA_OBJECT arg0;
   void* multifield;
   longlong value;
   if(EnvArgCountCheck(theEnv, "slice2", EXACTLY, 1) == -1) {
      EnvSetMultifieldErrorValue(theEnv, retVal);
      return;
   } 
   if(EnvArgTypeCheck(theEnv, "slice2", 1, INTEGER, &arg0) == FALSE) {
      EnvSetMultifieldErrorValue(theEnv, retVal);
      return;
   }
   value = DOToLong(arg0); 
   multifield = EnvCreateMultifield(theEnv, 2);
   SetMultifieldSlot(1, 0LL, 32LL);
   SetMultifieldSlot(2, 32LL, 64LL);
   
   SetpType(retVal, MULTIFIELD);
   SetpValue(retVal, multifield);

   SetpDOBegin(retVal, 1);
   SetpDOEnd(retVal, 2);
}

#undef SetMultifieldSlot
