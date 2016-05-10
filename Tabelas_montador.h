/*------------------------------------------------------------------------------------
	Trabalho 1 - Software Básico 01/2016 - Turma B

Nome: 	Letícia Helena Silva Porto 						11/0127846
		Rodrigo Werberich da Silva Moreira de Oliveira 	11/0139411

Nome do arquivo: Tabelas_montador.h

Descricao: Esqueleto das classes Tabela_Instrucoes, que armazena a tabela de instrucoes, e 
da classe Tabela_Diretivas, que armazena a tabela de diretivas.
----------------------------------------------------------------------------------------*/
#ifndef SB_TABELAS_MONTADOR
#define SB_TABELAS_MONTADOR

#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

/*
Classe Tabela_Instrucoes
Armazena a tabela de instrucoes em vetores e possui métodos para buscar informacoes nos mesmos
*/
class Tabela_Instrucoes{

public:
	// Construtor da classe
	Tabela_Instrucoes();

	// Método da classe
	bool teste_instrucao (string instrucao);
	
	// Getters da classe
	int get_opcode (string instrucao) throw (invalid_argument);
	int get_operandos (string instrucao);
	int get_tamanho(string instrucao);

private:
	// Vetores que armazenam a instrucao e suas propriedades
	vector<string> instrucao;
	vector<int> opcode;
	vector<int> operando;
	vector<int> tamanho; 

};

/*
Classe Tabela_Diretiva
Armazena a tabela de diretivas em um vetor e possui métodos para buscar informacoes nos mesmos
*/
class Tabela_Diretivas{

public:
	// Construtor da classe
	Tabela_Diretivas();

	// Método da classe
	bool teste_diretiva(string diretiva);

	// Getters da classe
	int get_tamanho(string diretiva);
	int get_operandos(string diretiva);

private:
	// Vetores que armazenam a diretiva e suas propriedades
	vector<string> diretiva;
	vector<int> operando;
	vector<int> tamanho;

};

#endif /* SB_TABELAS_MONTADOR */
