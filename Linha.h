/*------------------------------------------------------------------------------------
	Trabalho 1 - Software Básico 01/2016 - Turma B

Nome: 	Letícia Helena Silva Porto 						11/0127846
		Rodrigo Werberich da Silva Moreira de Oliveira 	11/0139411

Nome do arquivo: Linha.h

Descricao: Esqueleto da classe Linha, que armazena o conteudo de uma linha original do 
texto escrito, separando-a em tokens e mantendo uma referência ao número da linha.
----------------------------------------------------------------------------------------*/

#ifndef SB_LINHA
#define SB_LINHA

#include "Token.h"
#include <vector>

namespace Montador{

class Linha
{
public:
	Linha(std::vector<Token>,int);
	//~Linha();
	std::vector<Token> get_tokens(){return tokens;};
	int get_numero() const{return numero;};
	void substituir_token(string,int);
	void remover_rotulo();
	
private:
	std::vector<Token> tokens;
	int numero;
};

} // namespace Montador
#endif /* SB_LINHA */