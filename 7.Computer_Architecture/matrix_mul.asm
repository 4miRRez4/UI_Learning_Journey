.data
X:      .word 1, 2, 3
        .word 4, 5, 6
        .word 7, 8, 9

Y:      .word 9, 8, 7
        .word 6, 5, 4
        .word 3, 2, 1

Z:      .space 36 

size:   .word 3

.text
.globl main

main:
    # Driver
    la $a0, X    # Address of matrix X
    la $a1, Y
    la $a2, Z
    lw $a3, size
    
    jal matrix_multiply
    
    li $v0, 10
    syscall

matrix_multiply:
    addi $sp, $sp, -20 
    sw $ra, 0($sp)
    sw $s0, 4($sp)
    sw $s1, 8($sp)
    sw $s2, 12($sp)
    sw $s3, 16($sp)

    move $s0, $a0
    move $s1, $a1
    move $s2, $a2
    move $s3, $a3

    li $t0, 0               # i = 0
    
i_loop:
    bge $t0, $s3, end_i     # if i >= n, exit
    
    li $t1, 0               # j = 0
    
j_loop:
    bge $t1, $s3, end_j     # if j >= n, next row
    
    li $t2, 0               # k = 0 (sum counter)
    li $t3, 0               # sum = 0
    
k_loop:
    bge $t2, $s3, end_k     # if k >= n, store sum
    
    # Calculate X[i][k] address
    mul $t4, $t0, $s3       # i * n
    add $t4, $t4, $t2       # + k
    sll $t4, $t4, 2         # *4 (word size)
    add $t4, $s0, $t4       # + X base address
    lw $t5, 0($t4)          # $t5 = X[i][k]
    
    # Calculate Y[k][j] address
    mul $t6, $t2, $s3       # k * n
    add $t6, $t6, $t1       # + j
    sll $t6, $t6, 2         # *4 (word size)
    add $t6, $s1, $t6       # + Y base address
    lw $t7, 0($t6)          # $t7 = Y[k][j]
    
    mul $t8, $t5, $t7       # X[i][k] * Y[k][j]
    add $t3, $t3, $t8       # sum += ...
    
    addi $t2, $t2, 1        # k++
    j k_loop
    
end_k:
    # Calculate Z[i][j] address
    mul $t4, $t0, $s3       # i * n
    add $t4, $t4, $t1       # + j
    sll $t4, $t4, 2         # *4 (word size)
    add $t4, $s2, $t4       # + Z base address
    sw $t3, 0($t4)          # Z[i][j] = sum
    
    addi $t1, $t1, 1        # j++
    j j_loop
    
end_j:
    addi $t0, $t0, 1        # i++
    j i_loop
    
end_i:
    lw $ra, 0($sp)
    lw $s0, 4($sp)
    lw $s1, 8($sp)
    lw $s2, 12($sp)
    lw $s3, 16($sp)
    addi $sp, $sp, 20
    
    move $v0, $s2           # Address of result matrix
    jr $ra