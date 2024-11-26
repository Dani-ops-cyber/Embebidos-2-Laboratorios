#******************************************************************************

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
# The default rule, which causes the labo4d example to be built.
#
all: ${COMPILER}
all: ${COMPILER}/labo4d.axf

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
# Rules for building the labo4d example.
#
${COMPILER}/labo4d.axf: ${COMPILER}/labo4d.o
${COMPILER}/labo4d.axf: ${COMPILER}/startup_${COMPILER}.o
${COMPILER}/labo4d.axf: ${ROOT}/driverlib/${COMPILER}/libdriver.a
${COMPILER}/labo4d.axf: labo4d.ld
SCATTERgcc_labo4d=labo4d.ld
ENTRY_labo4d=ResetISR
CFLAGSgcc=-DTARGET_IS_TM4C129_RA1

#
# Include the automatically generated dependency files.
#
ifneq (${MAKECMDGOALS},clean)
-include ${wildcard ${COMPILER}/*.d} __dummy__
endif
