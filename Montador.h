#ifndef SB_MONTADOR
#define SB_MONTADOR

#include <string>
#include <vector>

#include "SeparadorDeLinhas.h"
#include "Tabelas_montador.h"
#include "Tabelas.h"
#include "Linha.h"
#include "Token.h"

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
	int corretor_posicao; //Corrige a posicao dos tokens devido a tokens extras

	std::string identificar_rotulo(std::vector<Token> &);
	bool identificar_diretiva(std::vector<Token> &,int &);
	void gerar_erro(const std::invalid_argument&,int);
};

} // namespace Montador
#endif /* SB_MONTADOR */