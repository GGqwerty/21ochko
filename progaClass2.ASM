format PE GUI 4.0
entry start

include 'win32w.inc'

;Перечень идентификаторов
ID_DIALOG = 1 ;шаблона диалогового окна
ID_STATIC = 2 ;Статического элемента управления
width_cards = 71
height_cards = 96
width_button_menu = 266
height_button_menu = 61
width_button_game = 155
height_button_game = 85

MYMESSAGE_NEW_GAME = 0
MYMESSAGE_DEAL = 1
MYMESSAGE_STAND = 2
MYMESSAGE_HIT = 3
MYMESSAGE_DOUBLE = 4
MYMESSAGE_SPLIT = 5
MYMESSAGE_NEWPLAYER = 6



section '.code' code readable executable
include 'Units\mix.c'
include 'Units\random.c'
include 'Units\loadImages.c'
include 'Units\dealer.c'
include 'Units\drawBitmap.c'
include 'Units\static_class.c'
include 'Units\screen_translater.c'
include 'Units\mainWindow.c'
include 'Units\button_class.c'
include 'Units\gameProcess.c'
include 'Units\string_work.c'
include 'Units\bot.c'
include 'Units\brez.c'

start:
 invoke SetProcessDPIAware
 stdcall loadImages.CursorLoad
 invoke GetModuleHandle, 0
 mov dword [_hModule], eax
 stdcall mainWindow.init
 invoke CreateWindowEx, 0, mainWindow.ClassName, _WindowName,\
 WS_VISIBLE or WS_POPUP or WS_MAXIMIZE, 0, 0, 0, 0, HWND_DESKTOP, 0, [_hModule], NULL

mainLoop:
 invoke GetMessage, msg, NULL, 0, 0
 cmp eax, 1
 jb ExitProgramm
 invoke DispatchMessage, msg
 jmp mainLoop

ExitProgramm:
 invoke DeleteObject, [mainWindow.greenBrush]

 invoke ExitProcess, 0
;Диалоговая процедура
proc DialogProc uses edx, hwnddlg, msg, wParam, lParam
 cmp [msg], WM_CREATE
 jz msgCreateWindow
 cmp [msg], WM_CLOSE
 jz msgCloseWindow
 cmp [msg], WM_DESTROY
 jz msgDestroyWindow
 cmp [msg], WM_PAINT
 jz msgPaint
 cmp [msg], WM_LBUTTONDOWN
 jz msgLButtonDown
 cmp [msg], WM_LBUTTONUP
 jz msgLButtonUp
 cmp [msg], WM_KEYDOWN
 jz msgKeyDown

@@:
 jmp ExitWndProc

msgCreateWindow:
 invoke InitCommonControls
 invoke CreateSolidBrush, $00004600
 mov [mainWindow.greenBrush], eax

 stdcall screen_translater.init, [hwnddlg]
 call loadImages.StringNamesOfBitmaps

 stdcall loadImages.ButtonsLoad
 call Random.Initialize
 call mix.initialize
 stdcall mix.mix
 stdcall drawBitmap.swapQueue, 0
 stdcall loadImages.ButtonsLoad.init


 jmp ExitWndProc


msgPaint:
 cmp dword [printFlag], 0
 jz msgPaint.drawMenu
 cmp dword [printFlag], 1
 jz msgPaint.drawGame.prepare
 cmp dword [printFlag], 2
 jz msgPaint.drawGame.gameplay
 cmp dword [printFlag], 3
 jz msgPaint.drawGame.endgame
 cmp dword [printFlag], 4
 jz msgPaint.drawGame.hit
 cmp dword [printFlag], 5
 jz msgPaint.drawGame.continue
 cmp dword [printFlag], 6
 jz msgPaint.drawGame.double


 cmp dword [printFlag], 10
 jz msgPaint.drawGame.settings


msgPaint.drawMenu:
 invoke BeginPaint, [hwnddlg], ps

 stdcall drawBitmap.DrawAll, eax

 invoke EndPaint, [hwnddlg], ps

 jmp msgPaint.endPaint

msgPaint.drawGame.settings:
 invoke BeginPaint, [hwnddlg], ps

 stdcall drawBitmap.DrawAll, eax

 invoke EndPaint, [hwnddlg], ps

 jmp msgPaint.endPaint

msgPaint.drawGame.prepare:

 stdcall gameProcess.mix
 invoke BeginPaint, [hwnddlg], ps
 push eax
 push eax
 push eax
 push eax
 stdcall gameProcess.printStart, [hwnddlg], eax
 pop eax
 stdcall drawBitmap.DrawAll, eax
 pop eax
 stdcall dealer.gameplay, eax, 4
 pop eax
 stdcall bot.gameplay, eax, 3
 pop eax
 mov dword [printFlag], 2
 stdcall gameProcess.printPlayButtons
 stdcall drawBitmap.DrawAll, eax
 invoke EndPaint, [hwnddlg], ps

 jmp msgPaint.endPaint

msgPaint.drawGame.gameplay:
 mov dword [printFlag], 2
 invoke BeginPaint, [hwnddlg], ps

 stdcall drawBitmap.DrawAll, eax
 ;stdcall gameProcess.printStart, eax, [hwnddlg]

 invoke EndPaint, [hwnddlg], ps
 ;invoke InvalidateRect, [hwnddlg], NULL, FALSE
 jmp msgPaint.endPaint

msgPaint.drawGame.endgame:
 mov dword [printFlag], 2
 invoke BeginPaint, [hwnddlg], ps
 push eax
 push eax
 push eax
 stdcall dealer.gameplay, eax, 1
 pop eax
 stdcall bot.gameplay, eax, 0
 stdcall gameProcess.deletePlayButtons
 stdcall gameProcess.swapDealerFirstCard
 pop eax
 stdcall dealer.gameplay, eax, 5
 pop eax
 stdcall gameProcess.cmpResults
 mov dword [printFlag], 3
 stdcall drawBitmap.DrawAll, eax
 ;stdcall gameProcess.printStart, eax, [hwnddlg]
 mov dword [printFlag], 1
 invoke EndPaint, [hwnddlg], ps

 jmp msgPaint.endPaint

msgPaint.drawGame.hit:
 invoke BeginPaint, [hwnddlg], ps
 push eax
 stdcall gameProcess.Game, 2, MYMESSAGE_HIT, eax
 pop eax
 stdcall drawBitmap.DrawAll, eax

 invoke EndPaint, [hwnddlg], ps
 mov dword [printFlag], 2
 jmp msgPaint.endPaint

msgPaint.drawGame.double:
 mov dword [printFlag], 2
 invoke BeginPaint, [hwnddlg], ps
 push eax
 push eax
 push eax
 push eax
 push eax
 stdcall gameProcess.Game, 2, MYMESSAGE_HIT, eax
 pop eax
 stdcall drawBitmap.DrawAll, eax

 pop eax
 stdcall dealer.gameplay, eax, 1
 pop eax
 stdcall bot.gameplay, eax, 0
 stdcall gameProcess.deletePlayButtons
 stdcall gameProcess.swapDealerFirstCard
 pop eax
 stdcall dealer.gameplay, eax, 5
 pop eax
 stdcall gameProcess.cmpResults
 mov dword [printFlag], 3
 stdcall drawBitmap.DrawAll, eax
 ;stdcall gameProcess.printStart, eax, [hwnddlg]
 mov dword [printFlag], 1

 invoke EndPaint, [hwnddlg], ps

 jmp msgPaint.endPaint

msgPaint.drawGame.continue:
 cmp dword [lastPrintFlag], 2
 jz msgPaint.drawGame.gameplay
 stdcall gameProcess.deletePlayButtons
 invoke BeginPaint, [hwnddlg], ps

 stdcall drawBitmap.DrawAll, eax

 invoke EndPaint, [hwnddlg], ps

 mov dword [printFlag], 1
 jmp msgPaint.endPaint


msgPaint.endPaint:
 jmp ExitWndProc

msgKeyDown:
 cmp [wParam], VK_ESCAPE
 jnz ExitWndProc
 ;jz  msgDestroyWindow
 cmp dword [printFlag], 10
 jz @F
 cmp dword [printFlag], 0
 jz @F
 mov eax, [printFlag]
 mov [lastPrintFlag], eax
@@:
 mov dword [printFlag], 0
 stdcall drawBitmap.swapQueue, 0
 invoke InvalidateRect, [hwnddlg], NULL, FALSE
 jmp ExitWndProc

msgLButtonDown:
 push ebx
 push eax
 mov eax, [lParam]
 xor ebx, ebx
 mov bx, ax
 shr eax, 16
 mov [movePt.x], eax
 mov [movePt.y], ebx
 stdcall drawBitmap.PtInRect, eax, ebx
 cmp eax, 0
 jz lol.end
 ;mov dword [hwndBitmapMove], eax
 ;mov dword [moveFlag], 1
 cmp eax, [button_arr]
 jz msgLButtonDown.menu.Start
 cmp eax, [button_arr+8]
 jz msgLButtonDown.menu.Settings
 cmp eax, [button_arr+12]
 jz msgLButtonDown.menu.Exit
 cmp eax, [button_arr+4]
 jz msgLButtonDown.menu.Continue
 cmp eax, [button_arr_game]
 jz msgLButtonDown.game.Hit
 cmp eax, [button_arr_game+4]
 jz msgLButtonDown.game.Stand
 cmp eax, [button_arr_game+8]
 jz msgLButtonDown.game.Double
 cmp eax, [button_arr+16]
 jz msgLButtonDown.menu.chooseTextColor
 cmp eax, [button_arr+20]
 jz msgLButtonDown.menu.chooseBackground
 cmp eax, [button_arr+24]
 jz msgLButtonDown.menu.back

 jmp lol.end

msgLButtonDown.menu.Start:
 mov dword [printFlag], 1
 stdcall drawBitmap.swapQueue, 1
 jmp lol.end

msgLButtonDown.menu.Continue:
 mov dword [printFlag], 5
 stdcall drawBitmap.swapQueue, 1
 jmp lol.end

msgLButtonDown.menu.Settings:
 mov dword [printFlag], 10
 stdcall drawBitmap.swapQueue, 2
 jmp lol.end

msgLButtonDown.menu.Exit:
 jmp msgDestroyWindow

msgLButtonDown.menu.chooseTextColor:
 mov ecx, sizeof.CHOOSECOLOR
@@:
 mov byte[mainWindow.dialogColor+ecx-1], 0
 loop @B
 mov [mainWindow.dialogColor.lStructSize], sizeof.CHOOSECOLOR
 mov eax, [hwnddlg]
 mov [mainWindow.dialogColor.hwndOwner], eax
 mov [mainWindow.dialogColor.lpCustColors], mainWindow.arr
 mov dword [mainWindow.dialogColor.rgbResult], $00006400
 invoke ChooseColor, mainWindow.dialogColor
 cmp eax, 0
 jz @F
 mov eax, [mainWindow.dialogColor.rgbResult]
 mov [mainWindow.textColor], eax
@@:
 jmp lol.end

msgLButtonDown.menu.chooseBackground:
 mov ecx, sizeof.CHOOSECOLOR
@@:
 mov byte[mainWindow.dialogColor+ecx-1], 0
 loop @B
 mov [mainWindow.dialogColor.lStructSize], sizeof.CHOOSECOLOR
 mov eax, [hwnddlg]
 mov [mainWindow.dialogColor.hwndOwner], eax
 mov [mainWindow.dialogColor.lpCustColors], mainWindow.arr
 mov dword [mainWindow.dialogColor.rgbResult], $00006400
 invoke ChooseColor, mainWindow.dialogColor
 cmp eax, 0
 jz @F
 invoke DeleteObject, mainWindow.greenBrush
 invoke CreateSolidBrush, [mainWindow.dialogColor.rgbResult]
 mov [mainWindow.greenBrush], eax
@@:

 jmp lol.end


msgLButtonDown.menu.back:
 stdcall drawBitmap.swapQueue, 0
 mov dword [printFlag], 0
 jmp lol.end

msgLButtonDown.game.Hit:
 mov dword [printFlag], 4

 jmp lol.end

msgLButtonDown.game.Stand:
 mov dword [printFlag], 3

 jmp lol.end

msgLButtonDown.game.Double:
 mov dword [printFlag], 6
 jmp lol.end

lol.end:
 invoke InvalidateRect, [hwnddlg], NULL, FALSE
 pop eax
 pop ebx
 jmp ExitWndProc

msgMouseMove:
 cmp dword [moveFlag], 0
 jz ExitWndProc
 push eax
 push ebx
 mov eax, [lParam]
 xor ebx, ebx
 mov bx, ax
 shr eax, 16
 mov [movePtBuf.x], eax
 mov [movePtBuf.y], ebx
 sub eax, [movePt.x]
 sub ebx, [movePt.y]
 mov [xMove], eax
 mov [yMove], ebx
 stdcall drawBitmap.TakeCoords, [hwndBitmapMove]
 xor ebx, ebx
 mov bx, ax
 shr eax, 16
 add eax, [yMove]
 add ebx, [xMove]
 stdcall drawBitmap.ChangeUnderDraw, eax, ebx, [hwndBitmapMove]
 mov eax, [movePtBuf.x]
 mov ebx, [movePtBuf.y]
 mov [movePt.x], eax
 mov [movePt.y], ebx


 invoke InvalidateRect, [hwnddlg], NULL, FALSE

 pop ebx
 pop eax

 jmp ExitWndProc

msgLButtonUp:
 ;mov dword [moveFlag], 0
 jmp ExitWndProc

msgCloseWindow:
 invoke DestroyWindow, [hwnddlg]
 jmp ExitWndProc

msgDestroyWindow:
 invoke PostQuitMessage, 0
ExitWndProc:
 invoke DefWindowProc, [hwnddlg], [msg], [wParam], [lParam]
 ret
endp

section '.data' data readable writeable
        _WindowName: db 'gok', 0


        wc WNDCLASSEX
        ps PAINTSTRUCT
        msg MSG

section '.bss' data readable writeable
;Здесь будут храниться дескрипторы
_hModule: dd 00h ;модуля

printFlag: dd 0h
lastPrintFlag: dd 00h


moveFlag: dd 0
hwndBitmapMove: dd 0
movePt POINT
movePtBuf POINT
xMove: dd 0
yMove: dd 0

include 'Units\random.h'
include 'Units\random.du'

include 'Units\mix.h'
include 'Units\mix.du'

include 'Units\loadImages.h'
include 'Units\loadImages.du'

include 'Units\dealer.h'
include 'Units\dealer.du'

include 'Units\RECTANGLES.du'

include 'Units\drawBitmap.du'

include 'Units\static_class.du'

include 'Units\screen_translater.du'

include 'Units\mainWindow.du'

include 'Units\bot.du'

;include 'Units\brez.du'

include 'Units\button_class.du'
include 'Units\gameProcess.du'

include 'Units\string_work.du'

;Таблица импорта
section '.idata' data import readable writeable
library kernel, 'KERNEL32.DLL',\
 user , 'USER32.DLL' ,\
 gdi , 'GDI32.DLL',\
 time, 'Ntdll.dll',\
 ole, 'OLE32.DLL',\
 comct32, 'Comctl32.dll',\
 comdlg32, 'comdlg32.dll'
import kernel,\
 GetModuleHandle, 'GetModuleHandleW',\
 ExitProcess , 'ExitProcess',\
 Sleep, 'Sleep',\
 GetLastError, 'GetLastError',\
 GetTickCount, 'GetTickCount'

import user,\
 MessageBox, 'MessageBoxA',\
 DialogBoxParam, 'DialogBoxParamW',\
 EndDialog , 'EndDialog' ,\
 LoadImage , 'LoadImageA' ,\
 SendDlgItemMessage, 'SendDlgItemMessageA',\
 GetDlgItem, 'GetDlgItem',\
 GetWindowRect, 'GetWindowRect',\
 SetWindowText, 'SetWindowTextA',\
 RegisterClassEx, 'RegisterClassExA',\
 CreateWindowEx, 'CreateWindowExA',\
 GetMessage , 'GetMessageA' ,\
 TranslateMessage, 'TranslateMessage',\
 DispatchMessage , 'DispatchMessageA',\
 DestroyWindow, 'DestroyWindow',\
 PostQuitMessage, 'PostQuitMessage',\
 DefWindowProc, 'DefWindowProcA',\
 SetRect, 'SetRect',\
 BeginPaint, 'BeginPaint',\
 EndPaint, 'EndPaint',\
 GetSystemMetrics, 'GetSystemMetrics',\
 SetClassLong, 'SetClassLongA',\
 InvalidateRect, 'InvalidateRect',\
 SendMessage, 'SendMessageA',\
 PtInRect, 'PtInRect',\
 SetWindowLong, 'SetWindowLongA',\
 SetWindowPos, 'SetWindowPos',\
 SetDlgItemInt, 'SetDlgItemInt',\
 GetDlgItemInt, 'GetDlgItemInt',\
 SetDlgItemText, 'SetDlgItemTextA',\
 SetFocus, 'SetFocus',\
 GetDC, 'GetDC',\
 ReleaseDC, 'ReleaseDC',\
 GetClientRect, 'GetClientRect',\
 DrawText, 'DrawTextA',\
 LoadCursorFromFile, 'LoadCursorFromFileA',\
 SetProcessDPIAware, 'SetProcessDPIAware'

import gdi,\
 DeleteObject , 'DeleteObject',\
 CreateCompatibleDC, 'CreateCompatibleDC',\
 SelectObject, 'SelectObject',\
 DeleteDC, 'DeleteDC',\
 GetMapMode, 'GetMapMode',\
 SetMapMode, 'SetMapMode',\
 DPtoLP, 'DPtoLP',\
 GetObject, 'GetObjectA',\
 BitBlt, 'BitBlt',\
 CreateSolidBrush, 'CreateSolidBrush',\
 CreateCompatibleBitmap, 'CreateCompatibleBitmap',\
 Rectangle, 'Rectangle',\
 TextOut, 'TextOutA',\
 SetBkMode, 'SetBkMode',\
 SetTextColor, 'SetTextColor'

import time,\
 NtQuerySystemTime, 'NtQuerySystemTime'

import comct32,\
 InitCommonControls, 'InitCommonControls'

import comdlg32,\
 ChooseColor, 'ChooseColorA'

;Ресурсы
;section '.rsrc' resource data readable

















