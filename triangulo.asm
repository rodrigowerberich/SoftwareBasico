; comentário
FLAG: equ 1
SOMA: EQU ADD

SECTION TEXT
		INPUT		B ; comentario
		INPUT		H ;banana
		LOAD		B ;ola
		MULT		H
		IF FLAG
		DIV		DOIS
		STORE		R
		OUTPUT	B + 1
		SOMA R
		STOP

SECTION DATA
	B:		space 2
	H :		SPACE 
	r:		SPACE
	DOIS:	CONST		2
