# PSX system vars

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
