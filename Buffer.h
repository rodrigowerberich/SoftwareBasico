/*------------------------------------------------------------------------------------
	Trabalho 1 - Software Básico 01/2016 - Turma B

Nome: 	Letícia Helena Silva Porto 						11/0127846
		Rodrigo Werberich da Silva Moreira de Oliveira 	11/0139411

Nome do arquivo: Buffer.h

Descricao: Esqueleto da classe Buffer, que abre um arquivo, o mantem aberto para que se 
possa pegar linha a linha o seu conteúdo.
----------------------------------------------------------------------------------------*/

#ifndef SB_BUFFER
#define SB_BUFFER

#include <string>
#include <fstream>

namespace Montador {
	
	/*
	Classe Buffer
	Abre um arquivo, o mantem aberto para que se possa pegar linha a linha o seu conteúdo.
	*/
	class Buffer
	{
	public:
		// Métodos da classe
		Buffer(std::string);
		~Buffer();
		std::string proxima_linha();
		bool fim();

	private:
		// O arquivo que vai ser usado
		std::ifstream arquivo;
	};

} // namespace Montador
#endif /* SB_BUFFER */
