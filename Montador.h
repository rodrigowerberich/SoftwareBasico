#ifndef SB_MONTADOR
#define SB_MONTADOR

#include "Linha.h"
#include "SeparadorDeLinhas.h"
#include "Tabelas_montador.h"
#include "Tabelas.h"
#include <string>
#include <vector>

namespace Montador{

class Montador
{
public:
	Montador(std::string);
	void pre_processamento();
	void primeira_passagem();

private:
	std::string arquivo;
	std::vector<Linha> linhas;
	Tabela_Simbolos tabela_simbolo;
	Tabela_Definicoes tabela_definicao;
	Tabela_Uso tabela_de_uso;
	Tabela_Instrucoes tabela_instrucao;
	Tabela_Diretivas tabela_diretiva;
	bool modulo;
	bool section_text;
	bool section_data;
};

} // namespace Montador
#endif /* SB_MONTADOR */