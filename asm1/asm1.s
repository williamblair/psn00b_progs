# BJ Testing Assembly lang w/ mipsel-unknown-elf-gcc
#    .set noreoder
    .section .text
    .globl main
    .ent main
    .type main, @function
main:
	.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, gp= 0
	.mask	0x00000000,0
	.fmask	0x00000000,0

   
# forever loop
infloop:
    li      $v0, 4
    li      $v1, 76
    b       infloop 

    .end    main           # mark end of main function

