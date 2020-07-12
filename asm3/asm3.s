# BJ Testing Assembly lang w/ mipsel-unknown-elf-gcc

#    .set noreoder
    .section .text

    .include "PSX_DEFINES.inc"
    .include "GPU_Init.inc"

    .globl main
    .ent main
    .type main, @function
main:
	.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, gp= 0
	.mask	0x00000000,0
	.fmask	0x00000000,0

# A0 = I/O Port Base Address ($1F80XXXX)
    la $a0, IO_BASE 

# Resets, enables display, Set display mode, display range, display area
    GPU_Init

# Clear Screen - Fill Rect in VRAM
    li $t0, (0x02<<24)+(0x550000&0xFFFFFF) # Write GP0 Command Word (Color+Command), 0x550000 = color = darkblue
    sw $t0, GP0($a0)
    li $t0, (0x00<<16) + (0x00 & 0xFFFF) # Write GP0 Packet Word (Top left corner, X = LSB (0x00) Counted In Halfwords, Steps Of $10), Y = MSB (<<16)
    sw $t0, GP0($a0)
    li $t0, (239<<16) + (319 & 0xFFFF) # Write GP0 Packet Word (Width+Height: Width  = LSB (319) counted in halfwords, steps of $10)
    sw $t0, GP0($a0)

# Prepare to draw string
    la $a1, FontBlack
    la $a2, HelloStr
    li $t0, 12              # length of HelloStr string
    li $t1, 10              # X location to draw
    li $t2, 10              # Y location to draw

DrawString:
    li $t3, 0xA0<<24    # 0xA0<<24 = DATA command
    sw $t3, GP0($a0)

    # Send X and Y location to draw at
    # $t3 = (Y<<16) | X
    sll $t3, $t2, 16    # Put Y location in upper 16 bits of $t3
    addu $t3, $t1       # Puts X location in lower 16 bits of $t3
    sw $t3, GP0($a0)

    # Send width and height of rectangle
    li $t3, (8<<16)+8   # height = 8<<16, width = 8
    sw $t3, GP0($a0)

    # Send the actual data
    lbu $a3, 0($a2)         # lbu = load unsigned byte; loads hellostr data address into $a3
    li $t3, ((8*8)/2) - 1   # amount of data to copy = width*height, over two because of 8bit->16bit
    sll $a3, 7              # $a3 *= 128
    addu $a3, $a1           # $a3 = texture RAM font offset

    CopyTexture:
        
        lw $t4, 0($a3)          # Read 32 bits from the FontBlack data at current string val ($a2)
        addiu $a3, 4            # $a3 += 4 (delay slot)
        sw $t4, GP0($a0)        # write the data to GP0
        subu $t3, 1            # $t3-- (amount to copy decrease since we copied a word)
        bnez $t3, CopyTexture   # if ($t3 !=0) GOTO CopyTexture

    addiu $a2, 1            # increment text offset (HelloStr pointer)
    addiu $t1, 8            # Add text width to drawing X position (X += 8)
    subu $t0, 1            # $t0--
    bnez  $t0, DrawString   # $t0 tracks number of characters drawn, so number of characters left

# forever loop
infloop:

# jump back to infinite loop
    b       infloop 

    .end    main           # mark end of main function


# Data stuff
    .section .data
    .align 4
FontBlack:
    .incbin "FontBlack8x8.bin"
HelloStr:
    .ascii "Hello World!" # length = 12


