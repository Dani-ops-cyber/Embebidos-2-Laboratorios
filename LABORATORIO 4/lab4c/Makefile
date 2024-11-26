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
# The default rule, which causes the labo4c example to be built.
#
all: ${COMPILER}
all: ${COMPILER}/labo4c.axf

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
# Rules for building the labo4c example.
#
${COMPILER}/labo4c.axf: ${COMPILER}/labo4c.o
${COMPILER}/labo4c.axf: ${COMPILER}/startup_${COMPILER}.o
${COMPILER}/labo4c.axf: ${ROOT}/driverlib/${COMPILER}/libdriver.a
${COMPILER}/labo4c.axf: labo4c.ld
SCATTERgcc_labo4c=labo4c.ld
ENTRY_labo4c=ResetISR
CFLAGSgcc=-DTARGET_IS_TM4C129_RA1

#
# Include the automatically generated dependency files.
#
ifneq (${MAKECMDGOALS},clean)
-include ${wildcard ${COMPILER}/*.d} __dummy__
endif
