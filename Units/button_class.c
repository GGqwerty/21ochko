proc button_class.init
     mov ecx, 52
button_class.loop:
     mov [static_handles_id+ecx], ecx
loop button_class.loop
 ret
endp

proc button_class.Create_Button uses eax ebx edx ecx,\
     x, y, height, width, hwnd, idOf
     invoke CreateWindowEx, NULL,  _button_class_name,\
     0,\
     WS_VISIBLE or WS_CHILD or BS_CENTER,\ ;or BS_BITMAP,\
     [x],\
     [y],\
     [height],\
     [width],\
     [hwnd],\
     NULL,\
     [idOf],\
     NULL
     mov ebx,[button_schet]
     mov [button_handles+ebx], eax
     invoke SetWindowLong, eax, -12, [idOf]
     inc dword [button_schet]
     ;invoke SetWindowPos, [button_handles+ebx], [button_handles+ebx-4], [x], [y], [height], [width]
     ret
endp