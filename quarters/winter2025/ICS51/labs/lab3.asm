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
    li   $v0, 13       # system call for open file
    # a0 is already ready for file name
    li   $a1, 0        # Open for reading (flags are 0: read, 1: write)
    li   $a2, 0        # mode is ignored
    syscall            # open a file (file descriptor returned in $v0)
    move $t0, $v0      # save the file descriptor 

    li   $v0, 14       # system call for read file
    move $a0, $t0      # file descriptor 
    la   $a1, data_buffer   # address of buffer from which to read
    li   $a2, 300       # max hardcoded buffer length
    syscall            # read file

    li $v0, 16 # close file
    move $a0, $t0 # file descrip to close
    syscall

    la $s1, data_buffer
loop3a:
    lb $t0, ($s1)
    beqz $t0, end3
    beq $t0, 0x0A, next
    beq $t0, 0x20, next
    addi $t1, $t0, -48
    mul $t1, $t1, 10
    add $t1, $t1, $t0
    j loop3a
next:
end3:
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

############################### Part 3B: your code ends here   ##
jr $ra
