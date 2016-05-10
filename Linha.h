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

	/*
	Classe Linha
	Armazena o conteudo de uma linha original do texto escrito, separando-a em tokens e 
	mantendo uma referência ao número da linha.
	*/
	class Linha
	{
	public:
		// Contrutor
		Linha(std::vector<Token>,int);

		// Métodos da classe
		void substituir_token(string,int);
		void remover_rotulo();

		// Getters da classe
		std::vector<Token> get_tokens(){return tokens;};
		int get_numero() const{return numero;};

		
	private:
		// Os tokens que a linha contém
		std::vector<Token> tokens;
		// O número da linha
		int numero;
	};

} // namespace Montador
#endif /* SB_LINHA */