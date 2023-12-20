proc mainWindow.init uses eax
     mov [mainWindow.wc.cbSize], sizeof.WNDCLASSEX
     mov [mainWindow.wc.style], CS_HREDRAW
     mov [mainWindow.wc.lpfnWndProc], DialogProc
     mov [mainWindow.wc.cbClsExtra], 0
     mov [mainWindow.wc.cbWndExtra], 0
     mov eax, [_hModule]
     mov [mainWindow.wc.hInstance], eax
     mov [mainWindow.wc.hIcon], NULL
     mov eax, [cursor_handle]
     mov [mainWindow.wc.hCursor], eax
     mov [mainWindow.wc.hbrBackground], COLOR_WINDOWTEXT
     mov [mainWindow.wc.lpszMenuName], NULL
     mov [mainWindow.wc.lpszClassName], mainWindow.ClassName
     mov [mainWindow.wc.hIconSm], 0
     invoke RegisterClassEx, mainWindow.wc
     ret
endp


