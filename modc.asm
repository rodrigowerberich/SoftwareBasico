MOD_B : BEGIN
SECTION TEXT
A: EXTERN
L1: EXTERN
PUBLIC R
PUBLIC MOD_B
LOAD A
MULT B
STORE R
DIV DOIS
STORE R+1
COPY A, B
JMP L1

SECTION DATA
R: SPACE 2
DOIS: CONST 2
END
