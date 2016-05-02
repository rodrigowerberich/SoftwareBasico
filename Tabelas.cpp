#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

#include "Tabelas.h"

using namespace std;

// Definicao dos métodos da Classe Tabela de Símbolos

void Tabela_Simbolos::inserir_simbolo (string simbolo, int valor, bool importado) throw (invalid_argument){

	int i;

	for (i = 0; i < rotulo.size(); i++) {

		if ((rotulo[i]) == simbolo)
			throw invalid_argument ("Erro semântico");
	}

	rotulo.push_back(simbolo);
	endereco.push_back(valor);
	externo.push_back(importado);

}

int Tabela_Simbolos::getvalor (string simbolo) throw (invalid_argument){

	int i;

	int valor = -2;

	for (i = 0; i < rotulo.size(); i++) {

		if ((rotulo[i]) == simbolo)
			valor = endereco[i];
			
	}

	if (valor == -2)
		throw invalid_argument ("Erro semântico");

	return valor;
}

bool Tabela_Simbolos::teste_externo(string simbolo){
	
	int i;

	bool importado;

	for (i = 0; i < rotulo.size(); i++) {

		if ((rotulo[i]) == simbolo)
			importado = externo[i];
	}

	return importado;
}


// Definicao dos métodos da Classe Tabela de Definicoes


void Tabela_Definicoes::inserir_definicao (string simbolo, int valor){

	rotulo.push_back(simbolo);
	endereco.push_back(valor);
}

// Definicao dos métodos da classe Tabela_Uso

void Tabela_Uso::inserir_uso (string simbolo, int valor){

	rotulo.push_back(simbolo);
	endereco.push_back(valor);

}
