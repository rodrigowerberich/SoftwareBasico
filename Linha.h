#ifndef SB_LINHA
#define SB_LINHA

#include "Token.h"
#include <vector>

namespace Montador{

class Linha
{
public:
	Linha(std::vector<Token>,int);
	//~Linha();
	std::vector<Token> get_tokens(){return tokens;};
	int get_numero() const{return numero;};
	
private:
	std::vector<Token> tokens;
	int numero;
};

} // namespace Montador
#endif /* SB_LINHA */