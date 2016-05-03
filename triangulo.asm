; comentário
FLAG: equ 1


SECTION TEXT
		INPUT		B ; comentario
		INPUT		H ;banana
		LOAD		B ;ola
		MULT		H
		IF FLAG
		DIV		DOIS
		STORE		R
		OUTPUT	R
		STOP

SECTION DATA
	b:		space
	H:		SPACE 6
	r:		SPACE
	DOIS:	CONST		2
