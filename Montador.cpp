#include "Buffer.h"
#include "SeparadorDeLinhas.h"
#include <iostream>
#include <vector>
#include <string>
#include <sstream>


#include "Token.h"
#include "Montador.h"
#include "Linha.h"

namespace Montador{

	Montador::Montador(std::string arquivo_dado){
		arquivo = arquivo_dado;
	}

	void Montador::pre_processamento() 
	{ 
		using namespace std;
		Buffer b(arquivo);
		SeparadorDeLinhas sep;
		int num_linha = 1;
		while(!b.fim()){
			std::string linha = b.proxima_linha();
			try{
				std::vector<Token> tokens = sep.separar_linha(linha);
				linhas.push_back(Linha(tokens,num_linha));
				num_linha++;
			}catch(const std::invalid_argument& ia){
				if (ia.what() == string("Erro Léxico")){
					stringstream ss;
					ss << num_linha;
					string s_num_linha = ss.str();
					throw std::invalid_argument(std::string("Erro léxico na linha ")+s_num_linha);
				}else
					throw;
			}
		}
	}
}