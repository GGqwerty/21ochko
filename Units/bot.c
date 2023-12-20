;eax - сколько сейчас очков
proc bot.logic uses edx
     cmp eax, 21
     jg bot.returnLoose
     mov edx, eax
     stdcall Random.Get, 1, 20
     cmp  eax, edx
     jl bot.returnEnough

bot.returnMore:
     mov eax, 0
     ret

bot.returnLoose:
     mov eax, -1
     ret

bot.returnEnough:
     mov eax, 1
     ret
endp


proc bot.gameplay uses ecx edx,\
     hdc, num
     mov edx, [num]
msgPaint.drawGame.firstTwoBots.first.nextcmp:
     mov eax, [gameProcess.points+edx*4]
     stdcall bot.logic
     cmp eax, 0
     jz msgPaint.drawGame.firstTwoBots.first.getMore
     jg msgPaint.drawGame.firstTwoBots.first.cmpnext
     jl msgPaint.drawGame.firstTwoBots.first.cmpnext

msgPaint.drawGame.firstTwoBots.first.getMore:
     mov edx, [num]
     stdcall gameProcess.Game, edx, MYMESSAGE_HIT, [hdc]
     jmp msgPaint.drawGame.firstTwoBots.first.nextcmp
msgPaint.drawGame.firstTwoBots.first.cmpnext:

     ret
endp




