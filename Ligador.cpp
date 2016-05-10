#include "Ligador.h"
#include "SeparadorDeLinhas.h"
#include "Buffer.h"
#include "Token.h"
#include "Linha.h"
#include "Tabelas.h"
#include <string>
#include <stdexcept>
#include <cstdlib>
#include <sstream>
#include <algorithm>

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
		decodificar_tokens(linhas2, tabela_de_uso2, tabela_de_definicao2, relativo2, codigo2);
		gerar_tabela_unificada();
		gerar_codigo_unificado();
		escrever_arquivo();
	}

	void Ligador::obter_tokens(string arquivo,std::vector<Linha> & linhas){
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

	void Ligador::decodificar_tokens(std::vector<Linha> linhas, Tabela_Uso & tabela_de_uso, Tabela_Definicoes & tabela_de_definicao, std::vector<int> & relativo,std::vector<string> & codigo){
		std::vector<Linha>::iterator linha = linhas.begin();
		std::vector<Token> primeira_linha = linha->get_tokens();
		std::vector<Token> t_linha;
		if (primeira_linha.size()!=2){
			throw invalid_argument("Formatacao incorreta de arquivo");
		}
		if(primeira_linha[0].get_str()!="TABLE" || primeira_linha[1].get_str()!="USE"){
			throw invalid_argument("Formatacao incorreta de arquivo");
		}
		// Gerando a tabela de uso
		++linha;
		t_linha = linha->get_tokens();
		if (t_linha.size()!=2)
			throw invalid_argument("Formatacao incorreta de arquivo");
		
		while(t_linha[0].get_str() != "TABLE" && t_linha[1].get_str() != "DEFINITION"){
			tabela_de_uso.inserir_uso(t_linha[0].get_str(),atoi(t_linha[1].get_str().c_str()));
			++linha;
			t_linha = linha->get_tokens();	
			if (t_linha.size()!=2)
				throw invalid_argument("Formatacao incorreta de arquivo");
			if (linha == linhas.end())
				throw invalid_argument("Formatacao incorreta de arquivo");
		}
		// Gerando tabela de definicoes
		++linha;
		t_linha = linha->get_tokens();
		if (t_linha.size()!=2 && t_linha.size()!=1)
			throw invalid_argument("Formatacao incorreta de arquivo");
		
		while(t_linha[0].get_str() != "RELATIVE"){
			if (t_linha.size()!=2)
				throw invalid_argument("Formatacao incorreta de arquivo");
			tabela_de_definicao.inserir_definicao(t_linha[0].get_str(),atoi(t_linha[1].get_str().c_str()));
			++linha;
			t_linha = linha->get_tokens();
			if (t_linha.size()!=2 && t_linha.size()!=1)
				throw invalid_argument("Formatacao incorreta de arquivo");
			if (linha == linhas.end())
				throw invalid_argument("Formatacao incorreta de arquivo");
		}

		// Gerando relativos
		++linha;
		t_linha = linha->get_tokens();
		for(int i=0;i<t_linha.size();i++){
			relativo.push_back(atoi(t_linha[i].get_str().c_str()));
		}
		// Gerando codigo
		++linha;
		t_linha = linha->get_tokens();
		if(t_linha.size()!=1)
			throw invalid_argument("Formatacao incorreta de arquivo");
		if(t_linha[0].get_str()!="CODE")
			throw invalid_argument("Formatacao incorreta de arquivo");
		++linha;
		t_linha = linha->get_tokens();
		for(int i=0;i<t_linha.size();i++){
			codigo.push_back(t_linha[i].get_str());
		}
		++linha;
		if(linha!=linhas.end())
			throw invalid_argument("Formatacao incorreta de arquivo");
	}

	void Ligador::gerar_tabela_unificada(){
		string rotulo = " ",endereco;
		int i = 0;
		while(!rotulo.empty()){
			rotulo = tabela_de_definicao1.get_simbolo_def(i);
			endereco = tabela_de_definicao1.get_endereco_def(i);
			if(!rotulo.empty()){
				tabela_geral_definicao.inserir_definicao(rotulo,atoi(endereco.c_str()));
			}
			i++;
		}
		rotulo = " ";
		i = 0;
		while(!rotulo.empty()){
			rotulo = tabela_de_definicao2.get_simbolo_def(i);
			endereco = tabela_de_definicao2.get_endereco_def(i);
			if(!rotulo.empty()){
				tabela_geral_definicao.inserir_definicao(rotulo,atoi(endereco.c_str())+codigo1.size());
			}
			i++;
		}
	}

	void Ligador::gerar_codigo_unificado(){
		string rotulo = " ",endereco;
		int i, posicao;
		for(i=0;i<codigo1.size();i++)
			cout << codigo1[i] << " ";
		cout << endl;
		i=0;
		while(!rotulo.empty()){
			rotulo = tabela_de_uso1.get_simbolo_uso(i);
			endereco = tabela_de_uso1.get_endereco_uso(i);
			cout << "i="<<i<<endl;
			if(!rotulo.empty()){
				posicao = tabela_geral_definicao.get_endereco_def(rotulo);
				cout <<"Posicao "<< posicao << endl;
				if(posicao>-1){
					stringstream ss;
					ss << posicao+atoi(codigo1[atoi(endereco.c_str())].c_str());
					string s_posicao = ss.str();
					codigo1[atoi(endereco.c_str())] = s_posicao;
				}else
					throw invalid_argument("Erro Semântico: Label "+rotulo+" indefinido");
			}
			i++;
		}
		for(i=0;i<codigo1.size();i++)
			cout << codigo1[i] << " ";
		cout << endl;

		for(i=0;i<codigo2.size();i++)
			cout << codigo2[i] << " ";
		cout << endl;

		for (i=0;i<relativo2.size();i++){
			cout << relativo2[i] << " ";
		}
		cout <<endl;

		i=0;
		rotulo = " ";
		while(!rotulo.empty()){
			rotulo = tabela_de_uso2.get_simbolo_uso(i);
			endereco = tabela_de_uso2.get_endereco_uso(i);
			cout << "i="<<i<<endl;
			if(!rotulo.empty()){
				posicao = tabela_geral_definicao.get_endereco_def(rotulo);
				cout <<"Posicao "<< posicao << endl;
				if(posicao>-1){
					relativo2.erase(std::remove(relativo2.begin(), relativo2.end(), atoi(endereco.c_str())), relativo2.end());
					stringstream ss;
					ss << posicao+atoi(codigo2[atoi(endereco.c_str())].c_str());
					string s_posicao = ss.str();
					codigo2[atoi(endereco.c_str())] = s_posicao;
				}else
					throw invalid_argument("Erro Semântico: Label "+rotulo+" indefinido");
			}
			i++;
		}

		for (i=0;i<relativo2.size();i++){
			cout << relativo2[i] << " ";
		}
		cout <<endl;

		for (i=0;i<relativo2.size();i++){
			stringstream ss;
			ss<< atoi(codigo2[relativo2[i]].c_str()) + codigo1.size();
			codigo2[relativo2[i]] = ss.str();
		}

		for(i=0;i<codigo1.size();i++)
			codigo_geral += codigo1[i] + " ";
		for(i=0;i<codigo2.size();i++)
			codigo_geral += codigo2[i] + " ";
		cout << codigo_geral;

	}

	void Ligador::escrever_arquivo(){
		cout << saida << endl;
		std::ofstream s_arquivo(string(saida+".e").c_str());
		if (s_arquivo.is_open()){
			s_arquivo << codigo_geral << endl;
		}
		s_arquivo.close();
	}

}