/*------------------------------------------------------------------------------------
	Trabalho 1 - Software Básico 01/2016 - Turma B

Nome: 	Letícia Helena Silva Porto 						11/0127846
		Rodrigo Werberich da Silva Moreira de Oliveira 	11/0139411

Nome do arquivo: Tabelas.h

Descricao: Este arquivo contém a definicao dos métodos das classes Tabela_Simbolos, 
Tabela_Definicoes, Tabela_Uso e Tabela_EQU.
----------------------------------------------------------------------------------------*/

#include <iostream>
#include <stdexcept>
#include <sstream>
#include <string>
#include <vector>

#include "Tabelas.h"
#include "Tabelas_montador.h"

using namespace std;

namespace Montador {

	/* Classe Tabela_Simbolos
	*/
	/*	Método da classe Tabela_Simbolos
		Argumentos recebidos: símbolo, endereco desse simbolo, o tamanho reservado para esse simbolo,
		se ele externo, se ele é uma constante, se é um endereco válido para jump e se é zero.
		Esse método armazena as informacoes na Tabela_Simbolos, e dá erro caso o símbolo ja esteja na
		Tabela ou se for uma palavra reservada do Assembly inventado.
	*/
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

	/*	Método da classe Tabela_Simbolos
		Argumentos recebidos: símbolo.
		Retorna: endereco definido do símbolo.
		Recebe um símbolo e procura o endereco correspondente na tabela de simbolos
	*/
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

	/*	Método da classe Tabela_Simbolos
		Argumentos recebidos: símbolo.
		Retorna: tamanho de memoria definido do símbolo.
		Recebe um símbolo e procura o tamanho reservado correspondente na tabela de simbolos
	*/
	int Tabela_Simbolos::get_tamanho (string simbolo) {
		unsigned int i;
		for (i=0; i< rotulo.size(); i++){
			if (rotulo[i] == simbolo)
				return tamanho[i];
		}
		
		return 0;
	}

	/*	Método da classe Tabela_Simbolos
		Argumentos recebidos: símbolo.
		Retorna: se o símbolo é externo ou nao.
		Recebe um símbolo e procura o boleano que indica se ele é externo na tabela de simbolos
	*/
	bool Tabela_Simbolos::teste_externo(string simbolo){
		unsigned int i;
		bool importado=false;
		for (i = 0; i < rotulo.size(); i++) {
			if ((rotulo[i]) == simbolo)
				importado = externo[i];
		}

		return importado;
	}

	/*	Método da classe Tabela_Simbolos
		Argumentos recebidos: símbolo.
		Retorna: se o símbolo é constante.
		Recebe um símbolo e procura o boleano que indica se ele é constante na tabela de simbolos
	*/
	bool Tabela_Simbolos::teste_constante(string simbolo){
		unsigned int i;
		bool csnt=false;
		for (i = 0; i < rotulo.size(); i++) {
			if ((rotulo[i]) == simbolo)
				csnt = constante[i];
		}

		return csnt;
	}

	/*	Método da classe Tabela_Simbolos
		Argumentos recebidos: símbolo.
		Retorna: se o símbolo é um endereco para jump valido.
		Recebe um símbolo e procura o boleano que indica se ele é um endereco de jump valido na tabela de simbolos
	*/
	bool Tabela_Simbolos::teste_jump_valido(string simbolo){
		unsigned int i;
		bool jmp_valido=false;
		for (i = 0; i < rotulo.size(); i++) {
			if ((rotulo[i]) == simbolo)
				jmp_valido = jump_valido[i];
		}

		return jmp_valido;
	}

	/*	Método da classe Tabela_Simbolos
		Argumentos recebidos: símbolo.
		Retorna: se o símbolo é zero.
		Recebe um símbolo e procura o boleano que indica se ele é zero na tabela de simbolos
	*/
	bool Tabela_Simbolos::teste_const_zero(string simbolo){
		unsigned int i;
		for (i = 0; i < rotulo.size(); i++) {
			if ((rotulo[i]) == simbolo)
				 return zero[i];
		}

		return false;
	}

	/* Classe Tabela_Definicoes
	*/
	/*	Método da classe Tabela_Definicoes
		Argumentos recebidos: símbolo, endereco desse simbolo.
		Esse método armazena as informacoes na Tabela_Definicoes, e dá erro caso o símbolo ja esteja na
		Tabela.
	*/
	void Tabela_Definicoes::inserir_definicao (string simbolo, int valor){
		if(-1!=get_endereco_def(simbolo))
			throw invalid_argument("Erro léxico: Redefinicao do label "+simbolo);
		rotulo.push_back(simbolo);
		endereco.push_back(valor);
	}

	/*	Método da classe Tabela_Definicoes
		Argumentos recebidos: posicao do rótulo.
		Retorna: o rótulo da posicao dada.
		Recebe uma posicao do vetor "rotulo" e retorna esse rotulo, caso o vetor contenha essa posicao.
	*/
	string Tabela_Definicoes::get_simbolo_def (int posicao){
		string nada;
		if (posicao < rotulo.size()){
			return rotulo[posicao];
		}

		return nada;
	}

	/*	Método da classe Tabela_Definicoes
		Argumentos recebidos: posicao do rótulo.
		Retorna: o endereco do rotulo da posicao dada.
		Recebe uma posicao do vetor "endereco" e retorna esse endereco,
		caso o vetor contenha essa posicao.
	*/
	string Tabela_Definicoes::get_endereco_def (int posicao){
		string nada;
		int temp = 0;
		if (posicao < rotulo.size()){
			temp = endereco[posicao];
			stringstream ss;
			ss << temp;
			string s_endereco = ss.str();
			return s_endereco;
		}

		return nada;
	}

	/*	Método da classe Tabela_Definicoes
		Argumentos recebidos: um rótulo.
		Retorna: o endereco do rotulo dado.
		Recebe um elemento do vetor "rotulo" e retorna o endereco desse rotulo,
		caso o vetor contenha esse rotulo.
	*/
	int Tabela_Definicoes::get_endereco_def(string simbolo){
		unsigned int i;
		for (i=0; i< rotulo.size(); i++){
			if (rotulo[i] == simbolo)
				return endereco[i];
		}
		return -1;
	}

	/* Classe Tabela_Uso
	*/
	/*	Método da classe Tabela_Uso
		Argumentos recebidos: símbolo, endereco onde esse simbolo é usado.
		Esse método armazena as informacoes na Tabela_Uso.
	*/
	void Tabela_Uso::inserir_uso (string simbolo, int valor){

		rotulo.push_back(simbolo);
		endereco.push_back(valor);
	}

	/*	Método da classe Tabela_Uso
		Argumentos recebidos: uma posicao do vetor rotulo.
		Retorna: o rotulo correspondente a posicao.
		Recebe uma posicao do vetor "rotulo" e retorna esse rotulo,
		caso ele contenha um rotulo nessa posicao do vetor.
	*/
	string Tabela_Uso::get_simbolo_uso (int posicao){
		string nada;
		if (posicao < rotulo.size()){
			return rotulo[posicao];
		}

		return nada;
	}

	/*	Método da classe Tabela_Uso
		Argumentos recebidos: uma posicao do vetor endereco.
		Retorna: o endereco correspondente a posicao.
		Recebe uma posicao do vetor "endereco" e retorna esse endereco,
		caso ele contenha um rotulo nessa posicao do vetor.
	*/
	string Tabela_Uso::get_endereco_uso (int posicao){
		string nada;
		int temp = 0;
		if (posicao < rotulo.size()){
			temp = endereco[posicao];
			stringstream ss;
			ss << temp;
			string s_endereco = ss.str();
			return s_endereco;
		}

		return nada;
	}

	/* Classe Tabela_EQU
	*/
	/*	Método da classe Tabela_EQU
		Argumentos recebidos: símbolo, valor da EQU correspondente.
		Esse método armazena as informacoes na Tabela_EQU.
	*/	
	void Tabela_EQU::inserir_equ(string simbolo, string value)
	{
		rotulo.push_back(simbolo);
		valor.push_back(value);
	}

	/*	Método da classe Tabela_EQU
		Argumentos recebidos: um simbolo.
		Retorna: a EQU correspondente a label.
		Recebe um rotulo e verifica se ele tem uma definicao de EQU correspondente.
	*/
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
}
