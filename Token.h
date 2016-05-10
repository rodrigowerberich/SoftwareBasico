/*------------------------------------------------------------------------------------
	Trabalho 1 - Software Básico 01/2016 - Turma B

Nome: 	Letícia Helena Silva Porto 						11/0127846
		Rodrigo Werberich da Silva Moreira de Oliveira 	11/0139411

Nome do arquivo: Token.h

Descricao: Esqueleto da classe Token, que faz a verificacao lexica de uma string.
----------------------------------------------------------------------------------------*/

#ifndef SB_TOKEN
#define SB_TOKEN

#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

namespace Montador{
/*
Classe Token
Faz a verificacao lexica de uma string.
*/
	class Token
	{

	public:
		// Construtor da classe
		Token(string) throw (invalid_argument);

		// Getters da classe
		string get_str();
		const bool is_numerico();

		// Métodos da classe
		bool verifica_rotulo();


	protected:
		// A string que representa o token
		string my_token;
		// Um booleano que diz se o token é numerico ou nao
		bool numerico;
	};

} // namespace Montador

#endif /* SB_SEPARADOR */