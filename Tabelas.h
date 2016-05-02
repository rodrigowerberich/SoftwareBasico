#ifndef Tabelas_h
#define Tabelas_h

#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

// Classe Tabela de Símbolos.

class Tabela_Simbolos
{

public:
	void inserir_simbolo (string rotulo, int endereco, bool externo) throw (invalid_argument); 
	int getvalor (string rotulo) throw (invalid_argument);
	bool teste_externo (string rotulo);

private:
	vector<string> rotulo;
	vector<int> endereco;
	vector<bool> externo;
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

#endif