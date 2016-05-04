; comentário
FLAG: equ 1
SOMA: EQU ADD

SECTION TEXT
		INPUT		B ; comentario
SOMA:	INPUT		H ;banana
		LOAD		B ;ola
		MULT		H
		IF FLAG
		DIV		DOIS
		STORE		R
		OUTPUT	R
		SOMA R
		STOP

SECTION DATA
	b:		space
	H:		SPACE 
	r:		SPACE
	DOIS:	CONST		2