        section .text
        global start, run_once
        extern malloc, printf, check_neighbours

start:                      ;Procedure start (entry point)
        push rbp
        mov rbp, rsp
        mov [width], rdi
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
        pop rbp
        ret


run_once:
        push rbp
        mov rbp, rsp
        xor rcx, rcx                ; i = 0
        xor r10, r10                ; index = 0
heigth_loop:
        cmp ecx, [heigth]           ; i < heigth
        jge heigth_loop_end
        xor rdx, rdx                ; j = 0
width_loop:
        cmp edx, [width]          ; j < width
        jge width_loop_end

        push rcx
        push rdx
        push r10
        push r10                    ; set alignment

        mov rdi, [temp_board]
        mov rsi, rcx
        call check_neighbours       ; rax has number of living neighbours

        pop r10
        pop r10
        pop rdx
        pop rcx

        mov r11, [board]
        lea r8, [r11 + r10]
        mov r11, [temp_board]
        lea r9, [r11 + r10]
first_condition:
        cmp rax, 3
        je alive_cell
second_condition:
        cmp rax, 2
        jne dead_cell
third_condition:
        cmp byte [r9], 42   ; star
        jne dead_cell
alive_cell:
        mov byte [r8], 42   ; star
        jmp after_if
dead_cell:
        mov byte [r8], 32   ; space
after_if:
        inc edx
        inc r10
        jmp width_loop
width_loop_end:
        inc ecx
        jmp heigth_loop
heigth_loop_end:
        

        ; r8 - end of board tab ; r9 - end of temp_board tab
        ; r10 - index
copy:
        cmp r10, 0
        jle end_copy
        mov rax, [r8]
        mov [r9], rax
        dec r8
        dec r9
        dec r10
        jmp copy
end_copy:
        pop rbp
        ret

        section .bss

width: resb 4
heigth: resb 4
temp_board: resb 8
board: resb 8

        section .data
string: db "%c ", 0
STAR: equ '*'
SPACE: equ ' '