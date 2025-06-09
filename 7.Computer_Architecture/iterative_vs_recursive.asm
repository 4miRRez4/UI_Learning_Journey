#int fib1(int n) { //iterative
#    int i,x,y,z;
#    x=0,y=1;
#    if(n<2)
#        return n;
#    else{
#        for(i=0;i<n-1;i++){
#            z=x+y;
#            x=y;
#            y=z;
#       }
#       return z;
#       }
#}
#int fib2(int n){ //recursive
#    if(n<2)
#        return n;
#    else
#        return(fib2(n-1)+fib2(n-2));
#}


fib1:
    li $t1, 0   # x=0
    li $t2, 1   # y=1

    li $v0, $a0
    slt $t4, $a0, 2     # n<2
    bne $t4, $zero, fib1_end

    li $t5, $zero # counter
    addi $t6, $a0, -1 # upper bound
fib1_loop:
    slt $t7, $t5, $t6
    beq $t7, $zero, loop_end
    add $t3, $t1, $t2
    move $t1, $t2
    move $t2, $t3

    addi $t5, $t5, 1
    j fib1_loop

loop_end:
    move $v0, $t3

fib1_end:
    jr $ra


#-----------------------------------
fib2:
    # Base case
    move $v0, $a0
    blt $a0, 2, fib2_end    # if n<2

    addi $sp, $sp, -12
    sw $ra, 0($sp)
    sw $a0, 4($sp)
    sw $s0, 8($sp)

    # f(n-1)
    addi $a0, $a0, -1
    jal fib2
    move $s0, $v0

    # f(n-2)
    lw $a0, 4($sp)
    addi $a0, $a0, -2
    jal fib2
    add $v0, $v0, $s0   # f(n-2) + f(n-1)    

    lw $ra, 0($sp)
    lw $s0, 8($sp)
    addi $sp, $sp, 12

fib2_end:
    jr $ra

