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
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/DagobotHSMProject.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/DagobotHSMProject.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=Dagobot.c DagobotFrameworkEvents.c DagobotHSM.c DagobotMain.c TestBumpService.c Acquiring_AmmoSubHSM.c TestTapeService.c Wall_Hugging_SubHSM.c Portal_DashSubHSM.c AA_LineFollowing_SubHSM.c TestBeaconDetectorService.c Portal_Wall_Hugging_SubHSM.c Engage_Destroy_Wall_Hugging.c Engage_DestroySubHSM.c ../../../Test.X/AD.c ../../../Test.X/BOARD.c ../../../Test.X/ES_Framework.c ../../../Test.X/LED.c ../../../Test.X/pwm.c ../../../Test.X/RC_Servo.c ../../../Test.X/serial.c AlignCollect_SubHSM.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/Dagobot.o ${OBJECTDIR}/DagobotFrameworkEvents.o ${OBJECTDIR}/DagobotHSM.o ${OBJECTDIR}/DagobotMain.o ${OBJECTDIR}/TestBumpService.o ${OBJECTDIR}/Acquiring_AmmoSubHSM.o ${OBJECTDIR}/TestTapeService.o ${OBJECTDIR}/Wall_Hugging_SubHSM.o ${OBJECTDIR}/Portal_DashSubHSM.o ${OBJECTDIR}/AA_LineFollowing_SubHSM.o ${OBJECTDIR}/TestBeaconDetectorService.o ${OBJECTDIR}/Portal_Wall_Hugging_SubHSM.o ${OBJECTDIR}/Engage_Destroy_Wall_Hugging.o ${OBJECTDIR}/Engage_DestroySubHSM.o ${OBJECTDIR}/_ext/469261227/AD.o ${OBJECTDIR}/_ext/469261227/BOARD.o ${OBJECTDIR}/_ext/469261227/ES_Framework.o ${OBJECTDIR}/_ext/469261227/LED.o ${OBJECTDIR}/_ext/469261227/pwm.o ${OBJECTDIR}/_ext/469261227/RC_Servo.o ${OBJECTDIR}/_ext/469261227/serial.o ${OBJECTDIR}/AlignCollect_SubHSM.o
POSSIBLE_DEPFILES=${OBJECTDIR}/Dagobot.o.d ${OBJECTDIR}/DagobotFrameworkEvents.o.d ${OBJECTDIR}/DagobotHSM.o.d ${OBJECTDIR}/DagobotMain.o.d ${OBJECTDIR}/TestBumpService.o.d ${OBJECTDIR}/Acquiring_AmmoSubHSM.o.d ${OBJECTDIR}/TestTapeService.o.d ${OBJECTDIR}/Wall_Hugging_SubHSM.o.d ${OBJECTDIR}/Portal_DashSubHSM.o.d ${OBJECTDIR}/AA_LineFollowing_SubHSM.o.d ${OBJECTDIR}/TestBeaconDetectorService.o.d ${OBJECTDIR}/Portal_Wall_Hugging_SubHSM.o.d ${OBJECTDIR}/Engage_Destroy_Wall_Hugging.o.d ${OBJECTDIR}/Engage_DestroySubHSM.o.d ${OBJECTDIR}/_ext/469261227/AD.o.d ${OBJECTDIR}/_ext/469261227/BOARD.o.d ${OBJECTDIR}/_ext/469261227/ES_Framework.o.d ${OBJECTDIR}/_ext/469261227/LED.o.d ${OBJECTDIR}/_ext/469261227/pwm.o.d ${OBJECTDIR}/_ext/469261227/RC_Servo.o.d ${OBJECTDIR}/_ext/469261227/serial.o.d ${OBJECTDIR}/AlignCollect_SubHSM.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/Dagobot.o ${OBJECTDIR}/DagobotFrameworkEvents.o ${OBJECTDIR}/DagobotHSM.o ${OBJECTDIR}/DagobotMain.o ${OBJECTDIR}/TestBumpService.o ${OBJECTDIR}/Acquiring_AmmoSubHSM.o ${OBJECTDIR}/TestTapeService.o ${OBJECTDIR}/Wall_Hugging_SubHSM.o ${OBJECTDIR}/Portal_DashSubHSM.o ${OBJECTDIR}/AA_LineFollowing_SubHSM.o ${OBJECTDIR}/TestBeaconDetectorService.o ${OBJECTDIR}/Portal_Wall_Hugging_SubHSM.o ${OBJECTDIR}/Engage_Destroy_Wall_Hugging.o ${OBJECTDIR}/Engage_DestroySubHSM.o ${OBJECTDIR}/_ext/469261227/AD.o ${OBJECTDIR}/_ext/469261227/BOARD.o ${OBJECTDIR}/_ext/469261227/ES_Framework.o ${OBJECTDIR}/_ext/469261227/LED.o ${OBJECTDIR}/_ext/469261227/pwm.o ${OBJECTDIR}/_ext/469261227/RC_Servo.o ${OBJECTDIR}/_ext/469261227/serial.o ${OBJECTDIR}/AlignCollect_SubHSM.o

# Source Files
SOURCEFILES=Dagobot.c DagobotFrameworkEvents.c DagobotHSM.c DagobotMain.c TestBumpService.c Acquiring_AmmoSubHSM.c TestTapeService.c Wall_Hugging_SubHSM.c Portal_DashSubHSM.c AA_LineFollowing_SubHSM.c TestBeaconDetectorService.c Portal_Wall_Hugging_SubHSM.c Engage_Destroy_Wall_Hugging.c Engage_DestroySubHSM.c ../../../Test.X/AD.c ../../../Test.X/BOARD.c ../../../Test.X/ES_Framework.c ../../../Test.X/LED.c ../../../Test.X/pwm.c ../../../Test.X/RC_Servo.c ../../../Test.X/serial.c AlignCollect_SubHSM.c


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
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/DagobotHSMProject.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=32MX320F128H
MP_LINKER_FILE_OPTION=
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assembleWithPreprocess
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/Dagobot.o: Dagobot.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Dagobot.o.d 
	@${RM} ${OBJECTDIR}/Dagobot.o 
	@${FIXDEPS} "${OBJECTDIR}/Dagobot.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"C:/CMPE118/include" -I"C:/CMPE118/src" -I"../../../../../../../../../CMPE118/include" -MMD -MF "${OBJECTDIR}/Dagobot.o.d" -o ${OBJECTDIR}/Dagobot.o Dagobot.c     
	
${OBJECTDIR}/DagobotFrameworkEvents.o: DagobotFrameworkEvents.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/DagobotFrameworkEvents.o.d 
	@${RM} ${OBJECTDIR}/DagobotFrameworkEvents.o 
	@${FIXDEPS} "${OBJECTDIR}/DagobotFrameworkEvents.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"C:/CMPE118/include" -I"C:/CMPE118/src" -I"../../../../../../../../../CMPE118/include" -MMD -MF "${OBJECTDIR}/DagobotFrameworkEvents.o.d" -o ${OBJECTDIR}/DagobotFrameworkEvents.o DagobotFrameworkEvents.c     
	
${OBJECTDIR}/DagobotHSM.o: DagobotHSM.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/DagobotHSM.o.d 
	@${RM} ${OBJECTDIR}/DagobotHSM.o 
	@${FIXDEPS} "${OBJECTDIR}/DagobotHSM.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"C:/CMPE118/include" -I"C:/CMPE118/src" -I"../../../../../../../../../CMPE118/include" -MMD -MF "${OBJECTDIR}/DagobotHSM.o.d" -o ${OBJECTDIR}/DagobotHSM.o DagobotHSM.c     
	
${OBJECTDIR}/DagobotMain.o: DagobotMain.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/DagobotMain.o.d 
	@${RM} ${OBJECTDIR}/DagobotMain.o 
	@${FIXDEPS} "${OBJECTDIR}/DagobotMain.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"C:/CMPE118/include" -I"C:/CMPE118/src" -I"../../../../../../../../../CMPE118/include" -MMD -MF "${OBJECTDIR}/DagobotMain.o.d" -o ${OBJECTDIR}/DagobotMain.o DagobotMain.c     
	
${OBJECTDIR}/TestBumpService.o: TestBumpService.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/TestBumpService.o.d 
	@${RM} ${OBJECTDIR}/TestBumpService.o 
	@${FIXDEPS} "${OBJECTDIR}/TestBumpService.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"C:/CMPE118/include" -I"C:/CMPE118/src" -I"../../../../../../../../../CMPE118/include" -MMD -MF "${OBJECTDIR}/TestBumpService.o.d" -o ${OBJECTDIR}/TestBumpService.o TestBumpService.c     
	
${OBJECTDIR}/Acquiring_AmmoSubHSM.o: Acquiring_AmmoSubHSM.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Acquiring_AmmoSubHSM.o.d 
	@${RM} ${OBJECTDIR}/Acquiring_AmmoSubHSM.o 
	@${FIXDEPS} "${OBJECTDIR}/Acquiring_AmmoSubHSM.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"C:/CMPE118/include" -I"C:/CMPE118/src" -I"../../../../../../../../../CMPE118/include" -MMD -MF "${OBJECTDIR}/Acquiring_AmmoSubHSM.o.d" -o ${OBJECTDIR}/Acquiring_AmmoSubHSM.o Acquiring_AmmoSubHSM.c     
	
${OBJECTDIR}/TestTapeService.o: TestTapeService.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/TestTapeService.o.d 
	@${RM} ${OBJECTDIR}/TestTapeService.o 
	@${FIXDEPS} "${OBJECTDIR}/TestTapeService.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"C:/CMPE118/include" -I"C:/CMPE118/src" -I"../../../../../../../../../CMPE118/include" -MMD -MF "${OBJECTDIR}/TestTapeService.o.d" -o ${OBJECTDIR}/TestTapeService.o TestTapeService.c     
	
${OBJECTDIR}/Wall_Hugging_SubHSM.o: Wall_Hugging_SubHSM.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Wall_Hugging_SubHSM.o.d 
	@${RM} ${OBJECTDIR}/Wall_Hugging_SubHSM.o 
	@${FIXDEPS} "${OBJECTDIR}/Wall_Hugging_SubHSM.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"C:/CMPE118/include" -I"C:/CMPE118/src" -I"../../../../../../../../../CMPE118/include" -MMD -MF "${OBJECTDIR}/Wall_Hugging_SubHSM.o.d" -o ${OBJECTDIR}/Wall_Hugging_SubHSM.o Wall_Hugging_SubHSM.c     
	
${OBJECTDIR}/Portal_DashSubHSM.o: Portal_DashSubHSM.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Portal_DashSubHSM.o.d 
	@${RM} ${OBJECTDIR}/Portal_DashSubHSM.o 
	@${FIXDEPS} "${OBJECTDIR}/Portal_DashSubHSM.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"C:/CMPE118/include" -I"C:/CMPE118/src" -I"../../../../../../../../../CMPE118/include" -MMD -MF "${OBJECTDIR}/Portal_DashSubHSM.o.d" -o ${OBJECTDIR}/Portal_DashSubHSM.o Portal_DashSubHSM.c     
	
${OBJECTDIR}/AA_LineFollowing_SubHSM.o: AA_LineFollowing_SubHSM.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/AA_LineFollowing_SubHSM.o.d 
	@${RM} ${OBJECTDIR}/AA_LineFollowing_SubHSM.o 
	@${FIXDEPS} "${OBJECTDIR}/AA_LineFollowing_SubHSM.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"C:/CMPE118/include" -I"C:/CMPE118/src" -I"../../../../../../../../../CMPE118/include" -MMD -MF "${OBJECTDIR}/AA_LineFollowing_SubHSM.o.d" -o ${OBJECTDIR}/AA_LineFollowing_SubHSM.o AA_LineFollowing_SubHSM.c     
	
${OBJECTDIR}/TestBeaconDetectorService.o: TestBeaconDetectorService.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/TestBeaconDetectorService.o.d 
	@${RM} ${OBJECTDIR}/TestBeaconDetectorService.o 
	@${FIXDEPS} "${OBJECTDIR}/TestBeaconDetectorService.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"C:/CMPE118/include" -I"C:/CMPE118/src" -I"../../../../../../../../../CMPE118/include" -MMD -MF "${OBJECTDIR}/TestBeaconDetectorService.o.d" -o ${OBJECTDIR}/TestBeaconDetectorService.o TestBeaconDetectorService.c     
	
${OBJECTDIR}/Portal_Wall_Hugging_SubHSM.o: Portal_Wall_Hugging_SubHSM.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Portal_Wall_Hugging_SubHSM.o.d 
	@${RM} ${OBJECTDIR}/Portal_Wall_Hugging_SubHSM.o 
	@${FIXDEPS} "${OBJECTDIR}/Portal_Wall_Hugging_SubHSM.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"C:/CMPE118/include" -I"C:/CMPE118/src" -I"../../../../../../../../../CMPE118/include" -MMD -MF "${OBJECTDIR}/Portal_Wall_Hugging_SubHSM.o.d" -o ${OBJECTDIR}/Portal_Wall_Hugging_SubHSM.o Portal_Wall_Hugging_SubHSM.c     
	
${OBJECTDIR}/Engage_Destroy_Wall_Hugging.o: Engage_Destroy_Wall_Hugging.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Engage_Destroy_Wall_Hugging.o.d 
	@${RM} ${OBJECTDIR}/Engage_Destroy_Wall_Hugging.o 
	@${FIXDEPS} "${OBJECTDIR}/Engage_Destroy_Wall_Hugging.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"C:/CMPE118/include" -I"C:/CMPE118/src" -I"../../../../../../../../../CMPE118/include" -MMD -MF "${OBJECTDIR}/Engage_Destroy_Wall_Hugging.o.d" -o ${OBJECTDIR}/Engage_Destroy_Wall_Hugging.o Engage_Destroy_Wall_Hugging.c     
	
${OBJECTDIR}/Engage_DestroySubHSM.o: Engage_DestroySubHSM.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Engage_DestroySubHSM.o.d 
	@${RM} ${OBJECTDIR}/Engage_DestroySubHSM.o 
	@${FIXDEPS} "${OBJECTDIR}/Engage_DestroySubHSM.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"C:/CMPE118/include" -I"C:/CMPE118/src" -I"../../../../../../../../../CMPE118/include" -MMD -MF "${OBJECTDIR}/Engage_DestroySubHSM.o.d" -o ${OBJECTDIR}/Engage_DestroySubHSM.o Engage_DestroySubHSM.c     
	
${OBJECTDIR}/_ext/469261227/AD.o: ../../../Test.X/AD.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/469261227" 
	@${RM} ${OBJECTDIR}/_ext/469261227/AD.o.d 
	@${RM} ${OBJECTDIR}/_ext/469261227/AD.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/469261227/AD.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"C:/CMPE118/include" -I"C:/CMPE118/src" -I"../../../../../../../../../CMPE118/include" -MMD -MF "${OBJECTDIR}/_ext/469261227/AD.o.d" -o ${OBJECTDIR}/_ext/469261227/AD.o ../../../Test.X/AD.c     
	
${OBJECTDIR}/_ext/469261227/BOARD.o: ../../../Test.X/BOARD.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/469261227" 
	@${RM} ${OBJECTDIR}/_ext/469261227/BOARD.o.d 
	@${RM} ${OBJECTDIR}/_ext/469261227/BOARD.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/469261227/BOARD.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"C:/CMPE118/include" -I"C:/CMPE118/src" -I"../../../../../../../../../CMPE118/include" -MMD -MF "${OBJECTDIR}/_ext/469261227/BOARD.o.d" -o ${OBJECTDIR}/_ext/469261227/BOARD.o ../../../Test.X/BOARD.c     
	
${OBJECTDIR}/_ext/469261227/ES_Framework.o: ../../../Test.X/ES_Framework.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/469261227" 
	@${RM} ${OBJECTDIR}/_ext/469261227/ES_Framework.o.d 
	@${RM} ${OBJECTDIR}/_ext/469261227/ES_Framework.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/469261227/ES_Framework.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"C:/CMPE118/include" -I"C:/CMPE118/src" -I"../../../../../../../../../CMPE118/include" -MMD -MF "${OBJECTDIR}/_ext/469261227/ES_Framework.o.d" -o ${OBJECTDIR}/_ext/469261227/ES_Framework.o ../../../Test.X/ES_Framework.c     
	
${OBJECTDIR}/_ext/469261227/LED.o: ../../../Test.X/LED.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/469261227" 
	@${RM} ${OBJECTDIR}/_ext/469261227/LED.o.d 
	@${RM} ${OBJECTDIR}/_ext/469261227/LED.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/469261227/LED.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"C:/CMPE118/include" -I"C:/CMPE118/src" -I"../../../../../../../../../CMPE118/include" -MMD -MF "${OBJECTDIR}/_ext/469261227/LED.o.d" -o ${OBJECTDIR}/_ext/469261227/LED.o ../../../Test.X/LED.c     
	
${OBJECTDIR}/_ext/469261227/pwm.o: ../../../Test.X/pwm.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/469261227" 
	@${RM} ${OBJECTDIR}/_ext/469261227/pwm.o.d 
	@${RM} ${OBJECTDIR}/_ext/469261227/pwm.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/469261227/pwm.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"C:/CMPE118/include" -I"C:/CMPE118/src" -I"../../../../../../../../../CMPE118/include" -MMD -MF "${OBJECTDIR}/_ext/469261227/pwm.o.d" -o ${OBJECTDIR}/_ext/469261227/pwm.o ../../../Test.X/pwm.c     
	
${OBJECTDIR}/_ext/469261227/RC_Servo.o: ../../../Test.X/RC_Servo.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/469261227" 
	@${RM} ${OBJECTDIR}/_ext/469261227/RC_Servo.o.d 
	@${RM} ${OBJECTDIR}/_ext/469261227/RC_Servo.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/469261227/RC_Servo.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"C:/CMPE118/include" -I"C:/CMPE118/src" -I"../../../../../../../../../CMPE118/include" -MMD -MF "${OBJECTDIR}/_ext/469261227/RC_Servo.o.d" -o ${OBJECTDIR}/_ext/469261227/RC_Servo.o ../../../Test.X/RC_Servo.c     
	
${OBJECTDIR}/_ext/469261227/serial.o: ../../../Test.X/serial.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/469261227" 
	@${RM} ${OBJECTDIR}/_ext/469261227/serial.o.d 
	@${RM} ${OBJECTDIR}/_ext/469261227/serial.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/469261227/serial.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"C:/CMPE118/include" -I"C:/CMPE118/src" -I"../../../../../../../../../CMPE118/include" -MMD -MF "${OBJECTDIR}/_ext/469261227/serial.o.d" -o ${OBJECTDIR}/_ext/469261227/serial.o ../../../Test.X/serial.c     
	
${OBJECTDIR}/AlignCollect_SubHSM.o: AlignCollect_SubHSM.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/AlignCollect_SubHSM.o.d 
	@${RM} ${OBJECTDIR}/AlignCollect_SubHSM.o 
	@${FIXDEPS} "${OBJECTDIR}/AlignCollect_SubHSM.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"C:/CMPE118/include" -I"C:/CMPE118/src" -I"../../../../../../../../../CMPE118/include" -MMD -MF "${OBJECTDIR}/AlignCollect_SubHSM.o.d" -o ${OBJECTDIR}/AlignCollect_SubHSM.o AlignCollect_SubHSM.c     
	
else
${OBJECTDIR}/Dagobot.o: Dagobot.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Dagobot.o.d 
	@${RM} ${OBJECTDIR}/Dagobot.o 
	@${FIXDEPS} "${OBJECTDIR}/Dagobot.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"C:/CMPE118/include" -I"C:/CMPE118/src" -I"../../../../../../../../../CMPE118/include" -MMD -MF "${OBJECTDIR}/Dagobot.o.d" -o ${OBJECTDIR}/Dagobot.o Dagobot.c     
	
${OBJECTDIR}/DagobotFrameworkEvents.o: DagobotFrameworkEvents.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/DagobotFrameworkEvents.o.d 
	@${RM} ${OBJECTDIR}/DagobotFrameworkEvents.o 
	@${FIXDEPS} "${OBJECTDIR}/DagobotFrameworkEvents.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"C:/CMPE118/include" -I"C:/CMPE118/src" -I"../../../../../../../../../CMPE118/include" -MMD -MF "${OBJECTDIR}/DagobotFrameworkEvents.o.d" -o ${OBJECTDIR}/DagobotFrameworkEvents.o DagobotFrameworkEvents.c     
	
${OBJECTDIR}/DagobotHSM.o: DagobotHSM.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/DagobotHSM.o.d 
	@${RM} ${OBJECTDIR}/DagobotHSM.o 
	@${FIXDEPS} "${OBJECTDIR}/DagobotHSM.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"C:/CMPE118/include" -I"C:/CMPE118/src" -I"../../../../../../../../../CMPE118/include" -MMD -MF "${OBJECTDIR}/DagobotHSM.o.d" -o ${OBJECTDIR}/DagobotHSM.o DagobotHSM.c     
	
${OBJECTDIR}/DagobotMain.o: DagobotMain.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/DagobotMain.o.d 
	@${RM} ${OBJECTDIR}/DagobotMain.o 
	@${FIXDEPS} "${OBJECTDIR}/DagobotMain.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"C:/CMPE118/include" -I"C:/CMPE118/src" -I"../../../../../../../../../CMPE118/include" -MMD -MF "${OBJECTDIR}/DagobotMain.o.d" -o ${OBJECTDIR}/DagobotMain.o DagobotMain.c     
	
${OBJECTDIR}/TestBumpService.o: TestBumpService.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/TestBumpService.o.d 
	@${RM} ${OBJECTDIR}/TestBumpService.o 
	@${FIXDEPS} "${OBJECTDIR}/TestBumpService.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"C:/CMPE118/include" -I"C:/CMPE118/src" -I"../../../../../../../../../CMPE118/include" -MMD -MF "${OBJECTDIR}/TestBumpService.o.d" -o ${OBJECTDIR}/TestBumpService.o TestBumpService.c     
	
${OBJECTDIR}/Acquiring_AmmoSubHSM.o: Acquiring_AmmoSubHSM.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Acquiring_AmmoSubHSM.o.d 
	@${RM} ${OBJECTDIR}/Acquiring_AmmoSubHSM.o 
	@${FIXDEPS} "${OBJECTDIR}/Acquiring_AmmoSubHSM.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"C:/CMPE118/include" -I"C:/CMPE118/src" -I"../../../../../../../../../CMPE118/include" -MMD -MF "${OBJECTDIR}/Acquiring_AmmoSubHSM.o.d" -o ${OBJECTDIR}/Acquiring_AmmoSubHSM.o Acquiring_AmmoSubHSM.c     
	
${OBJECTDIR}/TestTapeService.o: TestTapeService.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/TestTapeService.o.d 
	@${RM} ${OBJECTDIR}/TestTapeService.o 
	@${FIXDEPS} "${OBJECTDIR}/TestTapeService.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"C:/CMPE118/include" -I"C:/CMPE118/src" -I"../../../../../../../../../CMPE118/include" -MMD -MF "${OBJECTDIR}/TestTapeService.o.d" -o ${OBJECTDIR}/TestTapeService.o TestTapeService.c     
	
${OBJECTDIR}/Wall_Hugging_SubHSM.o: Wall_Hugging_SubHSM.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Wall_Hugging_SubHSM.o.d 
	@${RM} ${OBJECTDIR}/Wall_Hugging_SubHSM.o 
	@${FIXDEPS} "${OBJECTDIR}/Wall_Hugging_SubHSM.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"C:/CMPE118/include" -I"C:/CMPE118/src" -I"../../../../../../../../../CMPE118/include" -MMD -MF "${OBJECTDIR}/Wall_Hugging_SubHSM.o.d" -o ${OBJECTDIR}/Wall_Hugging_SubHSM.o Wall_Hugging_SubHSM.c     
	
${OBJECTDIR}/Portal_DashSubHSM.o: Portal_DashSubHSM.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Portal_DashSubHSM.o.d 
	@${RM} ${OBJECTDIR}/Portal_DashSubHSM.o 
	@${FIXDEPS} "${OBJECTDIR}/Portal_DashSubHSM.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"C:/CMPE118/include" -I"C:/CMPE118/src" -I"../../../../../../../../../CMPE118/include" -MMD -MF "${OBJECTDIR}/Portal_DashSubHSM.o.d" -o ${OBJECTDIR}/Portal_DashSubHSM.o Portal_DashSubHSM.c     
	
${OBJECTDIR}/AA_LineFollowing_SubHSM.o: AA_LineFollowing_SubHSM.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/AA_LineFollowing_SubHSM.o.d 
	@${RM} ${OBJECTDIR}/AA_LineFollowing_SubHSM.o 
	@${FIXDEPS} "${OBJECTDIR}/AA_LineFollowing_SubHSM.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"C:/CMPE118/include" -I"C:/CMPE118/src" -I"../../../../../../../../../CMPE118/include" -MMD -MF "${OBJECTDIR}/AA_LineFollowing_SubHSM.o.d" -o ${OBJECTDIR}/AA_LineFollowing_SubHSM.o AA_LineFollowing_SubHSM.c     
	
${OBJECTDIR}/TestBeaconDetectorService.o: TestBeaconDetectorService.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/TestBeaconDetectorService.o.d 
	@${RM} ${OBJECTDIR}/TestBeaconDetectorService.o 
	@${FIXDEPS} "${OBJECTDIR}/TestBeaconDetectorService.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"C:/CMPE118/include" -I"C:/CMPE118/src" -I"../../../../../../../../../CMPE118/include" -MMD -MF "${OBJECTDIR}/TestBeaconDetectorService.o.d" -o ${OBJECTDIR}/TestBeaconDetectorService.o TestBeaconDetectorService.c     
	
${OBJECTDIR}/Portal_Wall_Hugging_SubHSM.o: Portal_Wall_Hugging_SubHSM.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Portal_Wall_Hugging_SubHSM.o.d 
	@${RM} ${OBJECTDIR}/Portal_Wall_Hugging_SubHSM.o 
	@${FIXDEPS} "${OBJECTDIR}/Portal_Wall_Hugging_SubHSM.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"C:/CMPE118/include" -I"C:/CMPE118/src" -I"../../../../../../../../../CMPE118/include" -MMD -MF "${OBJECTDIR}/Portal_Wall_Hugging_SubHSM.o.d" -o ${OBJECTDIR}/Portal_Wall_Hugging_SubHSM.o Portal_Wall_Hugging_SubHSM.c     
	
${OBJECTDIR}/Engage_Destroy_Wall_Hugging.o: Engage_Destroy_Wall_Hugging.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Engage_Destroy_Wall_Hugging.o.d 
	@${RM} ${OBJECTDIR}/Engage_Destroy_Wall_Hugging.o 
	@${FIXDEPS} "${OBJECTDIR}/Engage_Destroy_Wall_Hugging.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"C:/CMPE118/include" -I"C:/CMPE118/src" -I"../../../../../../../../../CMPE118/include" -MMD -MF "${OBJECTDIR}/Engage_Destroy_Wall_Hugging.o.d" -o ${OBJECTDIR}/Engage_Destroy_Wall_Hugging.o Engage_Destroy_Wall_Hugging.c     
	
${OBJECTDIR}/Engage_DestroySubHSM.o: Engage_DestroySubHSM.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Engage_DestroySubHSM.o.d 
	@${RM} ${OBJECTDIR}/Engage_DestroySubHSM.o 
	@${FIXDEPS} "${OBJECTDIR}/Engage_DestroySubHSM.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"C:/CMPE118/include" -I"C:/CMPE118/src" -I"../../../../../../../../../CMPE118/include" -MMD -MF "${OBJECTDIR}/Engage_DestroySubHSM.o.d" -o ${OBJECTDIR}/Engage_DestroySubHSM.o Engage_DestroySubHSM.c     
	
${OBJECTDIR}/_ext/469261227/AD.o: ../../../Test.X/AD.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/469261227" 
	@${RM} ${OBJECTDIR}/_ext/469261227/AD.o.d 
	@${RM} ${OBJECTDIR}/_ext/469261227/AD.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/469261227/AD.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"C:/CMPE118/include" -I"C:/CMPE118/src" -I"../../../../../../../../../CMPE118/include" -MMD -MF "${OBJECTDIR}/_ext/469261227/AD.o.d" -o ${OBJECTDIR}/_ext/469261227/AD.o ../../../Test.X/AD.c     
	
${OBJECTDIR}/_ext/469261227/BOARD.o: ../../../Test.X/BOARD.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/469261227" 
	@${RM} ${OBJECTDIR}/_ext/469261227/BOARD.o.d 
	@${RM} ${OBJECTDIR}/_ext/469261227/BOARD.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/469261227/BOARD.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"C:/CMPE118/include" -I"C:/CMPE118/src" -I"../../../../../../../../../CMPE118/include" -MMD -MF "${OBJECTDIR}/_ext/469261227/BOARD.o.d" -o ${OBJECTDIR}/_ext/469261227/BOARD.o ../../../Test.X/BOARD.c     
	
${OBJECTDIR}/_ext/469261227/ES_Framework.o: ../../../Test.X/ES_Framework.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/469261227" 
	@${RM} ${OBJECTDIR}/_ext/469261227/ES_Framework.o.d 
	@${RM} ${OBJECTDIR}/_ext/469261227/ES_Framework.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/469261227/ES_Framework.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"C:/CMPE118/include" -I"C:/CMPE118/src" -I"../../../../../../../../../CMPE118/include" -MMD -MF "${OBJECTDIR}/_ext/469261227/ES_Framework.o.d" -o ${OBJECTDIR}/_ext/469261227/ES_Framework.o ../../../Test.X/ES_Framework.c     
	
${OBJECTDIR}/_ext/469261227/LED.o: ../../../Test.X/LED.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/469261227" 
	@${RM} ${OBJECTDIR}/_ext/469261227/LED.o.d 
	@${RM} ${OBJECTDIR}/_ext/469261227/LED.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/469261227/LED.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"C:/CMPE118/include" -I"C:/CMPE118/src" -I"../../../../../../../../../CMPE118/include" -MMD -MF "${OBJECTDIR}/_ext/469261227/LED.o.d" -o ${OBJECTDIR}/_ext/469261227/LED.o ../../../Test.X/LED.c     
	
${OBJECTDIR}/_ext/469261227/pwm.o: ../../../Test.X/pwm.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/469261227" 
	@${RM} ${OBJECTDIR}/_ext/469261227/pwm.o.d 
	@${RM} ${OBJECTDIR}/_ext/469261227/pwm.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/469261227/pwm.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"C:/CMPE118/include" -I"C:/CMPE118/src" -I"../../../../../../../../../CMPE118/include" -MMD -MF "${OBJECTDIR}/_ext/469261227/pwm.o.d" -o ${OBJECTDIR}/_ext/469261227/pwm.o ../../../Test.X/pwm.c     
	
${OBJECTDIR}/_ext/469261227/RC_Servo.o: ../../../Test.X/RC_Servo.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/469261227" 
	@${RM} ${OBJECTDIR}/_ext/469261227/RC_Servo.o.d 
	@${RM} ${OBJECTDIR}/_ext/469261227/RC_Servo.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/469261227/RC_Servo.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"C:/CMPE118/include" -I"C:/CMPE118/src" -I"../../../../../../../../../CMPE118/include" -MMD -MF "${OBJECTDIR}/_ext/469261227/RC_Servo.o.d" -o ${OBJECTDIR}/_ext/469261227/RC_Servo.o ../../../Test.X/RC_Servo.c     
	
${OBJECTDIR}/_ext/469261227/serial.o: ../../../Test.X/serial.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/469261227" 
	@${RM} ${OBJECTDIR}/_ext/469261227/serial.o.d 
	@${RM} ${OBJECTDIR}/_ext/469261227/serial.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/469261227/serial.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"C:/CMPE118/include" -I"C:/CMPE118/src" -I"../../../../../../../../../CMPE118/include" -MMD -MF "${OBJECTDIR}/_ext/469261227/serial.o.d" -o ${OBJECTDIR}/_ext/469261227/serial.o ../../../Test.X/serial.c     
	
${OBJECTDIR}/AlignCollect_SubHSM.o: AlignCollect_SubHSM.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/AlignCollect_SubHSM.o.d 
	@${RM} ${OBJECTDIR}/AlignCollect_SubHSM.o 
	@${FIXDEPS} "${OBJECTDIR}/AlignCollect_SubHSM.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"C:/CMPE118/include" -I"C:/CMPE118/src" -I"../../../../../../../../../CMPE118/include" -MMD -MF "${OBJECTDIR}/AlignCollect_SubHSM.o.d" -o ${OBJECTDIR}/AlignCollect_SubHSM.o AlignCollect_SubHSM.c     
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/DagobotHSMProject.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mdebugger -D__MPLAB_DEBUGGER_PK3=1 -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/DagobotHSMProject.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}              -mreserve=boot@0x1FC02000:0x1FC02FEF -mreserve=boot@0x1FC02000:0x1FC024FF  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map"
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/DagobotHSMProject.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/DagobotHSMProject.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}            -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map"
	${MP_CC_DIR}/xc32-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/DagobotHSMProject.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
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
