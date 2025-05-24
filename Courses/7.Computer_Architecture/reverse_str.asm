.data
str: .asciiz "Hello, World!"
nline: .byte 10

.text
.globl main
main:
    la $a0, str
    jal str_len

    move $t0, $v0
    la $a1, str
    addi $a2, $t0, -1

reverse:
    blt $a2, $a1, reverse_done

    lb $t1, (0)$a1
    add $t4, $a1, $a2
    lb $t2, 0($t4)

    sb $t1, 0($t4)
    sb $t2, 0($a1)

    addi $a0, $a0, 1
    addi $a1, $a1, -1

    j reverse

reverse_done:
    la $a0, str
    li $v0, 4
    syscall

    lb   $a0, nline
    li   $v0, 11
    syscall

    li   $v0, 10
    syscall

str_len:
    move $t0, $a0
    add $t1, $zero, $zero

len_loop:
    lb $t2, 0($t0)
    addi $t1, $t1, 1
    addi $t0, $t0, 1
    bne $t2, $zero, len_loop
    move $v0, $t1
    jr $ra