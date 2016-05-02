#include <iostream>
#include <stdexcept>
#include <string>

#include "Token.h"

using namespace std;


Token::Token (string s_token) throw (invalid_argument) { 

	if (s_token.size() > 100)
		throw invalid_argument ("Erro Léxico.");

	if (s_token.at(0) == ';')
		throw invalid_argument ("Comentario");

	for (unsigned int i = 1; i < s_token.size()-1; i++){
		if (!isupper(s_token.at(i)) && !islower(s_token.at(i)) && !(s_token.at(i) == '_') && !(s_token.at(i) == '+') && !isdigit(s_token.at(i)))
			throw invalid_argument ("Erro Léxico");
	}
	int end = s_token.size()-1;
	if (!isupper(s_token.at(end)) && !islower(s_token.at(end)) && !(s_token.at(end) == '_') && !(s_token.at(end) == ':') && !isdigit(s_token.at(end)))
		throw invalid_argument ("Erro Léxico");

	my_token = s_token;

}

string Token::get_str(){
	return my_token;
}

bool Token::verifica_rotulo(){
	if (my_token.at(my_token.size()-1) == ':'){
		return true;
	}
	return false;
}