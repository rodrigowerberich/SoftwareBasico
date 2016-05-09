#include <iostream>
#include <stdexcept>
#include "Montador.h"

using namespace std;
int main(int argc, char const *argv[])
{
	if(argc != 3){
		throw invalid_argument("Número de argumentos invalidos");
	}
	Montador::Montador montador(argv[1],argv[2]);
	montador.pre_processamento();
	montador.primeira_passagem();
	montador.segunda_passagem();
	montador.gerar_arquivo();

    return 0;
}