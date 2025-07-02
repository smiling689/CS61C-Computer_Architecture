.globl factorial

.data
n: .word 7

.text
main:
    la t0, n # t0 = n的地址
    lw a0, 0(t0) # a0 = n
    jal ra, factorial # jump and link

    addi a1, a0, 0
    addi a0, x0, 1
    ecall # Print Result

    addi a1, x0, '\n'
    addi a0, x0, 11
    ecall # Print newline

    addi a0, x0, 10
    ecall # Exit

factorial:
    li a2, 1
    beq a0, a2, base # 运行完base会直接到调用这个fac的下一行去
    mv t0, a0 # t0 = a0
    addi sp, sp, -8
    sw ra, 0(sp) # 存一下要返回的地址，防止覆盖
    sw a0, 4(sp) # a0是最后要返回的，也要存一下
    addi a0, a0, -1 # a0--
    jal factorial
    mv t0, a0
    lw ra, 0(sp)
    lw a0, 4(sp)
    addi sp, sp, 8
    mul a0, a0, t0
    jr ra
    
    
base:
    li a0, 1
    jr ra # 这里ra是上一次的fac地址
    