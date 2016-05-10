/*------------------------------------------------------------------------------------
	Trabalho 1 - Software Básico 01/2016 - Turma B

Nome: 	Letícia Helena Silva Porto 						11/0127846
		Rodrigo Werberich da Silva Moreira de Oliveira 	11/0139411

Nome do arquivo: SeparadorDeLinhas.cpp

Descricao: Este arquivo contém a definicao dos métodos da classe SeparadorDeLinhas, que
recebe uma linha em formato string e quebra ela em vetor de tokens separados pelo espaco
em branco
----------------------------------------------------------------------------------------*/

#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <vector>

#include "Token.h"
#include "SeparadorDeLinhas.h"

namespace Montador{

	/*
	Método da classe SeparadorDeLinhas
	Separa uma linha em um vetor de tokens, se houver algum comentario, os tokens após ele 
	sao desconsiderados.
	*/
	std::vector<Token> SeparadorDeLinhas::separar_linha(string linha){
		using namespace std;
	    istringstream iss(linha);
		vector<string> s_tokens;
		std::vector<Token> tokens;
		copy(istream_iterator<string>(iss),
		     istream_iterator<string>(),
		     back_inserter(s_tokens));
		for(int i=0;i<s_tokens.size();i++){
			try{
				tokens.push_back(Token(s_tokens[i]));
			}catch(const std::invalid_argument& ia){
				if (ia.what() == string("Comentario")){
					break;
				}else
					throw;
			}
		}
		return tokens;
	}

}