/*------------------------------------------------------------------------------------
	Trabalho 1 - Software Básico 01/2016 - Turma B

Nome: 	Letícia Helena Silva Porto 						11/0127846
		Rodrigo Werberich da Silva Moreira de Oliveira 	11/0139411

Nome do arquivo: montador.c

Descricao: Este arquivo contém o código principal do Montador, ele cria um objeto da classe
Montador, passa os arquivos de entrada e de saida para o construtor e chama os métodos pre_processamento,
primeira_passagem, segunda_passagem e gerar_arquivo.
----------------------------------------------------------------------------------------*/
#include <iostream>
#include <stdexcept>
#include "Montador.h"

using namespace std;
int main(int argc, char const *argv[])
{
	// Verifica se foi dado o número correto de argumentos
	if(argc != 3){
		throw invalid_argument("Número de argumentos invalidos");
	}

	// Cria o objeto montador
	Montador::Montador montador(argv[1],argv[2]);

	montador.pre_processamento();
	montador.primeira_passagem();
	montador.segunda_passagem();
	montador.gerar_arquivo();

    return 0;
}