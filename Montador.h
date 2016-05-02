#ifndef SB_MONTADOR
#define SB_MONTADOR

#include "Linha.h"
#include "SeparadorDeLinhas.h"
#include <string>
#include <vector>

namespace Montador{

class Montador
{
public:
	Montador(std::string);
	void pre_processamento();

private:
	std::string arquivo;
	std::vector<Linha> linhas;
};

} // namespace Montador
#endif /* SB_MONTADOR */