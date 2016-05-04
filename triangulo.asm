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
		OUTPUT	R+1
		SOMA R
		STOP

SECTION DATA
	 ,sss :		space
	H :		SPACE 
	r:		SPACE
	DOIS:	CONST		2