section .text
global cmpstr

cmpstr:
push	ebp
mov	ebp, esp
mov	DWORD [ebp-4], 0

LOOP:
mov 	eax, [ebp+8]
add	eax,  [ebp-4]
movzx	eax, BYTE [eax]
mov 	ebx, [ebp+12]
add	ebx,  [ebp-4]
movzx	ebx, BYTE [ebx]
test 	al, al 
je 	Str1End
test 	bl, bl 
je 	Str2End
cmp 	al, bl
jne 	Str1NotEqToStr2
add	DWORD [ebp-4], 1 
jmp LOOP


Str1End:
test	bl, bl
je	Return0 
jmp 	 Return2	

Str2End:
test	al, al
je	Return0 
jmp 	Return1

Str1NotEqToStr2:
cmp	eax, ebx
jg	Return1
jmp 	 Return2	

Return0:
xor	 eax, eax
jmp 	 RETURN	

Return1:
mov	 eax, 1
jmp 	 RETURN	

Return2:
mov	 eax, 2
jmp 	 RETURN	

RETURN:
mov esp, ebp
pop ebp
ret



