#include "Buffer.h"
#include "SeparadorDeLinhas.h"
#include <iostream>
#include <vector>
#include <string>
#include <sstream>

#include "Token.h"
#include "Montador.h"
#include "Linha.h"
#include "Tabelas_montador.h"
#include "Tabelas.h"

using namespace std;

namespace Montador{

	Montador::Montador(std::string arquivo_dado){
		arquivo = arquivo_dado;
		section_text = false;
		section_data = false;
		modulo = false;
	}

	void Montador::pre_processamento() 
	{ 
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

	// Montar tabela de símbolos
	// verificar se instrucoes sao válidas
	// verificar se diretivas sao validas, caso válida, executa-la
	// verificar se sessoes do codigo sao validas
	void Montador::primeira_passagem(){

		int endereco = 0;
		string rotulo;

		for(vector<Linha>::iterator linha = linhas.begin(); linha!=linhas.end(); ++linha) {

			vector<Token> tokens_linha = linha->get_tokens();
			if (!tokens_linha.empty()){
				try {
					if (tokens_linha[0].verifica_rotulo()) {
						rotulo = tokens_linha[0].get_str().substr(0,tokens_linha[0].get_str().size()-1);
						tabela_simbolo.inserir_simbolo(rotulo,endereco,false);
						cout << rotulo<<endl;
					}else if(tokens_linha[1].get_str() == string(":")) {
						rotulo = tokens_linha[0].get_str();
						tabela_simbolo.inserir_simbolo(rotulo,endereco,false);
						cout << rotulo<<endl;
					}

				}catch(const std::invalid_argument& ia){
					stringstream ss;
					ss << linha->get_numero();
					string s_num_linha = ss.str();
					throw std::invalid_argument(ia.what()+std::string(" na linha ")+s_num_linha);
				}
			}
		}
	}
}