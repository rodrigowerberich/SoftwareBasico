#ifndef SB_LIGADOR
#define SB_LIGADOR

#include <string>
#include <vector>

#include "SeparadorDeLinhas.h"
#include "Tabelas_montador.h"
#include "Tabelas.h"
#include "Linha.h"
#include "Token.h"

namespace Montador{

class Ligador
{
public:
	Ligador(std::string, std::string, std::string);
	void ligar();
	void obter_tokens(std::string, std::vector<Linha>);

private:
	std::string arquivo1;
	std::string arquivo2;
	std::string saida;
	std::vector<Linha> linhas1;
	std::vector<Linha> linhas2;
	Tabela_Uso tabela_de_uso
};


} // namespace Montador
#endif /* SB_LIGADOR */