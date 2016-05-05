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
		ignorar_linha = false;
		existe_stop = false;
		linha_processada = false;
		rotulo_sozinho = false;
	}

	void Montador::pre_processamento() 
	{ 
		Buffer b(arquivo);
		SeparadorDeLinhas sep;
		unsigned int num_linha = 1;
		while(!b.fim()){
			std::string linha = b.proxima_linha();
			try{
				std::vector<Token> tokens = sep.separar_linha(linha);
				if(!tokens.empty()){
					Linha linha_separada = Linha(tokens,num_linha);
					tratar_EQU(linha_separada);
					linhas.push_back(linha_separada);
				}
			}catch(const std::invalid_argument& ia){
				gerar_erro(ia,num_linha);
			}
			num_linha++;
		}
		// for (unsigned int i=0;i<linhas.size();i++){
		// 	std::vector<Token> tokens = linhas[i].get_tokens();
		// 	for(unsigned int j=0;j<tokens.size();j++){
		// 		cout << tokens[j].get_str()<<" ";
		// 	}
		// 	cout << endl;
		// }
	}
	

	// Montar tabela de símbolos
	// verificar se instrucoes sao válidas
	// verificar se diretivas sao validas, caso válida, executa-la
	// verificar se sessoes do codigo sao validas
	void Montador::primeira_passagem(){

		int endereco = 0;
		string rotulo;
		std::vector<vector<Linha>::iterator> linhas_removidas;
		for(vector<Linha>::iterator linha = linhas.begin(); linha!=linhas.end(); ++linha) {

			vector<Token> tokens_linha = linha->get_tokens();
			corretor_posicao = 0;
			linha_processada = false;
			if(!ignorar_linha){
				try {
					rotulo = identificar_rotulo(tokens_linha);

					if(!rotulo.empty() && rotulo_sozinho)
						throw invalid_argument("Erro Sintático: Dois rótulos para a mesma linha");

					if(!rotulo.empty() && tokens_linha.size()<2){
						rotulo_sozinho = true;
						rotulo_anterior = rotulo;
					}
					else if(!rotulo.empty() && tokens_linha.size()<3){
						if(tokens_linha[1].get_str()==":"){
							rotulo_sozinho = true;
							rotulo_anterior = rotulo;
						}
					}
					else{
						if(rotulo.empty() && rotulo_sozinho)
							rotulo = rotulo_anterior;
						rotulo_sozinho = false;
					}

					//cout << rotulo << endl;
					if(!rotulo_sozinho){
						if(identificar_diretiva(tokens_linha))
							executar_diretiva(tokens_linha,rotulo,endereco);
						else if(identificar_instrucao(tokens_linha))
							executar_instrucao(tokens_linha,rotulo,endereco);
						else{
							linhas_removidas.push_back(linha);
							throw invalid_argument("Erro sintático: A linha contém Tokens inesperados");
						}
					}
					if(linha_processada)
						linhas_removidas.push_back(linha);
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
			}else{
				//linhas.erase(linha);
				//linhas.erase(linha-1);
				//linhas_removidas.push_back(linha-1);
				linhas_removidas.push_back(linha);
				ignorar_linha = false;
			}
		}
		while(!linhas_removidas.empty()){
			linhas.erase(linhas_removidas.back());
			linhas_removidas.pop_back();
		}
		if(!section_text)
			cout << "Erro Semântico: Secao TEXT faltante" << endl;
			//throw invalid_argument("Erro Semântico: Secao TEXT faltante");
		if(modulo_aberto)
			cout << "Erro Semântico: Diretiva BEGIN sem uma END" << endl;
		if(!modulo && !existe_stop)
			cout << "Erro Semântico: Falta pelo menos um STOP, e nao é modulo "<<endl;
			//throw invalid_argument("Erro Semântico: Diretiva END faltando");
		// for (unsigned int i=0;i<linhas.size();i++){
		// 	std::vector<Token> tokens = linhas[i].get_tokens();
		// 	for(unsigned int j=0;j<tokens.size();j++){
		// 		cout << tokens[j].get_str()<<" ";
		// 	}
		// 	cout << endl;
		// }
	}

	void Montador::segunda_passagem(){
		for (unsigned int i=0;i<linhas.size();i++){
			std::vector<Token> tokens = linhas[i].get_tokens();
			for(unsigned int j=0;j<tokens.size();j++){

				cout << tokens[j].get_str()<<" ";
			}
			cout << endl;
		}
	}

	void Montador::tratar_EQU(Linha & linha){
		vector<Token> tokens_linha = linha.get_tokens();
		string rotulo, valor, s_token;
		bool equ = false;
		bool dois_pontos;
		corretor_posicao = 0;
		
		for(unsigned int i=0;i<tokens_linha.size();i++){
			dois_pontos = false;
			s_token = tokens_linha[i].get_str();
			//cout << "S token "<<s_token << endl;
			valor = tabela_EQU.pegar_equ(s_token);
			//cout << "Valor antes " << valor << " Vazio? ";
			//cout << valor.empty() << " dois pontos "<< dois_pontos<<endl;
			if(valor.empty()){
				valor = tabela_EQU.pegar_equ(s_token.substr(0,s_token.size()-1));
				dois_pontos = true;
			}
			if(!valor.empty()){
				//cout << "Valor "<<valor << " ";
				//cout << dois_pontos << endl;
				if(dois_pontos){
					linha.substituir_token(valor+string(":"),i);
				}else{
					linha.substituir_token(valor,i);
				}
			}
		}

		if(tokens_linha.size()>1){
			if(tokens_linha[1].get_str()=="EQU"){
				equ = true;
			}else if(tokens_linha.size()>2){
				if(tokens_linha[1].get_str()==":" && tokens_linha[2].get_str()=="EQU"){
					equ = true;
					corretor_posicao++;
				}
			}
		}
		if(equ){
			rotulo = tokens_linha[0].get_str().substr(0,tokens_linha[0].get_str().size()-1);
			//cout << rotulo << endl;
			if(tokens_linha.size() > (2+corretor_posicao)){
				valor = tokens_linha[2+corretor_posicao].get_str();
				//cout << valor << endl;
				tabela_EQU.inserir_equ(rotulo, valor);
			}
		}
	}

	std::string Montador::identificar_rotulo(std::vector<Token> & tokens){
		string rotulo;
		if (tokens[0].verifica_rotulo()) {
			rotulo = tokens[0].get_str().substr(0,tokens[0].get_str().size()-1);
			//tabela_simbolo.inserir_simbolo(rotulo,endereco,false);
			//cout << rotulo<<endl;
		}else if(tokens.size() > 1){
			if(tokens[1].get_str() == string(":")) {
				rotulo = tokens[0].get_str();
				corretor_posicao++;
				//tabela_simbolo.inserir_simbolo(rotulo,endereco,false);
				//cout << rotulo<<endl;
			}else{
				corretor_posicao--;
			}
		}else{
			corretor_posicao--;
		}	
		
		if(!rotulo.empty()){
			int tamanho = rotulo.size();
			if ((rotulo.at(tamanho-1) ==',') || (rotulo.at(0) == '-') || (isdigit(rotulo.at(0))) ||(rotulo == "+")||(rotulo == ","))
				throw invalid_argument("Erro Sintático: Token invalido como label");
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
			linha_processada = true;
			if(!rotulo.empty()){
				tabela_simbolo.inserir_simbolo(rotulo,endereco,false,true,true);
				cout << rotulo << " " << endereco << endl;
			}
			if(modulo && !modulo_aberto)
				throw invalid_argument("Erro Semântico: SECTION apos o END");
			diretiva_section(tokens[2+corretor_posicao].get_str());
		}else if (diretiva == "SPACE"){
			if(!rotulo.empty()){
				tabela_simbolo.inserir_simbolo(rotulo,endereco,false,false,false);
				cout << rotulo << " " << endereco << endl;
			}
			if(modulo && !modulo_aberto)
				throw invalid_argument("Erro Semântico: SPACE apos o END");
			if (!section_data)
				throw invalid_argument("Erro Semântico: Diretiva SPACE na secao errada");
			if (rotulo.empty()){
				throw invalid_argument("Erro Sintático: SPACE nao possui um label antes");
			}
		}else if(diretiva == "CONST"){
			if(!rotulo.empty()){
				tabela_simbolo.inserir_simbolo(rotulo,endereco,false,true,false);
				cout << rotulo << " " << endereco << endl;
			}
			if(modulo && !modulo_aberto)
				throw invalid_argument("Erro Semântico: CONST apos o END");
			if (!section_data)
				throw invalid_argument("Erro Semântico: Diretiva CONST na secao errada");
			if (rotulo.empty()){
				throw invalid_argument("Erro Sintático: CONST nao possui um label antes");
			}
		}else if(diretiva == "BEGIN"){
			linha_processada = true;
			if(!rotulo.empty()){
				tabela_simbolo.inserir_simbolo(rotulo,endereco,false,true,true);
				cout << rotulo << " " << endereco << endl;
			}
			modulo = true;
			if (modulo_aberto)
				throw invalid_argument("Erro Semântico: BEGIN duplicado");
			modulo_aberto = true;
			if (rotulo.empty()){
				throw invalid_argument("Erro Sintático: BEGIN nao possui um label antes");
			}
			if (section_data || section_text)
				throw invalid_argument("Erro Semântico: Diretiva BEGIN deve ficar fora de secao");
		}else if(diretiva == "END"){
			linha_processada = true;
			if(!rotulo.empty()){
				tabela_simbolo.inserir_simbolo(rotulo,endereco,false,true,false);
				cout << rotulo << " " << endereco << endl;
			}
			if (!modulo)
				throw invalid_argument("Erro Semântico: END sem detectar um BEGIN");
			if(!section_text)
				throw invalid_argument("Erro Semântico: END antes da secao TEXT");
			if (!modulo_aberto)
				throw invalid_argument("Erro Semântico: END duplicado");
			modulo_aberto = false;
		}
		else if(diretiva == "PUBLIC"){
			if(!rotulo.empty()){
				tabela_simbolo.inserir_simbolo(rotulo,endereco,false,true,true);
				cout << rotulo << " " << endereco << endl;
			}
			if(modulo && !modulo_aberto)
				throw invalid_argument("Erro Semântico: PUBLIC apos o END");
			if (!modulo)
				throw invalid_argument("Erro Semântico: Diretiva PUBLIC fora de modulo");	
			if(!section_text || section_data)
				throw invalid_argument("Erro Semântico: Diretiva PUBLIC na secao errada");			
		}else if(diretiva == "EXTERN"){
			if(!rotulo.empty()){
				tabela_simbolo.inserir_simbolo(rotulo,0,true,false,true);
				cout << rotulo << " " << endereco << endl;
			}else{
				throw invalid_argument("Erro Sintático: EXTERN sem label");
			}
			if(modulo && !modulo_aberto)
				throw invalid_argument("Erro Semântico: EXTERN apos o END");
			if (!modulo)
				throw invalid_argument("Erro Semântico: Diretiva EXTERN fora de modulo");	
			if(!section_text || section_data)
				throw invalid_argument("Erro Semântico: Diretiva EXTERN na secao errada");	
		}else if(diretiva == "EQU"){
			linha_processada = true;
			if (rotulo.empty()){
				throw invalid_argument("Erro Sintático: EQU nao possui um label antes");
			}
			if (modulo)
				throw invalid_argument("Erro Semântico: Diretiva EQU deve vir antes do inicio do modulo");
			if (section_data || section_text)
				throw invalid_argument("Erro Semântico: Diretiva EQU deve vir antes das secoes");
		}else if(diretiva == "IF"){
			linha_processada = true;

			if(!section_text || section_data)
				throw invalid_argument("Erro Semântico: Diretiva IF na secao errada");	
			string argumento = tokens[2+corretor_posicao].get_str();
			if(argumento == "0"){
				ignorar_linha = true;
			}else if(argumento != "1"){
				throw invalid_argument("Erro sintático: argumento inválido");
			}
			//int n_argumento = atoi(argumento.c_str());
			//cout << "argumento " << n_argumento << endl;
		}
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

	bool Montador::identificar_instrucao(std::vector<Token> & tokens){
		string instrucao = tokens[1+corretor_posicao].get_str();
		if (tabela_instrucao.teste_instrucao(instrucao)){
			return true;
		}else{
			return false;
		}
	}

	void Montador::executar_instrucao(std::vector<Token> & tokens,string rotulo, int & endereco){
		string instrucao = tokens[1+corretor_posicao].get_str();
		if(!rotulo.empty()){
				tabela_simbolo.inserir_simbolo(rotulo,endereco,false,true,true);
				cout << rotulo << " " << endereco << endl;
		}
		if(!section_text || section_data)
			throw invalid_argument("Erro Semântico: "+instrucao+" na secao errada");

		if(instrucao == "STOP")
			existe_stop = true;

		unsigned int num_op = tabela_instrucao.get_operandos(instrucao);
		if(instrucao == "COPY"){
			if(2!=tokens.size()-(2+corretor_posicao) && 3!=tokens.size()-(2+corretor_posicao)){
				throw invalid_argument("Erro Sintático: Número incorreto de argumentos");
			}else if(3==tokens.size()-(2+corretor_posicao) && tokens[3+corretor_posicao].get_str() !=","){
				throw invalid_argument("Erro Sintático: Número incorreto de argumentos");
			}else if(2==tokens.size()-(2+corretor_posicao) && (tokens[2+corretor_posicao].get_str() =="," || tokens[3+corretor_posicao].get_str() ==",")){
				throw invalid_argument("Erro Sintático: Argumento incorreto");
			}
		}else if(instrucao == "JMP" || instrucao == "JMPN" || instrucao == "JMPP" || instrucao == "JMPZ"){
			if(num_op!=tokens.size()-(2+corretor_posicao)){
				throw invalid_argument("Erro Sintático: Número incorreto de argumentos");
			}
		}else{
			//cout << "num op "<< num_op +2 << " OUtro " << (tokens.size()-(2+corretor_posicao)) <<endl;
			if(num_op!=tokens.size()-(2+corretor_posicao) && (num_op+2)!=(tokens.size()-(2+corretor_posicao))){
				throw invalid_argument("Erro Sintático 1: Número incorreto de argumentos");
			}
		}
		endereco += tabela_instrucao.get_tamanho(instrucao);
	}

	void Montador::gerar_erro(const std::invalid_argument& ia,int num_linha){
		stringstream ss;
		ss << num_linha;
		string s_num_linha = ss.str();
		//throw std::invalid_argument(std::string(" Linha ")+s_num_linha+string(": ")+ia.what());		
		std::cout << std::string(" Linha ")+s_num_linha+std::string(": ")+ia.what() << std::endl;
	}

	void Montador::diretiva_section(string argumento){
		if (argumento == "TEXT"){
			if(section_text){
				throw invalid_argument("Erro Semântico: Secao TEXT já existe");
			}
			section_text = true;
			if(section_data){
				throw invalid_argument("Erro Semântico: Secao DATA antes da secao TEXT");
			}
		}else if(argumento == "DATA"){
			if(section_data){
				throw invalid_argument("Erro Semântico: Secao DATA já existe");
			}
			section_data = true;
			if(!section_text){
				throw invalid_argument("Erro Semântico: Secao TEXT nao foi declarada ainda");
			}
		}else{
			throw invalid_argument("Erro Sintático: Secao invalida");
		}
	}
}