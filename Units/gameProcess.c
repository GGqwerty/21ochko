proc gameProcess.Game uses edx ecx ebx,\
     param, message, hdc

     cmp [message], MYMESSAGE_NEW_GAME
     jz gameProcess.newGame
     cmp [message], MYMESSAGE_HIT
     jz gameProcess.Hit



     jmp gameProcess.EndTurn


gameProcess.Hit:
     cmp [param], 0
     jz gameProcess.Hit.p1
     cmp [param], 1
     jz gameProcess.Hit.p2
     cmp [param], 2
     jz gameProcess.Hit.p3
     cmp [param], 3
     jz gameProcess.Hit.p4
     cmp [param], 4
     jz gameProcess.Hit.p5
     cmp [param], 5
     jz gameProcess.Hit.d


gameProcess.Hit.p1:
     mov eax, [gameProcess.CardNow]

     stdcall mix.TranslateNumInCardNum
     stdcall loadImages.TranslateNumInHandle
     mov eax, [eax]
     xor ecx, ecx
     mov cx, [screen_translate.coordy1]
     push ecx
     push eax
     stdcall drawBitmap.AddToDraw, [gameProcess.coordx+0*4], ecx, eax
     pop eax
     pop ecx
     stdcall brez.DrawLine, 5, 5, [gameProcess.coordx+0*4], ecx, eax, [hdc]
     add dword [gameProcess.coordx+0*4], 30

     mov eax, [gameProcess.CardNow]
     stdcall mix.TranslateNumInCardNum
     call loadImages.TranslateNumInOchki
     add dword [gameProcess.points+0*4], eax
     cmp eax, 1
     jnz @F
     cmp dword [gameProcess.points+0*4], 11
     jg @F
     add dword [gameProcess.points+0*4], 10
     inc dword [gameProcess.Aces+0*4]

@@:
     cmp dword [gameProcess.points+0*4], 22
     jl @F
     cmp dword [gameProcess.Aces+0*4], 0
     jz @F
     dec dword [gameProcess.Aces+0*4]
     sub dword [gameProcess.points+0*4], 10

@@:
     dec dword [gameProcess.CardNow]
     inc byte [gameProcess.CardCount+0]
     jmp gameProcess.EndTurn

gameProcess.Hit.p2:
     mov eax, [gameProcess.CardNow]

     stdcall mix.TranslateNumInCardNum
     stdcall loadImages.TranslateNumInHandle
     mov eax, [eax]
     xor ecx, ecx
     mov cx, [screen_translate.coordy2]
     push ecx
     push eax
     stdcall drawBitmap.AddToDraw, [gameProcess.coordx+1*4], ecx, eax
     pop eax
     pop ecx
     stdcall brez.DrawLine, 5, 5, [gameProcess.coordx+1*4], ecx, eax, [hdc]
     add dword [gameProcess.coordx+1*4], 30

     mov eax, [gameProcess.CardNow]
     stdcall mix.TranslateNumInCardNum
     call loadImages.TranslateNumInOchki
     add dword [gameProcess.points+1*4], eax
     cmp eax, 1
     jnz @F
     cmp dword [gameProcess.points+1*4], 11
     jg @F
     add dword [gameProcess.points+1*4], 10
     inc dword [gameProcess.Aces+1*4]

@@:

     cmp dword [gameProcess.points+1*4], 22
     jl @F
     cmp dword [gameProcess.Aces+1*4], 0
     jz @F
     dec dword [gameProcess.Aces+1*4]
     sub dword [gameProcess.points+1*4], 10

@@:
     inc byte [gameProcess.CardCount+1]
     dec dword [gameProcess.CardNow]
     jmp gameProcess.EndTurn

gameProcess.Hit.p3:
     mov eax, [gameProcess.CardNow]

     stdcall mix.TranslateNumInCardNum
     stdcall loadImages.TranslateNumInHandle
     mov eax, [eax]
     xor ecx, ecx
     mov cx, [screen_translate.coordy3]
     push ecx
     push eax
     stdcall drawBitmap.AddToDraw, [gameProcess.coordx+2*4], ecx, eax
     pop eax
     pop ecx
     stdcall brez.DrawLine, 5, 5, [gameProcess.coordx+2*4], ecx, eax, [hdc]
     add dword [gameProcess.coordx+2*4], 30

     mov eax, [gameProcess.CardNow]
     stdcall mix.TranslateNumInCardNum
     call loadImages.TranslateNumInOchki
     add dword [gameProcess.points+2*4], eax
     cmp eax, 1
     jnz @F
     cmp dword [gameProcess.points+2*4], 11
     jg @F
     add dword [gameProcess.points+2*4], 10
     inc dword [gameProcess.Aces+2*4]

@@:

     cmp dword [gameProcess.points+2*4], 22
     jl @F
     cmp dword [gameProcess.Aces+2*4], 0
     jz @F
     dec dword [gameProcess.Aces+2*4]
     sub dword [gameProcess.points+2*4], 10

@@:
     inc byte [gameProcess.CardCount+2]
     dec dword [gameProcess.CardNow]
     jmp gameProcess.EndTurn

gameProcess.Hit.p4:
     mov eax, [gameProcess.CardNow]

     stdcall mix.TranslateNumInCardNum
     stdcall loadImages.TranslateNumInHandle
     mov eax, [eax]
     xor ecx, ecx
     mov cx, [screen_translate.coordy4]
     push ecx
     push eax
     stdcall drawBitmap.AddToDraw, [gameProcess.coordx+3*4], ecx, eax
     pop eax
     pop ecx
     stdcall brez.DrawLine, 5, 5, [gameProcess.coordx+3*4], ecx, eax, [hdc]
     add dword [gameProcess.coordx+3*4], 30

     mov eax, [gameProcess.CardNow]
     stdcall mix.TranslateNumInCardNum
     call loadImages.TranslateNumInOchki
     add dword [gameProcess.points+3*4], eax
     cmp eax, 1
     jnz @F
     cmp dword [gameProcess.points+3*4], 11
     jg @F
     add dword [gameProcess.points+3*4], 10
     inc dword [gameProcess.Aces+3*4]

@@:

     cmp dword [gameProcess.points+3*4], 22
     jl @F
     cmp dword [gameProcess.Aces+3*4], 0
     jz @F
     dec dword [gameProcess.Aces+3*4]
     sub dword [gameProcess.points+3*4], 10

@@:
     inc byte [gameProcess.CardCount+3]
     dec dword [gameProcess.CardNow]
     jmp gameProcess.EndTurn

gameProcess.Hit.p5:
     mov eax, [gameProcess.CardNow]

     stdcall mix.TranslateNumInCardNum
     stdcall loadImages.TranslateNumInHandle
     mov eax, [eax]
     xor ecx, ecx
     mov cx, [screen_translate.coordy5]
     push ecx
     push eax
     stdcall drawBitmap.AddToDraw, [gameProcess.coordx+4*4], ecx, eax
     pop eax
     pop ecx
     stdcall brez.DrawLine, 5, 5, [gameProcess.coordx+4*4], ecx, eax, [hdc]
     add dword [gameProcess.coordx+4*4], 30

     mov eax, [gameProcess.CardNow]
     stdcall mix.TranslateNumInCardNum
     call loadImages.TranslateNumInOchki
     add dword [gameProcess.points+4*4], eax
     cmp eax, 1
     jnz @F
     cmp dword [gameProcess.points+4*4], 11
     jg @F
     add dword [gameProcess.points+4*4], 10
     inc dword [gameProcess.Aces+4*4]

@@:

     cmp dword [gameProcess.points+4*4], 22
     jl @F
     cmp dword [gameProcess.Aces+4*4], 0
     jz @F
     dec dword [gameProcess.Aces+4*4]
     sub dword [gameProcess.points+4*4], 10

@@:
     inc byte [gameProcess.CardCount+4]
     dec dword [gameProcess.CardNow]
     jmp gameProcess.EndTurn

gameProcess.Hit.d:
     mov al, [gameProcess.CardCount+5]
     cmp al, 0
     jz gameProcess.Hit.d.first
     mov eax, [gameProcess.CardNow]

     stdcall mix.TranslateNumInCardNum
     stdcall loadImages.TranslateNumInHandle
     mov eax, [eax]
     xor ecx, ecx
     mov cx, [screen_translate.coordyd]
     push ecx
     push eax
     stdcall drawBitmap.AddToDraw, [gameProcess.coordx+5*4], ecx, eax
     pop eax
     pop ecx
     stdcall brez.DrawLine, 5, 5, [gameProcess.coordx+5*4], ecx, eax, [hdc]
     add dword [gameProcess.coordx+5*4], 30

     mov eax, [gameProcess.CardNow]
     stdcall mix.TranslateNumInCardNum
     call loadImages.TranslateNumInOchki
     add dword [gameProcess.points+5*4], eax
     cmp eax, 1
     jnz @F
     cmp dword [gameProcess.points+5*4], 11
     jg @F
     add dword [gameProcess.points+5*4], 10
     inc dword [gameProcess.Aces+5*4]
@@:

     cmp dword [gameProcess.points+5*4], 22
     jl @F
     cmp dword [gameProcess.Aces+5*4], 0
     jz @F
     dec dword [gameProcess.Aces+5*4]
     sub dword [gameProcess.points+5*4], 10

@@:
     mov eax, [gameProcess.points+5*4]
     inc byte [gameProcess.CardCount+5]
     dec dword [gameProcess.CardNow]
     jmp gameProcess.EndTurn
gameProcess.Hit.d.first:
     stdcall drawBitmap.AddToDraw, [gameProcess.coordx+5*4], [screen_translate.coordyd], [card_cover]
     stdcall brez.DrawLine, 5, 5, [gameProcess.coordx+5*4], [screen_translate.coordyd], [card_cover], [hdc]
     add dword [gameProcess.coordx+5*4], 30
     inc byte [gameProcess.CardCount+5]
     jmp gameProcess.EndTurn

gameProcess.newGame:
     mov ecx, 6
@@:
     mov dword [gameProcess.Aces+ecx*4-4], 0
     loop @B

     mov ecx, 6
@@:
     mov dword [gameProcess.points+ecx*4-4], 0
     loop @B

     mov ecx, 6
@@:
     mov byte [gameProcess.CardCount+ecx-1], 0
     loop @B


     xor ecx, ecx
     mov cx, [screen_translate.coordx1]
     mov [gameProcess.coordx+0*4], ecx

     xor ecx, ecx
     mov cx, [screen_translate.coordx2]
     mov [gameProcess.coordx+1*4], ecx

     xor ecx, ecx
     mov cx, [screen_translate.coordx3]
     mov [gameProcess.coordx+2*4], ecx

     xor ecx, ecx
     mov cx, [screen_translate.coordx4]
     mov [gameProcess.coordx+3*4], ecx

     xor ecx, ecx
     mov cx, [screen_translate.coordx5]
     mov [gameProcess.coordx+4*4], ecx

     xor ecx, ecx
     mov cx, [screen_translate.coordxd]
     mov [gameProcess.coordx+5*4], ecx

     stdcall drawBitmap.DeleteAllFromDraw
     stdcall drawBitmap.AddToDraw,  5, 5, [card_cover_koloda]
     mov ecx, [screen_translate.width]
     sub ecx, volume_size
     stdcall drawBitmap.AddToDraw,  ecx, 0, [button_onof]

     cmp dword[gameProcess.WhoPlayNow+0*4], 0
     jz @F
     stdcall gameProcess.Game, 0, MYMESSAGE_HIT, [hdc]
     stdcall gameProcess.Game, 0, MYMESSAGE_HIT, [hdc]
@@:
     cmp dword[gameProcess.WhoPlayNow+1*4], 0
     jz @F
     stdcall gameProcess.Game, 1, MYMESSAGE_HIT, [hdc]
     stdcall gameProcess.Game, 1, MYMESSAGE_HIT, [hdc]
@@:
     cmp dword[gameProcess.WhoPlayNow+2*4], 0
     jz @F
     stdcall gameProcess.Game, 2, MYMESSAGE_HIT, [hdc]
     stdcall gameProcess.Game, 2, MYMESSAGE_HIT, [hdc]
@@:
     cmp dword[gameProcess.WhoPlayNow+3*4], 0
     jz @F
     stdcall gameProcess.Game, 3, MYMESSAGE_HIT, [hdc]
     stdcall gameProcess.Game, 3, MYMESSAGE_HIT, [hdc]
@@:
     cmp dword[gameProcess.WhoPlayNow+4*4], 0
     jz @F
     stdcall gameProcess.Game, 4, MYMESSAGE_HIT, [hdc]
     stdcall gameProcess.Game, 4, MYMESSAGE_HIT, [hdc]
@@:
     cmp dword[gameProcess.WhoPlayNow+4*5], 0
     jz @F
     stdcall gameProcess.Game, 5, MYMESSAGE_HIT, [hdc]
     stdcall gameProcess.Game, 5, MYMESSAGE_HIT, [hdc]
@@:

     jmp gameProcess.EndTurn



gameProcess.EndTurn:
    ret
endp

proc gameProcess.swapDealerFirstCard
     mov eax, [gameProcess.CardNow]

     stdcall mix.TranslateNumInCardNum
     stdcall loadImages.TranslateNumInHandle
     mov eax, [eax]
     stdcall drawBitmap.ChangeBitmapUnderDraw, eax, [card_cover]

     mov eax, [gameProcess.CardNow]
     stdcall mix.TranslateNumInCardNum
     call loadImages.TranslateNumInOchki
     add dword [gameProcess.points+5*4], eax
     cmp eax, 1
     jnz @F
     cmp dword [gameProcess.points+5*4], 11
     jg @F
     add dword [gameProcess.points+5*4], 10
     inc dword [gameProcess.Aces+5*4]
@@:

     cmp dword [gameProcess.points+5*4], 22
     jl @F
     cmp dword [gameProcess.Aces+5*4], 0
     jz @F
     dec dword [gameProcess.Aces+5*4]
     sub dword [gameProcess.points+5*4], 10

@@:
     mov eax, [gameProcess.points+5*4]
     dec dword [gameProcess.CardNow]

     ret
endp

proc gameProcess.mix uses ebx edx
     stdcall mix.mix
     mov dword [gameProcess.CardNow], 51
     ret
endp


proc gameProcess.printStart uses ebx edx ecx,\
     hwnddlg, hdc


     xor eax, eax
     mov ax, [screen_translate.coordx3]
     mov dword [gameProcess.coordx+2*4], eax
     add dword [gameProcess.coordx+2*4], 60
     mov dword [gameProcess.WhoPlayNow+2*4], 1

     xor eax, eax
     mov ax, [screen_translate.coordxd]
     mov dword [gameProcess.coordx+5*4], eax
     add dword [gameProcess.coordx+5*4], 60
     mov dword [gameProcess.WhoPlayNow+5*4], 1

     xor eax, eax
     mov ax, [screen_translate.coordx4]
     mov dword [gameProcess.coordx+3*4], eax
     add dword [gameProcess.coordx+3*4], 60
     mov dword [gameProcess.WhoPlayNow+3*4], 1

     xor eax, eax
     mov ax, [screen_translate.coordx1]
     mov dword [gameProcess.coordx+0*4], eax
     add dword [gameProcess.coordx+0*4], 60
     mov dword [gameProcess.WhoPlayNow+0*4], 1

     xor eax, eax
     mov ax, [screen_translate.coordx2]
     mov dword [gameProcess.coordx+1*4], eax
     add dword [gameProcess.coordx+1*4], 60
     mov dword [gameProcess.WhoPlayNow+1*4], 1

     xor eax, eax
     mov ax, [screen_translate.coordx5]
     mov dword [gameProcess.coordx+4*4], eax
     add dword [gameProcess.coordx+4*4], 60
     mov dword [gameProcess.WhoPlayNow+4*4], 1

     stdcall gameProcess.Game, 0, MYMESSAGE_NEW_GAME, [hdc]

;mainWindow.greenBrush
     ret
endp

proc gameProcess.cmpResults uses ecx edx eax

 mov edx, 0
@@:
 xor eax, eax
 xor ecx, ecx
 mov al, byte [gameProcess.points+5*4]
 mov ah, [gameProcess.CardCount+5*1]
 mov cl, byte [gameProcess.points+edx*4]
 mov ch, [gameProcess.CardCount+edx*1]
 stdcall dealer.campare
 cmp eax, 0
 jz endGameDraw
 jg endGameLoose
 jl endGameWin

endGameDraw:
 mov dword [gameProcess.GameResult+edx*4], 1
 jmp endGame

endGameLoose:
 mov dword [gameProcess.GameResult+edx*4], 0
 jmp endGame

endGameWin:
 mov dword [gameProcess.GameResult+edx*4], 2
 jmp endGame

endGame:
 inc edx
 cmp edx, 5
 jl @B



     ret
endp


proc gameProcess.printPlayButtons uses ebx ecx eax

     mov ebx, [screen_translate.width]
     mov ecx, [screen_translate.height]
     sub ecx, height_button_game*2
     sub ebx, width_button_game/2+width_button_game*4
     stdcall drawBitmap.AddToDraw, ebx, ecx, [button_arr_game]

     add ebx, width_button_game/2*3
     stdcall drawBitmap.AddToDraw, ebx, ecx, [button_arr_game+4]

     add ebx, width_button_game/2*3
     stdcall drawBitmap.AddToDraw, ebx, ecx, [button_arr_game+8]


     ret
endp

proc gameProcess.deletePlayButtons uses ebx ecx eax

     mov ecx, 1
@@:
     stdcall drawBitmap.DeleteFromDraw, [button_arr_game+4*ecx-4]
     inc ecx
     cmp ecx, 5
     jl @B

     ret
endp















