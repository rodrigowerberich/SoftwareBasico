/*------------------------------------------------------------------------------------
	Trabalho 1 - Software Básico 01/2016 - Turma B

Nome: 	Letícia Helena Silva Porto 						11/0127846
		Rodrigo Werberich da Silva Moreira de Oliveira 	11/0139411

Nome do arquivo: Ligador.h

Descricao: Esqueleto da classe Ligador, que recebe dois arquivos no formato .o, que teoricamente
sao pares de módulos, os "liga" e gera um executável de saída .e.
----------------------------------------------------------------------------------------*/

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

	/* 	Definicao da Classe Ligador
		Essa classe possui métodos que obtem e decodifica os caracteres dos arquivos recebidos,
		gera a tabela geral de definicoes e escreve o código de saída ligando os dois arquivos 
		originais.   
	*/
	class Ligador
	{
	public:
		// Construtor da classe Ligador
		Ligador(std::string, std::string, std::string);
		
		// Método privado da classe Ligador
		void ligar();
	private:
		// String que armazena o nome do primeiro arquivo de entrada
		std::string arquivo1;
		// String que armazena o nome do segundo arquivo de entrada
		std::string arquivo2;
		// String que armazena o nome do arquivo de saida
		std::string saida;
		// Vetor de objetos da classe Linha que armazena as linhas do primeiro arquivo de entrada
		std::vector<Linha> linhas1;
		// Vetor de objetos da classe Linha que armazena as linhas do segundo arquivo de entrada
		std::vector<Linha> linhas2;
		// Objeto da classe Tabela_Uso que armazena a tabela de uso do primeiro modulo de entrada
		Tabela_Uso tabela_de_uso1;
		// Objeto da classe Tabela_Uso que armazena a tabela de uso do segundo modulo de entrada
		Tabela_Uso tabela_de_uso2;
		// Objeto da classe Tabela_Definicoes que armazena a tabela de definicoes do primeiro modulo de entrada
		Tabela_Definicoes tabela_de_definicao1;
		// Objeto da classe Tabela_Definicoes que armazena a tabela de definicoes do primeiro modulo de entrada
		Tabela_Definicoes tabela_de_definicao2;
		// Objeto da classe Tabela_Definicoes que armazena a tabela de definicoes geral
		Tabela_Definicoes tabela_geral_definicao;
		// String que armazena o código do primeiro modulo de entrada
		std::vector<std::string> codigo1;
		// String que armazena o código do segundo modulo de entrada
		std::vector<std::string> codigo2;
		// String que armazena o código após a ligacao
		std::string codigo_geral;
		// String que armazena os enderecos relativos do primeiro modulo de entrada
		std::vector<int> relativo1;
		// String que armazena os enderecos relativso do segundo modulo de entrada
		std::vector<int> relativo2;

		// Métodos privados da classe Ligador 
		void obter_tokens(std::string, std::vector<Linha>&);
		void decodificar_tokens(std::vector<Linha>, Tabela_Uso&, Tabela_Definicoes&, std::vector<int>&,std::vector<string>&);
		void gerar_tabela_unificada();
		void gerar_codigo_unificado();
		void escrever_arquivo();

	};


} // namespace Montador
#endif /* SB_LIGADOR */