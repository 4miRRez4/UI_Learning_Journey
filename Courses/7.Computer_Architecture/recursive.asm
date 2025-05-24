# main(){
#     int i = foo (10);
#     cout << i << endl;
#}
#int foo (int n){
#     if (n>15 || n<5) return 1;
#     return 2*foo(n-1);

.data
nline: .byte 10
.text
.globl main

main:
    li $a0, 10
    jal foo

    add $a0, $v0, $zero
    li $v0, 1
    syscall

    lbu $a0, nline
    li $v0, 11
    syscall

    li $v0, 10
    syscall

foo:
    addi $sp, $sp, -8
    sw $ra, 4($sp)
    sw $a0, 0($sp)

    addi $t0, $zero, 15
    addi $t1, $zero, 5

    sgt $t2, $a0, $t0
    slt $t3, $a0, $t1

    or $t4, $t2, $t3
    beq $t4, $zero, continue_foo

    li $v0, 1
    addi $sp, $sp, 8
    jr $ra

continue_foo:
    addi $a0, $a0, -1
    jal foo

    lw $a0, 0($sp)
    lw $ra, 4($sp)
    addi $sp, $sp, 8

    mul $v0, $v0, 2
    jr $ra