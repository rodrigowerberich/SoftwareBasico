/*------------------------------------------------------------------------------------
	Trabalho 1 - Software Básico 01/2016 - Turma B

Nome: 	Letícia Helena Silva Porto 						11/0127846
		Rodrigo Werberich da Silva Moreira de Oliveira 	11/0139411

Nome do arquivo: Linha.cpp

Descricao: Este arquivo contém a definicao dos métodos da classe Linha, que armazena o 
conteudo de uma linha original do texto escrito, separando-a em tokens e mantendo uma 
referência ao número da linha.
----------------------------------------------------------------------------------------*/

#include <iostream>
#include <vector>
#include <string>

#include "Buffer.h"
#include "SeparadorDeLinhas.h"
#include "Token.h"
#include "Linha.h"

namespace Montador{

	/*
	Construtor da classe Linha
	Cria um objeto linha a partir de um vetor de tokens e o número da linha
	*/
	Linha::Linha(std::vector<Token> tokens_dado,int numero_dado){
		tokens = tokens_dado;
		numero = numero_dado;
	}

	/*
	Método da classe Linha
	Substitui um token em uma dada posicao por um novo token a partir de uma string
	Parâmetros: novo_valor, uma string que será o novo token
				posicao, a posicao do token a ser substituido
	*/
	void Linha::substituir_token(string novo_valor,int posicao){
		tokens[posicao] = Token(novo_valor);
	}

	/*
	Método da classe Linha
	Remove o primeiro elemento da linha, se o segundo elemento for ':', remove ele 
	também
	*/
	void Linha::remover_rotulo(){
		if (tokens.size()>1)
			if(tokens[1].get_str()==":")
				tokens.erase(tokens.begin());
		tokens.erase(tokens.begin());
		
	}
}