section .data
ad:	dq 0x580
message: dw "test", 0x0a

section .text
	global _main
	extern _printf

_main:
	lea r9, [message]
	ret
