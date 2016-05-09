OBJS = Buffer.o Linha.o Montador.o Tabelas.o Tabelas_montador.o Token.o SeparadorDeLinhas.o montador.o
OBJSL = Ligador.o ligador.o Buffer.o SeparadorDeLinhas.o Token.o Linha.o Tabelas.o
CC = g++
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)

montador : $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o montador

ligador : $(OBJSL)
	$(CC) $(LFLAGS) $(OBJSL) -o ligador

Buffer.o : Buffer.h Buffer.cpp
	$(CC) $(CFLAGS) Buffer.cpp

Linha.o : Linha.h Linha.cpp Buffer.h Token.h SeparadorDeLinhas.h 
	$(CC) $(CFLAGS) Linha.cpp

Montador.o : Montador.h Montador.cpp Buffer.h SeparadorDeLinhas.h Token.h Montador.h Linha.h Tabelas_montador.h Tabelas.h
	$(CC) $(CFLAGS) Montador.cpp

Tabelas.o : Tabelas_montador.h Tabelas.cpp Tabelas.h
	$(CC) $(CFLAGS) Tabelas.cpp

Tabelas_montador.o : Tabelas_montador.h Tabelas_montador.cpp
	$(CC) $(CFLAGS) Tabelas_montador.cpp

Token.o : Token.h Token.cpp
	$(CC) $(CFLAGS) Token.cpp

SeparadorDeLinhas.o: SeparadorDeLinhas.h SeparadorDeLinhas.cpp Token.h
	$(CC) $(CFLAGS) SeparadorDeLinhas.cpp

montador.o : montador.c Montador.h
	$(CC) $(CFLAGS) montador.c

Ligador.o: Ligador.h Ligador.cpp Buffer.h SeparadorDeLinhas.h Token.h Linha.h Tabelas.h
	$(CC) $(CFLAGS) Ligador.cpp

ligador.o: ligador.c Ligador.h
	$(CC) $(CFLAGS) ligador.c

clean:
	\rm *.o montador
