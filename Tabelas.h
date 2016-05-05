#ifndef Tabelas_h
#define Tabelas_h

#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

#include "Tabelas_montador.h"

using namespace std;

// Classe Tabela de Símbolos.

class Tabela_Simbolos
{

public:
	void inserir_simbolo (string rotulo, int endereco, int tamanho, bool externo, bool constante, bool jump_valido) throw (invalid_argument); 
	int getvalor (string rotulo) throw (invalid_argument);
	int get_tamanho (string rotulo);
	bool teste_externo (string rotulo);
	bool teste_constante (string rotulo);
	bool teste_jump_valido (string rotulo);

private:
	vector<string> rotulo;
	vector<int> endereco;
	vector<int> tamanho;
	vector<bool> externo;
	vector<bool> constante;
	vector<bool> jump_valido;
	Tabela_Instrucoes tabela_instrucao;
	Tabela_Diretivas tabela_diretiva;
};

// Classe Tabela de Definicoes.

class Tabela_Definicoes
{

public:
	void inserir_definicao (string rotulo, int endereco);

private:
	vector<string> rotulo;
	vector<int> endereco;
};

// Classe Tabela de Uso.

class Tabela_Uso
{

public:
	void inserir_uso (string rotulo, int endereco);

private:
	vector<string> rotulo;
	vector<int> endereco;
};

class Tabela_EQU
{
public:
	void inserir_equ (string rotulo, string valor);
	string pegar_equ (string rotulo);
private:
	vector<string> rotulo;
	vector<string> valor;
};

#endif