#include "Ligador.h"
#include <iostream>

using namespace std;
int main(int argc, char const *argv[])
{
	if(argc != 4){
		throw invalid_argument("Número de argumentos invalidos");
	}
	Montador::Ligador ligador(argv[1],argv[2],argv[3]);
	ligador.ligar();

    return 0;
}