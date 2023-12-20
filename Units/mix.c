proc mix.mix uses ebx
     mov  ecx, 51
StartMix:
     push ecx
     stdcall Random.Get, 0, ecx
     pop ecx
     mov bl, [koloda_cart+eax]
     xchg bl, [koloda_cart+ecx]
     mov [koloda_cart+eax], bl
     loop StartMix
     ret
endp


proc mix.initialize
     mov ecx, 51
     mov eax, 51
@@:
     mov byte [koloda_cart+eax], cl
     dec eax
     loop @B
     mov [koloda_cart+eax], cl
     ret
endp

; in eax - num, out eax num
proc mix.TranslateNumInCardNum uses ecx
     mov  ecx, eax
     xor eax, eax
     mov al, byte [koloda_cart+ecx]


     ret
endp