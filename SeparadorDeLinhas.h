#ifndef SB_SEPARADOR
#define SB_SEPARADOR

#include <string>
#include <vector>
#include "Token.h"

namespace Montador {

class SeparadorDeLinhas
{
public:
	//SeparadorDeLinhas();
	//~SeparadorDeLinhas();
	std::vector<Token> separar_linha(std::string);
	
};

} // namespace Montador
#endif /* SB_SEPARADOR */