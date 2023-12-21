;in ax - number
;out eax - adress of string
proc string_work.numInStringWinapi uses ecx
     aam
     cmp ah, 0
     jz @F
     mov byte [string_work.bufSrting], '['
     mov byte [string_work.bufSrting+1], ah
     add byte [string_work.bufSrting+1], '0'
     mov byte [string_work.bufSrting+2], al
     add byte [string_work.bufSrting+2], '0'
     mov byte [string_work.bufSrting+3], ']'
     mov byte [string_work.bufSrting+4], ' '


     jmp string_work.numInString.end
@@:
     mov byte [string_work.bufSrting], '['
     mov byte [string_work.bufSrting+1], al
     add byte [string_work.bufSrting+1], '0'
     mov byte [string_work.bufSrting+2], ']'
     mov byte [string_work.bufSrting+3], ' '
string_work.numInString.end:
     mov eax, string_work.bufSrting
     ret
endp

proc string_work.numInString uses ecx edi esi edx
    mov byte [string_work.bufSrting+99], 0
    mov dword [string_work.flag], 1
    mov edi, string_work.bufSrting+98
    mov esi, string_work.bufInt
    mov byte [string_work.bufSrting+98], ']'
    cmp eax, 0
    jnl @F
    neg eax
    mov byte [string_work.bufSrting+1], '-'
    mov dword [string_work.flag], 0
@@:
    mov [string_work.bufInt], eax
    mov eax, dword [esi]
.next_digit:

    mov edx, 10
    div dl
    push eax
    add ah, '0'
    dec edi
    mov [edi], ah
    pop eax
    mov ah, 0
    test al, al
    jnz .next_digit
    cmp dword [string_work.flag], 0
    jnz @F
    dec edi
    mov byte [edi], '-'
@@:
    dec edi
    mov byte [edi], '['
    mov eax, edi
    ret
endp


;in eax - 0 Lose, 1 Draw, 2 Win
;out eax - adress of string
proc string_work.printResult
     cmp eax, 0
     jnz @F
     mov eax, YouLose

     ret
@@:
     cmp eax, 1
     jnz @F
     mov eax, YouDraw
     ret
@@:
     cmp eax, 2
     jnz @F
     mov eax, YouWin
@@:
     ret
endp














