proc screen_translater.init,\
     hwnd
     push edx
     push ecx
     ;invoke GetClientRect, [hwnd], screen_translate.clientRect
     ;invoke GetLastError
     ;mov eax, [screen_translate.clientRect.right]
     invoke GetSystemMetrics, SM_CXSCREEN
     mov [screen_translate.width], eax
     xor edx, edx
     mov ecx, 3
     div cx
     mov word [screen_translate.coordx1], 100
     mov word [screen_translate.coordxd], 100
     add word [screen_translate.coordxd], ax
     mov word [screen_translate.coordx2], 300
     mov word [screen_translate.coordx3], 100
     add word [screen_translate.coordx3], ax
     mov word [screen_translate.coordx4], -100
     add word [screen_translate.coordx4], ax
     add word [screen_translate.coordx4], ax
     mov word [screen_translate.coordx5], 100
     add word [screen_translate.coordx5], ax
     add word [screen_translate.coordx5], ax
     mov eax, [screen_translate.width]
     xor edx, edx
     mov ecx, 2
     div cx
     mov [screen_translate.width.half], eax


     invoke GetSystemMetrics, SM_CYSCREEN
     ;mov eax, [screen_translate.clientRect.bottom]
     mov [screen_translate.height], eax
     xor edx, edx
     mov ecx, 2
     div cx
     mov word [screen_translate.coordy1], 200
     mov word [screen_translate.coordyd], 10
     mov word [screen_translate.coordy5], 200
     mov word [screen_translate.coordy2], 10
     add word [screen_translate.coordy2], ax
     mov word [screen_translate.coordy3], 150
     add word [screen_translate.coordy3], ax
     mov word [screen_translate.coordy4], 10
     add word [screen_translate.coordy4], ax

     mov [screen_translate.height.half], eax
     pop ecx
     pop edx
     ret
endp