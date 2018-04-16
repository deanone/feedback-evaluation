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
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/Cluster.o \
	${OBJECTDIR}/Kmeans.o \
	${OBJECTDIR}/MixedTypeDataFunctions.o \
	${OBJECTDIR}/PropertiesParser.o \
	${OBJECTDIR}/TravelProfile.o \
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
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/clustering

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/clustering: /usr/lib/x86_64-linux-gnu/libcurl-gnutls.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/clustering: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/clustering ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/Cluster.o: Cluster.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -Irapidjson-master/rapidjson-master/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Cluster.o Cluster.cpp

${OBJECTDIR}/Kmeans.o: Kmeans.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -Irapidjson-master/rapidjson-master/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Kmeans.o Kmeans.cpp

${OBJECTDIR}/MixedTypeDataFunctions.o: MixedTypeDataFunctions.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -Irapidjson-master/rapidjson-master/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/MixedTypeDataFunctions.o MixedTypeDataFunctions.cpp

${OBJECTDIR}/PropertiesParser.o: PropertiesParser.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -Irapidjson-master/rapidjson-master/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/PropertiesParser.o PropertiesParser.cpp

${OBJECTDIR}/TravelProfile.o: TravelProfile.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -Irapidjson-master/rapidjson-master/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/TravelProfile.o TravelProfile.cpp

${OBJECTDIR}/WebService.o: WebService.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -Irapidjson-master/rapidjson-master/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/WebService.o WebService.cpp

${OBJECTDIR}/main.o: main.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -Irapidjson-master/rapidjson-master/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.cpp

${OBJECTDIR}/restclient.o: restclient.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -Irapidjson-master/rapidjson-master/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/restclient.o restclient.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} -r ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libcurl-gnutls.so
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/clustering

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
