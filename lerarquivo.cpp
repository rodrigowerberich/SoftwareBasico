#include <iostream>
#include <stdexcept>
#include "Montador.h"

using namespace std;
int main(int argc, char const *argv[])
{
	if(argc != 3){
		throw invalid_argument("Número de argumentos invalidos");
	}
	Montador::Montador montador(argv[1]);
	montador.pre_processamento();
    return 0;
}