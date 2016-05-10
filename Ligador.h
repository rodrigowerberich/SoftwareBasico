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
private:
	std::string arquivo1;
	std::string arquivo2;
	std::string saida;
	std::vector<Linha> linhas1;
	std::vector<Linha> linhas2;
	Tabela_Uso tabela_de_uso1;
	Tabela_Uso tabela_de_uso2;
	Tabela_Definicoes tabela_de_definicao1;
	Tabela_Definicoes tabela_de_definicao2;
	Tabela_Definicoes tabela_geral_definicao;
	std::vector<std::string> codigo1;
	std::vector<std::string> codigo2;
	std::string codigo_geral;
	std::vector<int> relativo1;
	std::vector<int> relativo2;


	void obter_tokens(std::string, std::vector<Linha>&);
	void decodificar_tokens(std::vector<Linha>, Tabela_Uso&, Tabela_Definicoes&, std::vector<int>&,std::vector<string>&);
	void gerar_tabela_unificada();
	void gerar_codigo_unificado();
	void escrever_arquivo();

};


} // namespace Montador
#endif /* SB_LIGADOR */