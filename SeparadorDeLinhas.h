/*------------------------------------------------------------------------------------
	Trabalho 1 - Software Básico 01/2016 - Turma B

Nome: 	Letícia Helena Silva Porto 						11/0127846
		Rodrigo Werberich da Silva Moreira de Oliveira 	11/0139411

Nome do arquivo: SeparadorDeLinhas.h

Descricao: Esqueleto da classe SeparadorDeLinhas, que recebe uma linha em formato string 
e quebra ela em vetor de tokens separados pelo espaco em branco
----------------------------------------------------------------------------------------*/

#ifndef SB_SEPARADOR
#define SB_SEPARADOR

#include <string>
#include <vector>

#include "Token.h"

namespace Montador {

	/*
	Classe SeparadorDeLinhas
	Recebe uma linha em formato string e quebra ela em vetor de tokens separados pelo espaco em branco.
	*/
	class SeparadorDeLinhas
	{
	public:
		// Método da classe
		std::vector<Token> separar_linha(std::string);
		
	};

} // namespace Montador
#endif /* SB_SEPARADOR */