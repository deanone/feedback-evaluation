#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux
CND_DLIB_EXT=so
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/PropertiesParser.o \
	${OBJECTDIR}/Rating.o \
	${OBJECTDIR}/Reputation.o \
	${OBJECTDIR}/WebService.o \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/restclient.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=/usr/lib/x86_64-linux-gnu/libcurl-gnutls.so

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/reputationestimation

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/reputationestimation: /usr/lib/x86_64-linux-gnu/libcurl-gnutls.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/reputationestimation: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/reputationestimation ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/PropertiesParser.o: PropertiesParser.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Irapidjson-master/rapidjson-master/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/PropertiesParser.o PropertiesParser.cpp

${OBJECTDIR}/Rating.o: Rating.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Irapidjson-master/rapidjson-master/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Rating.o Rating.cpp

${OBJECTDIR}/Reputation.o: Reputation.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Irapidjson-master/rapidjson-master/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Reputation.o Reputation.cpp

${OBJECTDIR}/WebService.o: WebService.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Irapidjson-master/rapidjson-master/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/WebService.o WebService.cpp

${OBJECTDIR}/main.o: main.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Irapidjson-master/rapidjson-master/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.cpp

${OBJECTDIR}/restclient.o: restclient.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Irapidjson-master/rapidjson-master/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/restclient.o restclient.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} -r ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libcurl-gnutls.so
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/reputationestimation

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
