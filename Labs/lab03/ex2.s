.globl main

.data
source:
    .word   3
    .word   1
    .word   4
    .word   1
    .word   5
    .word   9
    .word   0
dest:
    .word   0
    .word   0
    .word   0
    .word   0
    .word   0
    .word   0
    .word   0
    .word   0
    .word   0
    .word   0

.text
fun:
    addi t0, a0, 1 # t0 = a0 + 1
    sub t1, x0, a0 # -a0取到t1中来
    mul a0, t0, t1 # 乘积
    jr ra

main:
    # BEGIN PROLOGUE
    addi sp, sp, -20
    sw s0, 0(sp)
    sw s1, 4(sp)
    sw s2, 8(sp)
    sw s3, 12(sp)
    sw ra, 16(sp)
    # END PROLOGUE
    addi t0, x0, 0 # t0 = 0
    addi s0, x0, 0 # s0 = 0
    la s1, source # s1 = source
    la s2, dest # s2 = dest
loop:
    slli s3, t0, 2 # s3 = t0 << 2,t0 = k  
    add t1, s1, s3 # t1 = s1 + s3，s1+s3记录source[k]地址
    lw t2, 0(t1) # t2 获取 t1 地址的数字,即source[k]
    beq t2, x0, exit # =0 退出
    add a0, x0, t2 # a0 = t2（加载进参数表，a0用在函数里）
    addi sp, sp, -8
    sw t0, 0(sp)
    sw t2, 4(sp)
    jal fun
    lw t0, 0(sp)
    lw t2, 4(sp)
    addi sp, sp, 8
    add t2, x0, a0 # t2 = a0（取出返回值）
    add t3, s2, s3 # t3 = s2 + s3（s2是dest，加s3是dest[k]的地址）
    sw t2, 0(t3) # t2 -> t3
    add s0, s0, t2 # s0 += t2(sum+=返回值)
    addi t0, t0, 1 # t0 += 1 
    jal x0, loop
exit:
    add a0, x0, s0
    # BEGIN EPILOGUE
    lw s0, 0(sp)
    lw s1, 4(sp)
    lw s2, 8(sp)
    lw s3, 12(sp)
    lw ra, 16(sp)
    addi sp, sp, 20
    # END EPILOGUE
    jr ra
