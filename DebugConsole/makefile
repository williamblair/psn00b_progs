include ../sdk-common.mk

TARGET		= Console.elf

CFILES		= $(notdir $(wildcard *.c))
CPPFILES 	= $(notdir $(wildcard *.cpp))
AFILES		= $(notdir $(wildcard *.s))

OFILES		= $(addprefix build/,$(CFILES:.c=.o) $(CPPFILES:.cpp=.o) $(AFILES:.s=.o))

INCLUDE	 	+= -I.
LIBDIRS		+= 

LIBS		= -lc -lpsxetc -lpsxgpu -lpsxgte -lpsxspu -lpsxapi -lgcc

CFLAGS		= -g -O2 -fno-builtin -fdata-sections -ffunction-sections
CPPFLAGS	= $(CFLAGS) -fno-exceptions
AFLAGS		= -g -msoft-float
LDFLAGS		= -g -Ttext=0x80010000 -gc-sections -T $(GCC_BASE)/mipsel-unknown-elf/lib/ldscripts/elf32elmip.x

CC			= $(PREFIX)gcc
CXX			= $(PREFIX)g++
AS			= $(PREFIX)as
LD			= $(PREFIX)ld

all: $(OFILES)
	$(LD) $(LDFLAGS) $(LIBDIRS) $(OFILES) $(LIBS) -o $(TARGET)
	elf2x -q $(TARGET)
	
build/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@
	
build/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CPPFLAGS) $(INCLUDE) -c $< -o $@

build/%.o: %.s
	@mkdir -p $(dir $@)
	$(CC) $(AFLAGS) $(INCLUDE) -c $< -o $@
	
clean:
	rm -rf build $(TARGET) $(TARGET:.elf=.exe)

run:
	/d/psx/no\$$psx/NO\$$PSX.EXE $(TARGET:.elf=.exe)

