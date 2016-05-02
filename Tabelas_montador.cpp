#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

#include "Tabelas_montador.h"

using namespace std;

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

int Tabela_Instrucoes::get_opcode(string inst) throw (invalid_argument){

	int i = 0;
	int op = -2;

	for (i = 0; i < instrucao.size(); i++) {

		if ((instrucao[i]) == inst)
			op = opcode[i];
	}

	if (op == -2)
		throw invalid_argument ("Erro Léxico");

	return op;
}

int Tabela_Instrucoes::get_operandos(string inst){

	int i = 0;
	int num_operandos;

	for (i = 0; i < instrucao.size(); i++) {

		if ((instrucao[i]) == inst)
			num_operandos = operando[i];
	}

	return num_operandos;
}

int Tabela_Instrucoes::get_tamanho(string inst){

	int i = 0;
	int tamanho_inst;

	for (i = 0; i < instrucao.size(); i++) {

		if ((instrucao[i]) == inst)
			tamanho_inst = tamanho[i];
	}

	return tamanho_inst;
}

bool Tabela_Instrucoes::teste_instrucao(string inst){

	int i = 0, temp = 0;

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
	operando.push_back(0);
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


int Tabela_Diretivas::get_operandos(string dir){

	int i = 0;
	int num_operandos;

	for (i = 0; i < diretiva.size(); i++) {

		if ((diretiva[i]) == dir)
			num_operandos = operando[i];
	}

	return num_operandos;
}

int Tabela_Diretivas::get_tamanho(string dir){

	int i = 0;
	int tamanho_dir;

	for (i = 0; i < diretiva.size(); i++) {

		if ((diretiva[i]) == dir)
			tamanho_dir = tamanho[i];
	}

	return tamanho_dir;
}

bool Tabela_Diretivas::teste_diretiva(string dir){

	int i = 0, temp = 0;

	for (i = 0; i < diretiva.size(); i++) {

		if ((diretiva[i]) == dir)
			temp = 1;
	}

	if (temp == 1)
		return true;
	else
		return false;
}