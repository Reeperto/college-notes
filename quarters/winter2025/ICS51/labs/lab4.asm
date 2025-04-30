#                         ICS 51, Lab #4
#
#      IMPORTANT NOTES:
#
#      Write your assembly code only in the marked blocks.
#
#      DO NOT change anything outside the marked blocks.
#
###############################################################
#                           Text Section
.text

###############################################################
###############################################################
#                       PART 1 (Image Thresholding)
#a0: input buffer address
#a1: output buffer address
#a2: image dimension (Image will be square sized, i.e., number of pixels = a2*a2)
#a3: threshold value 
###############################################################
threshold:
############################## Part 1: your code begins here ###
    addi $sp, $sp, -12
    sw   $a0, 0($sp)
    sw   $a1, 4($sp)
    sw   $a2, 8($sp)

    mul  $a2, $a2, $a2

threshold_loop:
    beqz $a2, threshold_ret
    addi $a2, $a2, -1

    lbu  $t1, ($a0)
    sge  $t0, $t1, $a3
    mul  $t0, $t0, 255

    sb   $t0, ($a1)

    addi $a0, $a0, 1
    addi $a1, $a1, 1

    j threshold_loop

threshold_ret:
    lw   $a0, 0($sp)
    lw   $a1, 4($sp)
    lw   $a2, 8($sp)
    addi $sp, $sp,  12
############################## Part 1: your code ends here ###
jr $ra

###############################################################
###############################################################
#                           PART 2 (Matrix Transform)
#a0: input buffer address
#a1: output buffer address
#a2: transform matrix address
#a3: image dimension  (Image will be square sized, i.e., number of pixels = a3*a3)
###############################################################
transform:
############################### Part 2: your code begins here ##
    addi $sp, $sp, -8
    sw   $a0,  ($sp)
    sw   $a1, 4($sp)

    li   $t0, 0 # x
    li   $t1, 0 # y

    move $t4, $a3      # size = length
    mul  $t4, $t4, $t4 # [ size = length^2 ]

transform_loop:
    beqz $t4, transform_ret
    subi $t4, $t4, 1

    li   $t2, 0 # x0
    li   $t3, 0 # y0
         
    # x0  += M_00 * x
    lw   $t9, 0($a2)
    mul  $t8, $t0, $t9
    add  $t2, $t2, $t8
         
    # x0  += M_01 * y
    lw   $t9, 4($a2)
    mul  $t8, $t1, $t9
    add  $t2, $t2, $t8
         
    # x0  += M_02
    lw   $t9, 8($a2)
    add  $t2, $t2, $t9
         
    # y0  += M_00 * x
    lw   $t9, 12($a2)
    mul  $t8, $t0, $t9
    add  $t3, $t3, $t8
         
    # y0  += M_01 * y
    lw   $t9, 16($a2)
    mul  $t8, $t1, $t9
    add  $t3, $t3, $t8

    # y0 += M_02
    lw   $t9, 20($a2)
    add  $t3, $t3, $t9

    bge  $t2, $a3, transform_skip # if x0 >= length -> skip
    bge  $t3, $a3, transform_skip # if y0 >= length -> skip
    blt  $t2, $0,  transform_skip # if x0 < 0       -> skip
    blt  $t3, $0,  transform_skip # if y0 < 0       -> skip

    mul  $t9, $t3, $a3  # idx  = y0 * length
    add  $t9, $t9, $t2  # idx += x0

    add  $t8, $a0, $t9  # addr = input_base + idx
    lbu  $t9, ($t8)     # val  = *addr
 
    sb   $t9, ($a1)     # *output_base = val

    b    transform_next

transform_skip:
    sb   $0, ($a1)

transform_next:
    addi $t0, $t0, 1
    sge  $t9, $t0, $a3 # larger = x >= size
    add  $t1, $t1, $t9 # y += larger

    mul  $t9, $t9, $a3
    sub  $t0, $t0, $t9 

    addi $a1, $a1, 1

    j transform_loop

transform_ret:
    addi $sp, $sp, 8
    lw   $a0,  ($sp)
    lw   $a1, 4($sp)
    
############################### Part 2: your code ends here  ##
jr $ra
###############################################################
