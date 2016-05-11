/*------------------------------------------------------------------------------------
	Trabalho 1 - Software Básico 01/2016 - Turma B

Nome: 	Letícia Helena Silva Porto 						11/0127846
		Rodrigo Werberich da Silva Moreira de Oliveira 	11/0139411

Nome do arquivo: ligador.c

Descricao: Este arquivo contém o código principal do Ligador, ele cria um objeto da classe
Ligador, passa os arquivos de entrada e de saida para o construtor e chama o método ligar,
que realiza, atraves de métodos auxiliares, as etapas de "ligacao" dos dois módulos de entrada. 
----------------------------------------------------------------------------------------*/

#include "Ligador.h"
#include <iostream>

using namespace std;
int main(int argc, char const *argv[])
{
	// Verifica se foi dado o número correto de argumentos
	if(argc != 4){
		throw invalid_argument("Número de argumentos invalidos");
	}
	// Cria o objeto ligador
	Montador::Ligador ligador(argv[1],argv[2],argv[3]);
	
	// Chama o método "ligar" que realiza as etapas de ligacao.
	ligador.ligar();

    return 0;
}