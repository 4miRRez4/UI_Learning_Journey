.data
str1: .asciiz "ABC"
str2: .asciiz "ABC"
nline: .asciiz "\n"

.text
.globl main

main:
    la $a0, str1
    la $a1, str2
    jal strcomp

    li $a0, $v0
    li $v0, 1
    syscall

    li $v0, 4
    la $a0, nline
    syscall

    li $v0, 10
    syscall

strcomp:
    addi $sp, $sp, -16 #save needed data
    sw $ra, 0($sp)
    sw $s0, 4($sp)
    sw $s1, 8($sp)
    sw $s2, 12($sp)

    move $s0, $a0
    move $s1, $a1

    #count string lengths
    move $a0, $s0
    jal str_len 
    move $s2, $v0 #str1 length

    move $a0, $s1
    jal str_len
    move $t0, $v0 #str2 length

    #compare length
    beq $s2, $t0, same_length
    li $v0, 0
    j strcomp_end

str_len:
    li $v0, 0 #str length
len_loop:
    lb $t0, 0($a0)
    beq $t0, $zero, len_loop_end
    addi $v0, $v0, 1
    addi $a0, $a0, 1 #next character
    j len_loop
len_loop_end:
    jr $ra

same_length:
    addi $sp, $sp, -4    
    sw   $ra, 0($sp)     #save ra

    #convert to lowercase
    move $a0, $s0
    move $a1, $s2
    jal to_lower

    move $a0, $s1
    move $a1, $s2
    jal to_lower

    lw $ra, 0($sp)
    addi $sp, $sp, 4
    
    li $t1, 0 #counter
compare_loop:
    bge $t1, $s2, compare_equal

    add $t2, $s0, $t1     #address of str1[i]
    lb $t3, 0($t2)        # str1[i]
    add $t2, $s1, $t1     #address of str2[i]
    lb $t4, 0($t2)        # str2[i]

    bne $t3, $t4, compare_nequal
    addi $t1, $t1, 1
    j compare_loop

compare_equal:
    li $v0, 1
    j strcomp_end

compare_nequal:
    li $v0, 0
    j strcomp_end


to_lower:
    li $t0, 0                #counter
to_lower_loop:
    bge $t0, $a1, to_lower_end
    add $t1, $a0, $t0        
    lb $t2, 0($t1)           #current character
    
    #is upper case
    blt $t2, 'A', not_upper
    bgt $t2, 'Z', not_upper
    
    #convert to lowercase
    addi $t2, $t2, 32 
    sb $t2, 0($t1)
    
not_upper:
    addi $t0, $t0, 1         #increment counter
    j to_lower_loop
    
to_lower_end:
    jr $ra

strcomp_end:
    lw $ra, 0($sp)
    lw $s0, 4($sp)
    lw $s1, 8($sp)
    lw $s2, 12($sp)

    addi $sp, $sp, 16
    jr $ra
