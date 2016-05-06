#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

#include "Tabelas.h"
#include "Tabelas_montador.h"

using namespace std;

// Definicao dos métodos da Classe Tabela de Símbolos

void Tabela_Simbolos::inserir_simbolo (string simbolo, int valor,int tam, bool importado, bool cnst, bool val_jmp, bool z) throw (invalid_argument){

	unsigned int i;

	if (tabela_instrucao.teste_instrucao(simbolo)) {
		throw invalid_argument (string("Erro sintático: O Token ")+simbolo+string(" usado é uma palavra reservada"));
	}

	if (tabela_diretiva.teste_diretiva(simbolo))
		throw invalid_argument (string("Erro sintático: O Token ")+simbolo+string(" usado é uma palavra reservada"));

	for (i = 0; i < rotulo.size(); i++) {

		if ((rotulo[i]) == simbolo)
			throw invalid_argument ("Erro semântico: Definicao duplicada");
	}

	rotulo.push_back(simbolo);
	endereco.push_back(valor);
	externo.push_back(importado);
	constante.push_back(cnst);
	jump_valido.push_back(val_jmp);
	tamanho.push_back(tam);
	zero.push_back(z);
}

int Tabela_Simbolos::getvalor (string simbolo) throw (invalid_argument){

	unsigned int i;

	int valor = -2;

	for (i = 0; i < rotulo.size(); i++) {

		if ((rotulo[i]) == simbolo)
			valor = endereco[i];
			
	}

	if (valor == -2)
		throw invalid_argument ("Erro semântico: Declaracao do rótulo "+simbolo+" ausente");

	return valor;
}

int Tabela_Simbolos::get_tamanho (string simbolo) {

	unsigned int i;

	for (i=0; i< rotulo.size(); i++){
		if (rotulo[i] == simbolo)
			return tamanho[i];
	}
	return 0;
}

bool Tabela_Simbolos::teste_externo(string simbolo){
	
	unsigned int i;

	bool importado=false;

	for (i = 0; i < rotulo.size(); i++) {

		if ((rotulo[i]) == simbolo)
			importado = externo[i];
	}

	return importado;
}


bool Tabela_Simbolos::teste_constante(string simbolo){
	
	unsigned int i;

	bool csnt=false;

	for (i = 0; i < rotulo.size(); i++) {

		if ((rotulo[i]) == simbolo)
			csnt = constante[i];
	}

	return csnt;
}

bool Tabela_Simbolos::teste_jump_valido(string simbolo){
	
	unsigned int i;

	bool jmp_valido=false;

	for (i = 0; i < rotulo.size(); i++) {

		if ((rotulo[i]) == simbolo)
			jmp_valido = jump_valido[i];
	}

	return jmp_valido;
}


bool Tabela_Simbolos::teste_const_zero(string simbolo){
	
	unsigned int i;

	for (i = 0; i < rotulo.size(); i++) {

		if ((rotulo[i]) == simbolo)
			 return zero[i];
	}

	return false;
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

void Tabela_EQU::inserir_equ(string simbolo, string value)
{
	rotulo.push_back(simbolo);
	valor.push_back(value);
}

string Tabela_EQU::pegar_equ(string simbolo)
{
	unsigned int i;
	string value;

	for (i = 0; i < rotulo.size(); i++) {

		if ((rotulo[i]) == simbolo){
			return valor[i];
		}
	}
	return value;
}
