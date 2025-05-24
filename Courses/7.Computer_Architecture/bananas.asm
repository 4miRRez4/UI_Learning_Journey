.data
newline:    .asciiz "\n"
tree_node_size: .word 12  # sizeof(struct treeNode) = 12 (4 for nob + 4 for left + 4 for right)

.text
.globl main

.eqv nob_offset 0
.eqv left_offset 4
.eqv right_offset 8

main:
    # Root node
    li $v0, 9            
    li $a0, 12  
    syscall
    move $s0, $v0         # $s0 = myTree
    
    # Initialize root node
    sw $zero, nob_offset($s0)    # myTree->nob = 0
    sw $zero, left_offset($s0)   # myTree->left = NULL
    sw $zero, right_offset($s0)  # myTree->right = NULL
    
    # Insert nodes
    move $a0, $s0         # tmp
    li $a1, 3             # left nob
    li $a2, 5             # right nob
    jal insert
    
    # Insert to left child
    lw $a0, left_offset($s0)  # tmp->left
    li $a1, 6             # left nob
    li $a2, 9             # right nob
    jal insert
    
    # Insert to right child
    lw $a0, right_offset($s0) # tmp->right
    li $a1, 4             # left nob
    li $a2, 10            # right nob
    jal insert
    
    # Count bananas
    move $a0, $s0         
    jal countBs
    move $s1, $v0   
    
    li $v0, 1
    move $a0, $s1
    syscall

    li $v0, 4
    la $a0, newline
    syscall

    li $v0, 10
    syscall

countBs:
    addi $sp, $sp, -12
    sw $ra, 0($sp)
    sw $s0, 4($sp)
    sw $s1, 8($sp)
    
    move $s0, $a
    li $v0, 0             # Initialize count to 0
    
    beqz $s0, countBs_end 
    
    # Current node's banana count
    lw $t0, nob_offset($s0)
    add $v0, $v0, $t0
    
    # Left subtree
    lw $a0, left_offset($s0)
    jal countBs
    move $s1, $v0
    
    # Right subtree
    lw $a0, right_offset($s0)
    jal countBs
    
    add $v0, $v0, $s1
    
countBs_end:
    lw $ra, 0($sp)
    lw $s0, 4($sp)
    lw $s1, 8($sp)
    addi $sp, $sp, 12
    jr $ra

insert:
    addi $sp, $sp, -16
    sw $ra, 0($sp)
    sw $s0, 4($sp)
    sw $s1, 8($sp)
    sw $s2, 12($sp)
    
    move $s0, $a0         # $s0 = head
    move $s1, $a1         # $s1 = l
    move $s2, $a2         # $s2 = r
    
    # Store current node's banana count (average of l and r)
    add $t0, $s1, $s2
    srl $t0, $t0, 1 
    sw $t0, nob_offset($s0)
    
    # Create left child if l != 0
    beqz $s1, no_left_child
    li $v0, 9   
    li $a0, 12
    syscall
    sw $v0, left_offset($s0)
    
    # Initialize left child
    sw $s1, nob_offset($v0)
    sw $zero, left_offset($v0)
    sw $zero, right_offset($v0)
    
no_left_child:
    # Create right child if r != 0
    beqz $s2, no_right_child
    li $v0, 9 
    li $a0, 12
    syscall
    sw $v0, right_offset($s0)
    
    # Initialize right child
    sw $s2, nob_offset($v0)
    sw $zero, left_offset($v0)
    sw $zero, right_offset($v0)
    
no_right_child:
    lw $ra, 0($sp)
    lw $s0, 4($sp)
    lw $s1, 8($sp)
    lw $s2, 12($sp)
    addi $sp, $sp, 16
    jr $ra