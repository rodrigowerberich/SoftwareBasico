/*------------------------------------------------------------------------------------
	Trabalho 1 - Software Básico 01/2016 - Turma B

Nome: 	Letícia Helena Silva Porto 						11/0127846
		Rodrigo Werberich da Silva Moreira de Oliveira 	11/0139411

Nome do arquivo: Ligador.cpp

Descricao: Este arquivo contém a definicao dos métodos da classe Ligador, que realiza as 
etapas de ligamento e geracao do arquivo de saida.
----------------------------------------------------------------------------------------*/
#include <string>
#include <stdexcept>
#include <cstdlib>
#include <sstream>
#include <algorithm>

#include "Ligador.h"
#include "SeparadorDeLinhas.h"
#include "Buffer.h"
#include "Token.h"
#include "Linha.h"
#include "Tabelas.h"

using namespace std;

namespace Montador{

	/*
	Construtor da classe Ligador
	Cria um objeto Ligador, armazendo o nome dos arquivos que serao ligados e do arquivo de saída
	*/
	Ligador::Ligador(std::string a1, std::string a2, std::string s){
		arquivo1 = a1;
		arquivo2 = a2;
		saida = s;
	}

	/*
	Método da classe Ligador
	Liga os dois codigos objetos e escreve no arquivo de saida usando os metodos auxiliares 
	da classe
	*/
	void Ligador::ligar(){
		obter_tokens(arquivo1,linhas1);
		obter_tokens(arquivo2,linhas2);
		decodificar_tokens(linhas1, tabela_de_uso1, tabela_de_definicao1, relativo1, codigo1);
		decodificar_tokens(linhas2, tabela_de_uso2, tabela_de_definicao2, relativo2, codigo2);
		gerar_tabela_unificada();
		gerar_codigo_unificado();
		escrever_arquivo();
	}

	/*
	Método da classe Ligador
	Dado um arquivo e um vetor de linhas, esse método converte o texto do arquivo em sua 
	estrutura equivalente de vetor de linhas, cada uma composta por tokens. Para tanto 
	utiliza auxilio das classes Buffer e SeparadorDeLinhas
	Recebe: uma string que indica o arquivo a ser lido e o vetor de linhas de saida
	*/
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
			}
			num_linha++;
		}
	}

	/*
	Método da classe Ligador
	Decodifica os tokens, gerando as tabelas de uso, tabela de definicoes, 
	quais enderecos sao relativos e o codigo em si de um vetor de linhas dado. 
	Caso haja algum erro de formatacao, o programa é fechado durante a execucao.
	Recebe: o vetor de Linha a ser analisado, as tabelas de uso e de definicao, o
	vetor de int, que armazena os enderecos relativos e o vetor de string que ar-
	mazena o código, nos quais as informacoes devem ser salvas
	*/
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

	/*
	Método da classe Ligador
	Gera a tabela de definicao global, corrigindo a posicao dos tokens do se-
	gundo arquivo de acordo com o tamanho do primeiro 
	*/
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

	/*
	Método da classe Ligador
	Gera o codigo final ligado, corrige a posicao dos enderecos relativos de maneira apropriada,
	ger um erro que fecha o programa caso haja algum label indefinido
	*/
	void Ligador::gerar_codigo_unificado(){
		string rotulo = " ",endereco;
		int i=0, posicao;
		while(!rotulo.empty()){
			rotulo = tabela_de_uso1.get_simbolo_uso(i);
			endereco = tabela_de_uso1.get_endereco_uso(i);
			if(!rotulo.empty()){
				posicao = tabela_geral_definicao.get_endereco_def(rotulo);
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
		i=0;
		rotulo = " ";
		while(!rotulo.empty()){
			rotulo = tabela_de_uso2.get_simbolo_uso(i);
			endereco = tabela_de_uso2.get_endereco_uso(i);
			if(!rotulo.empty()){
				posicao = tabela_geral_definicao.get_endereco_def(rotulo);
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
			stringstream ss;
			ss<< atoi(codigo2[relativo2[i]].c_str()) + codigo1.size();
			codigo2[relativo2[i]] = ss.str();
		}

		for(i=0;i<codigo1.size();i++)
			codigo_geral += codigo1[i] + " ";
		for(i=0;i<codigo2.size();i++)
			codigo_geral += codigo2[i] + " ";
	}

	/*
	Método da classe Ligador
	Escreve o resutado final no arquivo de saida
	*/
	void Ligador::escrever_arquivo(){
		std::ofstream s_arquivo(string(saida+".e").c_str());
		if (s_arquivo.is_open()){
			s_arquivo << codigo_geral << endl;
		}
		s_arquivo.close();
	}

}