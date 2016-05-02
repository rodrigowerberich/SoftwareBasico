#include "Buffer.h"
#include "SeparadorDeLinhas.h"
#include <iostream>
#include <vector>
#include <string>

#include "Token.h"
#include "Linha.h"

namespace Montador{

	Linha::Linha(std::vector<Token> tokens_dado,int numero_dado){
		tokens = tokens_dado;
		numero = numero_dado;
	}
}