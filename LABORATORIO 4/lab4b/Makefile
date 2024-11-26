#******************************************************************************
# LABORATORIO 4
# Parpadea el LED de usuario PN1 con interrupciones del temporizador en el Tiva. Inicialmente, 
# haz que el LED parpadee cada segundo. 
# 
#  LED parpadee cada 2 segundos  /  LED parpadee cada 5 segundos
#******************************************************************************

#
# Defines the part type that this project uses.
#
PART=TM4C1294NCPDT

#
# The base directory for TivaWare.
#
ROOT=../../../..

#
# Include the common make definitions.
#
include ${ROOT}/makedefs

#
# Where to find header files that do not live in the source directory.
#
IPATH=../../../..

#
# The default rule, which causes the labo4b example to be built.
#
all: ${COMPILER}
all: ${COMPILER}/labo4b.axf

#
# The rule to clean out all the build products.
#
clean:
	@rm -rf ${COMPILER} ${wildcard *~}

#
# The rule to create the target directory.
#
${COMPILER}:
	@mkdir -p ${COMPILER}

#
# Rules for building the labo4b example.
#
${COMPILER}/labo4b.axf: ${COMPILER}/labo4b.o
${COMPILER}/labo4b.axf: ${COMPILER}/startup_${COMPILER}.o
${COMPILER}/labo4b.axf: ${ROOT}/driverlib/${COMPILER}/libdriver.a
${COMPILER}/labo4b.axf: labo4b.ld
SCATTERgcc_labo4b=labo4b.ld
ENTRY_labo4b=ResetISR
CFLAGSgcc=-DTARGET_IS_TM4C129_RA1

#
# Include the automatically generated dependency files.
#
ifneq (${MAKECMDGOALS},clean)
-include ${wildcard ${COMPILER}/*.d} __dummy__
endif
