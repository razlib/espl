section .text
global bsplit
global main 

extern fread
extern fwrite
extern sprintf
extern fopen
extern fclose
extern rewind

section .data
buffer resb 100
tmpbuf resb 15
newName resb 100
msg1	db  "rb"
msg2	db  "w+"
msg3	db  "%d"
msg4	db  "%s%s%s"
msg5	db  "."

main:

bsplit:
  push 	ebp
  mov	ebp, esp
  ;local vars
  mov	DWORD [ebp-0x04]  , 10 ;chunk size
  mov 	DWORD [ebp - 0x08], 0 ;filename
  mov 	DWORD [ebp - 0x0C], 0 ;count
  mov 	DWORD [ebp - 0X10], 3 ;filecounter
  mov	DWORD [ebp - 0x14], 0 ;mychecksum
  mov	DWORD [ebp - 0x18], 0 ;bigfile
  mov	DWORD [ebp - 0x1C], 0 ;smallfile
  sub 	esp, 0x1C

  ;filename = arg[1]
  mov	eax, [ebp + 0x08]
  mov	DWORD [ebp - 0x08], eax

  ;prepare for fopen
  push	DWORD [ebp - 0x08]
  push 	msg1
  ;*bigFile = fopen(fileName, "rb")
  call 	fopen 
  mov	[ebp - 0x18], eax ;

LOOP:
  ;prepare for fread
  push	buffer
  mov 	ebx, 1
  push 	ebx
  push 	DWORD [ebp-0x04]
  push 	DWORD [ebp - 0x18]
  ; count = fread(buffer, 1, chunkSize, bigFile); 
  call 	fread
  mov	[ebp - 0x0C], eax

  ;prepare for sprintf
  push	tmpbuf
  push 	msg3
  push	DWORD [ebp - 0X10]
  call 	sprintf

  ;prepare for sprintf
  push	newName
  mov	ebx, 100
  push 	ebx
  push 	msg4
  push 	DWORD [ebp - 0x08]
  push 	msg5
  push    tmpbuf
  call 	sprintf

  ;smallFile = fopen(newName, "w+");
  push	newName	
  push 	msg2
  call 	fopen
  mov	[ebp - 0x1C], eax

  ;fwrite(&mychceksum,4,1,smallFile);
  lea	ebx, [ebp - 0x14]
  push 	ebx
  mov	ebx, 4
  push 	ebx
  mov	ebx, 1
  push 	ebx
  push 	DWORD [ebp - 0x1C]
  call	fwrite

  ;fwrite(buffer,count,1, smallFile);
  push	buffer
  push	DWORD [ebp - 0x0C]
  mov	ebx, 1
  push 	ebx
  push 	DWORD [ebp - 0x1C]
  call	fwrite

  ;fileCounter++;
  add	DWORD [ebp - 0X10], 1

  ;rewind(smallFile);
  push 	DWORD [ebp - 0x1C]
  call	rewind

  mov	eax, [ebp-0x04]
  mov	ebx, [ebp - 0x0C] 
  cmp	eax, ebx
  jne	EXIT

  ;fclose(smallFile);
  push	DWORD [ebp - 0x1C]
  call	fclose
  jmp	LOOP


EXIT:
  ;fclose(bigFile);
  push	DWORD [ebp - 0x18]
  call	fclose
  mov 	eax, 0
  mov	esp, ebp
  pop	ebp
  ret


