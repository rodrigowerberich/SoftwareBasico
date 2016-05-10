/*------------------------------------------------------------------------------------
	Trabalho 1 - Software Básico 01/2016 - Turma B

Nome: 	Letícia Helena Silva Porto 						11/0127846
		Rodrigo Werberich da Silva Moreira de Oliveira 	11/0139411

Nome do arquivo: Token.cpp

Descricao: Este arquivo contém a definicao dos métodos da classe Token, que faz a verifi-
cacao lexica de uma string.
----------------------------------------------------------------------------------------*/

#include <iostream>
#include <stdexcept>
#include <string>
#include <algorithm>

#include "Token.h"

using namespace std;

namespace Montador{
	/*
	Construtor da classe Token
	Cria um objeto Token a partir de uma string, faz verificacao léxica e acusa erros, verifica se o
	token é numerico(contem apenas numeros ou '-' seguido de numeros) e transforma a string para 
	maiusculo.
	*/
	Token::Token (string s_token) throw (invalid_argument) { 

		numerico = false;

		if (s_token.size() > 100)
			throw invalid_argument ("Erro Léxico: Linha com mais de 100 Caracteres!");

		if (s_token.at(0) == ';')
			throw invalid_argument ("Comentario");

		if (s_token.at(0) == '+' && s_token.size()>1)
			throw invalid_argument ("Erro Léxico: Caracter + invalido");		

		if (s_token.at(0) == '-' && s_token.size()<2)
			throw invalid_argument ("Erro Léxico: Caracter - invalido sozinho");

		if (s_token.at(0) == ',' && s_token.size()>1)
			throw invalid_argument ("Erro Léxico: Caracter , invalido");

		if (!isupper(s_token.at(0)) && !islower(s_token.at(0)) &&!(s_token.at(0) == ',')&& !(s_token.at(0) == '_') && !(s_token.at(0) == '+') && !(s_token.at(0) == '-') && !(s_token.at(0) == ':') && !isdigit(s_token.at(0)))
				throw invalid_argument (string("Erro Léxico: Caracter '")+s_token.at(0)+string("' inválido!"));

		if(isdigit(s_token.at(0)) || (s_token.at(0) == '-'))
			numerico = true;

		for (unsigned int i = 1; i < s_token.size()-1; i++){
			if (!isupper(s_token.at(i)) && !islower(s_token.at(i)) && !(s_token.at(i) == '_') && !isdigit(s_token.at(i)))
				throw invalid_argument (string("Erro Léxico: Caracter '")+s_token.at(i)+string("' inválido!"));
			if(!isdigit(s_token.at(i)) && numerico)
				throw invalid_argument (string("Erro Léxico: Caracter '")+s_token.at(0)+string("' inválido!"));
		}
		int end = s_token.size()-1;
		if(end!=0){
			if (!isupper(s_token.at(end)) && !islower(s_token.at(end)) && !(s_token.at(end) == '_') && !(s_token.at(end) == ':') && !isdigit(s_token.at(end)) && !(s_token.at(end) == ','))
				throw invalid_argument (string("Erro Léxico: Caracter '")+s_token.at(end)+string("' inválido!"));
			if(!isdigit(s_token.at(end)) && numerico && !(s_token.at(end) == ','))
				throw invalid_argument (string("Erro Léxico: Caracter '")+s_token.at(0)+string("' inválido!"));
		}

		my_token = s_token;
		transform (my_token.begin(), my_token.end(), my_token.begin(), ::toupper);

	}

	/*
	Método da classe Token
	Retorna a string que representa o token
	*/
	string Token::get_str(){
		return my_token;
	}

	/*
	Método da classe Token
	Verifica se o token é um label, vendo se o último caracter é ':'
	Retorna um booleano dizendo se é um rotulo ou nao
	*/
	bool Token::verifica_rotulo(){
		if (my_token.at(my_token.size()-1) == ':'){
			if (my_token.size() < 2)
			{
				throw invalid_argument("Erro Sintático: ':' deve ter um label antes");
			}
			return true;
		}
		return false;
	}


	/*
	Método da classe Token
	Retorna um booleano dizendo se é ou nao um número
	*/
	const bool Token::is_numerico(){
		return numerico;
	}
}