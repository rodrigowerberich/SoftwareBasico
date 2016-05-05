#include <iostream>
#include <vector>
#include <string>

#include "Buffer.h"
#include "SeparadorDeLinhas.h"
#include "Token.h"
#include "Linha.h"

namespace Montador{

	Linha::Linha(std::vector<Token> tokens_dado,int numero_dado){
		tokens = tokens_dado;
		numero = numero_dado;
	}

	void Linha::substituir_token(string novo_valor,int posicao){
		tokens[posicao] = Token(novo_valor);
	}

	void Linha::remover_rotulo(){
		if (tokens.size()>1)
			if(tokens[1].get_str()==":")
				tokens.erase(tokens.begin());
		tokens.erase(tokens.begin());
		
	}
}