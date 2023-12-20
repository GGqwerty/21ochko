;eax - сколько сейчас очков
proc dealer.logic
     cmp eax, 21
     ja dealer.returnLoose
     cmp  eax, 16
     ja dealer.returnEnough

dealer.returnMore:
     mov eax, 0
     ret

dealer.returnLoose:
     mov eax, -1
     ret

dealer.returnEnough:
     mov eax, 1
     ret
endp


proc dealer.gameplay uses ecx edx,\
     hdc, num
     mov edx, [num]
dealer.nextcmp:
     mov eax, [gameProcess.points+edx*4]
     stdcall dealer.logic
     cmp eax, 0
     jz dealer.getMore
     jg dealer.cmpnext
     jl dealer.cmpnext

dealer.getMore:
     mov edx, [num]
     stdcall gameProcess.Game, edx, MYMESSAGE_HIT, [hdc]
     jmp dealer.nextcmp
dealer.cmpnext:

     ret
endp


;al - сколько очков у дилера, ah - кол-во карт у дилера
;cl - сколько очков у игрока, ch - кол-во карт у игрока
;eax - результат
proc dealer.campare
     cmp cl, 21
     jg dealer.dealerWin
     cmp al, 21
     jg dealer.checkBigWin
     cmp al, cl
     jg dealer.dealerWin
     jl dealer.checkBigWin
     cmp al, 21
     jnz dealer.dealerDraw
     cmp ah, 2
     jz dealer.dealerHaveBlack
     cmp ch, 2
     jz dealer.dealerLooseBlack
     jmp dealer.dealerDraw


dealer.dealerHaveBlack:
     cmp ch, 2
     jz dealer.dealerDraw
     jmp dealer.dealerWin


dealer.checkBigWin:
     cmp cl, 21
     jnz dealer.dealerLoose
     cmp ch, 2
     jnz dealer.dealerLoose
     jmp dealer.dealerLooseBlack

dealer.dealerWin:
     mov eax, 1
     ret
dealer.dealerLoose:
     mov eax, -1
     ret
dealer.dealerLooseBlack:
     mov eax, -2
     ret
dealer.dealerDraw:
     mov eax, 0
     ret
endp