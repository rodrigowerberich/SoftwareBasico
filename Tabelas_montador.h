/*------------------------------------------------------------------------------------
	Trabalho 1 - Software Básico 01/2016 - Turma B

Nome: 	Letícia Helena Silva Porto 						11/0127846
		Rodrigo Werberich da Silva Moreira de Oliveira 	11/0139411

Nome do arquivo: Tabelas_montador.h

Descricao: Esqueleto da classes Tabela_Instrucoes, que faz a verificacao lexica de uma string.
----------------------------------------------------------------------------------------*/
#ifndef SB_TABELAS_MONTADOR
#define SB_TABELAS_MONTADOR

#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;


class Tabela_Instrucoes{

public:

	Tabela_Instrucoes();
	bool teste_instrucao (string instrucao);
	int get_opcode (string instrucao) throw (invalid_argument);
	int get_operandos (string instrucao);
	int get_tamanho(string instrucao);

private:
	vector<string> instrucao;
	vector<int> opcode;
	vector<int> operando;
	vector<int> tamanho; 

};

class Tabela_Diretivas{

public:

	Tabela_Diretivas();
	bool teste_diretiva(string diretiva);
	int get_tamanho(string diretiva);
	int get_operandos(string diretiva);

private:	
	vector<string> diretiva;
	vector<int> operando;
	vector<int> tamanho;

};

#endif /* SB_TABELAS_MONTADOR */
