LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := clips 
LOCAL_SRC_FILES := agenda.c analysis.c argacces.c binary_operations.c bload.c bmathfun.c bsave.c \
classcom.c classexm.c classfun.c classinf.c classini.c classpsr.c clsltpsr.c commline.c conscomp.c \
constrct.c constrnt.c crstrtgy.c cstrcbin.c cstrccom.c cstrcpsr.c cstrnbin.c cstrnchk.c cstrncmp.c \
cstrnops.c cstrnpsr.c cstrnutl.c default.c defins.c developr.c dffctbin.c dffctbsc.c dffctcmp.c \
dffctdef.c dffctpsr.c dffnxbin.c dffnxcmp.c dffnxexe.c dffnxfun.c dffnxpsr.c dfinsbin.c dfinscmp.c \
drive.c edbasic.c edmain.c edmisc.c edstruct.c edterm.c emathfun.c engine.c envrnmnt.c evaluatn.c \
expressn.c exprnbin.c exprnops.c exprnpsr.c extnfunc.c factbin.c factbld.c factcmp.c factcom.c \
factfun.c factgen.c facthsh.c factlhs.c factmch.c factmngr.c factprt.c factqpsr.c factqury.c \
factrete.c factrhs.c filecom.c filertr.c generate.c genrcbin.c genrccmp.c genrccom.c genrcexe.c \
genrcfun.c genrcpsr.c globlbin.c globlbsc.c globlcmp.c globlcom.c globldef.c globlpsr.c \
immthpsr.c incrrset.c inherpsr.c inscom.c insfile.c insfun.c insmngr.c insmoddp.c insmult.c \
inspsr.c insquery.c insqypsr.c iofun.c lgcldpnd.c main.c memalloc.c miscfun.c modulbin.c \
modulbsc.c modulcmp.c moduldef.c modulpsr.c modulutl.c msgcom.c msgfun.c msgpass.c msgpsr.c \
multifld.c multifun.c objbin.c objcmp.c objrtbin.c objrtbld.c objrtcmp.c objrtfnx.c objrtgen.c \
objrtmch.c parsefun.c pattern.c pprint.c prccode.c prcdrfun.c prcdrpsr.c prdctfun.c prntutil.c \
proflfun.c reorder.c reteutil.c retract.c router.c rulebin.c rulebld.c rulebsc.c rulecmp.c \
rulecom.c rulecstr.c ruledef.c ruledlt.c rulelhs.c rulepsr.c scanner.c sortfun.c strngfun.c \
strngrtr.c symblbin.c symblcmp.c symbol.c sysdep.c textpro.c tmpltbin.c tmpltbsc.c tmpltcmp.c \
tmpltdef.c tmpltfun.c tmpltlhs.c tmpltpsr.c tmpltrhs.c tmpltutl.c userdata.c userfunctions.c \
utility.c watch.c CLIPSJNI_Environment.c
include $(BUILD_SHARED_LIBRARY)
