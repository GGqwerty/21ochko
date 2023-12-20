proc brez.DrawLine uses edx eax,\
     x0,y0,x1,y1,hBitmap,hdc
        locals
                deltaX dd ?
                deltaY dd ?
                raznica dd ?
                deltaerr dd ?
                dir dd 1
                variable dd ?
                Flag dd 0
        endl

        mov eax, [x1]
        cmp eax,[x0]
        jnl @F
        xchg eax,[x0]
        mov [x1],eax
        mov eax, [y1]
        xchg eax, [y0]
        mov [y1], eax
@@:

        mov eax, [x1]
        sub eax, [x0]
        mov [deltaX], eax

        mov eax, [y1]
        sub eax, [y0]
        jg .Greater
        jz .Zeroer
        neg eax
        mov [dir],-1
        jmp .Greater
.Zeroer:
        mov [dir], 0
.Greater:
        mov [deltaY], eax

        cmp eax, [deltaX]
        jng .AllOk
        xchg eax, [deltaX]
        mov [deltaY], eax

        mov eax, [x0]
        xchg eax, [y0]
        mov [x0], eax

        mov eax, [x1]
        xchg eax, [y1]
        mov [x1], eax

        mov eax, [x1]
        cmp eax,[x0]
        jnl @F
        xchg eax,[x0]
        mov [x1], eax
        mov eax, [y1]
        xchg eax, [y0]
        mov [y1], eax
@@:
        mov [Flag], 1

.AllOk:
        mov eax, [deltaY]
        mov [deltaerr], eax
        inc [deltaerr]
        inc [deltaX]
        mov eax, 0
        mov ecx, [deltaX]
        ;inc cx

LoopMark:
        push ecx
        cmp [Flag],0
        jne .Swapped
        push eax
        stdcall drawBitmap.ChangeUnderDraw, [x0], [y0],[hBitmap]
        pop eax
        jmp @F
.Swapped:
        push eax
        stdcall drawBitmap.ChangeUnderDraw, [y0],[x0],[hBitmap]
        pop eax
@@:

        add eax, [deltaerr]
        cmp eax, [deltaX]
        jng @F
        sub eax, [deltaX]
        mov edx, [dir]
        add [y0], edx

@@:
        inc [x0]
        test ecx, 11111b
        jnz @F
        stdcall drawBitmap.DrawAll, [hdc]
@@:
        pop ecx
        loop LoopMark

        ret
endp