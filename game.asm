        section .text
        global start, run
        extern malloc

start:
        push rbp
        mov rbp, rsp
        mov [width], edi
        mov [heigth], esi
        mov [board], rdx            ; init values
        imul edi, esi               ; size of temp_board
        push rdi
        call malloc
        mov [temp_board], rax       ; rax has new pointer
        pop rdi                     ; rdi has size of board
        mov rsi, [board]            ; rsi has original pointer
init_tmp:                           ; copy board to temp_board
        cmp edi, 0
        jle end_init
        mov r8b, [rsi]
        mov byte [rax], r8b         ; copy original tab
        inc rax
        inc rsi
        dec edi
        jmp init_tmp
end_init:
        pop rbp
        ret

run:
        push rbp
        push r12
        push r13
        push r14
        push r15
        push rbx
        mov rbp, rsp
loop_run:
        cmp rdi, 0
        jle end_run
        call run_once
        dec rdi
        jmp loop_run
end_run:
        pop rbx
        pop r15
        pop r14
        pop r13
        pop r12
        pop rbp
        ret

run_once:                           ; helper function - one step of game run
        push rbp
        mov rbp, rsp
        xor rcx, rcx                ; i = 0
        xor rbx, rbx                ; index = 0
        mov r12d, [heigth]
        mov r13d, [width]
        mov r14, [board]
        mov r15, [temp_board]
heigth_loop:
        cmp ecx, r12d               ; i < heigth
        jge heigth_loop_end
        xor rdx, rdx                ; j = 0
width_loop:
        cmp edx, r13d               ; j < width
        jge width_loop_end
        call check_neighbours       ; rcx - row; rdx - column; rax has number of living neighbours
        lea r8, [r14 + rbx]
        lea r9, [r15 + rbx]
first_condition:
        cmp rax, 3
        je alive_cell
second_condition:
        cmp rax, 2
        jne dead_cell
third_condition:
        cmp byte [r9], 42           ; star
        jne dead_cell
alive_cell:
        mov byte [r8], 42           ; star
        jmp after_if
dead_cell:
        mov byte [r8], 32           ; space
after_if:
        inc edx
        inc rbx
        jmp width_loop
width_loop_end:
        inc ecx
        jmp heigth_loop
heigth_loop_end:                    ; r8 - end of board tab ; r9 - end of temp_board tab
copy:                               ; rbx - index
        cmp rbx, 0
        jle end_copy
        mov al, [r8]
        mov byte [r9], al
        dec r8
        dec r9
        dec rbx
        jmp copy
end_copy:
        pop rbp
        ret


check_neighbours:                   ; helper function - check how many neighbours of cell are alive
        push rbp
        mov rbp, rsp
        xor rax, rax                ; count = 0; rcx - row; rdx - col
        mov r8, r15
        mov r9, rcx
        imul r9d, r13d
        add r9, rdx
        dec r9
        lea r9, [r8 + r9]           ; temp_board[i*w + j - 1]
check_left:
        cmp edx, 0
        je check_right
        cmp byte [r9], 42           ; star
        jne check_right
        inc rax
check_right:
        add r9, 2                   ; temp_board[i*w + j + 1]
        mov r10d, r13d
        dec r10d
        cmp edx, r10d
        je check_top
        cmp byte [r9], 42           ; star
        jne check_top
        inc rax
check_top:
        dec r9
        sub r9d, r13d               ; temp_board[(i-1)*w + j]
        cmp ecx, 0
        je check_bottom
        cmp byte [r9], 42           ; star
        jne check_bottom
        inc rax
check_bottom:
        add r9d, r13d
        add r9d, r13d               ; temp_board[(i+1)*w + j]
        mov r10d, r12d
        dec r10d
        cmp ecx, r10d
        je check_left_bottom
        cmp byte [r9], 42           ; star
        jne check_left_bottom
        inc rax

check_left_bottom:
        dec r9                      ; temp_board[(i+1)*w + j - 1]
        cmp edx, 0
        je check_right_bottom
        mov r10d, r12d
        dec r10d
        cmp ecx, r10d
        je check_right_bottom
        cmp byte [r9], 42           ; star
        jne check_right_bottom
        inc rax

check_right_bottom:
        add r9, 2                   ; temp_board[(i+1)*w + j + 1]
        mov r10d, r13d
        dec r10d
        cmp edx, r10d
        je check_right_top
        mov r10d, r12d
        dec r10d
        cmp ecx, r10d
        je check_right_top
        cmp byte [r9], 42           ; star
        jne check_right_top
        inc rax
check_right_top:
        sub r9d, r13d
        sub r9d, r13d               ; temp_board[(i-1)*w + j + 1]
        mov r10d, r13d
        dec r10d
        cmp edx, r10d
        je check_left_top
        cmp ecx, 0
        je check_left_top
        cmp byte [r9], 42           ; star
        jne check_left_top
        inc rax
check_left_top:
        sub r9, 2                   ; temp_board[(i-1)*w + j - 1]
        cmp edx, 0
        je end_check
        cmp ecx, 0
        je end_check
        cmp byte [r9], 42           ; star
        jne end_check
        inc rax
end_check:
        pop rbp
        ret

        section .bss
width: resb 4
heigth: resb 4
temp_board: resb 8
board: resb 8
