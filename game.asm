        section .text
        global start
        extern malloc

start:                      ;Procedure start (entry point)
        push rbp
        mov rbp, rsp
        mov [width], rdi           ;Computed value
        mov [heigth], rsi
        mov [board], rdx
        mov rax, rdi
        imul rax, rsi               ; size of temp_board
        push rax
        mov rdi, rax
        call malloc
        mov [temp_board], rax       ; rax has new pointer
        pop rdi                     ; rdi has size of new tab
        mov rsi, [board]            ; rsi has original pointer
init_tmp:
        cmp rdi, 0
        jle end_init
        mov r8, [rsi]
        mov [rax], r8                  ; copy original tab
        inc rax
        inc rsi
        dec rdi
        jmp init_tmp
end_init:
        mov rax, [temp_board]
        pop rbp
        ret

        section .bss

width: resb 4
heigth: resb 4
temp_board: resb 8
board: resb 8