/*------------------------------------------------------------------------------------
	Trabalho 1 - Software Básico 01/2016 - Turma B

Nome: 	Letícia Helena Silva Porto 						11/0127846
		Rodrigo Werberich da Silva Moreira de Oliveira 	11/0139411

Nome do arquivo: Tabelas_montador.cpp

Descricao: Este arquivo contém a definicao dos métodos das classes Tabela_Instrucoes, que 
armazena a tabela de instrucoes, e da classe Tabela_Diretivas, que armazena a tabela de 
diretivas.
----------------------------------------------------------------------------------------*/
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

#include "Tabelas_montador.h"

using namespace std;

/*
Construtor da classe Tabela_Instrucoes
Cria um objeto Tabela_Instrucoes e cria a tabela de instrucoes do Assembler inventado, incluindo informacoes como
opcode, numero de operandos e o tamanho em bytes que será ocupado pela instrucao
*/
Tabela_Instrucoes::Tabela_Instrucoes(){

	instrucao.push_back("ADD");
	opcode.push_back(1);
	operando.push_back(1);
	tamanho.push_back(2);

	instrucao.push_back("SUB");
	opcode.push_back(2);
	operando.push_back(1);
	tamanho.push_back(2);

	instrucao.push_back("MULT");
	opcode.push_back(3);
	operando.push_back(1);
	tamanho.push_back(2);

	instrucao.push_back("DIV");
	opcode.push_back(4);
	operando.push_back(1);
	tamanho.push_back(2);

	instrucao.push_back("JMP");
	opcode.push_back(5);
	operando.push_back(1);
	tamanho.push_back(2);

	instrucao.push_back("JMPN");
	opcode.push_back(6);
	operando.push_back(1);
	tamanho.push_back(2);

	instrucao.push_back("JMPP");
	opcode.push_back(7);
	operando.push_back(1);
	tamanho.push_back(2);

	instrucao.push_back("JMPZ");
	opcode.push_back(8);
	operando.push_back(1);
	tamanho.push_back(2);

	instrucao.push_back("COPY");
	opcode.push_back(9);
	operando.push_back(2);
	tamanho.push_back(3);

	instrucao.push_back("LOAD");
	opcode.push_back(10);
	operando.push_back(1);
	tamanho.push_back(2);

	instrucao.push_back("STORE");
	opcode.push_back(11);
	operando.push_back(1);
	tamanho.push_back(2);

	instrucao.push_back("INPUT");
	opcode.push_back(12);
	operando.push_back(1);
	tamanho.push_back(2);

	instrucao.push_back("OUTPUT");
	opcode.push_back(13);
	operando.push_back(1);
	tamanho.push_back(2);

	instrucao.push_back("STOP");
	opcode.push_back(14);
	operando.push_back(0);
	tamanho.push_back(1);

}

/*
Método da classe Tabela_Instrucoes
Busca o opcode de uma instrucao,se ele nao existir ele acusa erro sintático
Recebe: uma string que é nome da instrucao
Retorna: o numero do opcode
*/
int Tabela_Instrucoes::get_opcode(string inst) throw (invalid_argument){

	unsigned int i = 0;
	int op = -2;

	for (i = 0; i < instrucao.size(); i++) {

		if ((instrucao[i]) == inst)
			op = opcode[i];
	}

	if (op == -2)
		throw invalid_argument ("Erro Sintático");

	return op;
}

/*
Método da classe Tabela_Instrucoes
Busca o número de operandos de uma instrucao
Recebe: uma string que é nome da instrucao
Retorna: a quantidade de operandos da instrucao
*/
int Tabela_Instrucoes::get_operandos(string inst){

	unsigned int i = 0;
	int num_operandos;

	for (i = 0; i < instrucao.size(); i++) {

		if ((instrucao[i]) == inst)
			num_operandos = operando[i];
	}

	return num_operandos;
}

/*
Método da classe Tabela_Instrucoes
Busca o tamanho de uma instrucao
Recebe: uma string que é nome da instrucao
Retorna: o tamanho da instrucao
*/
int Tabela_Instrucoes::get_tamanho(string inst){

	unsigned int i = 0;
	int tamanho_inst;

	for (i = 0; i < instrucao.size(); i++) {

		if ((instrucao[i]) == inst)
			tamanho_inst = tamanho[i];
	}

	return tamanho_inst;
}

/*
Método da classe Tabela_Instrucoes
Verifica se a instrucao é valida, ou seja, se ela existe na tabela
Recebe: uma string que é nome da instrucao
Retorna: um booleano que fala se a instrucao existe ou nao
*/
bool Tabela_Instrucoes::teste_instrucao(string inst){

	unsigned int i = 0;
	int temp = 0;

	for (i = 0; i < instrucao.size(); i++) {

		if ((instrucao[i]) == inst){
			temp = 1;
		}
	}

	if (temp == 1)
		return true;
	else
		return false;
}

/*
Construtor da classe Tabela_Diretivas
Cria um objeto Tabela_Diretivas e cria a tabela de diretivas do Assembler inventado, incluindo informacoes como
numero de operandos e o tamanho em bytes que será ocupado pela diretiva
*/
Tabela_Diretivas::Tabela_Diretivas(){

	diretiva.push_back("SECTION");
	operando.push_back(1);
	tamanho.push_back(0);
	
	diretiva.push_back("SPACE");
	operando.push_back(1);
	tamanho.push_back(1);

	diretiva.push_back("CONST");
	operando.push_back(1);
	tamanho.push_back(1);

	diretiva.push_back("PUBLIC");
	operando.push_back(1);
	tamanho.push_back(0);

	diretiva.push_back("EQU");
	operando.push_back(1);
	tamanho.push_back(0);

	diretiva.push_back("IF");
	operando.push_back(1);
	tamanho.push_back(0);

	diretiva.push_back("EXTERN");
	operando.push_back(0);
	tamanho.push_back(0);

	diretiva.push_back("BEGIN");
	operando.push_back(0);
	tamanho.push_back(0);

	diretiva.push_back("END");
	operando.push_back(0);
	tamanho.push_back(0);

}

/*
Método da classe Tabela_Diretivas
Busca o número de operandos de uma diretiva
Recebe: uma string que é nome da diretiva
Retorna: a quantidade de operandos da diretiva
*/
int Tabela_Diretivas::get_operandos(string dir){

	unsigned int i = 0;
	int num_operandos;

	for (i = 0; i < diretiva.size(); i++) {

		if ((diretiva[i]) == dir)
			num_operandos = operando[i];
	}

	return num_operandos;
}

/*
Método da classe Tabela_Diretivas
Busca o tamanho de uma diretiva
Recebe: uma string que é nome da diretiva
Retorna: o tamanho da diretiva
*/
int Tabela_Diretivas::get_tamanho(string dir){

	unsigned int i = 0;
	int tamanho_dir;

	for (i = 0; i < diretiva.size(); i++) {

		if ((diretiva[i]) == dir)
			tamanho_dir = tamanho[i];
	}

	return tamanho_dir;
}

/*
Método da classe Tabela_Diretivas
Verifica se a diretiva é valida, ou seja, se ela existe na tabela
Recebe: uma string que é nome da diretiva
Retorna: um booleano que fala se a diretiva existe ou nao
*/
bool Tabela_Diretivas::teste_diretiva(string dir){

	unsigned int i = 0;
	int temp = 0;

	for (i = 0; i < diretiva.size(); i++) {

		if ((diretiva[i]) == dir)
			temp = 1;
	}

	if (temp == 1)
		return true;
	else
		return false;
}