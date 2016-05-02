OBJS = Buffer.o Linha.o Montador.o Tabelas.o Tabelas_montador.o Token.o SeparadorDeLinhas.o lerarquivo.o
CC = g++
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)

p1 : $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o p1

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


lerarquivo.o : lerarquivo.cpp Montador.h
	$(CC) $(CFLAGS) lerarquivo.cpp

clean:
	\rm *.o *~ p1
