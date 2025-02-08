#                                           ICS 51, Lab #2
# 
#                                          IMPORTANT NOTES:
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
#                            PART 1 (Fibonacci)
#
# 	The Fibonacci Sequence is the series of integer numbers:
#
#		0, 1, 1, 2, 3, 5, 8, 13, 21, 34, ...

#	The next number is found by adding up the two numbers before it.
	
#	The `2` is found by adding the two numbers before it (1+1)
#	The `3` is found by adding the two numbers before it (1+2),
#	And the `5` is (2+3),
#	and so on!
#
# You should compute N ($a0) number of elements of fibonacci and put
# in array, named fib_array.
# 
fibonacci:
# $a0: Number of elements. 
# fib_array: The destination array.
################## Part 1: your code begins here ###############
    
    la $t0, fib_array
    li $t1, 0 # f_prev = 0
    li $t2, 1 # f_curr = 1
    li $t3, 2 # index  = 2

    blt $a0, 1, fib_return   # n < 1 => return
    sw $t1, ($t0)
    blt $a0, 2, fib_return   # n < 2 => return
    sw $t2, 4($t0)

    addi $t0, $t0, 8

fib_loop:
    bge $t3, $a0, fib_return # if i >= n, return
    move $t5, $t2            # temp = f_curr
    add $t2, $t2, $t1        # f_curr = f_curr + f_prev
    move $t1, $t5            # f_prev = temp

    sw $t2, ($t0)           # fib_array[i] = f_curr

    addi $t0, $t0, 4         
    addi $t3, $t3, 1         # i += 1

    j fib_loop
    
fib_return:

############################## Part 1: your code ends here   ###
jr $ra

###############################################################
###############################################################
###############################################################
#                  PART 2 (local maximum points)
# Write a function in MIPS assembly that takes an array of 
# integers and finds local maximum points. i.e., points that if 
# the input entry is larger than both adjacent entries. The 
# output is an array of the same size of the input array. The 
# output point is 1 if the corresponding input entry is a 
# relative maximum, otherwise 0. (You should ignore the output
# array's boundary items, set to 0.) 
# 
# For example,
# 
# the input array of integers is {1, 3, 2, 4, 6, 5, 7, 8}. Then,
# the output array of integers should be {0, 1, 0, 0, 1, 0, 0, 0}
# 
# (Note: The first/last entry of the output array is always 0
#  since it's ignored, never be a local maximum.)
# $a0: The base address of the input array
# $a1: The base address of the output array with local maximum points
# $a2: Size of array
find_local_maxima:
############################ Part 2: your code begins here ###

    ble $a2, 1, flm_ret
    sw $0, 0($a1)
    ble $a2, 2, flm_ret
    sw $0, 4($a1)

    li $t0, 1         # index
    addi $t1, $a0, 4  # in*
    addi $t2, $a1, 4  # out*
    addi $t3, $a2, -1 # capped_size

flm_loop:
    bge $t0, $t3, flm_ret

    li $t6, 0
    lw $t4,  ($t1)  # curr = in[0]
    lw $t5, -4($t1)  # prev = in[-1]
    # curr > prev => curr <= prev
    ble $t4, $t5, flm_smaller
    lw $t5,  4($t1)  # next = in[1]
    ble $t4, $t5, flm_smaller
    li $t6, 1
flm_smaller:
    sw $t6, ($t2) # out[i] = 0 or 1

    addi $t0, $t0, 1
    addi $t1, $t1, 4
    addi $t2, $t2, 4
    
    j flm_loop

flm_ret:
############################ Part 2: your code ends here ###
jr $ra

###############################################################
###############################################################
###############################################################
#                       PART 3 (Change Case)
# Complete the change_case function that takes a Null-terminated
# string and converts the lowercase characters (a-z) to 
# uppercase and convert the uppercase ones (A-Z) to lower case. 
# Your function should also ignore non-alphabetical characters. 
# For example, "L!A##b@@3" should be converted to "laB". 
# In null-terminated strings, end of the string is specified 
# by a special null character (i.e., value of 0).

#a0: The base address of the input array
#a1: The base address of the output array
###############################################################
change_case:
############################## Part 3: your code begins here ###

    move $t0, $a0 # in*
    move $t1, $a1 # out*

change_case_loop:
    lbu $t2, ($t0) # char c = *in
    beq $t2, $0, change_case_ret # if c == 0, return

    bltu $t2, 0x41, ignore   # if c < 'A', ignore
    bgtu $t2, 0x7A, ignore   # if c > 'z', ignore

    bleu $t2, 0x5A, uppercase # c <= 'Z'
    bgeu $t2, 0x61, lowercase # c >= 'a'
    j ignore

uppercase: # going to lowercase
    addi $t2, $t2, 0x20 # c += 'a' - 'A'
    j store_char

lowercase: # going to uppercase
    addi $t2, $t2, -0x20 # c += 'A' - 'a'

store_char:
    sb $t2, ($t1)     # *out = c
    addi $t1, $t1, 1   # out += 1
ignore:
    addi $t0, $t0, 1   # in += 1
    j change_case_loop

change_case_ret:
    sb $0, ($t1)      # *out = 0

############################## Part 3: your code ends here ###
jr $ra
