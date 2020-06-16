# BJ Testing Assembly lang w/ mipsel-unknown-elf-gcc

#    .set noreoder
    .section .text

# GPU Registers
    .equ GP0, 0x1810 # $1F801810..$1F801813 GPU Registers: Write GP0 Commands/Packets (Rendering & VRAM Access)
    .equ GP1, 0x1814 # $1F801814..$1F801817 GPU Registers: Write GP1 Commands (Display Control)

# I/O Map
    .equ IO_BASE, 0x1F800000 # I/O Port Base Address ($1F80XXXX)

#==================================================================================
# GPU Display Control Commands (GP1) (Command = 8-Bit MSB, Parameter = 24-Bit LSB)
#==================================================================================
    .equ GPURESET,  0x00<<24 # GPU Display Control Commands (GP1): $00 - Reset GPU
    .equ GPUDISPEN, 0x03<<24 # GPU Display Control Commands (GP1): $03 - Display Enable
    .equ GPUDISPH,  0x06<<24 # GPU Display Control Commands (GP1): $06 - Horizontal Display Range (On Screen)
    .equ GPUDISPV,  0x07<<24 # GPU Display Control Commands (GP1): $07 - Vertical Display Range (On Screen)
    .equ GPUDISPM,  0x08<<24 # GPU Display Control Commands (GP1): $08 - Display Mode

    .equ HRES320, 0x01 # Display Mode: Horizontal Resolution 1 320 (Bit 0..1)
    .equ VRES240, 0x00 # Display Mode: Vertical Resolution 240 (Bit 2)
    .equ VNTSC,   0x00 # Display Mode: Video Mode NTSC 60Hz (Bit 3)
    .equ BPP15,   0x00 # Display Mode: Display Area Color Depth 15BPP R5/G5/B5 (Bit 4)

#=================================
# GPU Rendering Attributes (GP0)
#=================================
    .equ GPUDRAWM,   0xE1<<24 # GPU Rendering Attributes (GP0): $E1 - Draw Mode Setting (AKA "Texpage")
    .equ GPUDRAWATL, 0xE3<<24 # GPU Rendering Attributes (GP0): $E3 - Set Drawing Area Top Left (X1, Y1)
    .equ GPUDRAWABR, 0xE4<<24 # GPU Rendering Attributes (GP0): $E4 - Set Drawing Area Bottom Right (X2, Y2)
    .equ GPUDRAWOFS, 0xE5<<24 # GPU Rendering Attributes (GP0): $E5 - Set Drawing Offset (X,Y)

    .globl main
    .ent main
    .type main, @function
main:
	.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, gp= 0
	.mask	0x00000000,0
	.fmask	0x00000000,0

# A0 = I/O Port Base Address ($1F80XXXX)
    la $a0, IO_BASE 

# Write GP1 - Reset GPU
    li $t0, GPURESET + (0 & 0xFFFFFF) # command = GPURESET, parameter = 0
    sw $t0, GP1($a0) # $a0 = IO_BASE

# Write GP1 - Enable Display
    li $t0, GPUDISPEN + (0 & 0xFFFFFF) # command = GPUDISPEN, parameter = 0
    sw $t0, GP1($a0) # $a0 = IO_BASE

# TODO - I believe these parameters are technically incorrect and should
# be shifted appropriately based on their bit positions above
# they just happen to work for this case since they're mostly zeros
# Write GP1 - Set Display Mode (320x240, 15BPP, NTSC)
    li $t0, GPUDISPM + ((HRES320+VRES240+BPP15+VNTSC) & 0xFFFFFF)
    sw $t0, GP1($a0)

# Write GP1 - Horizontal Display Range 608..3168
    li $t0, GPUDISPH + (0xC60260 & 0xFFFFFF)
    sw $t0, GP1($a0)

# Write GP1 - Vertical Display Range 24..264
    li $t0, GPUDISPV + (0x042018 & 0xFFFFFF)
    sw $t0, GP1($a0)

# Write GP0 Command Word (Drawing To Display Area Allowed Bit 10)
    li $t0, GPUDRAWM + (0x000400 & 0xFFFFFF)
    sw $t0, GP0($a0)

# Write GP0 Command Word (Set Drawing Area Top Left X1=0, Y1=0)
    li $t0, GPUDRAWATL + (0x000000 & 0xFFFFFF)
    sw $t0, GP0($a0)

# Write GP0 Command Word (Set Drawing Area Bottom Right X2=319, Y2=239)
    li $t0, GPUDRAWABR + (0x03BD3F & 0xFFFFFF)
    sw $t0, GP0($a0)

# Write GP0 Command Word (Set Drawing Offset X=0, Y=0)
    li $t0, GPUDRAWOFS + (0x000000 & 0xFFFFFF)
    sw $t0, GP0($a0)

# forever loop
infloop:

# Clear Screen - Fill Rect in VRAM
    li $t0, (0x02<<24)+(0xFF0000&0xFFFFFF) # Write GP0 Command Word (Color+Command), 0xFF0000 = color = blue
    sw $t0, GP0($a0)
    li $t0, (0x00<<16) + (0x00 & 0xFFFF) # Write GP0 Packet Word (Top left corner, X = LSB (0x00) Counted In Halfwords, Steps Of $10), Y = MSB (<<16)
    sw $t0, GP0($a0)
    li $t0, (239<<16) + (319 & 0xFFFF) # Write GP0 Packet Word (Width+Height: Width  = LSB (319) counted in halfwords, steps of $10)
    sw $t0, GP0($a0)

# jump back to infinite loop
    b       infloop 

    .end    main           # mark end of main function


