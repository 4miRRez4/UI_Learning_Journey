foo:
    addi $sp, $sp, -8     
    sw $ra, 4($sp)
    sw $a0, 0($sp)

    # Base case
    li $v0, 0 
    ble $a0, 1, foo_end     # If n <= 1

    # f(n-1)
    addi $a0, $a0, -1
    jal foo

    lw $a0, 0($sp)          # Restore n
    mul $t0, $a0, 2
    add $v0, $v0, $t0

foo_end:
    lw $ra, 4($sp)  
    addi $sp, $sp, 8  
    jr $ra  