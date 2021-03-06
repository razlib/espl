 
section .text

global _start
global read
global write
global open
global close
global strlen

extern main
_start:
lea ecx,[esp+4]
push	ecx
push	DWORD [esp+4] 

call	main
        mov ebx,eax
mov	eax,1
int 0x80

read:
mov eax, 3
mov ebx, [esp+4]
mov ecx, [esp+8]
mov edx, [esp+12]
int 0x80
ret


write:
mov eax, 4
mov ebx, [esp+4]
mov ecx, [esp+8]
mov edx, [esp+12]
int 0x80
ret


open:
mov eax, 5
mov ebx, [esp+4]
mov ecx, [esp+8]
mov edx, [esp+12]
int 0x80
ret


close:
mov eax, 6
mov ebx, [esp+4]
int 0x80
ret


strlen:
push	ebp
mov	ebp, esp
mov	DWORD [ebp-4], 0

LOOP:
mov 	eax, [ebp+8]
add	eax,  [ebp-4]
movzx	eax, BYTE [eax]
test 	al, al 
je 	End
add	DWORD [ebp-4], 1 
jmp LOOP

End:
mov eax, DWORD [ebp-4]
mov esp, ebp
pop ebp
ret

