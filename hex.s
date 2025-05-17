
.global PrintHexFormat
.type PrintHexFormat, @function

.section .rodata
hex_format: .string "%02x "
newline:    .string "\n"

.text
PrintHexFormat:
    pushq  %rbp
    pushq  %r12
    pushq  %r13
    pushq  %r14
    pushq  %rbx


    movq    %rdi, %r12        #; r12 = input_f
    movq    %rsi, %r13        #; r13 = output_f
    movl    %edx, %r14d       #; r14d = count_of_bytes_in_str
    xorl    %ebx, %ebx        #; ebx = counter = 0

LOOP:

    movq    %r12, %rdi
    call    fgetc@PLT
    
    cmpl    $-1, %eax         #; Проверка на EOF
    je      END
    
    movq    %r13, %rdi
    leaq    hex_format(%rip), %rsi
    movl    %eax, %edx        #; Символ для печати
    xorl    %eax, %eax        
    call    fprintf@PLT
    
    incl    %ebx              #;увеличили счетчик
    cmpl    %r14d, %ebx       #;сравнили с count_of_bytes_in_str
    jl      LOOP
    
    movq    %r13, %rdi        #;вывод новой строки
    leaq    newline(%rip), %rsi
    xorl    %eax, %eax
    call    fprintf@PLT
    
    xorl    %ebx, %ebx        #; Сброс счетчика
    jmp     LOOP

END:
    popq %rbx
    popq %r14
    popq %r13
    popq %r12
    popq %rbp


    ret

.section .note.GNU-stack,"",@progbits
.section .note.gnu.property,"a"
.align 8
.long 1f - 0f
.long 4f - 1f
.long 5
0:
.string "GNU"
1:
.align 8
.long 0xc0000002
.long 3f - 2f
2:
.long 3
3:
.align 8
4:
