#ifndef Tabelas_montador_h
#define Tabelas_montador_h

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

#endif
