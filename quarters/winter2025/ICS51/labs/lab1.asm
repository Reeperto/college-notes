#                                           ICS 51, Lab #1
# 
#                                          IMPORTATNT NOTES:
# 
#                       Write your assembly code only in the marked blocks.
# 
#                       DO NOT change anything outside the marked blocks.
# 
#

###############################################################
#                           Text Section
.text

###############################################################
###############################################################
###############################################################
#                            PART 1 (Swap Bits)
# 
# You are given an 32-bits integer stored in $a0. You need swap the bits
# at odd and even positions. i.e. b31 <-> b30, b29 <-> b28, ... , b1 <-> b0
# 
# Implementation details:
# The integer is stored in register $a0. You need to store the answer 
# into register $v0 in order to be returned by the function to the caller.
swap_bits:
    
############################## Part 1: your code begins here ###

    li $v0, 0 # result
    li $t0, 1 # mask
    li $t1, 0 # iteration counter

swap_loop:
    ## put bit n to n+1
    and $t2, $a0, $t0   # mask off bit n into t2
    sll $t2, $t2, 1     # shift t2 left 1 bit
    or $v0, $v0, $t2    # put bit in t2 into v0
    sll $t0, $t0, 1     # shift mask +1

    ## put bit n+1 to n
    and $t2, $a0, $t0   # mask off bit n into t2 
    srl $t2, $t2, 1     # shift t2 right 1 bit
    or $v0, $v0, $t2    # put bit in t2 into v0
    sll $t0, $t0, 1     # shift mask +1

    addi $t1, $t1, 2    # increment bit position +2

    bne $t1, 32, swap_loop # loop until last bit

############################## Part 1: your code ends here ###
jr $ra

###############################################################
###############################################################
###############################################################
#                           PART 2 (Triple Range)
# 
# You are given three integers. You need to find the smallest 
# one and the largest one and multiply their sum by three and return it.
# 
# Implementation details:
# The three integers are stored in registers $a0, $a1, and $a2. You 
# need to store the answer into register $v0 in order to be returned by 
# the function to the caller.
triple_range:
############################### Part 2: your code begins here ##
    move $t0, $a0 # $t0 is minimum
    move $t1, $a0 # $t1 is maximum

.macro check_min_max(%x)
    sgt $t2, %x, $t0 # t2 = %x > $t0
    slt $t3, %x, $t1 # t3 = %x < $t1

    movz $t0, %x, $t2 # put %x into $t0 if $t2 == 0
    movz $t1, %x, $t3 # put %x into $t1 if $t3 == 0
.end_macro

    check_min_max($a0)
    check_min_max($a1)
    check_min_max($a2)

    add $v0, $t0, $t1
    mul $v0, $v0, 3

############################### Part 2: your code ends here  ##
jr $ra

###############################################################
###############################################################
###############################################################
#                            PART 3 (Determinant)
# 
# You are given a 2x2 matrix and each element is a 16-bit 
# signed integer. Calculate its determinant.
# 
# Implementation details:
# The four 16-bit integers are stored in registers $a0, $a1. 
# You need to store the answer into register $v0 in order to 
# be returned by the function to the caller.
determinant:
############################## Part 3: your code begins here ###

    # Extract {a,b} from a0
    andi $t0, $a0, 0xFFFF0000
    sra $t0, $t0, 16
    andi $t1, $a0, 0x0000FFFF
    sll $t1, $t1, 16
    sra $t1, $t1, 16

    # Extract {c,d} from a0
    andi $t2, $a1, 0xFFFF0000
    sra $t2, $t2, 16
    andi $t3, $a1, 0x0000FFFF
    sll $t3, $t3, 16
    sra $t3, $t3, 16

    mul $t0, $t0, $t3 # t0 = a * d
    mul $t1, $t1, $t2 # t1 = b * c

    sub $v0, $t0, $t1

############################## Part 3: your code ends here ###
jr $ra

