/*------------------------------------------------------------------------------------
	Trabalho 1 - Software Básico 01/2016 - Turma B

Nome: 	Letícia Helena Silva Porto 						11/0127846
		Rodrigo Werberich da Silva Moreira de Oliveira 	11/0139411

Nome do arquivo: Buffer.cpp

Descricao: Este arquivo contém a definicao dos métodos da classe Buffer, que abre um ar-
quivo, o mantem aberto para que se possa pegar linha a linha o seu conteúdo.
----------------------------------------------------------------------------------------*/

#include <string>
#include <fstream>
#include <iostream>
#include <stdexcept>

#include "Buffer.h"

namespace Montador{

	/*
	Construtor da classe Buffer
	Abre um arquivo de acordo com uma string fornecida
	*/
	Buffer::Buffer(std::string nome_arquivo){
		arquivo.open((nome_arquivo).c_str());
	}

	/*
	Destrutor da classe Buffer
	Fecha o arquivo aberto pelo construtor
	*/
	Buffer::~Buffer(){
		arquivo.close();
	}

	/*
	Método da classe Buffer
	Fornece a próxima linha do arquivo aberto, verificando se ele está aberto e ainda nao está no fim
	Retorno: A próxima linha disponível no arquivo
	*/
	std::string Buffer::proxima_linha(){
		std::string linha;
		if(arquivo.is_open()){
			if (!arquivo.eof()){
				std::getline(arquivo,linha);
				//std::cout << linha << std::endl;
			}
		}else{
			throw std::runtime_error("Arquivo inexistente!");
		}
		return linha;
	}

	/*
	Método da classe Buffer
	Verifica se o arquivo está no fim
	Retorno: Um booleano indicando se o arquivo está no fim ou nap-
	*/
	bool Buffer::fim(){
		return arquivo.eof();
	}

}