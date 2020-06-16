## ASM Program 1: Hello World 
### infinite loop of setting 2 register values

This program just verifies successful compilation and the registers
are modified as expected

Using NO$PSX, you can set a breakpoint at 80010000 (the entry point for
PSX programs) and step one line at a time to verify the register values $v0
and $v1 are updated as expected

The base code is based off of hello.c.bak, which was compiled to assembly with:

    mipsel-unknown-elf-gcc -g -O2 -fno-builtin -fdata-sections -ffunction-sections \
                            -I../../../libpsn00b/include \
                            -I/d/mipsel-unknown-elf/lib/gcc/mipsel-unknown-elf/7.4.0/include \
                            -S hello.c -o hello.s


