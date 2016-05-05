#include <iostream>
#include <stdexcept>
#include <string>
#include <algorithm>

#include "Token.h"

using namespace std;


Token::Token (string s_token) throw (invalid_argument) { 

	numerico = false;
	vetor = false;

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
		if (!isupper(s_token.at(i)) && !islower(s_token.at(i)) && !(s_token.at(i) == '_') && !(s_token.at(i) == '+') && !isdigit(s_token.at(i)))
			throw invalid_argument (string("Erro Léxico: Caracter '")+s_token.at(i)+string("' inválido!"));
		if(!isdigit(s_token.at(i)) && numerico)
			throw invalid_argument (string("Erro Léxico: Caracter '")+s_token.at(0)+string("' inválido!"));
		if((s_token.at(i) == '+')){
			vetor=true;
			vetor_posicao.push_back(i);
		}
	}
	int end = s_token.size()-1;
	if(end!=0){
		if (!isupper(s_token.at(end)) && !islower(s_token.at(end)) && !(s_token.at(end) == '_') && !(s_token.at(end) == ':') && !isdigit(s_token.at(end)) && !(s_token.at(end) == ','))
			throw invalid_argument (string("Erro Léxico: Caracter '")+s_token.at(end)+string("' inválido!"));
		if(!isdigit(s_token.at(end)) && numerico)
			throw invalid_argument (string("Erro Léxico: Caracter '")+s_token.at(0)+string("' inválido!"));
	}

	my_token = s_token;
	transform (my_token.begin(), my_token.end(), my_token.begin(), ::toupper);

}

string Token::get_str(){
	return my_token;
}

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

const bool Token::is_numerico(){
	return numerico;
}

const bool Token::verifica_vetor(){
	if(vetor)
		if(vetor_posicao.size()==1)
			return true;
		else
			throw invalid_argument("Erro léxico: Mais de um + na expressao");
	else 
		return false;
}

int Token::posicao_mais(){
	if(verifica_vetor())
		return vetor_posicao[0];
	else 
		return -1;
}