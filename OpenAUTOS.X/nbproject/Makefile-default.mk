#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=mkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=cof
DEBUGGABLE_SUFFIX=cof
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/OpenAUTOS.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=cof
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/OpenAUTOS.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=--mafrlcsj
else
COMPARISON_BUILD=
endif

ifdef SUB_IMAGE_ADDRESS

else
SUB_IMAGE_ADDRESS_COMMAND=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=/home/bruno/Documents/UFSC/TCC/TccBruno/OpenAUTOS/app/main.c /home/bruno/Documents/UFSC/TCC/TccBruno/OpenAUTOS/os/osek/interrupts.c /home/bruno/Documents/UFSC/TCC/TccBruno/OpenAUTOS/os/osek/status_types.c /home/bruno/Documents/UFSC/TCC/TccBruno/OpenAUTOS/os/osek/resources.c /home/bruno/Documents/UFSC/TCC/TccBruno/OpenAUTOS/os/osek/os.c /home/bruno/Documents/UFSC/TCC/TccBruno/OpenAUTOS/os/osek/tasks.c /home/bruno/Documents/UFSC/TCC/TccBruno/OpenAUTOS/os/platform/pic18f25k80/task_context.c /home/bruno/Documents/UFSC/TCC/TccBruno/OpenAUTOS/os/platform/pic18f25k80/system_counter.c /home/bruno/Documents/UFSC/TCC/TccBruno/OpenAUTOS/os/platform/pic18f25k80/setup.c /home/bruno/Documents/UFSC/TCC/TccBruno/OpenAUTOS/os/resource.c /home/bruno/Documents/UFSC/TCC/TccBruno/OpenAUTOS/os/system_counter.c /home/bruno/Documents/UFSC/TCC/TccBruno/OpenAUTOS/os/setup.c /home/bruno/Documents/UFSC/TCC/TccBruno/OpenAUTOS/os/task.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/681081929/main.p1 ${OBJECTDIR}/_ext/229191317/interrupts.p1 ${OBJECTDIR}/_ext/229191317/status_types.p1 ${OBJECTDIR}/_ext/229191317/resources.p1 ${OBJECTDIR}/_ext/229191317/os.p1 ${OBJECTDIR}/_ext/229191317/tasks.p1 ${OBJECTDIR}/_ext/732895632/task_context.p1 ${OBJECTDIR}/_ext/732895632/system_counter.p1 ${OBJECTDIR}/_ext/732895632/setup.p1 ${OBJECTDIR}/_ext/1502050702/resource.p1 ${OBJECTDIR}/_ext/1502050702/system_counter.p1 ${OBJECTDIR}/_ext/1502050702/setup.p1 ${OBJECTDIR}/_ext/1502050702/task.p1
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/681081929/main.p1.d ${OBJECTDIR}/_ext/229191317/interrupts.p1.d ${OBJECTDIR}/_ext/229191317/status_types.p1.d ${OBJECTDIR}/_ext/229191317/resources.p1.d ${OBJECTDIR}/_ext/229191317/os.p1.d ${OBJECTDIR}/_ext/229191317/tasks.p1.d ${OBJECTDIR}/_ext/732895632/task_context.p1.d ${OBJECTDIR}/_ext/732895632/system_counter.p1.d ${OBJECTDIR}/_ext/732895632/setup.p1.d ${OBJECTDIR}/_ext/1502050702/resource.p1.d ${OBJECTDIR}/_ext/1502050702/system_counter.p1.d ${OBJECTDIR}/_ext/1502050702/setup.p1.d ${OBJECTDIR}/_ext/1502050702/task.p1.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/681081929/main.p1 ${OBJECTDIR}/_ext/229191317/interrupts.p1 ${OBJECTDIR}/_ext/229191317/status_types.p1 ${OBJECTDIR}/_ext/229191317/resources.p1 ${OBJECTDIR}/_ext/229191317/os.p1 ${OBJECTDIR}/_ext/229191317/tasks.p1 ${OBJECTDIR}/_ext/732895632/task_context.p1 ${OBJECTDIR}/_ext/732895632/system_counter.p1 ${OBJECTDIR}/_ext/732895632/setup.p1 ${OBJECTDIR}/_ext/1502050702/resource.p1 ${OBJECTDIR}/_ext/1502050702/system_counter.p1 ${OBJECTDIR}/_ext/1502050702/setup.p1 ${OBJECTDIR}/_ext/1502050702/task.p1

# Source Files
SOURCEFILES=/home/bruno/Documents/UFSC/TCC/TccBruno/OpenAUTOS/app/main.c /home/bruno/Documents/UFSC/TCC/TccBruno/OpenAUTOS/os/osek/interrupts.c /home/bruno/Documents/UFSC/TCC/TccBruno/OpenAUTOS/os/osek/status_types.c /home/bruno/Documents/UFSC/TCC/TccBruno/OpenAUTOS/os/osek/resources.c /home/bruno/Documents/UFSC/TCC/TccBruno/OpenAUTOS/os/osek/os.c /home/bruno/Documents/UFSC/TCC/TccBruno/OpenAUTOS/os/osek/tasks.c /home/bruno/Documents/UFSC/TCC/TccBruno/OpenAUTOS/os/platform/pic18f25k80/task_context.c /home/bruno/Documents/UFSC/TCC/TccBruno/OpenAUTOS/os/platform/pic18f25k80/system_counter.c /home/bruno/Documents/UFSC/TCC/TccBruno/OpenAUTOS/os/platform/pic18f25k80/setup.c /home/bruno/Documents/UFSC/TCC/TccBruno/OpenAUTOS/os/resource.c /home/bruno/Documents/UFSC/TCC/TccBruno/OpenAUTOS/os/system_counter.c /home/bruno/Documents/UFSC/TCC/TccBruno/OpenAUTOS/os/setup.c /home/bruno/Documents/UFSC/TCC/TccBruno/OpenAUTOS/os/task.c


CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/OpenAUTOS.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=18F25K80
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/681081929/main.p1: /home/bruno/Documents/UFSC/TCC/TccBruno/OpenAUTOS/app/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/681081929" 
	@${RM} ${OBJECTDIR}/_ext/681081929/main.p1.d 
	@${RM} ${OBJECTDIR}/_ext/681081929/main.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=none  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,+debug --addrqual=request --mode=free -DPLATFORM=PIC18F25K80 -P -N255 -I"../os" --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=+mcof,-elf:multilocs --stack=compiled:auto:auto:auto --output=+mcof,+elf:multilocs "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/681081929/main.p1  /home/bruno/Documents/UFSC/TCC/TccBruno/OpenAUTOS/app/main.c 
	@-${MV} ${OBJECTDIR}/_ext/681081929/main.d ${OBJECTDIR}/_ext/681081929/main.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/681081929/main.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/229191317/interrupts.p1: /home/bruno/Documents/UFSC/TCC/TccBruno/OpenAUTOS/os/osek/interrupts.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/229191317" 
	@${RM} ${OBJECTDIR}/_ext/229191317/interrupts.p1.d 
	@${RM} ${OBJECTDIR}/_ext/229191317/interrupts.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=none  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,+debug --addrqual=request --mode=free -DPLATFORM=PIC18F25K80 -P -N255 -I"../os" --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=+mcof,-elf:multilocs --stack=compiled:auto:auto:auto --output=+mcof,+elf:multilocs "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/229191317/interrupts.p1  /home/bruno/Documents/UFSC/TCC/TccBruno/OpenAUTOS/os/osek/interrupts.c 
	@-${MV} ${OBJECTDIR}/_ext/229191317/interrupts.d ${OBJECTDIR}/_ext/229191317/interrupts.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/229191317/interrupts.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/229191317/status_types.p1: /home/bruno/Documents/UFSC/TCC/TccBruno/OpenAUTOS/os/osek/status_types.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/229191317" 
	@${RM} ${OBJECTDIR}/_ext/229191317/status_types.p1.d 
	@${RM} ${OBJECTDIR}/_ext/229191317/status_types.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=none  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,+debug --addrqual=request --mode=free -DPLATFORM=PIC18F25K80 -P -N255 -I"../os" --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=+mcof,-elf:multilocs --stack=compiled:auto:auto:auto --output=+mcof,+elf:multilocs "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/229191317/status_types.p1  /home/bruno/Documents/UFSC/TCC/TccBruno/OpenAUTOS/os/osek/status_types.c 
	@-${MV} ${OBJECTDIR}/_ext/229191317/status_types.d ${OBJECTDIR}/_ext/229191317/status_types.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/229191317/status_types.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/229191317/resources.p1: /home/bruno/Documents/UFSC/TCC/TccBruno/OpenAUTOS/os/osek/resources.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/229191317" 
	@${RM} ${OBJECTDIR}/_ext/229191317/resources.p1.d 
	@${RM} ${OBJECTDIR}/_ext/229191317/resources.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=none  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,+debug --addrqual=request --mode=free -DPLATFORM=PIC18F25K80 -P -N255 -I"../os" --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=+mcof,-elf:multilocs --stack=compiled:auto:auto:auto --output=+mcof,+elf:multilocs "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/229191317/resources.p1  /home/bruno/Documents/UFSC/TCC/TccBruno/OpenAUTOS/os/osek/resources.c 
	@-${MV} ${OBJECTDIR}/_ext/229191317/resources.d ${OBJECTDIR}/_ext/229191317/resources.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/229191317/resources.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/229191317/os.p1: /home/bruno/Documents/UFSC/TCC/TccBruno/OpenAUTOS/os/osek/os.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/229191317" 
	@${RM} ${OBJECTDIR}/_ext/229191317/os.p1.d 
	@${RM} ${OBJECTDIR}/_ext/229191317/os.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=none  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,+debug --addrqual=request --mode=free -DPLATFORM=PIC18F25K80 -P -N255 -I"../os" --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=+mcof,-elf:multilocs --stack=compiled:auto:auto:auto --output=+mcof,+elf:multilocs "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/229191317/os.p1  /home/bruno/Documents/UFSC/TCC/TccBruno/OpenAUTOS/os/osek/os.c 
	@-${MV} ${OBJECTDIR}/_ext/229191317/os.d ${OBJECTDIR}/_ext/229191317/os.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/229191317/os.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/229191317/tasks.p1: /home/bruno/Documents/UFSC/TCC/TccBruno/OpenAUTOS/os/osek/tasks.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/229191317" 
	@${RM} ${OBJECTDIR}/_ext/229191317/tasks.p1.d 
	@${RM} ${OBJECTDIR}/_ext/229191317/tasks.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=none  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,+debug --addrqual=request --mode=free -DPLATFORM=PIC18F25K80 -P -N255 -I"../os" --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=+mcof,-elf:multilocs --stack=compiled:auto:auto:auto --output=+mcof,+elf:multilocs "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/229191317/tasks.p1  /home/bruno/Documents/UFSC/TCC/TccBruno/OpenAUTOS/os/osek/tasks.c 
	@-${MV} ${OBJECTDIR}/_ext/229191317/tasks.d ${OBJECTDIR}/_ext/229191317/tasks.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/229191317/tasks.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/732895632/task_context.p1: /home/bruno/Documents/UFSC/TCC/TccBruno/OpenAUTOS/os/platform/pic18f25k80/task_context.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/732895632" 
	@${RM} ${OBJECTDIR}/_ext/732895632/task_context.p1.d 
	@${RM} ${OBJECTDIR}/_ext/732895632/task_context.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=none  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,+debug --addrqual=request --mode=free -DPLATFORM=PIC18F25K80 -P -N255 -I"../os" --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=+mcof,-elf:multilocs --stack=compiled:auto:auto:auto --output=+mcof,+elf:multilocs "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/732895632/task_context.p1  /home/bruno/Documents/UFSC/TCC/TccBruno/OpenAUTOS/os/platform/pic18f25k80/task_context.c 
	@-${MV} ${OBJECTDIR}/_ext/732895632/task_context.d ${OBJECTDIR}/_ext/732895632/task_context.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/732895632/task_context.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/732895632/system_counter.p1: /home/bruno/Documents/UFSC/TCC/TccBruno/OpenAUTOS/os/platform/pic18f25k80/system_counter.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/732895632" 
	@${RM} ${OBJECTDIR}/_ext/732895632/system_counter.p1.d 
	@${RM} ${OBJECTDIR}/_ext/732895632/system_counter.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=none  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,+debug --addrqual=request --mode=free -DPLATFORM=PIC18F25K80 -P -N255 -I"../os" --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=+mcof,-elf:multilocs --stack=compiled:auto:auto:auto --output=+mcof,+elf:multilocs "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/732895632/system_counter.p1  /home/bruno/Documents/UFSC/TCC/TccBruno/OpenAUTOS/os/platform/pic18f25k80/system_counter.c 
	@-${MV} ${OBJECTDIR}/_ext/732895632/system_counter.d ${OBJECTDIR}/_ext/732895632/system_counter.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/732895632/system_counter.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/732895632/setup.p1: /home/bruno/Documents/UFSC/TCC/TccBruno/OpenAUTOS/os/platform/pic18f25k80/setup.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/732895632" 
	@${RM} ${OBJECTDIR}/_ext/732895632/setup.p1.d 
	@${RM} ${OBJECTDIR}/_ext/732895632/setup.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=none  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,+debug --addrqual=request --mode=free -DPLATFORM=PIC18F25K80 -P -N255 -I"../os" --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=+mcof,-elf:multilocs --stack=compiled:auto:auto:auto --output=+mcof,+elf:multilocs "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/732895632/setup.p1  /home/bruno/Documents/UFSC/TCC/TccBruno/OpenAUTOS/os/platform/pic18f25k80/setup.c 
	@-${MV} ${OBJECTDIR}/_ext/732895632/setup.d ${OBJECTDIR}/_ext/732895632/setup.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/732895632/setup.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1502050702/resource.p1: /home/bruno/Documents/UFSC/TCC/TccBruno/OpenAUTOS/os/resource.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1502050702" 
	@${RM} ${OBJECTDIR}/_ext/1502050702/resource.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1502050702/resource.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=none  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,+debug --addrqual=request --mode=free -DPLATFORM=PIC18F25K80 -P -N255 -I"../os" --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=+mcof,-elf:multilocs --stack=compiled:auto:auto:auto --output=+mcof,+elf:multilocs "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/1502050702/resource.p1  /home/bruno/Documents/UFSC/TCC/TccBruno/OpenAUTOS/os/resource.c 
	@-${MV} ${OBJECTDIR}/_ext/1502050702/resource.d ${OBJECTDIR}/_ext/1502050702/resource.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1502050702/resource.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1502050702/system_counter.p1: /home/bruno/Documents/UFSC/TCC/TccBruno/OpenAUTOS/os/system_counter.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1502050702" 
	@${RM} ${OBJECTDIR}/_ext/1502050702/system_counter.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1502050702/system_counter.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=none  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,+debug --addrqual=request --mode=free -DPLATFORM=PIC18F25K80 -P -N255 -I"../os" --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=+mcof,-elf:multilocs --stack=compiled:auto:auto:auto --output=+mcof,+elf:multilocs "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/1502050702/system_counter.p1  /home/bruno/Documents/UFSC/TCC/TccBruno/OpenAUTOS/os/system_counter.c 
	@-${MV} ${OBJECTDIR}/_ext/1502050702/system_counter.d ${OBJECTDIR}/_ext/1502050702/system_counter.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1502050702/system_counter.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1502050702/setup.p1: /home/bruno/Documents/UFSC/TCC/TccBruno/OpenAUTOS/os/setup.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1502050702" 
	@${RM} ${OBJECTDIR}/_ext/1502050702/setup.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1502050702/setup.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=none  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,+debug --addrqual=request --mode=free -DPLATFORM=PIC18F25K80 -P -N255 -I"../os" --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=+mcof,-elf:multilocs --stack=compiled:auto:auto:auto --output=+mcof,+elf:multilocs "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/1502050702/setup.p1  /home/bruno/Documents/UFSC/TCC/TccBruno/OpenAUTOS/os/setup.c 
	@-${MV} ${OBJECTDIR}/_ext/1502050702/setup.d ${OBJECTDIR}/_ext/1502050702/setup.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1502050702/setup.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1502050702/task.p1: /home/bruno/Documents/UFSC/TCC/TccBruno/OpenAUTOS/os/task.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1502050702" 
	@${RM} ${OBJECTDIR}/_ext/1502050702/task.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1502050702/task.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=none  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,+debug --addrqual=request --mode=free -DPLATFORM=PIC18F25K80 -P -N255 -I"../os" --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=+mcof,-elf:multilocs --stack=compiled:auto:auto:auto --output=+mcof,+elf:multilocs "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/1502050702/task.p1  /home/bruno/Documents/UFSC/TCC/TccBruno/OpenAUTOS/os/task.c 
	@-${MV} ${OBJECTDIR}/_ext/1502050702/task.d ${OBJECTDIR}/_ext/1502050702/task.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1502050702/task.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
else
${OBJECTDIR}/_ext/681081929/main.p1: /home/bruno/Documents/UFSC/TCC/TccBruno/OpenAUTOS/app/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/681081929" 
	@${RM} ${OBJECTDIR}/_ext/681081929/main.p1.d 
	@${RM} ${OBJECTDIR}/_ext/681081929/main.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,+debug --addrqual=request --mode=free -DPLATFORM=PIC18F25K80 -P -N255 -I"../os" --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=+mcof,-elf:multilocs --stack=compiled:auto:auto:auto --output=+mcof,+elf:multilocs "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/681081929/main.p1  /home/bruno/Documents/UFSC/TCC/TccBruno/OpenAUTOS/app/main.c 
	@-${MV} ${OBJECTDIR}/_ext/681081929/main.d ${OBJECTDIR}/_ext/681081929/main.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/681081929/main.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/229191317/interrupts.p1: /home/bruno/Documents/UFSC/TCC/TccBruno/OpenAUTOS/os/osek/interrupts.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/229191317" 
	@${RM} ${OBJECTDIR}/_ext/229191317/interrupts.p1.d 
	@${RM} ${OBJECTDIR}/_ext/229191317/interrupts.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,+debug --addrqual=request --mode=free -DPLATFORM=PIC18F25K80 -P -N255 -I"../os" --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=+mcof,-elf:multilocs --stack=compiled:auto:auto:auto --output=+mcof,+elf:multilocs "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/229191317/interrupts.p1  /home/bruno/Documents/UFSC/TCC/TccBruno/OpenAUTOS/os/osek/interrupts.c 
	@-${MV} ${OBJECTDIR}/_ext/229191317/interrupts.d ${OBJECTDIR}/_ext/229191317/interrupts.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/229191317/interrupts.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/229191317/status_types.p1: /home/bruno/Documents/UFSC/TCC/TccBruno/OpenAUTOS/os/osek/status_types.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/229191317" 
	@${RM} ${OBJECTDIR}/_ext/229191317/status_types.p1.d 
	@${RM} ${OBJECTDIR}/_ext/229191317/status_types.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,+debug --addrqual=request --mode=free -DPLATFORM=PIC18F25K80 -P -N255 -I"../os" --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=+mcof,-elf:multilocs --stack=compiled:auto:auto:auto --output=+mcof,+elf:multilocs "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/229191317/status_types.p1  /home/bruno/Documents/UFSC/TCC/TccBruno/OpenAUTOS/os/osek/status_types.c 
	@-${MV} ${OBJECTDIR}/_ext/229191317/status_types.d ${OBJECTDIR}/_ext/229191317/status_types.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/229191317/status_types.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/229191317/resources.p1: /home/bruno/Documents/UFSC/TCC/TccBruno/OpenAUTOS/os/osek/resources.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/229191317" 
	@${RM} ${OBJECTDIR}/_ext/229191317/resources.p1.d 
	@${RM} ${OBJECTDIR}/_ext/229191317/resources.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,+debug --addrqual=request --mode=free -DPLATFORM=PIC18F25K80 -P -N255 -I"../os" --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=+mcof,-elf:multilocs --stack=compiled:auto:auto:auto --output=+mcof,+elf:multilocs "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/229191317/resources.p1  /home/bruno/Documents/UFSC/TCC/TccBruno/OpenAUTOS/os/osek/resources.c 
	@-${MV} ${OBJECTDIR}/_ext/229191317/resources.d ${OBJECTDIR}/_ext/229191317/resources.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/229191317/resources.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/229191317/os.p1: /home/bruno/Documents/UFSC/TCC/TccBruno/OpenAUTOS/os/osek/os.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/229191317" 
	@${RM} ${OBJECTDIR}/_ext/229191317/os.p1.d 
	@${RM} ${OBJECTDIR}/_ext/229191317/os.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,+debug --addrqual=request --mode=free -DPLATFORM=PIC18F25K80 -P -N255 -I"../os" --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=+mcof,-elf:multilocs --stack=compiled:auto:auto:auto --output=+mcof,+elf:multilocs "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/229191317/os.p1  /home/bruno/Documents/UFSC/TCC/TccBruno/OpenAUTOS/os/osek/os.c 
	@-${MV} ${OBJECTDIR}/_ext/229191317/os.d ${OBJECTDIR}/_ext/229191317/os.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/229191317/os.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/229191317/tasks.p1: /home/bruno/Documents/UFSC/TCC/TccBruno/OpenAUTOS/os/osek/tasks.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/229191317" 
	@${RM} ${OBJECTDIR}/_ext/229191317/tasks.p1.d 
	@${RM} ${OBJECTDIR}/_ext/229191317/tasks.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,+debug --addrqual=request --mode=free -DPLATFORM=PIC18F25K80 -P -N255 -I"../os" --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=+mcof,-elf:multilocs --stack=compiled:auto:auto:auto --output=+mcof,+elf:multilocs "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/229191317/tasks.p1  /home/bruno/Documents/UFSC/TCC/TccBruno/OpenAUTOS/os/osek/tasks.c 
	@-${MV} ${OBJECTDIR}/_ext/229191317/tasks.d ${OBJECTDIR}/_ext/229191317/tasks.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/229191317/tasks.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/732895632/task_context.p1: /home/bruno/Documents/UFSC/TCC/TccBruno/OpenAUTOS/os/platform/pic18f25k80/task_context.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/732895632" 
	@${RM} ${OBJECTDIR}/_ext/732895632/task_context.p1.d 
	@${RM} ${OBJECTDIR}/_ext/732895632/task_context.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,+debug --addrqual=request --mode=free -DPLATFORM=PIC18F25K80 -P -N255 -I"../os" --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=+mcof,-elf:multilocs --stack=compiled:auto:auto:auto --output=+mcof,+elf:multilocs "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/732895632/task_context.p1  /home/bruno/Documents/UFSC/TCC/TccBruno/OpenAUTOS/os/platform/pic18f25k80/task_context.c 
	@-${MV} ${OBJECTDIR}/_ext/732895632/task_context.d ${OBJECTDIR}/_ext/732895632/task_context.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/732895632/task_context.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/732895632/system_counter.p1: /home/bruno/Documents/UFSC/TCC/TccBruno/OpenAUTOS/os/platform/pic18f25k80/system_counter.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/732895632" 
	@${RM} ${OBJECTDIR}/_ext/732895632/system_counter.p1.d 
	@${RM} ${OBJECTDIR}/_ext/732895632/system_counter.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,+debug --addrqual=request --mode=free -DPLATFORM=PIC18F25K80 -P -N255 -I"../os" --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=+mcof,-elf:multilocs --stack=compiled:auto:auto:auto --output=+mcof,+elf:multilocs "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/732895632/system_counter.p1  /home/bruno/Documents/UFSC/TCC/TccBruno/OpenAUTOS/os/platform/pic18f25k80/system_counter.c 
	@-${MV} ${OBJECTDIR}/_ext/732895632/system_counter.d ${OBJECTDIR}/_ext/732895632/system_counter.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/732895632/system_counter.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/732895632/setup.p1: /home/bruno/Documents/UFSC/TCC/TccBruno/OpenAUTOS/os/platform/pic18f25k80/setup.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/732895632" 
	@${RM} ${OBJECTDIR}/_ext/732895632/setup.p1.d 
	@${RM} ${OBJECTDIR}/_ext/732895632/setup.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,+debug --addrqual=request --mode=free -DPLATFORM=PIC18F25K80 -P -N255 -I"../os" --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=+mcof,-elf:multilocs --stack=compiled:auto:auto:auto --output=+mcof,+elf:multilocs "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/732895632/setup.p1  /home/bruno/Documents/UFSC/TCC/TccBruno/OpenAUTOS/os/platform/pic18f25k80/setup.c 
	@-${MV} ${OBJECTDIR}/_ext/732895632/setup.d ${OBJECTDIR}/_ext/732895632/setup.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/732895632/setup.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1502050702/resource.p1: /home/bruno/Documents/UFSC/TCC/TccBruno/OpenAUTOS/os/resource.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1502050702" 
	@${RM} ${OBJECTDIR}/_ext/1502050702/resource.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1502050702/resource.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,+debug --addrqual=request --mode=free -DPLATFORM=PIC18F25K80 -P -N255 -I"../os" --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=+mcof,-elf:multilocs --stack=compiled:auto:auto:auto --output=+mcof,+elf:multilocs "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/1502050702/resource.p1  /home/bruno/Documents/UFSC/TCC/TccBruno/OpenAUTOS/os/resource.c 
	@-${MV} ${OBJECTDIR}/_ext/1502050702/resource.d ${OBJECTDIR}/_ext/1502050702/resource.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1502050702/resource.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1502050702/system_counter.p1: /home/bruno/Documents/UFSC/TCC/TccBruno/OpenAUTOS/os/system_counter.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1502050702" 
	@${RM} ${OBJECTDIR}/_ext/1502050702/system_counter.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1502050702/system_counter.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,+debug --addrqual=request --mode=free -DPLATFORM=PIC18F25K80 -P -N255 -I"../os" --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=+mcof,-elf:multilocs --stack=compiled:auto:auto:auto --output=+mcof,+elf:multilocs "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/1502050702/system_counter.p1  /home/bruno/Documents/UFSC/TCC/TccBruno/OpenAUTOS/os/system_counter.c 
	@-${MV} ${OBJECTDIR}/_ext/1502050702/system_counter.d ${OBJECTDIR}/_ext/1502050702/system_counter.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1502050702/system_counter.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1502050702/setup.p1: /home/bruno/Documents/UFSC/TCC/TccBruno/OpenAUTOS/os/setup.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1502050702" 
	@${RM} ${OBJECTDIR}/_ext/1502050702/setup.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1502050702/setup.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,+debug --addrqual=request --mode=free -DPLATFORM=PIC18F25K80 -P -N255 -I"../os" --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=+mcof,-elf:multilocs --stack=compiled:auto:auto:auto --output=+mcof,+elf:multilocs "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/1502050702/setup.p1  /home/bruno/Documents/UFSC/TCC/TccBruno/OpenAUTOS/os/setup.c 
	@-${MV} ${OBJECTDIR}/_ext/1502050702/setup.d ${OBJECTDIR}/_ext/1502050702/setup.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1502050702/setup.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1502050702/task.p1: /home/bruno/Documents/UFSC/TCC/TccBruno/OpenAUTOS/os/task.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1502050702" 
	@${RM} ${OBJECTDIR}/_ext/1502050702/task.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1502050702/task.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,+debug --addrqual=request --mode=free -DPLATFORM=PIC18F25K80 -P -N255 -I"../os" --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=+mcof,-elf:multilocs --stack=compiled:auto:auto:auto --output=+mcof,+elf:multilocs "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/1502050702/task.p1  /home/bruno/Documents/UFSC/TCC/TccBruno/OpenAUTOS/os/task.c 
	@-${MV} ${OBJECTDIR}/_ext/1502050702/task.d ${OBJECTDIR}/_ext/1502050702/task.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1502050702/task.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/OpenAUTOS.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE) --chip=$(MP_PROCESSOR_OPTION) -G -mdist/${CND_CONF}/${IMAGE_TYPE}/OpenAUTOS.X.${IMAGE_TYPE}.map  -D__DEBUG=1 --debugger=none  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,+debug --addrqual=request --mode=free -DPLATFORM=PIC18F25K80 -P -N255 -I"../os" --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib --output=+mcof,-elf:multilocs --stack=compiled:auto:auto:auto --output=+mcof,+elf:multilocs "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"        $(COMPARISON_BUILD) --memorysummary dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml -odist/${CND_CONF}/${IMAGE_TYPE}/OpenAUTOS.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}     
	@${RM} dist/${CND_CONF}/${IMAGE_TYPE}/OpenAUTOS.X.${IMAGE_TYPE}.hex 
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/OpenAUTOS.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE) --chip=$(MP_PROCESSOR_OPTION) -G -mdist/${CND_CONF}/${IMAGE_TYPE}/OpenAUTOS.X.${IMAGE_TYPE}.map  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,+debug --addrqual=request --mode=free -DPLATFORM=PIC18F25K80 -P -N255 -I"../os" --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib --output=+mcof,-elf:multilocs --stack=compiled:auto:auto:auto --output=+mcof,+elf:multilocs "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"     $(COMPARISON_BUILD) --memorysummary dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml -odist/${CND_CONF}/${IMAGE_TYPE}/OpenAUTOS.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}     
	
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/default
	${RM} -r dist/default

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell "${PATH_TO_IDE_BIN}"mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
