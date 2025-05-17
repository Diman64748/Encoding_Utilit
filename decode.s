.global Decoding
.type Decoding, @function

.section .rodata
x:   .string "%x"    
c:   .string "%c"    
s:   .string "%s"     


.text
Decoding:
    pushq  %r12
    pushq  %r13   
    pushq  %rbp
    pushq  %rbx

    movq    %rsp, %rbp   
    
    #;буду использовать неизменяемые регистры для хранения параметров 

    
    movq    %rdi, %r12      #; r12 = input
    movq    %rsi, %r13      #; r13 = output
    
    subq    $16, %rsp       #; 16 байт: 4 - счетчик, 4 - текущий символ, 8 - буфер
    
    movq    $0, -8(%rbp)    #; ru_c[0..7] = 0 (8 байт)
    
    movl    $0, -12(%rbp)   #; count_bytes = 0

LOOP:
    leaq    -16(%rbp), %rdx 
    leaq    x(%rip), %rsi   
    movq    %r12, %rdi      
    xorl    %eax, %eax      #; 0 аргументов с плавающей точкой
    call    fscanf@PLT      
    
    cmpl    $-1, %eax       #; проверили на EOF
    je      END       
    
    movzbl  -16(%rbp), %ebx #; Загружаем прочитанный байт (с нулевым расширением)
    
    cmpb    $0x80, %bl      #; Сравниваем с 0x80
    jb      ASCII    
    
    movl    -12(%rbp), %eax #; Текущее положение в буфере
    leaq    -8(%rbp), %rcx  #; Адрес начала буфера
    movb    %bl,(%rcx,%rax) #; Сохраняем байт в буфер
    incl    -12(%rbp)       #; Увеличиваем счетчик байт
    
    cmpl    $2, -12(%rbp)
    jb      LOOP            #; Если меньше 2, продолжаем чтение
    
    leaq    -8(%rbp), %rdx  
    movq    %r13, %rdi      
    leaq    s(%rip), %rsi   #; 2-й арг: строка формата "%s"
    xorl    %eax, %eax      
    call    fprintf@PLT     
    
    movl    $0, -12(%rbp)   #; Сбрасываем счетчик байт
    jmp     LOOP            #; Продолжаем цикл

ASCII:
    movq    %r13, %rdi      
    leaq    c(%rip), %rsi   #; 2-й арг: строка формата "%c"
    movl    %ebx, %edx      
    xorl    %eax, %eax     
    call    fprintf@PLT     
    jmp     LOOP     

END:
    addq    $16, %rsp  

    popq %rbx
    popq %rbp
    popq %r13
    popq %r12   
    ret

#;взял из интернета, чтобы линковщик не ругался на стек 
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

