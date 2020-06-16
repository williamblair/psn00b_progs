## ASM Program 2: GPU initialization and screen clear
### Inits the GPU via registers GP0 and GP1, then fills the screen blue

## Registers: GP1

GP1 is for managing the display: initialization, NSTC/PAL, BPP, etc.
Register location is 0x1F801814. Command instructions are in the following form:
the 8 most significant bits are the command, then the remaining 24 bits are 
parameters for the command (for a total of 32 bits, or 1 word)

## Registers: GP0
GP0 is for Rendering and VRAM management - you send it drawing commands, drawing area, 
primitive drawing packets, etc. Register location is 0x1F801810.
For the most part the command format are the same as GP1: 8 MSB command, remaining 24
parameter, however, some commands require further packets as information to be written
next to GP0, which have different formats. For example, the last GP0 command in this
program is a fill rectangle command (0x0200 0xBBGGRR). After this command is written,
the next two words written to GP0 are first the top left corner of the drawing rectangle
(0xYYYY 0xXXXX) then the width and height of the rectangle (0xHHHH 0xWWWW). There
each parameter takes up 16 out of 32 bits. 

