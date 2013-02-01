   /*******************************************************/
   /*      "C" Language Integrated Production System      */
   /*                                                     */
   /*             CLIPS Version 6.30  10/19/06            */
   /*                                                     */
   /*                   DEVELOPER MODULE                  */
   /*******************************************************/

/*************************************************************/
/* Purpose: Provides routines useful for browsing various    */
/*   data structures. The functions are provided for         */
/*   development use.                                        */
/*                                                           */
/* Principal Programmer(s):                                  */
/*      Gary D. Riley                                        */
/*                                                           */
/* Contributing Programmer(s):                               */
/*                                                           */
/* Revision History:                                         */
/*                                                           */
/*      6.24: Converted INSTANCE_PATTERN_MATCHING to         */
/*            DEFRULE_CONSTRUCT.                             */
/*                                                           */
/*      6.30: Added support for hashed alpha memories.       */
/*                                                           */
/*************************************************************/

#define _DEVELOPR_SOURCE_

#include <stdio.h>
#define _STDIO_INCLUDED_

#include "setup.h"

#include "argacces.h"
#include "envrnmnt.h"
#include "extnfunc.h"
#include "inscom.h"
#include "modulutl.h"
#include "router.h"
#include "utility.h"

#if DEFRULE_CONSTRUCT && DEFTEMPLATE_CONSTRUCT
#include "tmpltdef.h"
#include "factbld.h"
#include "facthsh.h"
#endif

#if DEFRULE_CONSTRUCT && OBJECT_SYSTEM
#include "classcom.h"
#include "classfun.h"
#include "objrtmch.h"
#endif
#if OBJECT_SYSTEM
#include "insfun.h"
#endif

#include "developr.h"

#if DEVELOPER

#if DEFRULE_CONSTRUCT && OBJECT_SYSTEM
static void PrintOPNLevel(void *theEnv,OBJECT_PATTERN_NODE *,char *,int);
#endif

/**************************************************/
/* DeveloperCommands: Sets up developer commands. */
/**************************************************/
globle void DeveloperCommands(
  void *theEnv)
  {
#if ! RUN_TIME
   EnvDefineFunction2(theEnv,(char*)"primitives-info",'v', PTIEF PrimitiveTablesInfo,(char*)"PrimitiveTablesInfo",(char*)"00");
   EnvDefineFunction2(theEnv,(char*)"primitives-usage",'v', PTIEF PrimitiveTablesUsage,(char*)"PrimitiveTablesUsage",(char*)"00");
   EnvDefineFunction2(theEnv,(char*)"enable-gc-heuristics",'v', PTIEF EnableGCHeuristics,(char*)"EnableGCHeuristics",(char*)"00");
   EnvDefineFunction2(theEnv,(char*)"disable-gc-heuristics",'v', PTIEF DisableGCHeuristics,(char*)"DisableGCHeuristics",(char*)"00");

#if DEFRULE_CONSTRUCT && DEFTEMPLATE_CONSTRUCT
   EnvDefineFunction2(theEnv,(char*)"show-fpn",'v', PTIEF ShowFactPatternNetwork,(char*)"ShowFactPatternNetwork",(char*)"11w");
   EnvDefineFunction2(theEnv,(char*)"show-fht",'v', PTIEF ShowFactHashTable,(char*)"ShowFactHashTable",(char*)"00");
#endif

#if DEFRULE_CONSTRUCT && OBJECT_SYSTEM
   EnvDefineFunction2(theEnv,(char*)"show-opn",'v',PTIEF PrintObjectPatternNetwork,
                   (char*)"PrintObjectPatternNetwork",(char*)"00");
#endif

#if OBJECT_SYSTEM
   EnvDefineFunction2(theEnv,(char*)"instance-table-usage",'v', PTIEF InstanceTableUsage,(char*)"InstanceTableUsage",(char*)"00");
#endif

#endif
  }

/******************************************************/
/* EnableGCHeuristics:      */
/******************************************************/
globle void EnableGCHeuristics(
  void *theEnv)
  {
   EnvArgCountCheck(theEnv,(char*)"enable-gc-heuristics",EXACTLY,0);
   SetGarbageCollectionHeuristics(theEnv,TRUE);
  }
  
/******************************************************/
/* DisableGCHeuristics:      */
/******************************************************/
globle void DisableGCHeuristics(
  void *theEnv)
  {
   EnvArgCountCheck(theEnv,(char*)"disable-gc-heuristics",EXACTLY,0);
   SetGarbageCollectionHeuristics(theEnv,FALSE);
  }

/******************************************************/
/* PrimitiveTablesInfo: Prints information about the  */
/*   symbol, float, integer, and bitmap tables.       */
/******************************************************/
globle void PrimitiveTablesInfo(
  void *theEnv)
  {
   unsigned long i;
   SYMBOL_HN **symbolArray, *symbolPtr;
   FLOAT_HN **floatArray, *floatPtr;
   INTEGER_HN **integerArray, *integerPtr;
   BITMAP_HN **bitMapArray, *bitMapPtr;
   unsigned long int symbolCount = 0, integerCount = 0;
   unsigned long int floatCount = 0, bitMapCount = 0;

   EnvArgCountCheck(theEnv,(char*)"primitives-info",EXACTLY,0);

   /*====================================*/
   /* Count entries in the symbol table. */
   /*====================================*/

   symbolArray = GetSymbolTable(theEnv);
   for (i = 0; i < SYMBOL_HASH_SIZE; i++)
     {
      for (symbolPtr = symbolArray[i]; symbolPtr != NULL; symbolPtr = symbolPtr->next)
        { symbolCount++; }
     }

   /*====================================*/
   /* Count entries in the integer table. */
   /*====================================*/

   integerArray = GetIntegerTable(theEnv);
   for (i = 0; i < INTEGER_HASH_SIZE; i++)
     {
      for (integerPtr = integerArray[i]; integerPtr != NULL; integerPtr = integerPtr->next)
        { integerCount++; }
     }

   /*====================================*/
   /* Count entries in the float table. */
   /*====================================*/

   floatArray = GetFloatTable(theEnv);
   for (i = 0; i < FLOAT_HASH_SIZE; i++)
     {
      for (floatPtr = floatArray[i]; floatPtr != NULL; floatPtr = floatPtr->next)
        { floatCount++; }
     }

   /*====================================*/
   /* Count entries in the bitmap table. */
   /*====================================*/

   bitMapArray = GetBitMapTable(theEnv);
   for (i = 0; i < BITMAP_HASH_SIZE; i++)
     {
      for (bitMapPtr = bitMapArray[i]; bitMapPtr != NULL; bitMapPtr = bitMapPtr->next)
        { bitMapCount++; }
     }

   /*========================*/
   /* Print the information. */
   /*========================*/

   EnvPrintRouter(theEnv,WDISPLAY,(char*)"Symbols: ");
   PrintLongInteger(theEnv,WDISPLAY,(long long) symbolCount);
   EnvPrintRouter(theEnv,WDISPLAY,(char*)"\n");
   EnvPrintRouter(theEnv,WDISPLAY,(char*)"Integers: ");
   PrintLongInteger(theEnv,WDISPLAY,(long long) integerCount);
   EnvPrintRouter(theEnv,WDISPLAY,(char*)"\n");
   EnvPrintRouter(theEnv,WDISPLAY,(char*)"Floats: ");
   PrintLongInteger(theEnv,WDISPLAY,(long long) floatCount);
   EnvPrintRouter(theEnv,WDISPLAY,(char*)"\n");
   EnvPrintRouter(theEnv,WDISPLAY,(char*)"BitMaps: ");
   PrintLongInteger(theEnv,WDISPLAY,(long long) bitMapCount);
   EnvPrintRouter(theEnv,WDISPLAY,(char*)"\n");
   /*
   EnvPrintRouter(theEnv,WDISPLAY,(char*)"Ephemerals: ");
   PrintLongInteger(theEnv,WDISPLAY,(long long) EphemeralSymbolCount());
   EnvPrintRouter(theEnv,WDISPLAY,(char*)"\n");
   */
  }
  
#define COUNT_SIZE 21

/******************************************************/
/* PrimitiveTablesUsage: Prints information about the  */
/*   symbol, float, integer, and bitmap tables.       */
/******************************************************/
globle void PrimitiveTablesUsage(
  void *theEnv)
  {
   unsigned long i;
   int symbolCounts[COUNT_SIZE], floatCounts[COUNT_SIZE];
   SYMBOL_HN **symbolArray, *symbolPtr;
   FLOAT_HN **floatArray, *floatPtr;
   unsigned long int symbolCount, totalSymbolCount = 0;
   unsigned long int floatCount, totalFloatCount = 0;

   EnvArgCountCheck(theEnv,(char*)"primitives-usage",EXACTLY,0);

   for (i = 0; i < 21; i++)
     {
      symbolCounts[i] = 0;
      floatCounts[i] = 0; 
     }
     
   /*====================================*/
   /* Count entries in the symbol table. */
   /*====================================*/

   symbolArray = GetSymbolTable(theEnv);
   for (i = 0; i < SYMBOL_HASH_SIZE; i++)
     {
      symbolCount = 0;
      for (symbolPtr = symbolArray[i]; symbolPtr != NULL; symbolPtr = symbolPtr->next)
        { 
         symbolCount++;
         totalSymbolCount++;
        }
           
      if (symbolCount < (COUNT_SIZE - 1))
        { symbolCounts[symbolCount]++; }
      else
        { symbolCounts[COUNT_SIZE - 1]++; }
     }

   /*===================================*/
   /* Count entries in the float table. */
   /*===================================*/
   
   floatArray = GetFloatTable(theEnv);
   for (i = 0; i < FLOAT_HASH_SIZE; i++)
     {
      floatCount = 0;
      for (floatPtr = floatArray[i]; floatPtr != NULL; floatPtr = floatPtr->next)
        { 
         floatCount++;
         totalFloatCount++;
        }
           
      if (floatCount < (COUNT_SIZE - 1))
        { floatCounts[floatCount]++; }
      else
        { floatCounts[COUNT_SIZE - 1]++; }
     }


   /*========================*/
   /* Print the information. */
   /*========================*/

   EnvPrintRouter(theEnv,WDISPLAY,(char*)"Total Symbols: ");
   PrintLongInteger(theEnv,WDISPLAY,(long long) totalSymbolCount);
   EnvPrintRouter(theEnv,WDISPLAY,(char*)"\n");
   for (i = 0; i < COUNT_SIZE; i++)
     {
      PrintLongInteger(theEnv,WDISPLAY,(long long) i);
      EnvPrintRouter(theEnv,WDISPLAY,(char*)" ");
      PrintLongInteger(theEnv,WDISPLAY,(long long) symbolCounts[i]);
      EnvPrintRouter(theEnv,WDISPLAY,(char*)"\n");
     }

   EnvPrintRouter(theEnv,WDISPLAY,(char*)"\nTotal Floats: ");
   PrintLongInteger(theEnv,WDISPLAY,(long long) totalFloatCount);
   EnvPrintRouter(theEnv,WDISPLAY,(char*)"\n");
   for (i = 0; i < COUNT_SIZE; i++)
     {
      PrintLongInteger(theEnv,WDISPLAY,(long long) i);
      EnvPrintRouter(theEnv,WDISPLAY,(char*)" ");
      PrintLongInteger(theEnv,WDISPLAY,(long long) floatCounts[i]);
      EnvPrintRouter(theEnv,WDISPLAY,(char*)"\n");
     }

  }

#if DEFRULE_CONSTRUCT && DEFTEMPLATE_CONSTRUCT

/*******************************************************/
/* ShowFactPatternNetwork: Command for displaying the  */
/*   fact pattern network for a specified deftemplate. */
/*******************************************************/
globle void ShowFactPatternNetwork(
  void *theEnv)
  {
   struct factPatternNode *patternPtr;
   struct deftemplate *theDeftemplate;
   char *theName;
   int depth = 0, i;

   theName = GetConstructName(theEnv,(char*)"show-fpn",(char*)"template name");
   if (theName == NULL) return;

   theDeftemplate = (struct deftemplate *) EnvFindDeftemplate(theEnv,theName);
   if (theDeftemplate == NULL) return;

   patternPtr = theDeftemplate->patternNetwork;
   while (patternPtr != NULL)
     {
      for (i = 0; i < depth; i++) EnvPrintRouter(theEnv,WDISPLAY,(char*)" ");
      if (patternPtr->header.singlefieldNode) EnvPrintRouter(theEnv,WDISPLAY,(char*)"SF   ");
      else if (patternPtr->header.multifieldNode)
        {
         EnvPrintRouter(theEnv,WDISPLAY,(char*)"MF");
         if (patternPtr->header.endSlot) EnvPrintRouter(theEnv,WDISPLAY,(char*)")");
         else EnvPrintRouter(theEnv,WDISPLAY,(char*)"*");
         PrintLongInteger(theEnv,WDISPLAY,(long long) patternPtr->leaveFields);
         EnvPrintRouter(theEnv,WDISPLAY,(char*)" ");
        }

      EnvPrintRouter(theEnv,WDISPLAY,(char*)"Slot: ");

      PrintLongInteger(theEnv,WDISPLAY,(long long) patternPtr->whichSlot);
      EnvPrintRouter(theEnv,WDISPLAY,(char*)" Field: ");
      PrintLongInteger(theEnv,WDISPLAY,(long long) patternPtr->whichField);
      EnvPrintRouter(theEnv,WDISPLAY,(char*)" Expression: ");
      if (patternPtr->networkTest == NULL) EnvPrintRouter(theEnv,WDISPLAY,(char*)"None");
      else PrintExpression(theEnv,WDISPLAY,patternPtr->networkTest);
      EnvPrintRouter(theEnv,WDISPLAY,(char*)" RightHash: ");
      if (patternPtr->header.rightHash == NULL) EnvPrintRouter(theEnv,WDISPLAY,(char*)"None");
      else PrintExpression(theEnv,WDISPLAY,patternPtr->header.rightHash);
      EnvPrintRouter(theEnv,WDISPLAY,(char*)"\n");

      if (patternPtr->nextLevel == NULL)
        {
         while (patternPtr->rightNode == NULL)
           {
            patternPtr = patternPtr->lastLevel;
            depth--;
            if (patternPtr == NULL) return;
           }
         patternPtr = patternPtr->rightNode;
        }
      else
        {
         patternPtr = patternPtr->nextLevel;
         depth++;
        }
     }
  }

#endif

#if DEFRULE_CONSTRUCT && OBJECT_SYSTEM

/***************************************************
  NAME         : PrintObjectPatternNetwork
  DESCRIPTION  : Displays an indented printout of
                 the object pattern network
  INPUTS       : None
  RETURNS      : Nothing useful
  SIDE EFFECTS : Object pattern network displayed
  NOTES        : None
 ***************************************************/
globle void PrintObjectPatternNetwork(
  void *theEnv)
  {
   char indentbuf[80];

   indentbuf[0] = '\0';
   PrintOPNLevel(theEnv,ObjectNetworkPointer(theEnv),indentbuf,0);
  }

/**********************************************************
  NAME         : PrintOPNLevel
  DESCRIPTION  : Recursivley prints object pattern network
  INPUTS       : 1) The current object pattern network node
                 2) A buffer holding preceding indentation
                    text showing the level in the tree
                 3) The length of the indentation text
  RETURNS      : Nothing useful
  SIDE EFFECTS : Pattern nodes recursively printed
  NOTES        : None
 **********************************************************/
static void PrintOPNLevel(
  void *theEnv,
  OBJECT_PATTERN_NODE *pptr,
  char *indentbuf,
  int ilen)
  {
   CLASS_BITMAP *cbmp;
   SLOT_BITMAP *sbmp;
   register unsigned i;
   OBJECT_PATTERN_NODE *uptr;
   OBJECT_ALPHA_NODE *alphaPtr;

   while (pptr != NULL)
     {
      EnvPrintRouter(theEnv,WDISPLAY,indentbuf);
      if (pptr->alphaNode != NULL)
        EnvPrintRouter(theEnv,WDISPLAY,(char*)"+");
      EnvPrintRouter(theEnv,WDISPLAY,ValueToString(FindIDSlotName(theEnv,pptr->slotNameID)));
      EnvPrintRouter(theEnv,WDISPLAY,(char*)" (");
      PrintLongInteger(theEnv,WDISPLAY,(long long) pptr->slotNameID);
      EnvPrintRouter(theEnv,WDISPLAY,(char*)") ");
      EnvPrintRouter(theEnv,WDISPLAY,pptr->endSlot ? (char*)"EPF#" : (char*)"PF#");
      PrintLongInteger(theEnv,WDISPLAY,(long long) pptr->whichField);
      EnvPrintRouter(theEnv,WDISPLAY,(char*)" ");
      EnvPrintRouter(theEnv,WDISPLAY,pptr->multifieldNode ? (char*)"$? " : (char*) "? ");
      if (pptr->networkTest != NULL)
        PrintExpression(theEnv,WDISPLAY,pptr->networkTest);
      EnvPrintRouter(theEnv,WDISPLAY,(char*)"\n");
      alphaPtr = pptr->alphaNode;
      while (alphaPtr != NULL)
        {
         EnvPrintRouter(theEnv,WDISPLAY,indentbuf);
         EnvPrintRouter(theEnv,WDISPLAY,(char*)"     Classes:");
         cbmp = (CLASS_BITMAP *) ValueToBitMap(alphaPtr->classbmp);
         for (i = 0 ; i <= cbmp->maxid ; i++)
           if (TestBitMap(cbmp->map,i))
             {
              EnvPrintRouter(theEnv,WDISPLAY,(char*)" ");
              EnvPrintRouter(theEnv,WDISPLAY,EnvGetDefclassName(theEnv,(void *) DefclassData(theEnv)->ClassIDMap[i]));
             }
         if (alphaPtr->slotbmp != NULL)
           {
            sbmp = (SLOT_BITMAP *) ValueToBitMap(pptr->alphaNode->slotbmp);
            EnvPrintRouter(theEnv,WDISPLAY,(char*)" *** Slots:");
            for (i = NAME_ID ; i <= sbmp->maxid ; i++)
              if (TestBitMap(sbmp->map,i))
                {
                 for (uptr = pptr ; uptr != NULL ; uptr  = uptr->lastLevel)
                   if ((unsigned)(uptr->slotNameID) == i)
                     break;
                 if (uptr == NULL)
                   {
                    EnvPrintRouter(theEnv,WDISPLAY,(char*)" ");
                    EnvPrintRouter(theEnv,WDISPLAY,ValueToString(FindIDSlotName(theEnv,i)));
                   }
                }
           }
         if (alphaPtr->header.rightHash != NULL)
           {
            EnvPrintRouter(theEnv,WDISPLAY,(char*)" RH: ");
            PrintExpression(theEnv,WDISPLAY,alphaPtr->header.rightHash);
           }

         EnvPrintRouter(theEnv,WDISPLAY,(char*)"\n");
         alphaPtr = alphaPtr->nxtInGroup;
        }
      indentbuf[ilen++] = (char) ((pptr->rightNode != NULL) ? '|' : ' ');
      indentbuf[ilen++] = ' ';
      indentbuf[ilen++] = ' ';
      indentbuf[ilen] = '\0';
      PrintOPNLevel(theEnv,pptr->nextLevel,indentbuf,ilen);
      ilen -= 3;
      indentbuf[ilen] = '\0';
      pptr = pptr->rightNode;
     }
  }

#endif

#if OBJECT_SYSTEM

/******************************************************/
/* InstanceTableUsage: Prints information about the  */
/*   instances in the instance hash table.       */
/******************************************************/
globle void InstanceTableUsage(
  void *theEnv)
  {
   unsigned long i;
   int instanceCounts[COUNT_SIZE];
   INSTANCE_TYPE *ins;
   unsigned long int instanceCount, totalInstanceCount = 0;

   EnvArgCountCheck(theEnv,(char*)"instance-table-usage",EXACTLY,0);

   for (i = 0; i < COUNT_SIZE; i++)
     { instanceCounts[i] = 0; }
     
   /*======================================*/
   /* Count entries in the instance table. */
   /*======================================*/

   for (i = 0; i < INSTANCE_TABLE_HASH_SIZE; i++)
     {
      instanceCount = 0;
      for (ins = InstanceData(theEnv)->InstanceTable[i]; ins != NULL; ins = ins->nxtHash)
        { 
         instanceCount++;
         totalInstanceCount++;
        }
           
      if (instanceCount < (COUNT_SIZE - 1))
        { instanceCounts[instanceCount]++; }
      else
        { instanceCounts[COUNT_SIZE - 1]++; }
     }

   /*========================*/
   /* Print the information. */
   /*========================*/

   EnvPrintRouter(theEnv,WDISPLAY,(char*)"Total Instances: ");
   PrintLongInteger(theEnv,WDISPLAY,(long long) totalInstanceCount);
   EnvPrintRouter(theEnv,WDISPLAY,(char*)"\n");
   for (i = 0; i < COUNT_SIZE; i++)
     {
      PrintLongInteger(theEnv,WDISPLAY,(long long) i);
      EnvPrintRouter(theEnv,WDISPLAY,(char*)" ");
      PrintLongInteger(theEnv,WDISPLAY,(long long) instanceCounts[i]);
      EnvPrintRouter(theEnv,WDISPLAY,(char*)"\n");
     }
  }
  
#endif

#endif

