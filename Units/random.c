proc Random.Initialize
     invoke NtQuerySystemTime, Random.wPrevNumberNach
     ret
endp

proc Random.Get uses edx,\
     wMin, wMax

     invoke NtQuerySystemTime, Random.wPrevNumberBuf
     mov        edx, [Random.wPrevNumberBuf]
     rol        edx, 3
     adc        edx, 15
     mov        [Random.wPrevNumberNach], eax
     mov        eax, [Random.wPrevNumberNach]
     rol        eax, 7
     adc        eax, 37
     add        eax, edx
     mov        [Random.wPrevNumberNach], eax

     mov        ecx, [wMax]
     sub        ecx, [wMin]
     inc        ecx
     xor        edx, edx
     div        cx
     add        edx, [wMin]
     xchg       eax, edx
     ret
endp