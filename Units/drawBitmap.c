proc drawBitmap.MyDrawBitmap uses ebx edx ecx eax,\
     hdc, x, y, hBitmap
     invoke CreateCompatibleDC, [hdc]
     mov [drawBitmap.hMemDC], eax
     invoke SelectObject, [drawBitmap.hMemDC], [hBitmap]
     mov [drawBitmap.hOldbm], eax
     ;cmp [drawBitmap.hOldbm], 0
     ;jz drawBitmap.End
     invoke GetMapMode, [hdc]
     invoke SetMapMode, [drawBitmap.hMemDC], eax
     invoke GetObject, [hBitmap], sizeof.BITMAP, drawBitmap.bm
     mov ebx,[drawBitmap.bm.bmWidth]
     mov [drawBitmap.ptSize.x], ebx
     mov ebx, [drawBitmap.bm.bmHeight]
     mov [drawBitmap.ptSize.y], ebx
     invoke DPtoLP, [hdc], drawBitmap.ptSize, 1
     mov [drawBitmap.ptOrg.x], 0
     mov [drawBitmap.ptOrg.y], 0
     invoke DPtoLP, [drawBitmap.hMemDC], drawBitmap.ptOrg, 1
     invoke BitBlt, [hdc], [x], [y], [drawBitmap.ptSize.x], [drawBitmap.ptSize.y],\
                    [drawBitmap.hMemDC], [drawBitmap.ptOrg.x], [drawBitmap.ptOrg.y], SRCCOPY

     invoke SelectObject, [drawBitmap.hMemDC], [drawBitmap.hOldbm]


drawBitmap.End:
     invoke DeleteDC, [drawBitmap.hMemDC]
     ret
endp

proc drawBitmap.RepairOfDraw uses ebx eax ecx edx
    mov eax, 0
    mov ecx, 0
@@:
    cmp dword [drawBitmap.bitmapHandles+ecx], 0
    jz drawBitmap.repair.next
    mov ebx, [drawBitmap.bitmapHandles+ecx]
    mov [drawBitmap.bitmapHandles+eax], ebx
    mov ebx, [drawBitmap.bitmapCoord+ecx*2]
    mov [drawBitmap.bitmapCoord+eax*2], ebx
    mov ebx, [drawBitmap.bitmapCoord+ecx*2+4]
    mov [drawBitmap.bitmapCoord+eax*2+4], ebx
    add eax, 4

drawBitmap.repair.next:
    add ecx, 4
    cmp ecx, 104*4
    jz drawBitmap.repair.end
    jmp @B

drawBitmap.repair.end:
    mov dword [drawBitmap.bitmapHandles+eax], 0
    add eax, 4
    cmp eax, 104*4
    jz drawBitmap.repair.exit
    jmp drawBitmap.repair.end

drawBitmap.repair.exit:
    ret
endp

proc drawBitmap.AddToDraw uses ebx eax ecx edx,\
     x, y, hBitmap
     mov ecx, 0
@@:
     cmp dword [drawBitmap.bitmapHandles+ecx], 0
     jz drawBitmap.Add
     add ecx, 4
     jmp @B

drawBitmap.Add:
     mov eax, [hBitmap]
     mov [drawBitmap.bitmapHandles+ecx], eax
     mov eax, [x]
     mov [drawBitmap.bitmapCoord+ecx*2], eax
     mov eax, [y]
     mov [drawBitmap.bitmapCoord+ecx*2+4], eax
     stdcall drawBitmap.RepairOfDraw
     ret
endp

proc drawBitmap.DeleteFromDraw uses ebx eax ecx edx,\
     hBitmap

     mov ecx, 103*4
@@:
     mov eax, [hBitmap]
     cmp [drawBitmap.bitmapHandles+ecx], eax
     jnz drawBitmap.Delete.next
     mov dword [drawBitmap.bitmapHandles+ecx], 0

drawBitmap.Delete.next:
     cmp ecx, 0
     jz drawBitmap.endDelete
     sub ecx, 4
     jmp @B

drawBitmap.endDelete:
     stdcall drawBitmap.RepairOfDraw
     ret
endp

proc drawBitmap.DeleteAllFromDraw uses ebx eax ecx edx

     mov ecx, 103*4
@@:
     mov dword [drawBitmap.bitmapHandles+ecx], 0

     cmp ecx, 0
     jz drawBitmap.endDeleteAll
     sub ecx, 4
     jmp @B

drawBitmap.endDeleteAll:
     ret
endp

proc drawBitmap.ChangeUnderDraw uses ebx eax ecx edx,\
     x, y, hBitmap

mov ecx, 103*4
@@:
     mov eax, [hBitmap]
     cmp [drawBitmap.bitmapHandles+ecx], eax
     jnz drawBitmap.Change.next
     mov eax, [x]
     mov [drawBitmap.bitmapCoord+ecx*2], eax
     mov eax, [y]
     mov [drawBitmap.bitmapCoord+ecx*2+4], eax
     jmp drawBitmap.endChange

drawBitmap.Change.next:
     cmp ecx, 0
     jz drawBitmap.endChange
     sub ecx, 4
     jmp @B

drawBitmap.endChange:
     ret
endp

proc drawBitmap.ChangeBitmapUnderDraw uses ebx eax ecx edx,\
     NewhBitmap, hBitmap

mov ecx, 103*4
@@:
     mov eax, [hBitmap]
     cmp [drawBitmap.bitmapHandles+ecx], eax
     jnz drawBitmap.ChangeBitmap.next
     mov eax, [NewhBitmap]
     mov [drawBitmap.bitmapHandles+ecx], eax
     jmp drawBitmap.endChangeBitmap

drawBitmap.ChangeBitmap.next:
     cmp ecx, 0
     jz drawBitmap.endChangeBitmap
     sub ecx, 4
     jmp @B

drawBitmap.endChangeBitmap:
     ret
endp

proc drawBitmap.TakeCoords uses ebx ecx edx,\
     hBitmap
     mov edi, [drawBitmap.bitmapCoord.pointer]
     mov esi, [drawBitmap.bitmapHandles.pointer]
mov ecx, 103*4
@@:
     mov eax, [hBitmap]
     cmp [esi+ecx], eax
     jnz drawBitmap.Take.next
     mov eax, [edi+ecx*2]
     shl eax, 16
     mov ebx, [edi+ecx*2+4]
     mov ax, bx
     jmp drawBitmap.endTake

drawBitmap.Take.next:
     cmp ecx, 0
     jz drawBitmap.endTake
     sub ecx, 4
     jmp @B

drawBitmap.endTake:
     ret
endp



proc drawBitmap.DrawAll uses ebx eax ecx edx esi edi,\
     hdc
     mov edi, [drawBitmap.bitmapCoord.pointer]
     mov esi, [drawBitmap.bitmapHandles.pointer]
     mov eax, [hdc]
     mov [drawBitmap.windowHdc], eax
     invoke CreateCompatibleDC, eax
     mov [drawBitmap.buf.hMemDC], eax
     invoke CreateCompatibleBitmap, [hdc], [screen_translate.width], [screen_translate.height]
     mov [drawBitmap.buf.bm], eax
     invoke SelectObject, [drawBitmap.buf.hMemDC], [drawBitmap.buf.bm]
     invoke SelectObject, [drawBitmap.buf.hMemDC], [mainWindow.greenBrush]
     invoke Rectangle, [drawBitmap.buf.hMemDC], 0, 0, [screen_translate.width], [screen_translate.height]
     mov ecx, 0
@@:
     cmp dword [esi+ecx], 0
     jz drawBitmap.next
     stdcall drawBitmap.MyDrawBitmap, dword [drawBitmap.buf.hMemDC], dword [edi+ecx*2], dword [edi+ecx*2+4] ,dword [esi+ecx]


drawBitmap.next:
     cmp ecx, 103*4
     jz drawBitmap.endAllDraw
     add ecx, 4
     jmp @B

drawBitmap.endAllDraw:
     invoke SetBkMode, [drawBitmap.buf.hMemDC], TRANSPARENT

     stdcall drawBitmap.drawStrings, [drawBitmap.buf.hMemDC]

     invoke BitBlt, [hdc], 0, 0, [screen_translate.width], [screen_translate.height],\
                    [drawBitmap.buf.hMemDC], 0, 0, SRCCOPY
     invoke DeleteObject, [drawBitmap.buf.bm]
     invoke DeleteObject, [drawBitmap.buf.hMemDC]
     ret
endp

proc drawBitmap.PtInRect uses ecx edx ebx esi edi,\
     x, y
     mov edi, [drawBitmap.bitmapCoord.pointer]
     mov esi, [drawBitmap.bitmapHandles.pointer]
     mov ebx, [x]
     mov [drawBitmap.PtInRect.pt.x], ebx
     mov ebx, [y]
     mov [drawBitmap.PtInRect.pt.y], ebx
     mov ecx, 103*4
@@:
     push ecx
     cmp dword [esi+ecx], 0
     jz drawBitmap.PtInRect.next
     mov ebx, [edi+ecx*2]
     mov [drawBitmap.PtInRect.rect.left], ebx
     mov [drawBitmap.PtInRect.rect.right], ebx
     mov ebx, [edi+ecx*2+4]
     mov [drawBitmap.PtInRect.rect.top], ebx
     mov [drawBitmap.PtInRect.rect.bottom], ebx
     invoke GetObject, [esi+ecx], sizeof.BITMAP, drawBitmap.PtInRect.bm
     mov ebx, [drawBitmap.PtInRect.bm.bmWidth]
     add [drawBitmap.PtInRect.rect.right], ebx
     mov ebx, [drawBitmap.PtInRect.bm.bmHeight]
     add [drawBitmap.PtInRect.rect.bottom], ebx
     invoke PtInRect, drawBitmap.PtInRect.rect, [drawBitmap.PtInRect.pt.y], [drawBitmap.PtInRect.pt.x]
     cmp eax, 0
     jz drawBitmap.PtInRect.next
     pop ecx
     mov eax, [esi+ecx]
     jmp drawBitmap.PtInRect.endCheck


drawBitmap.PtInRect.next:
     mov eax, 0
     pop ecx
     cmp ecx, 0
     jz drawBitmap.PtInRect.endCheck
     sub ecx, 4
     jmp @B

drawBitmap.PtInRect.endCheck:
     ret
endp

proc drawBitmap.drawStrings uses ecx ebx,\
     hdc
     invoke SetTextColor, [hdc], [mainWindow.textColor]
     cmp dword [printFlag], 0
     jz drawBitmap.drawStrings.end
     cmp dword [printFlag], 10
     jz drawBitmap.drawStrings.end

     cmp dword [printFlag], 3
     jz drawBitmap.drawStrings.endgame

     cmp dword [printFlag], 5
     jz drawBitmap.drawStrings.endgame


     cmp dword [gameProcess.WhoPlayNow], 0
     jz @F
drawBitmap.playerScore.1:
     mov eax, [gameProcess.points+0]
     stdcall string_work.numInString, eax
     xor ecx, ecx
     xor ebx, ebx
     mov cx, [screen_translate.coordx1]
     mov bx, [screen_translate.coordy1]
     add ecx, width_cards/2
     sub ebx, 20
     invoke TextOut, [drawBitmap.buf.hMemDC], ecx, ebx, eax, 4
drawBitmap.playerScore.2:
@@:
     cmp dword[gameProcess.WhoPlayNow+4], 0
     jz @F
     mov eax, [gameProcess.points+4]
     stdcall string_work.numInString, eax
     xor ecx, ecx
     xor ebx, ebx
     mov cx, [screen_translate.coordx2]
     mov bx, [screen_translate.coordy2]
     add ecx, width_cards/2
     sub ebx, 20
     invoke TextOut, [drawBitmap.buf.hMemDC], ecx, ebx, eax, 4



drawBitmap.playerScore.3:
@@:
     cmp dword[gameProcess.WhoPlayNow+8], 0
     jz @F
     mov eax, [gameProcess.points+8]
     stdcall string_work.numInString, eax
     xor ecx, ecx
     xor ebx, ebx
     mov cx, [screen_translate.coordx3]
     mov bx, [screen_translate.coordy3]
     add ecx, width_cards/2
     sub ebx, 20
     invoke TextOut, [drawBitmap.buf.hMemDC], ecx, ebx, eax, 4
drawBitmap.playerScore.4:
@@:
     cmp dword[gameProcess.WhoPlayNow+12], 0
     jz @F
     mov eax, [gameProcess.points+12]
     stdcall string_work.numInString, eax
     xor ecx, ecx
     xor ebx, ebx
     mov cx, [screen_translate.coordx4]
     mov bx, [screen_translate.coordy4]
     add ecx, width_cards/2
     sub ebx, 20
     invoke TextOut, [drawBitmap.buf.hMemDC], ecx, ebx, eax, 4
drawBitmap.playerScore.5:
@@:
     cmp dword[gameProcess.WhoPlayNow+16], 0
     jz @F
     mov eax, [gameProcess.points+16]
     stdcall string_work.numInString, eax
     xor ecx, ecx
     xor ebx, ebx
     mov cx, [screen_translate.coordx5]
     mov bx, [screen_translate.coordy5]
     add ecx, width_cards/2
     sub ebx, 20
     invoke TextOut, [drawBitmap.buf.hMemDC], ecx, ebx, eax, 4
drawBitmap.playerScore.d:
@@:
     cmp dword[gameProcess.WhoPlayNow+20], 0
     jz @F
     mov eax, [gameProcess.points+20]
     stdcall string_work.numInString, eax
     xor ecx, ecx
     xor ebx, ebx
     mov cx, [screen_translate.coordxd]
     mov bx, [screen_translate.coordyd]
     add ecx, width_cards/2
     add ebx, height_cards+5
     invoke TextOut, [drawBitmap.buf.hMemDC], ecx, ebx, eax, 4
@@:


     jmp drawBitmap.drawStrings.end
drawBitmap.drawStrings.endgame:

drawBitmap.playerResult.1:
     cmp dword [gameProcess.WhoPlayNow], 0
     jz @F
     mov eax, [gameProcess.GameResult+0]
     stdcall string_work.printResult, eax
     xor ecx, ecx
     xor ebx, ebx
     mov cx, [screen_translate.coordx1]
     mov bx, [screen_translate.coordy1]
     add ecx, width_cards/2
     sub ebx, 20
     invoke TextOut, [drawBitmap.buf.hMemDC], ecx, ebx, eax, 4
drawBitmap.playerResult.2:
@@:
     cmp dword [gameProcess.WhoPlayNow+4], 0
     jz @F
     mov eax, [gameProcess.GameResult+4]
     stdcall string_work.printResult, eax
     xor ecx, ecx
     xor ebx, ebx
     mov cx, [screen_translate.coordx2]
     mov bx, [screen_translate.coordy2]
     add ecx, width_cards/2
     sub ebx, 20
     invoke TextOut, [drawBitmap.buf.hMemDC], ecx, ebx, eax, 4
drawBitmap.playerResult.3:
@@:
     cmp dword [gameProcess.WhoPlayNow+8], 0
     jz @F
     mov eax, [gameProcess.GameResult+8]
     stdcall string_work.printResult, eax
     xor ecx, ecx
     xor ebx, ebx
     mov cx, [screen_translate.coordx3]
     mov bx, [screen_translate.coordy3]
     add ecx, width_cards/2
     sub ebx, 20
     invoke TextOut, [drawBitmap.buf.hMemDC], ecx, ebx, eax, 4
drawBitmap.playerResult.4:
@@:
     cmp dword [gameProcess.WhoPlayNow+12], 0
     jz @F
     mov eax, [gameProcess.GameResult+12]
     stdcall string_work.printResult, eax
     xor ecx, ecx
     xor ebx, ebx
     mov cx, [screen_translate.coordx4]
     mov bx, [screen_translate.coordy4]
     add ecx, width_cards/2
     sub ebx, 20
     invoke TextOut, [drawBitmap.buf.hMemDC], ecx, ebx, eax, 4
drawBitmap.playerResult.5:
@@:
     cmp dword [gameProcess.WhoPlayNow+16], 0
     jz @F
     mov eax, [gameProcess.GameResult+16]
     stdcall string_work.printResult, eax
     xor ecx, ecx
     xor ebx, ebx
     mov cx, [screen_translate.coordx5]
     mov bx, [screen_translate.coordy5]
     add ecx, width_cards/2
     sub ebx, 20
     invoke TextOut, [drawBitmap.buf.hMemDC], ecx, ebx, eax, 4
drawBitmap.playerResult.d:
@@:
     cmp dword [gameProcess.WhoPlayNow+20], 0
     jz @F
     mov eax, [gameProcess.points+20]
     stdcall string_work.numInString, eax
     xor ecx, ecx
     xor ebx, ebx
     mov cx, [screen_translate.coordxd]
     mov bx, [screen_translate.coordyd]
     add ecx, width_cards/2
     add ebx, height_cards+5
     invoke TextOut, [drawBitmap.buf.hMemDC], ecx, ebx, eax, 4
@@:

     jmp drawBitmap.drawStrings.end
drawBitmap.drawStrings.end:
     ret
endp

proc drawBitmap.swapQueue,\
     m
     cmp [m], 0
     jnz @F
     mov dword [drawBitmap.bitmapHandles.pointer], drawBitmap.bitmapHandles.menu
     mov dword [drawBitmap.bitmapCoord.pointer], drawBitmap.bitmapCoord.menu
     jmp drawBitmap.swapQueueuses.end
@@:
     cmp [m], 1
     jnz @F
     mov dword [drawBitmap.bitmapHandles.pointer], drawBitmap.bitmapHandles
     mov dword [drawBitmap.bitmapCoord.pointer], drawBitmap.bitmapCoord
     jmp drawBitmap.swapQueueuses.end
@@:
     cmp [m], 2
     jnz @F
     mov dword [drawBitmap.bitmapHandles.pointer], drawBitmap.bitmapHandles.settings
     mov dword [drawBitmap.bitmapCoord.pointer], drawBitmap.bitmapCoord.settings
     jmp drawBitmap.swapQueueuses.end
@@:


drawBitmap.swapQueueuses.end:
    ret

endp





