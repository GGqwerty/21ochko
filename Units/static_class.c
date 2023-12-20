proc static_class.init
     mov ecx, 52
static_class.loop:
     mov [static_handles_id+ecx], ecx
loop static_class.loop
 ret
endp

proc static_class.Create_Static uses eax ebx edx ecx,\
     x, y, height, width, hwnd, idOf
     invoke CreateWindowEx, NULL,  _static_class_name,\
     0,\
     WS_VISIBLE or WS_CHILD or SS_BITMAP or SS_NOTIFY,\
     [x],\
     [y],\
     [height],\
     [width],\
     [hwnd],\
     NULL,\
     [idOf],\
     NULL
     mov ebx,[static_schet]
     mov [static_handles+ebx], eax
     invoke SetWindowLong, eax, -12, [idOf]
     inc dword [static_schet]
     invoke SetWindowPos, [static_handles+ebx], [static_handles+ebx-4], [x], [y], [height], [width]
     ret
endp