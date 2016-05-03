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
		modulo_aberto = false; 
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
					//cout << rotulo << endl;
					if(identificar_diretiva(tokens_linha))
						executar_diretiva(tokens_linha,rotulo,endereco);
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
		if(!section_text)
			throw invalid_argument("Erro Semântico: Secao TEXT faltante");
		if(modulo_aberto)
			throw invalid_argument("Erro Semântico: Diretiva END faltando");
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

	bool Montador::identificar_diretiva(std::vector<Token> & tokens){
		string diretiva = tokens[1+corretor_posicao].get_str();
		if (tabela_diretiva.teste_diretiva(diretiva)){
			return true;
		}else{
			return false;
		}
	}

	void Montador::executar_diretiva(std::vector<Token> & tokens,string rotulo, int & endereco){
		string diretiva = tokens[1+corretor_posicao].get_str();
		if (diretiva == "SECTION"){
			if(modulo && !modulo_aberto)
				throw invalid_argument("Erro Semântico: SECTION apos o END");
			diretiva_section(tokens[2+corretor_posicao].get_str());
		}else if (diretiva == "SPACE"){
			if(modulo && !modulo_aberto)
				throw invalid_argument("Erro Semântico: SPACE apos o END");
			if (!section_data)
				throw invalid_argument("Erro Semântico: Diretiva SPACE na secao errada");
			tabela_simbolo.inserir_simbolo(rotulo,endereco,false,false,false);
			cout << rotulo << " " << endereco << endl;
		}else if(diretiva == "CONST"){
			if(modulo && !modulo_aberto)
				throw invalid_argument("Erro Semântico: CONST apos o END");
			if (!section_data)
				throw invalid_argument("Erro Semântico: Diretiva CONST na secao errada");
			tabela_simbolo.inserir_simbolo(rotulo,endereco,false,true,false);
			cout << rotulo << " " << endereco << endl;
		}else if(diretiva == "BEGIN"){
			if (modulo_aberto)
				throw invalid_argument("Erro Semântico: BEGIN duplicado");
			if (section_data || section_text)
				throw invalid_argument("Erro Semântico: Diretiva BEGIN deve ficar fora de secao");
			modulo = true;
			modulo_aberto = true;
		}else if(diretiva == "END"){
			if (!modulo)
				throw invalid_argument("Erro Semântico: END sem detectar um BEGIN");
			if (!modulo_aberto)
				throw invalid_argument("Erro Semântico: END duplicado");
			if(!section_text)
				throw invalid_argument("Erro Semântico: END antes da secao TEXT");
			modulo_aberto = false;
		}
		else if(diretiva == "PUBLIC"){
			if(modulo && !modulo_aberto)
				throw invalid_argument("Erro Semântico: PUBLIC apos o END");
			if (!modulo)
				throw invalid_argument("Erro Semântico: Diretiva PUBLIC fora de modulo");	
			if(!section_text || section_data)
				throw invalid_argument("Erro Semântico: Diretiva PUBLIC na secao errada");			
		}
		// FALTAM EQU, IF e EXTERN


		unsigned int num_op = tabela_diretiva.get_operandos(diretiva);
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
	}

	void Montador::gerar_erro(const std::invalid_argument& ia,int num_linha){
		stringstream ss;
		ss << num_linha;
		string s_num_linha = ss.str();
		throw std::invalid_argument(std::string(" Linha ")+s_num_linha+string(": ")+ia.what());		
	}

	void Montador::diretiva_section(string argumento){
		if (argumento == "TEXT"){
			if(section_text){
				throw invalid_argument("Erro semântico: Secao TEXT já existe");
			}
			if(section_data){
				throw invalid_argument("Erro semântico: Secao DATA antes da secao TEXT");
			}
			section_text = true;
		}else if(argumento == "DATA"){
			if(!section_text){
				throw invalid_argument("Erro semântico: Secao TEXT nao foi declarada ainda");
			}
			if(section_data){
				throw invalid_argument("Erro semântico: Secao DATA já existe");
			}
			section_data = true;				
		}else{
			throw invalid_argument("Erro semântico: Secao invalida");
		}
	}
}