#include "SeparadorDeLinhas.h"
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <vector>
#include "Token.h"
namespace Montador{

	std::vector<Token> SeparadorDeLinhas::separar_linha(string linha){
		using namespace std;
	    istringstream iss(linha);
		vector<string> s_tokens;
		std::vector<Token> tokens;
		copy(istream_iterator<string>(iss),
		     istream_iterator<string>(),
		     back_inserter(s_tokens));
		for(int i=0;i<s_tokens.size();i++){
			//cout << s_tokens[i] << endl;
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