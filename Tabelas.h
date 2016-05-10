/*------------------------------------------------------------------------------------
	Trabalho 1 - Software Básico 01/2016 - Turma B

Nome: 	Letícia Helena Silva Porto 						11/0127846
		Rodrigo Werberich da Silva Moreira de Oliveira 	11/0139411

Nome do arquivo: Tabelas.h

Descricao: Esqueleto das classes Tabela_Simbolos, Tabela_Definicoes, Tabela_Uso e Tabela_EQU.
----------------------------------------------------------------------------------------*/

#ifndef Tabelas_h
#define Tabelas_h

#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

#include "Tabelas_montador.h"

using namespace std;

namespace Montador {

	/* Definicao da Classe Tabela_Simbolos
	   Armazena os rótulos contidos no programa, seu endereco, seu tamanho reservado, caso seja um vetor,
	   se o rótulo é um argumento externo, se é uma constante, se é um endereco de jump válido
	   e se o rótulo é igual a zero.
	   Possui métodos que retornam essas informacoes sobre um determinado rótulo do programa.
	*/
	class Tabela_Simbolos
	{
	public:
		// métodos públicos da classe Tabela_Simbolos
		void inserir_simbolo (string rotulo, int endereco, int tamanho, bool externo, bool constante, bool jump_valido, bool zero) throw (invalid_argument); 
		int getvalor (string rotulo) throw (invalid_argument);
		int get_tamanho (string rotulo);
		bool teste_externo (string rotulo);
		bool teste_constante (string rotulo);
		bool teste_jump_valido (string rotulo);
		bool teste_const_zero (string rotulo);
	private:
		// atributos privados da classe Tabela_Simbolos
		vector<string> rotulo;
		vector<int> endereco;
		vector<int> tamanho;
		vector<bool> externo;
		vector<bool> constante;
		vector<bool> jump_valido;
		vector<bool> zero;
		Tabela_Instrucoes tabela_instrucao;
		Tabela_Diretivas tabela_diretiva;
	};

	/* Definicao da Classe Tabela_Definicoes
	   Armazena os rótulos contidos no programa que sao do tipo PUBLIC, caso o programa seja um módulo.
	   Possui métodos para armazenar esse atributo e o endereco em que é definido e métodos que retornam
	   as informacoes armazenadas.
	*/
	class Tabela_Definicoes
	{
	public:
		// Métodos publicos classe Tabela_Definicoes
		void inserir_definicao (string rotulo, int endereco);
		string get_simbolo_def (int posicao);
		string get_endereco_def (int posicao);
		int get_endereco_def(string rotulo);
	private:
		// Atributos privados da classe Tabela_Definicoes
		vector<string> rotulo;
		vector<int> endereco;
	};

	/* Definicao da Classe Tabela_Uso
	   Armazena os argumentos que sao do tipo EXTERN, caso o programa seja um módulo.
	   Possui métodos para armazenar esse atributo e o endereco em que é usado e métodos
	   que retornam as informacoes armazenadas.
	*/
	class Tabela_Uso
	{
	public:
		// Métodos publicos da classe Tabela_Uso
		void inserir_uso (string rotulo, int endereco);
		string get_simbolo_uso (int posicao);
		string get_endereco_uso (int posicao);
	private:
		// Atributos privados da classe Tabela_Uso
		vector<string> rotulo;
		vector<int> endereco;
	};

	/* Definicao da Classe Tabela_EQU
	   Recebe os rotulos das EQU existentes e armazena o valor correnspodente de cada um.
	   Possui um método para retornar o valor correspondente de uma determinada EQU.
	*/
	class Tabela_EQU
	{
	public:
		// Métodos públicos da classe Tabela_EQU
		void inserir_equ (string rotulo, string valor);
		string pegar_equ (string rotulo);
	private:
		// Atributos privados da classe Tabela_EQU
		vector<string> rotulo;
		vector<string> valor;
	};

}
#endif