#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <stdlib.h>

#include "Token.h"
#include "Montador.h"
#include "Linha.h"
#include "Tabelas_montador.h"
#include "Tabelas.h"
#include "Buffer.h"
#include "SeparadorDeLinhas.h"

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
				gerar_erro(ia,num_linha);
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
			corretor_posicao = 0;
			if (!tokens_linha.empty()){
				try {
					rotulo = identificar_rotulo(tokens_linha);
					cout << rotulo << endl;
					if(identificar_diretiva(tokens_linha,endereco))
						cout << "É diretiva" << endl;
					// if (tabela_diretiva.teste_diretiva(tokens_linha[1+corretor_posicao].get_str())){
					// 	cout <<tokens_linha[1+corretor_posicao].get_str() <<" é uma diretiva" << endl;
					// }else if(tabela_instrucao.teste_instrucao(tokens_linha[1+corretor_posicao].get_str())){
					// 	cout <<tokens_linha[1+corretor_posicao].get_str() <<" é uma instrucao" << endl;
					// }else{
					// 	cout <<tokens_linha[1+corretor_posicao].get_str() << " nao é nada"<<endl;
					// }

				}catch(const std::invalid_argument& ia){
					gerar_erro(ia,linha->get_numero());
				}
			}
		}
	}

	std::string Montador::identificar_rotulo(std::vector<Token> & tokens){
		string rotulo;
		if (tokens[0].verifica_rotulo()) {
			rotulo = tokens[0].get_str().substr(0,tokens[0].get_str().size()-1);
			//tabela_simbolo.inserir_simbolo(rotulo,endereco,false);
			//cout << rotulo<<endl;
		}else if(tokens[1].get_str() == string(":")) {
			rotulo = tokens[0].get_str();
			corretor_posicao++;
			//tabela_simbolo.inserir_simbolo(rotulo,endereco,false);
			//cout << rotulo<<endl;
		}else{
			corretor_posicao--;
		}
		return rotulo;
	}

	bool Montador::identificar_diretiva(std::vector<Token> & tokens,int & endereco){
		string diretiva = tokens[1+corretor_posicao].get_str();
		if (tabela_diretiva.teste_diretiva(diretiva)){
			int num_op = tabela_diretiva.get_operandos(diretiva);
			if(diretiva == "SPACE"){
				if(1!=tokens.size()-(2+corretor_posicao) && 0!=tokens.size()-(2+corretor_posicao)){
					throw invalid_argument("Erro Sintático: Número incorreto de argumentos");
				}
				if(0==tokens.size()-(2+corretor_posicao)){
					endereco+=1;
				}else if(1==tokens.size()-(2+corretor_posicao)){
					string num = tokens[2+corretor_posicao].get_str();
					endereco += atoi(num.c_str());
				}
			}else{
				if(num_op!=tokens.size()-(2+corretor_posicao)){
					throw invalid_argument("Erro Sintático: Número incorreto de argumentos");
				}
				endereco += tabela_diretiva.get_tamanho(diretiva);
			}
			return true;
		}else{
			return false;
		}
	}

	void Montador::gerar_erro(const std::invalid_argument& ia,int num_linha){
		stringstream ss;
		ss << num_linha;
		string s_num_linha = ss.str();
		throw std::invalid_argument(std::string(" Linha ")+s_num_linha+string(": ")+ia.what());		
	}
}