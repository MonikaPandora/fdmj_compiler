	.cpu cortex-a72
	.eabi_attribute 28, 1
	.eabi_attribute 20, 1
	.eabi_attribute 21, 1
	.eabi_attribute 23, 3
	.eabi_attribute 24, 1
	.eabi_attribute 25, 1
	.eabi_attribute 26, 2
	.eabi_attribute 30, 6
	.eabi_attribute 34, 1
	.eabi_attribute 18, 4
	.file	"libsysy32.c"
	.text
	.comm	_sysy_start,8,4
	.comm	_sysy_end,8,4
	.comm	_sysy_l1,4096,4
	.comm	_sysy_l2,4096,4
	.comm	_sysy_h,4096,4
	.comm	_sysy_m,4096,4
	.comm	_sysy_s,4096,4
	.comm	_sysy_us,4096,4
	.comm	_sysy_idx,4,4
	.section	.rodata
	.align	2
.LC0:
	.ascii	"%d\000"
	.text
	.align	2
	.global	getint
	.arch armv8-a
	.arch_extension crc
	.syntax unified
	.arm
	.fpu neon
	.type	getint, %function
getint:
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	str	fp, [sp, #-8]!
	str	lr, [sp, #4]
	add	fp, sp, #4
	sub	sp, sp, #8
	sub	r3, fp, #8
	mov	r1, r3
	movw	r0, #:lower16:.LC0
	movt	r0, #:upper16:.LC0
	bl	__isoc99_scanf
	ldr	r3, [fp, #-8]
	mov	r0, r3
	sub	sp, fp, #4
	@ sp needed
	ldr	fp, [sp]
	add	sp, sp, #4
	ldr	pc, [sp], #4
	.size	getint, .-getint
	.section	.rodata
	.align	2
.LC1:
	.ascii	"%c\000"
	.text
	.align	2
	.global	getch
	.syntax unified
	.arm
	.fpu neon
	.type	getch, %function
getch:
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	str	fp, [sp, #-8]!
	str	lr, [sp, #4]
	add	fp, sp, #4
	sub	sp, sp, #8
	sub	r3, fp, #5
	mov	r1, r3
	movw	r0, #:lower16:.LC1
	movt	r0, #:upper16:.LC1
	bl	__isoc99_scanf
	ldrb	r3, [fp, #-5]	@ zero_extendqisi2
	mov	r0, r3
	sub	sp, fp, #4
	@ sp needed
	ldr	fp, [sp]
	add	sp, sp, #4
	ldr	pc, [sp], #4
	.size	getch, .-getch
	.align	2
	.global	getarray
	.syntax unified
	.arm
	.fpu neon
	.type	getarray, %function
getarray:
	@ args = 0, pretend = 0, frame = 16
	@ frame_needed = 1, uses_anonymous_args = 0
	str	fp, [sp, #-8]!
	str	lr, [sp, #4]
	add	fp, sp, #4
	sub	sp, sp, #16
	str	r0, [fp, #-16]
	sub	r3, fp, #12
	mov	r1, r3
	movw	r0, #:lower16:.LC0
	movt	r0, #:upper16:.LC0
	bl	__isoc99_scanf
	mov	r3, #0
	str	r3, [fp, #-8]
	b	.L6
.L7:
	ldr	r3, [fp, #-8]
	lsl	r3, r3, #2
	ldr	r2, [fp, #-16]
	add	r3, r2, r3
	mov	r1, r3
	movw	r0, #:lower16:.LC0
	movt	r0, #:upper16:.LC0
	bl	__isoc99_scanf
	ldr	r3, [fp, #-8]
	add	r3, r3, #1
	str	r3, [fp, #-8]
.L6:
	ldr	r3, [fp, #-12]
	ldr	r2, [fp, #-8]
	cmp	r2, r3
	blt	.L7
	ldr	r3, [fp, #-12]
	mov	r0, r3
	sub	sp, fp, #4
	@ sp needed
	ldr	fp, [sp]
	add	sp, sp, #4
	ldr	pc, [sp], #4
	.size	getarray, .-getarray
	.align	2
	.global	putint
	.syntax unified
	.arm
	.fpu neon
	.type	putint, %function
putint:
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	str	fp, [sp, #-8]!
	str	lr, [sp, #4]
	add	fp, sp, #4
	sub	sp, sp, #8
	str	r0, [fp, #-8]
	ldr	r1, [fp, #-8]
	movw	r0, #:lower16:.LC0
	movt	r0, #:upper16:.LC0
	bl	printf
	nop
	sub	sp, fp, #4
	@ sp needed
	ldr	fp, [sp]
	add	sp, sp, #4
	ldr	pc, [sp], #4
	.size	putint, .-putint
	.align	2
	.global	putch
	.syntax unified
	.arm
	.fpu neon
	.type	putch, %function
putch:
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	str	fp, [sp, #-8]!
	str	lr, [sp, #4]
	add	fp, sp, #4
	sub	sp, sp, #8
	str	r0, [fp, #-8]
	ldr	r0, [fp, #-8]
	bl	putchar
	nop
	sub	sp, fp, #4
	@ sp needed
	ldr	fp, [sp]
	add	sp, sp, #4
	ldr	pc, [sp], #4
	.size	putch, .-putch
	.section	.rodata
	.align	2
.LC2:
	.ascii	"%d:\000"
	.align	2
.LC3:
	.ascii	" %d\000"
	.text
	.align	2
	.global	putarray
	.syntax unified
	.arm
	.fpu neon
	.type	putarray, %function
putarray:
	@ args = 0, pretend = 0, frame = 16
	@ frame_needed = 1, uses_anonymous_args = 0
	str	fp, [sp, #-8]!
	str	lr, [sp, #4]
	add	fp, sp, #4
	sub	sp, sp, #16
	str	r0, [fp, #-16]
	str	r1, [fp, #-20]
	ldr	r1, [fp, #-16]
	movw	r0, #:lower16:.LC2
	movt	r0, #:upper16:.LC2
	bl	printf
	mov	r3, #0
	str	r3, [fp, #-8]
	b	.L12
.L13:
	ldr	r3, [fp, #-8]
	lsl	r3, r3, #2
	ldr	r2, [fp, #-20]
	add	r3, r2, r3
	ldr	r3, [r3]
	mov	r1, r3
	movw	r0, #:lower16:.LC3
	movt	r0, #:upper16:.LC3
	bl	printf
	ldr	r3, [fp, #-8]
	add	r3, r3, #1
	str	r3, [fp, #-8]
.L12:
	ldr	r2, [fp, #-8]
	ldr	r3, [fp, #-16]
	cmp	r2, r3
	blt	.L13
	mov	r0, #10
	bl	putchar
	nop
	sub	sp, fp, #4
	@ sp needed
	ldr	fp, [sp]
	add	sp, sp, #4
	ldr	pc, [sp], #4
	.size	putarray, .-putarray
	.align	2
	.global	before_main
	.syntax unified
	.arm
	.fpu neon
	.type	before_main, %function
before_main:
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	@ link register save eliminated.
	str	fp, [sp, #-4]!
	add	fp, sp, #0
	sub	sp, sp, #12
	mov	r3, #0
	str	r3, [fp, #-8]
	b	.L15
.L16:
	movw	r3, #:lower16:_sysy_us
	movt	r3, #:upper16:_sysy_us
	ldr	r2, [fp, #-8]
	mov	r1, #0
	str	r1, [r3, r2, lsl #2]
	movw	r3, #:lower16:_sysy_us
	movt	r3, #:upper16:_sysy_us
	ldr	r2, [fp, #-8]
	ldr	r1, [r3, r2, lsl #2]
	movw	r3, #:lower16:_sysy_s
	movt	r3, #:upper16:_sysy_s
	ldr	r2, [fp, #-8]
	str	r1, [r3, r2, lsl #2]
	movw	r3, #:lower16:_sysy_s
	movt	r3, #:upper16:_sysy_s
	ldr	r2, [fp, #-8]
	ldr	r1, [r3, r2, lsl #2]
	movw	r3, #:lower16:_sysy_m
	movt	r3, #:upper16:_sysy_m
	ldr	r2, [fp, #-8]
	str	r1, [r3, r2, lsl #2]
	movw	r3, #:lower16:_sysy_m
	movt	r3, #:upper16:_sysy_m
	ldr	r2, [fp, #-8]
	ldr	r1, [r3, r2, lsl #2]
	movw	r3, #:lower16:_sysy_h
	movt	r3, #:upper16:_sysy_h
	ldr	r2, [fp, #-8]
	str	r1, [r3, r2, lsl #2]
	ldr	r3, [fp, #-8]
	add	r3, r3, #1
	str	r3, [fp, #-8]
.L15:
	ldr	r3, [fp, #-8]
	cmp	r3, #1024
	blt	.L16
	movw	r3, #:lower16:_sysy_idx
	movt	r3, #:upper16:_sysy_idx
	mov	r2, #1
	str	r2, [r3]
	nop
	add	sp, fp, #0
	@ sp needed
	ldr	fp, [sp], #4
	bx	lr
	.size	before_main, .-before_main
	.section	.init_array,"aw",%init_array
	.align	2
	.word	before_main(target1)
	.section	.rodata
	.align	2
.LC4:
	.ascii	"Timer@%04d-%04d: %dH-%dM-%dS-%dus\012\000"
	.text
	.align	2
	.global	after_main
	.syntax unified
	.arm
	.fpu neon
	.type	after_main, %function
after_main:
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	strd	r4, [sp, #-16]!
	str	fp, [sp, #8]
	str	lr, [sp, #12]
	add	fp, sp, #12
	sub	sp, sp, #24
	mov	r3, #1
	str	r3, [fp, #-16]
	b	.L18
.L19:
	movw	r3, #:lower16:stderr
	movt	r3, #:upper16:stderr
	ldr	lr, [r3]
	movw	r3, #:lower16:_sysy_l1
	movt	r3, #:upper16:_sysy_l1
	ldr	r2, [fp, #-16]
	ldr	r4, [r3, r2, lsl #2]
	movw	r3, #:lower16:_sysy_l2
	movt	r3, #:upper16:_sysy_l2
	ldr	r2, [fp, #-16]
	ldr	r5, [r3, r2, lsl #2]
	movw	r3, #:lower16:_sysy_h
	movt	r3, #:upper16:_sysy_h
	ldr	r2, [fp, #-16]
	ldr	r2, [r3, r2, lsl #2]
	movw	r3, #:lower16:_sysy_m
	movt	r3, #:upper16:_sysy_m
	ldr	r1, [fp, #-16]
	ldr	r1, [r3, r1, lsl #2]
	movw	r3, #:lower16:_sysy_s
	movt	r3, #:upper16:_sysy_s
	ldr	r0, [fp, #-16]
	ldr	r0, [r3, r0, lsl #2]
	movw	r3, #:lower16:_sysy_us
	movt	r3, #:upper16:_sysy_us
	ldr	ip, [fp, #-16]
	ldr	r3, [r3, ip, lsl #2]
	str	r3, [sp, #12]
	str	r0, [sp, #8]
	str	r1, [sp, #4]
	str	r2, [sp]
	mov	r3, r5
	mov	r2, r4
	movw	r1, #:lower16:.LC4
	movt	r1, #:upper16:.LC4
	mov	r0, lr
	bl	fprintf
	movw	r3, #:lower16:_sysy_us
	movt	r3, #:upper16:_sysy_us
	ldr	r2, [r3]
	movw	r3, #:lower16:_sysy_us
	movt	r3, #:upper16:_sysy_us
	ldr	r1, [fp, #-16]
	ldr	r3, [r3, r1, lsl #2]
	add	r2, r2, r3
	movw	r3, #:lower16:_sysy_us
	movt	r3, #:upper16:_sysy_us
	str	r2, [r3]
	movw	r3, #:lower16:_sysy_s
	movt	r3, #:upper16:_sysy_s
	ldr	r2, [r3]
	movw	r3, #:lower16:_sysy_s
	movt	r3, #:upper16:_sysy_s
	ldr	r1, [fp, #-16]
	ldr	r3, [r3, r1, lsl #2]
	add	r2, r2, r3
	movw	r3, #:lower16:_sysy_s
	movt	r3, #:upper16:_sysy_s
	str	r2, [r3]
	movw	r3, #:lower16:_sysy_us
	movt	r3, #:upper16:_sysy_us
	ldr	r2, [r3]
	movw	r3, #56963
	movt	r3, 17179
	smull	r1, r3, r3, r2
	asr	r1, r3, #18
	asr	r3, r2, #31
	sub	r3, r1, r3
	movw	r1, #16960
	movt	r1, 15
	mul	r3, r1, r3
	sub	r3, r2, r3
	movw	r2, #:lower16:_sysy_us
	movt	r2, #:upper16:_sysy_us
	str	r3, [r2]
	movw	r3, #:lower16:_sysy_m
	movt	r3, #:upper16:_sysy_m
	ldr	r2, [r3]
	movw	r3, #:lower16:_sysy_m
	movt	r3, #:upper16:_sysy_m
	ldr	r1, [fp, #-16]
	ldr	r3, [r3, r1, lsl #2]
	add	r2, r2, r3
	movw	r3, #:lower16:_sysy_m
	movt	r3, #:upper16:_sysy_m
	str	r2, [r3]
	movw	r3, #:lower16:_sysy_s
	movt	r3, #:upper16:_sysy_s
	ldr	r2, [r3]
	movw	r3, #34953
	movt	r3, 34952
	smull	r1, r3, r3, r2
	add	r3, r3, r2
	asr	r1, r3, #5
	asr	r3, r2, #31
	sub	r1, r1, r3
	mov	r3, r1
	lsl	r3, r3, #4
	sub	r3, r3, r1
	lsl	r3, r3, #2
	sub	r1, r2, r3
	movw	r3, #:lower16:_sysy_s
	movt	r3, #:upper16:_sysy_s
	str	r1, [r3]
	movw	r3, #:lower16:_sysy_h
	movt	r3, #:upper16:_sysy_h
	ldr	r2, [r3]
	movw	r3, #:lower16:_sysy_h
	movt	r3, #:upper16:_sysy_h
	ldr	r1, [fp, #-16]
	ldr	r3, [r3, r1, lsl #2]
	add	r2, r2, r3
	movw	r3, #:lower16:_sysy_h
	movt	r3, #:upper16:_sysy_h
	str	r2, [r3]
	movw	r3, #:lower16:_sysy_m
	movt	r3, #:upper16:_sysy_m
	ldr	r2, [r3]
	movw	r3, #34953
	movt	r3, 34952
	smull	r1, r3, r3, r2
	add	r3, r3, r2
	asr	r1, r3, #5
	asr	r3, r2, #31
	sub	r1, r1, r3
	mov	r3, r1
	lsl	r3, r3, #4
	sub	r3, r3, r1
	lsl	r3, r3, #2
	sub	r1, r2, r3
	movw	r3, #:lower16:_sysy_m
	movt	r3, #:upper16:_sysy_m
	str	r1, [r3]
	ldr	r3, [fp, #-16]
	add	r3, r3, #1
	str	r3, [fp, #-16]
.L18:
	movw	r3, #:lower16:_sysy_idx
	movt	r3, #:upper16:_sysy_idx
	ldr	r3, [r3]
	ldr	r2, [fp, #-16]
	cmp	r2, r3
	blt	.L19
	nop
	sub	sp, fp, #12
	@ sp needed
	ldrd	r4, [sp]
	ldr	fp, [sp, #8]
	add	sp, sp, #12
	ldr	pc, [sp], #4
	.size	after_main, .-after_main
	.section	.fini_array,"aw",%fini_array
	.align	2
	.word	after_main(target1)
	.text
	.align	2
	.global	_sysy_starttime
	.syntax unified
	.arm
	.fpu neon
	.type	_sysy_starttime, %function
_sysy_starttime:
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	str	fp, [sp, #-8]!
	str	lr, [sp, #4]
	add	fp, sp, #4
	sub	sp, sp, #8
	str	r0, [fp, #-8]
	movw	r3, #:lower16:_sysy_idx
	movt	r3, #:upper16:_sysy_idx
	ldr	r2, [r3]
	movw	r3, #:lower16:_sysy_l1
	movt	r3, #:upper16:_sysy_l1
	ldr	r1, [fp, #-8]
	str	r1, [r3, r2, lsl #2]
	mov	r1, #0
	movw	r0, #:lower16:_sysy_start
	movt	r0, #:upper16:_sysy_start
	bl	gettimeofday
	nop
	sub	sp, fp, #4
	@ sp needed
	ldr	fp, [sp]
	add	sp, sp, #4
	ldr	pc, [sp], #4
	.size	_sysy_starttime, .-_sysy_starttime
	.align	2
	.global	_sysy_stoptime
	.syntax unified
	.arm
	.fpu neon
	.type	_sysy_stoptime, %function
_sysy_stoptime:
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	str	fp, [sp, #-8]!
	str	lr, [sp, #4]
	add	fp, sp, #4
	sub	sp, sp, #8
	str	r0, [fp, #-8]
	mov	r1, #0
	movw	r0, #:lower16:_sysy_end
	movt	r0, #:upper16:_sysy_end
	bl	gettimeofday
	movw	r3, #:lower16:_sysy_idx
	movt	r3, #:upper16:_sysy_idx
	ldr	r2, [r3]
	movw	r3, #:lower16:_sysy_l2
	movt	r3, #:upper16:_sysy_l2
	ldr	r1, [fp, #-8]
	str	r1, [r3, r2, lsl #2]
	movw	r3, #:lower16:_sysy_idx
	movt	r3, #:upper16:_sysy_idx
	ldr	r2, [r3]
	movw	r3, #:lower16:_sysy_us
	movt	r3, #:upper16:_sysy_us
	ldr	r0, [r3, r2, lsl #2]
	movw	r3, #:lower16:_sysy_end
	movt	r3, #:upper16:_sysy_end
	ldr	r2, [r3]
	movw	r3, #:lower16:_sysy_start
	movt	r3, #:upper16:_sysy_start
	ldr	r3, [r3]
	sub	r2, r2, r3
	movw	r3, #16960
	movt	r3, 15
	mul	r2, r3, r2
	movw	r3, #:lower16:_sysy_end
	movt	r3, #:upper16:_sysy_end
	ldr	r3, [r3, #4]
	add	r2, r2, r3
	movw	r3, #:lower16:_sysy_start
	movt	r3, #:upper16:_sysy_start
	ldr	r3, [r3, #4]
	sub	r1, r2, r3
	movw	r3, #:lower16:_sysy_idx
	movt	r3, #:upper16:_sysy_idx
	ldr	r2, [r3]
	add	r1, r0, r1
	movw	r3, #:lower16:_sysy_us
	movt	r3, #:upper16:_sysy_us
	str	r1, [r3, r2, lsl #2]
	movw	r3, #:lower16:_sysy_idx
	movt	r3, #:upper16:_sysy_idx
	ldr	r2, [r3]
	movw	r3, #:lower16:_sysy_s
	movt	r3, #:upper16:_sysy_s
	ldr	r0, [r3, r2, lsl #2]
	movw	r3, #:lower16:_sysy_idx
	movt	r3, #:upper16:_sysy_idx
	ldr	r2, [r3]
	movw	r3, #:lower16:_sysy_us
	movt	r3, #:upper16:_sysy_us
	ldr	r2, [r3, r2, lsl #2]
	movw	r3, #56963
	movt	r3, 17179
	smull	r1, r3, r3, r2
	asr	r1, r3, #18
	asr	r3, r2, #31
	sub	r1, r1, r3
	movw	r3, #:lower16:_sysy_idx
	movt	r3, #:upper16:_sysy_idx
	ldr	r2, [r3]
	add	r1, r0, r1
	movw	r3, #:lower16:_sysy_s
	movt	r3, #:upper16:_sysy_s
	str	r1, [r3, r2, lsl #2]
	movw	r3, #:lower16:_sysy_idx
	movt	r3, #:upper16:_sysy_idx
	ldr	r2, [r3]
	movw	r3, #:lower16:_sysy_us
	movt	r3, #:upper16:_sysy_us
	ldr	r2, [r3, r2, lsl #2]
	movw	r3, #:lower16:_sysy_idx
	movt	r3, #:upper16:_sysy_idx
	ldr	r0, [r3]
	movw	r3, #56963
	movt	r3, 17179
	smull	r1, r3, r3, r2
	asr	r1, r3, #18
	asr	r3, r2, #31
	sub	r3, r1, r3
	movw	r1, #16960
	movt	r1, 15
	mul	r3, r1, r3
	sub	r3, r2, r3
	movw	r2, #:lower16:_sysy_us
	movt	r2, #:upper16:_sysy_us
	str	r3, [r2, r0, lsl #2]
	movw	r3, #:lower16:_sysy_idx
	movt	r3, #:upper16:_sysy_idx
	ldr	r2, [r3]
	movw	r3, #:lower16:_sysy_m
	movt	r3, #:upper16:_sysy_m
	ldr	r0, [r3, r2, lsl #2]
	movw	r3, #:lower16:_sysy_idx
	movt	r3, #:upper16:_sysy_idx
	ldr	r2, [r3]
	movw	r3, #:lower16:_sysy_s
	movt	r3, #:upper16:_sysy_s
	ldr	r3, [r3, r2, lsl #2]
	movw	r2, #34953
	movt	r2, 34952
	smull	r1, r2, r2, r3
	add	r2, r2, r3
	asr	r2, r2, #5
	asr	r3, r3, #31
	sub	r1, r2, r3
	movw	r3, #:lower16:_sysy_idx
	movt	r3, #:upper16:_sysy_idx
	ldr	r2, [r3]
	add	r1, r0, r1
	movw	r3, #:lower16:_sysy_m
	movt	r3, #:upper16:_sysy_m
	str	r1, [r3, r2, lsl #2]
	movw	r3, #:lower16:_sysy_idx
	movt	r3, #:upper16:_sysy_idx
	ldr	r2, [r3]
	movw	r3, #:lower16:_sysy_s
	movt	r3, #:upper16:_sysy_s
	ldr	r2, [r3, r2, lsl #2]
	movw	r3, #:lower16:_sysy_idx
	movt	r3, #:upper16:_sysy_idx
	ldr	r0, [r3]
	movw	r3, #34953
	movt	r3, 34952
	smull	r1, r3, r3, r2
	add	r3, r3, r2
	asr	r1, r3, #5
	asr	r3, r2, #31
	sub	r1, r1, r3
	mov	r3, r1
	lsl	r3, r3, #4
	sub	r3, r3, r1
	lsl	r3, r3, #2
	sub	r1, r2, r3
	movw	r3, #:lower16:_sysy_s
	movt	r3, #:upper16:_sysy_s
	str	r1, [r3, r0, lsl #2]
	movw	r3, #:lower16:_sysy_idx
	movt	r3, #:upper16:_sysy_idx
	ldr	r2, [r3]
	movw	r3, #:lower16:_sysy_h
	movt	r3, #:upper16:_sysy_h
	ldr	r0, [r3, r2, lsl #2]
	movw	r3, #:lower16:_sysy_idx
	movt	r3, #:upper16:_sysy_idx
	ldr	r2, [r3]
	movw	r3, #:lower16:_sysy_m
	movt	r3, #:upper16:_sysy_m
	ldr	r3, [r3, r2, lsl #2]
	movw	r2, #34953
	movt	r2, 34952
	smull	r1, r2, r2, r3
	add	r2, r2, r3
	asr	r2, r2, #5
	asr	r3, r3, #31
	sub	r1, r2, r3
	movw	r3, #:lower16:_sysy_idx
	movt	r3, #:upper16:_sysy_idx
	ldr	r2, [r3]
	add	r1, r0, r1
	movw	r3, #:lower16:_sysy_h
	movt	r3, #:upper16:_sysy_h
	str	r1, [r3, r2, lsl #2]
	movw	r3, #:lower16:_sysy_idx
	movt	r3, #:upper16:_sysy_idx
	ldr	r2, [r3]
	movw	r3, #:lower16:_sysy_m
	movt	r3, #:upper16:_sysy_m
	ldr	r2, [r3, r2, lsl #2]
	movw	r3, #:lower16:_sysy_idx
	movt	r3, #:upper16:_sysy_idx
	ldr	r0, [r3]
	movw	r3, #34953
	movt	r3, 34952
	smull	r1, r3, r3, r2
	add	r3, r3, r2
	asr	r1, r3, #5
	asr	r3, r2, #31
	sub	r1, r1, r3
	mov	r3, r1
	lsl	r3, r3, #4
	sub	r3, r3, r1
	lsl	r3, r3, #2
	sub	r1, r2, r3
	movw	r3, #:lower16:_sysy_m
	movt	r3, #:upper16:_sysy_m
	str	r1, [r3, r0, lsl #2]
	movw	r3, #:lower16:_sysy_idx
	movt	r3, #:upper16:_sysy_idx
	ldr	r3, [r3]
	add	r2, r3, #1
	movw	r3, #:lower16:_sysy_idx
	movt	r3, #:upper16:_sysy_idx
	str	r2, [r3]
	nop
	sub	sp, fp, #4
	@ sp needed
	ldr	fp, [sp]
	add	sp, sp, #4
	ldr	pc, [sp], #4
	.size	_sysy_stoptime, .-_sysy_stoptime
	.align	2
	.global	starttime
	.syntax unified
	.arm
	.fpu neon
	.type	starttime, %function
starttime:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	str	fp, [sp, #-8]!
	str	lr, [sp, #4]
	add	fp, sp, #4
	mov	r0, #74
	bl	_sysy_starttime
	nop
	sub	sp, fp, #4
	@ sp needed
	ldr	fp, [sp]
	add	sp, sp, #4
	ldr	pc, [sp], #4
	.size	starttime, .-starttime
	.align	2
	.global	stoptime
	.syntax unified
	.arm
	.fpu neon
	.type	stoptime, %function
stoptime:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	str	fp, [sp, #-8]!
	str	lr, [sp, #4]
	add	fp, sp, #4
	mov	r0, #75
	bl	_sysy_stoptime
	nop
	sub	sp, fp, #4
	@ sp needed
	ldr	fp, [sp]
	add	sp, sp, #4
	ldr	pc, [sp], #4
	.size	stoptime, .-stoptime
	.ident	"GCC: (GNU Toolchain for the A-profile Architecture 8.2-2018.11 (arm-rel-8.26)) 8.2.1 20180802"
	.section	.note.GNU-stack,"",%progbits
