#                         ICS 51, Lab #3
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
###############################################################
#                           PART 1 (fib_recur)
# $a0: input number
###############################################################
fib_recur:
############################### Part 1: your code begins here ##
.macro push(%x)
    addiu $sp, $sp, -4
    sw    %x, ($sp)
.end_macro

.macro pop(%x)
    lw    %x, ($sp)
    addiu $sp, $sp, 4
.end_macro

    bgt $a0, 1, fib_rec
    move $v0, $a0
    j fib_ret
fib_rec:
    push($ra)          # [ ra ]
    push($a0)          # [ ra, n ]
    subi $a0, $a0, 1   # $a0 = n -1
    jal fib_recur

    pop($a0)           # [ ra ], a0 = n
    push($v0)          # [ ra, fib(n-1) ]

    subi $a0, $a0, 2   # $a0 = n - 2
    jal fib_recur     

    pop($t0)           # [ ra ], t0 = fib(n-1)
    add $v0, $t0, $v0  # v0 = fib(n-1) + fib(n-2)

    pop($ra)           # [ ], $ra = ra
fib_ret:
    
############################### Part 1: your code ends here  ##
jr $ra

###############################################################
###############################################################
###############################################################
#                           PART 2 (catalan_recur)
# $a0: input number
###############################################################
catalan_recur:
############################### Part 2: your code begins here ##

    # STACK:
    # 0  => ra
    # 4  => n
    # 8  => i
    # 12 => sum
    # 16 => temp

    addiu $sp, $sp, -20
    sw    $ra,  0($sp)

    bgt   $a0, 1, catalan_inner # n > 1

    addi  $v0, $0, 1
    sw    $v0, 12($sp)
    j     catalan_ret

catalan_inner:
    sw    $a0,  4($sp) # n
    sw    $0,   8($sp) # i
    sw    $0,  12($sp) # sum

catalan_loop:
    lw    $a0, 4($sp)                # $a0 = n
    lw    $t0, 8($sp)                # $t0 = i
    bge   $t0, $a0, catalan_ret      # i >= n ? ret : continue

    move  $a0, $t0                   # $a0 = i
    jal   catalan_recur              
    sw    $v0, 16($sp)               # temp = catalan(i)

    lw    $a0, 4($sp)                # $a0 = n
    lw    $t0, 8($sp)                # $t0 = i
    sub   $a0, $a0, $t0              # $a0 = $a0 - $t0 = n - i
    subi  $a0, $a0, 1                # $a0 = $a0 - 1   = n - i - 1
    jal   catalan_recur

    lw    $t2, 16($sp)               # $t2 = temp
    mul   $t3, $v0, $t2              # $t3 = temp * catalan(i-1) = catalan(i) * catalan(i-1)
    
    lw    $t1, 12($sp)               # $t1  = sum
    add   $t1, $t1, $t3              # $t1 += $t3 = catalan(i) * catalan(i-1)
    sw    $t1, 12($sp)               # sum  = $t1

    lw    $t0, 8($sp)                # $t0  = i
    addi  $t0, $t0, 1                # $t0 += 1
    sw    $t0, 8($sp)                # i    = $t0

    j     catalan_loop

catalan_ret:
    lw    $v0,  12($sp)

    lw    $ra,  0($sp)
    addiu $sp, $sp, 20
############################### Part 2: your code ends here  ##
jr $ra

###############################################################
###############################################################
###############################################################
#                           PART 3A (SYSCALL: file read, ASCII to Integer)
#
# $a0: the address of the string that represents the input file name
# $a1: the base address of an integer array that will be used to store distances
# data_buffer : the buffer that you use to hold data for file read (MAXIMUM: 300 bytes)
load_pts_file:
############################### Part 3A: your code begins here ##
    addiu $sp, $sp, -8
    sw    $a0, 0($sp)
    sw    $a1, 4($sp)

    li    $v0, 13            # system call for open file
                             # a0 is already ready for file name
    li    $a1, 0             # Open for reading (flags are 0: read, 1: write)
    li    $a2, 0             # mode is ignored
    syscall                  # open a file (file descriptor returned in $v0)
    move  $t0, $v0           # save the file descriptor 

    li    $v0, 14            # system call for read file
    move  $a0, $t0           # file descriptor 
    la    $a1, data_buffer   # address of buffer from which to read
    li    $a2, 300           # max hardcoded buffer length
    syscall                  # read file

    li    $v0, 16            # close file
    move  $a0, $t0           # file descrip to close
    syscall

    lw    $a0, 0($sp)
    lw    $a1, 4($sp)


    # Registers:
    #   
    #   $t0 = current char / numerical value
    #   $t1 = number 1
    #   $t2 = number 2
    #   $t3 = is negative flag
    #   $t4 = data buffer pointer
    #   $v0 = number of distances
    #

    la    $t4, data_buffer
    li    $t1, 0
    li    $t2, 0
    li    $t3, 0
    li    $v0, 0

load_loop_num1:
    lb    $t0, ($t4)
    beqz  $t0, load_ret

    beq   $t0, 0x0A, load_next_line  # $t0 == '\n'
    beq   $t0, 0x20, load_next_num   # $t0 == ' '
    beq   $t0, 0x2D, load_negative_num1

    subi  $t0, $t0, 0x30             # $t0 -= '0'
    
    mul   $t1, $t1, 10               # $t1 *= 10
    add   $t1, $t1, $t0              # $t1 += $t0

    addiu $t4, $t4, 1
    j     load_loop_num1

load_negative_num1:
    ori   $t3, $t3, 1
    addiu $t4, $t4, 1
    j     load_loop_num1

load_next_num:
    mul   $t3, $t3, -2
    addi  $t3, $t3, 1
    mul   $t1, $t1, $t3

    li    $t3, 0

    addi  $t4, $t4, 1

load_loop_num2:
    lb    $t0, ($t4)
    beqz  $t0, load_ret

    beq   $t0, 0x0A, load_next_line  # $t0 == '\n'
    beq   $t0, 0x2D, load_negative_num2

    subi  $t0, $t0, 0x30             # $t0 -= '0'
    
    mul   $t2, $t2, 10               # $t2 *= 10
    add   $t2, $t2, $t0              # $t2 += $t0

    addiu $t4, $t4, 1
    j     load_loop_num2

load_negative_num2:
    ori   $t3, $t3, 1
    addiu $t4, $t4, 1
    j     load_loop_num2

load_next_line:
    mul   $t3, $t3, -2
    addi  $t3, $t3, 1
    mul   $t2, $t2, $t3

    bge   $t1, $t2, load_num1_sub_num2

load_num2_sub_num1:
    sub   $t9, $t2, $t1
    j     load_store_dist

load_num1_sub_num2:
    sub   $t9, $t1, $t2

load_store_dist:
    sw    $t9, ($a1)

    li    $t1, 0
    li    $t2, 0
    li    $t3, 0

    addi  $v0, $v0, 1
    addi  $t4, $t4, 1
    addi  $a1, $a1, 4
    j     load_loop_num1
    
load_ret:
    lw    $a0, 0($sp)
    lw    $a1, 4($sp)
    addiu $sp, $sp, 8
############################### Part 3A: your code ends here   ##
jr $ra

###############################################################
###############################################################
###############################################################
#                           PART 3B (SYSCALL: file write, Integer to ASCII)
#
# $a0: the address of the string that represents the output file name
# $a1: the base address of an integer array that stores distances
# $a2: the number of valid distances to the integer array
# data_buffer : the buffer that you use to hold data for file read (MAXIMUM: 300 bytes)
save_dist_list:
############################### Part 3B: your code begins here ##
    addiu $sp, $sp, -12
    sw    $a0, 0($sp)
    sw    $a1, 4($sp)
    sw    $a2, 8($sp)

    # Registers:
    # 
    #   $t0 = current distance
    #   $t1 = current digit
    #   $t2 = # of bytes to write
    #   $t3 = current buf pos
    #   $t7 = digit place
    #   $t8 = constant, '\n'
    #   $t9 = constant, 10
    #

    li    $t2, 0
    la    $t3, data_buffer
    li    $t8, 0x0A
    li    $t9, 10

save_dist_loop:
    beqz  $a2, save_dist_write
    lw    $t0, ($a1)
    li    $t7, 1

save_dist_magnitude:
    mul   $t7, $t7, $t9
    bge   $t0, $t7, save_dist_magnitude

    div   $t7, $t9
    mflo  $t7

save_dist_digit_loop:
    div   $t0, $t7
    mfhi  $t0
    mflo  $t1

    div   $t7, $t9
    mflo  $t7

    addi  $t1, $t1, 0x30

    sb    $t1, ($t3)
    addiu $t3, $t3, 1
    addi  $t2, $t2, 1

    bgtz  $t7, save_dist_digit_loop

    sb    $t8, ($t3)
    addiu $t3, $t3, 1
    addi  $t2, $t2, 1

    addi  $a2, $a2, -1
    addi  $a1, $a1, 4
    j     save_dist_loop

save_dist_write:
    li    $v0, 13
    li    $a1, 1
    li    $a2, 1
    syscall

    move  $a0, $v0
    li    $v0, 15
    la    $a1, data_buffer
    move  $a2, $t2
    syscall

    addiu $sp, $sp, 12
    lw    $a0, 0($sp)
    lw    $a1, 4($sp)
    lw    $a2, 8($sp)

############################### Part 3B: your code ends here   ##
jr $ra
