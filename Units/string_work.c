;in ax - number
;out eax - adress of string
proc string_work.numInString uses ecx
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


;in eax - 0 Lose, 1 Draw, 2 Win
;out eax - adress of string
proc string_work.printResult uses ecx
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














