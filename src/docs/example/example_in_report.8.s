.text
.align 1
.global main
main:
push {fp, lr}
mov fp, sp
push {r9}
push {r8}
push {r7}
push {r6}
push {r5}
push {r4}
sub sp, sp, #32
C22:
mov r1, #0x0000
movt r1, #0x0000
mov r0, #0x0000
movt r0, #0x0000
add r7, r1, r0
mov r1, #0x0001
movt r1, #0x0000
mov r0, #0x0000
movt r0, #0x0000
add r6, r1, r0
mov r1, #0x0002
movt r1, #0x0000
mov r0, #0x0000
movt r0, #0x0000
add r5, r1, r0
mov r1, #0x0003
movt r1, #0x0000
mov r0, #0x0000
movt r0, #0x0000
add r4, r1, r0
mov r1, #0x0004
movt r1, #0x0000
mov r0, #0x0000
movt r0, #0x0000
add r8, r1, r0
str r8, [fp, #-28]
mov r1, #0x0005
movt r1, #0x0000
mov r0, #0x0000
movt r0, #0x0000
add r8, r1, r0
str r8, [fp, #-32]
mov r1, #0x0006
movt r1, #0x0000
mov r0, #0x0000
movt r0, #0x0000
add r8, r1, r0
str r8, [fp, #-36]
mov r0, #0x0007
movt r0, #0x0000
mov r1, #0x0000
movt r1, #0x0000
add r8, r0, r1
str r8, [fp, #-40]
mov r0, #0x000c
movt r0, #0x0000
mov r0, r0
bl malloc
mov r0, r0
mov r0, r0
mov r1, #0x0004
movt r1, #0x0000
add r1, r0, r1
mov r1, r1
mov r2, #0x0000
movt r2, #0x3f80
vmov.f32 s1, r2
mov r2, #0x0000
movt r2, #0x0000
vmov.f32 s0, r2
vadd.f32 s0, s1, s0
vstr.f32 s0, [r1]
mov r0, r0
mov r1, #0x0000
movt r1, #0x0000
mov r2, #0x0000
movt r2, #0x0000
add r1, r1, r2
str r1, [r0]
mov r1, #0x0008
movt r1, #0x0000
add r1, r0, r1
mov r1, r1
ldr r2, =base$b
str r2, [r1]
mov r8, r0
str r8, [fp, #-44]
mov r0, #0x0010
movt r0, #0x0000
mov r0, r0
bl malloc
mov r0, r0
mov r8, r0
str r8, [fp, #-48]
ldr r8, [fp, #-48]
mov r0, r8
mov r1, #0x0000
movt r1, #0x0000
mov r2, #0x0000
movt r2, #0x0000
add r1, r1, r2
str r1, [r0]
mov r0, #0x0004
movt r0, #0x0000
ldr r8, [fp, #-48]
add r0, r8, r0
mov r0, r0
mov r1, #0x0000
movt r1, #0x3f80
vmov.f32 s1, r1
mov r1, #0x0000
movt r1, #0x0000
vmov.f32 s0, r1
vadd.f32 s0, s1, s0
vstr.f32 s0, [r0]
mov r0, #0x0010
movt r0, #0x0000
mov r0, r0
bl malloc
mov r0, r0
mov r0, r0
mov r1, #0x0004
movt r1, #0x0000
add r0, r0, r1
mov r1, #0x0004
movt r1, #0x0000
sub r1, r0, r1
mov r1, r1
mov r2, #0x0003
movt r2, #0x0000
mov r3, #0x0000
movt r3, #0x0000
add r2, r2, r3
str r2, [r1]
mov r0, r0
mov r1, #0x0001
movt r1, #0x0000
mov r2, #0x0000
movt r2, #0x0000
add r1, r1, r2
str r1, [r0]
mov r1, #0x0004
movt r1, #0x0000
add r1, r0, r1
mov r1, r1
mov r2, #0x0002
movt r2, #0x0000
mov r3, #0x0000
movt r3, #0x0000
add r2, r2, r3
str r2, [r1]
mov r1, #0x0008
movt r1, #0x0000
add r1, r0, r1
mov r1, r1
mov r2, #0x0003
movt r2, #0x0000
mov r3, #0x0000
movt r3, #0x0000
add r2, r2, r3
str r2, [r1]
mov r1, #0x000c
movt r1, #0x0000
ldr r8, [fp, #-48]
add r1, r8, r1
mov r1, r1
str r0, [r1]
mov r0, #0x0008
movt r0, #0x0000
ldr r8, [fp, #-48]
add r0, r8, r0
mov r0, r0
ldr r1, =derived$b
str r1, [r0]
ldr r9, [fp, #-48]
mov r8, r9
str r8, [fp, #-52]
ldr r8, [fp, #-44]
mov r0, r8
ldr r0, [r0]
ldr r8, [fp, #-52]
mov r1, r8
ldr r1, [r1]
cmp r0, r1
beq L15
L16:
mov r0, #0x0000
movt r0, #0x0000
mov r0, r0
bl putint
b L17
L17:
mov r0, #0x000a
movt r0, #0x0000
mov r0, r0
bl putch
mov r8, r7
str r8, [fp, #-56]
b L18
L18:
mov r0, #0x000c
movt r0, #0x0000
ldr r8, [fp, #-52]
add r0, r8, r0
mov r0, r0
ldr r0, [r0]
mov r1, #0x0004
movt r1, #0x0000
sub r0, r0, r1
mov r0, r0
ldr r0, [r0]
ldr r8, [fp, #-56]
cmp r8, r0
blt L20
L19:
mov r0, #0x000a
movt r0, #0x0000
mov r0, r0
bl putch
mov r0, #0x0008
movt r0, #0x0000
ldr r8, [fp, #-44]
add r0, r8, r0
mov r0, r0
ldr r0, [r0]
mov r1, r0
ldr r8, [fp, #-44]
mov r0, r8
blx r1
mov r0, r0
mov r0, r0
bl putint
mov r0, #0x000a
movt r0, #0x0000
mov r0, r0
bl putch
mov r0, #0x0008
movt r0, #0x0000
ldr r8, [fp, #-52]
add r0, r8, r0
mov r0, r0
ldr r0, [r0]
mov r1, r0
ldr r8, [fp, #-52]
mov r0, r8
blx r1
mov r0, r0
mov r0, r0
bl putint
mov r0, #0x000a
movt r0, #0x0000
mov r0, r0
bl putch
mov r0, r6
bl putint
mov r0, #0x000a
movt r0, #0x0000
mov r0, r0
bl putch
mov r0, r5
bl putint
mov r0, #0x000a
movt r0, #0x0000
mov r0, r0
bl putch
mov r0, r4
bl putint
mov r0, #0x000a
movt r0, #0x0000
mov r0, r0
bl putch
ldr r8, [fp, #-28]
mov r0, r8
bl putint
mov r0, #0x000a
movt r0, #0x0000
mov r0, r0
bl putch
ldr r8, [fp, #-32]
mov r0, r8
bl putint
mov r0, #0x000a
movt r0, #0x0000
mov r0, r0
bl putch
ldr r8, [fp, #-36]
mov r0, r8
bl putint
mov r0, #0x000a
movt r0, #0x0000
mov r0, r0
bl putch
ldr r8, [fp, #-40]
mov r0, r8
bl putint
mov r0, #0x000a
movt r0, #0x0000
mov r0, r0
bl putch
mov r0, #0x0000
movt r0, #0x0000
mov r0, r0
sub sp, fp, #24
pop {r4}
pop {r5}
pop {r6}
pop {r7}
pop {r8}
pop {r9}
pop {fp, lr}
bx lr
L15:
mov r0, #0x0001
movt r0, #0x0000
mov r0, r0
bl putint
b L17
L20:
mov r0, #0x000c
movt r0, #0x0000
ldr r8, [fp, #-52]
add r0, r8, r0
mov r0, r0
ldr r0, [r0]
mov r1, #0x0004
movt r1, #0x0000
ldr r8, [fp, #-56]
mul r1, r8, r1
add r0, r0, r1
mov r0, r0
ldr r0, [r0]
mov r0, r0
bl putint
mov r0, #0x0020
movt r0, #0x0000
mov r0, r0
bl putint
mov r0, #0x0001
movt r0, #0x0000
ldr r8, [fp, #-56]
add r0, r8, r0
mov r8, r0
str r8, [fp, #-56]
b L18


.text
.align 1
.global derived$b
derived$b:
push {fp, lr}
mov fp, sp
mov r1, r0
C25:
mov r0, #0x000c
movt r0, #0x0000
add r0, r1, r0
mov r0, r0
ldr r1, [r0]
mov r0, #0x0004
movt r0, #0x0000
add r0, r1, r0
mov r0, r0
ldr r0, [r0]
mov r0, r0
sub sp, fp, #0
pop {fp, lr}
bx lr


.text
.align 1
.global base$b
base$b:
push {fp, lr}
mov fp, sp
mov r0, r0
C28:
mov r0, #0x0001
movt r0, #0x0000
mov r0, r0
sub sp, fp, #0
pop {fp, lr}
bx lr


.global malloc
.global getint
.global getch
.global getfloat
.global getarray
.global getfarray
.global putint
.global putch
.global putfloat
.global putarray
.global putfarray
.global starttime
.global stoptime
