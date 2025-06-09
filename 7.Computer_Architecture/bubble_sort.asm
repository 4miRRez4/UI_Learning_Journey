.data
array:      .word 5, 2, 9, 1, 5, 6, 8, 3, 7, 4
length:     .word 10
space:      .asciiz " "
newline:    .asciiz "\n"

.text
.globl main

main:
    la $a0, array
    lw $a1, length
    jal bubble_sort
    
    la $a0, array
    lw $a1, length
    jal print_array
    
    li $v0, 10
    syscall

bubble_sort:
    addi $sp, $sp, -4
    sw $ra, 0($sp)
    
    li $t0, 0               # i = 0 (outer loop counter)
    addi $t1, $a1, -1       # length - 1 (outer loop limit)
    
outer_loop:
    bge $t0, $t1, end_sort  # if i >= length-1
    
    li $t2, 0               # j = 0 (inner loop counter)
    sub $t3, $t1, $t0       # length-1 - i (inner loop limit)
    
inner_loop:
    bge $t2, $t3, end_inner # if j >= (length-1-i)
    
    sll $t4, $t2, 2         # j * 4
    add $t4, $a0, $t4       # address of array[j]
    lw $t5, 0($t4)          # array[j]
    lw $t6, 4($t4)          # array[j+1]
    
    ble $t5, $t6, no_swap   # if array[j] <= array[j+1]
    
    # Swap elements
    sw $t6, 0($t4)
    sw $t5, 4($t4)
    
no_swap:
    addi $t2, $t2, 1        # j++
    j inner_loop
    
end_inner:
    addi $t0, $t0, 1        # i++
    j outer_loop
    
end_sort:
    lw $ra, 0($sp) 
    addi $sp, $sp, 4
    jr $ra


print_array:
    li $t0, 0               # Counter i = 0
    
print_loop:
    bge $t0, $a1, end_print
    
    sll $t1, $t0, 2         # i * 4 
    add $t1, $a0, $t1       # address of array[i]
    lw $a0, 0($t1)          # array[i]
    
    li $v0, 1
    syscall

    la $a0, space
    li $v0, 4
    syscall

    la $a0, array
    
    addi $t0, $t0, 1        # i++
    j print_loop
    
end_print:
    la $a0, newline
    li $v0, 4
    syscall
    
    jr $ra