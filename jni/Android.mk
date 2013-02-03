LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := clips 
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/clips
LOCAL_SRC_FILES := clips/agenda.c clips/analysis.c clips/argacces.c clips/binary_operations.c clips/bload.c \
clips/bmathfun.c clips/bsave.c clips/classcom.c clips/classexm.c clips/classfun.c \
clips/classinf.c clips/classini.c clips/classpsr.c clips/clips_Environment.c clips/clsltpsr.c \
clips/commline.c clips/conscomp.c clips/constrct.c clips/constrnt.c clips/crstrtgy.c \
clips/cstrcbin.c clips/cstrccom.c clips/cstrcpsr.c clips/cstrnbin.c clips/cstrnchk.c \
clips/cstrncmp.c clips/cstrnops.c clips/cstrnpsr.c clips/cstrnutl.c clips/default.c \
clips/defins.c clips/developr.c clips/dffctbin.c clips/dffctbsc.c clips/dffctcmp.c \
clips/dffctdef.c clips/dffctpsr.c clips/dffnxbin.c clips/dffnxcmp.c clips/dffnxexe.c \
clips/dffnxfun.c clips/dffnxpsr.c clips/dfinsbin.c clips/dfinscmp.c clips/drive.c \
clips/edbasic.c clips/edmain.c clips/edmisc.c clips/edstruct.c clips/edterm.c \
clips/emathfun.c clips/engine.c clips/envrnmnt.c clips/evaluatn.c clips/expressn.c \
clips/exprnbin.c clips/exprnops.c clips/exprnpsr.c clips/extnfunc.c clips/factbin.c \
clips/factbld.c clips/factcmp.c clips/factcom.c clips/factfun.c clips/factgen.c \
clips/facthsh.c clips/factlhs.c clips/factmch.c clips/factmngr.c clips/factprt.c \
clips/factqpsr.c clips/factqury.c clips/factrete.c clips/factrhs.c clips/filecom.c  \
clips/filertr.c clips/generate.c clips/genrcbin.c clips/genrccmp.c clips/genrccom.c \
clips/genrcexe.c clips/genrcfun.c clips/genrcpsr.c clips/globlbin.c clips/globlbsc.c \
clips/globlcmp.c clips/globlcom.c clips/globldef.c clips/globlpsr.c clips/immthpsr.c \
clips/incrrset.c clips/inherpsr.c clips/inscom.c clips/insfile.c clips/insfun.c \
clips/insmngr.c clips/insmoddp.c clips/insmult.c clips/inspsr.c clips/insquery.c \
clips/insqypsr.c clips/iofun.c clips/lgcldpnd.c clips/main.c clips/memalloc.c \
clips/miscfun.c clips/modulbin.c clips/modulbsc.c clips/modulcmp.c clips/moduldef.c \
clips/modulpsr.c clips/modulutl.c clips/msgcom.c clips/msgfun.c clips/msgpass.c \
clips/msgpsr.c clips/multifld.c clips/multifun.c clips/objbin.c clips/objcmp.c \
clips/objrtbin.c clips/objrtbld.c clips/objrtcmp.c clips/objrtfnx.c clips/objrtgen.c \
clips/objrtmch.c clips/parsefun.c clips/pattern.c clips/pprint.c clips/prccode.c \
clips/prcdrfun.c clips/prcdrpsr.c clips/prdctfun.c clips/prntutil.c clips/proflfun.c \
clips/reorder.c clips/reteutil.c clips/retract.c clips/router.c clips/rulebin.c \
clips/rulebld.c clips/rulebsc.c clips/rulecmp.c clips/rulecom.c clips/rulecstr.c \
clips/ruledef.c clips/ruledlt.c clips/rulelhs.c clips/rulepsr.c clips/scanner.c \
clips/sortfun.c clips/strngfun.c clips/strngrtr.c clips/symblbin.c clips/symblcmp.c \
clips/symbol.c clips/sysdep.c clips/textpro.c clips/tmpltbin.c clips/tmpltbsc.c \
clips/tmpltcmp.c clips/tmpltdef.c clips/tmpltfun.c clips/tmpltlhs.c clips/tmpltpsr.c \
clips/tmpltrhs.c clips/tmpltutl.c clips/userdata.c clips/userfunctions.c clips/utility.c \
clips/watch.c clips/bionic-workarounds.c

include $(BUILD_SHARED_LIBRARY)
