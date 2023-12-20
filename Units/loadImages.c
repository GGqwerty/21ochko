proc loadImages.CursorLoad
     invoke LoadCursorFromFile, cursor_name
     mov [cursor_handle], eax
     ret
endp



proc loadImages.ButtonsLoad uses ebx edx ecx
     mov ecx, 1
@@:
     mov [button_name+13], cl
     add byte [button_name+13], '0'
     push ecx
     invoke LoadImage, [_hModule], button_name, IMAGE_BITMAP, 0, 0,\
LR_DEFAULTCOLOR+LR_DEFAULTSIZE+LR_LOADFROMFILE
     pop ecx
     mov [button_arr+4*ecx-4], eax
     inc ecx
     cmp ecx, 8
     jl @B

     mov ecx, 1
@@:
     mov [button_name_game+13], cl
     add byte [button_name_game+13], '0'
     push ecx
     invoke LoadImage, [_hModule], button_name_game, IMAGE_BITMAP, 0, 0,\
LR_DEFAULTCOLOR+LR_DEFAULTSIZE+LR_LOADFROMFILE
     pop ecx
     mov [button_arr_game+4*ecx-4], eax
     inc ecx
     cmp ecx, 5
     jl @B

     mov ecx, 1
@@:
     mov [button_name_game_push+13], cl
     add byte [button_name_game_push+13], '0'
     push ecx
     invoke LoadImage, [_hModule], button_name_game_push, IMAGE_BITMAP, 0, 0,\
LR_DEFAULTCOLOR+LR_DEFAULTSIZE+LR_LOADFROMFILE
     pop ecx
     mov [button_arr_game_push+4*ecx-4], eax
     inc ecx
     cmp ecx, 4
     jl @B

     ret
endp

proc loadImages.ButtonsLoad.init uses ecx ebx
     mov ecx, 0
@@:
     push ecx
     mov eax, [button_arr+4*ecx]
     mov [drawBitmap.bitmapHandles.menu+ecx*4], eax
     pop ecx
     inc ecx
     cmp ecx, 4
     jl @B

@@:
     push ecx
     mov eax, [button_arr+4*ecx]
     mov [drawBitmap.bitmapHandles.settings+ecx*4-16], eax
     pop ecx
     inc ecx
     cmp ecx, 8
     jl @B



     mov ebx, [screen_translate.width.half]
     sub ebx, width_button_menu/2
     mov ecx, [screen_translate.height.half]
     sub ecx, height_button_menu/2
     sub ecx, height_button_menu*3
     mov [drawBitmap.bitmapCoord.menu+0], ebx
     mov [drawBitmap.bitmapCoord.menu+4], ecx

     mov ebx, [screen_translate.width.half]
     sub ebx, width_button_menu/2
     mov ecx, [screen_translate.height.half]
     sub ecx, height_button_menu/2
     sub ecx, height_button_menu*1
     mov [drawBitmap.bitmapCoord.menu+8], ebx
     mov [drawBitmap.bitmapCoord.menu+12], ecx

     mov ebx, [screen_translate.width.half]
     sub ebx, width_button_menu/2
     mov ecx, [screen_translate.height.half]
     sub ecx, height_button_menu/2
     add ecx, height_button_menu*1
     mov [drawBitmap.bitmapCoord.menu+16], ebx
     mov [drawBitmap.bitmapCoord.menu+20], ecx

     mov ebx, [screen_translate.width.half]
     sub ebx, width_button_menu/2
     mov ecx, [screen_translate.height.half]
     sub ecx, height_button_menu/2
     add ecx, height_button_menu*3
     mov [drawBitmap.bitmapCoord.menu+24], ebx
     mov [drawBitmap.bitmapCoord.menu+28], ecx

     mov ebx, [screen_translate.width.half]
     sub ebx, width_button_menu/2
     mov ecx, [screen_translate.height.half]
     sub ecx, height_button_menu/2
     sub ecx, height_button_menu*3
     mov [drawBitmap.bitmapCoord.settings+0], ebx
     mov [drawBitmap.bitmapCoord.settings+4], ecx

     mov ebx, [screen_translate.width.half]
     sub ebx, width_button_menu/2
     mov ecx, [screen_translate.height.half]
     sub ecx, height_button_menu/2
     sub ecx, height_button_menu*1
     mov [drawBitmap.bitmapCoord.settings+8], ebx
     mov [drawBitmap.bitmapCoord.settings+12], ecx

     mov ebx, [screen_translate.width.half]
     sub ebx, width_button_menu/2
     mov ecx, [screen_translate.height.half]
     sub ecx, height_button_menu/2
     add ecx, height_button_menu*1
     mov [drawBitmap.bitmapCoord.settings+16], ebx
     mov [drawBitmap.bitmapCoord.settings+20], ecx


     ret
endp

proc loadImages.StringNamesOfBitmaps uses ebx edx
     xor ebx, ebx

;подгрузка червей
     mov dl, 'h'
     mov ecx, 13
@@:
     mov eax, ecx
     cmp eax, 10
     jb loadImages.h
     sub eax, 10
     inc ah
loadImages.h:
     add ah, '0'
     add al, '0'
     xchg al, ah
     mov [card_images+8], dl
     mov [card_images+9], ax
     push ecx
     push edx
     invoke LoadImage, [_hModule], card_images, IMAGE_BITMAP, 0, 0,\
LR_DEFAULTCOLOR+LR_DEFAULTSIZE+LR_LOADFROMFILE
     mov [card_handles+ebx], eax
     add ebx, 4
     pop edx
     pop ecx
     loop @B

;подгрузка бубны
     mov dl, 'd'
     mov ecx, 13
@@:
     mov eax, ecx
     cmp eax, 10
     jb loadImages.d
     sub eax, 10
     inc ah
loadImages.d:
     add ah, '0'
     add al, '0'
     xchg al, ah
     mov [card_images+8], dl
     mov [card_images+9], ax
     push ecx
     push edx
     invoke LoadImage, [_hModule], card_images, IMAGE_BITMAP, 0, 0,\
LR_DEFAULTCOLOR+LR_DEFAULTSIZE+LR_LOADFROMFILE
     mov [card_handles+ebx], eax
     add ebx, 4
     pop edx
     pop ecx
     loop @B

;подгрузка кресты
     mov dl, 'c'
     mov ecx, 13
@@:
     mov eax, ecx
     cmp eax, 10
     jb loadImages.c
     sub eax, 10
     inc ah
loadImages.c:
     add ah, '0'
     add al, '0'
     xchg al, ah
     mov [card_images+8], dl
     mov [card_images+9], ax
     push ecx
     push edx
     invoke LoadImage, [_hModule], card_images, IMAGE_BITMAP, 0, 0,\
LR_DEFAULTCOLOR+LR_DEFAULTSIZE+LR_LOADFROMFILE
     mov [card_handles+ebx], eax
     add ebx, 4
     pop edx
     pop ecx
     loop @B

;подгрузка пики
     mov dl, 's'
     mov ecx, 13
@@:
     mov eax, ecx
     cmp eax, 10
     jb loadImages.s
     sub eax, 10
     inc ah
loadImages.s:
     add ah, '0'
     add al, '0'
     xchg al, ah
     mov [card_images+8], dl
     mov [card_images+9], ax
     push ecx
     push edx
     invoke LoadImage, [_hModule], card_images, IMAGE_BITMAP, 0, 0,\
LR_DEFAULTCOLOR+LR_DEFAULTSIZE+LR_LOADFROMFILE
     mov [card_handles+ebx], eax
     add ebx, 4
     pop edx
     pop ecx
     loop @B
     invoke LoadImage, [_hModule], back_name1, IMAGE_BITMAP, 0, 0,\
LR_DEFAULTCOLOR+LR_DEFAULTSIZE+LR_LOADFROMFILE
     mov [card_cover_koloda], eax
     invoke LoadImage, [_hModule], back_name2, IMAGE_BITMAP, 0, 0,\
LR_DEFAULTCOLOR+LR_DEFAULTSIZE+LR_LOADFROMFILE
     mov [card_cover], eax

     ret
endp

; в eax число - в eax handle
proc loadImages.TranslateNumInHandle
     shl eax, 2
     add eax, card_handles
     ret
endp

proc loadImages.DeleteImages
     mov ecx, 51
loadImages.del:
     mov eax, ecx
     push ecx
     call loadImages.TranslateNumInHandle
     invoke DeleteObject, [eax]
     pop ecx
     loop loadImages.del
     mov eax, ecx
     call loadImages.TranslateNumInHandle
     invoke DeleteObject, [eax]


     mov ecx, 1
@@:
     mov eax, [button_arr+4*ecx-4]
     push ecx
     invoke DeleteObject, [eax]
     pop ecx
     inc ecx
     cmp ecx, 5
     jl @B

     mov ecx, 1
@@:
     mov eax, [button_arr_game+4*ecx-4]
     push ecx
     invoke DeleteObject, [eax]
     pop ecx
     inc ecx
     cmp ecx, 5
     jl @B

     ret
endp



; в eax число - в eax очки
;1 - значит туз
proc loadImages.TranslateNumInOchki
     push ecx
     push edx
     xor edx, edx
     mov ecx, 13
     div cx
     mov eax, 12
     sub eax, edx
     cmp ax, 9
     jb loadImages.TranslateNumInOchki.more
     mov eax, 9
loadImages.TranslateNumInOchki.more:
     inc eax
     pop edx
     pop ecx
     ret
endp