# Initializes PSX GPU
# Assumes PSX_Defines.inc is already included
# Assumes $a0 contains IO_BASE (0x1F800000)

.macro GPU_Init

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

.endm

