#include "Ligador.h"
#include "SeparadorDeLinhas.h"
#include "Buffer.h"
#include "Token.h"
#include "Linha.h"
#include "Tabelas.h"
#include <string>

using namespace std;
namespace Montador{
	Ligador::Ligador(std::string a1, std::string a2, std::string s){
		arquivo1 = a1;
		arquivo2 = a2;
		saida = s;
	}

	void Ligador::ligar(){
		obter_tokens(arquivo1,linhas1);
		obter_tokens(arquivo2,linhas2);
		decodificar_tokens(linhas1, tabela_de_uso1, tabela_de_definicao1, relativo1, codigo1);
	}

	void Ligador::obter_tokens(string arquivo,std::vector<Linha> linhas){
		Buffer b(arquivo+".o");
		SeparadorDeLinhas sep;
		int num_linha = 0;
		while(!b.fim()){
			std::string linha = b.proxima_linha();
			std::vector<Token> tokens = sep.separar_linha(linha);
			if(!tokens.empty()){
				Linha linha_separada = Linha(tokens,num_linha);
				linhas.push_back(linha_separada);
				for(int i=0;i<tokens.size();i++){
					cout << tokens[i].get_str()<<" ";
				}
				cout << endl;
			}
			num_linha++;
		}
	}

	void Ligador::decodificar_tokens(std::vector<Linha> linhas, )

}