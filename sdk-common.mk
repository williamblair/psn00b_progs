# Adjustable common makefile values for PSn00bSDK example programs.
# You may need to modify these values to match with your toolchain setup.

# psn00bsdk directory
PSN00B_BASE  = /d/Programming/psx/psn00bsdk

# Toolchain prefix
PREFIX		= mipsel-unknown-elf-

# Include directories
INCLUDE	 	= -I$(PSN00B_BASE)/libpsn00b/include

# Library directories, last entry must point toolchain libraries
LIBDIRS		= -L$(PSN00B_BASE)/libpsn00b

ifndef GCC_VERSION

GCC_VERSION	= 7.4.0

endif

ifndef GCC_BASE

ifeq "$(OS)" "Windows_NT"	# For Windows

GCC_BASE	= /d/mipsel-unknown-elf

else						# For Linux/BSDs

GCC_BASE	= /usr/local/mipsel-unknown-elf

endif

endif

LIBDIRS 	+= -L$(GCC_BASE)/lib/gcc/mipsel-unknown-elf/$(GCC_VERSION)
INCLUDE	 	+= -I$(GCC_BASE)/lib/gcc/mipsel-unknown-elf/$(GCC_VERSION)/include
