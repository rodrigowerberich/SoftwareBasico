/*------------------------------------------------------------------------------------
	Trabalho 1 - Software Básico 01/2016 - Turma B

Nome: 	Letícia Helena Silva Porto 						11/0127846
		Rodrigo Werberich da Silva Moreira de Oliveira 	11/0139411

Nome do arquivo: Tabelas.h

Descricao: Esqueleto da classe Montador
----------------------------------------------------------------------------------------*/

#ifndef SB_MONTADOR
#define SB_MONTADOR

#include <string>
#include <vector>

#include "SeparadorDeLinhas.h"
#include "Tabelas_montador.h"
#include "Tabelas.h"
#include "Linha.h"
#include "Token.h"

namespace Montador{

	/* 	Definicao da Classe Montador
		Essa classe possui métodos que realizam o pre processamento, a primeira e a segunda passagem
		no código de entrada e gera o arquivo final de saída.   
	*/
	class Montador
	{
	public:
		//Construtor da classe
		Montador(std::string, std::string);

		// Métodos publicos da classe
		void pre_processamento();
		void primeira_passagem();
		void segunda_passagem();
		void gerar_arquivo();

	private:
		// atributos privados
		// string que contem o nome do arquivo de entrada
		std::string arquivo;
		//string que contem o nome do arquivo de saida
		std::string saida;
		// vetor que armazena as linhas do arquivo de entrada
		std::vector<Linha> linhas;
		// Objeto da classe Tabela_EQU que armazena a tabela de EQUs
		Tabela_EQU tabela_EQU;
		// Objeto da classe Tabela_Simbolos que armazena a tabela de símbolos
		Tabela_Simbolos tabela_simbolo;		
		// Objeto da classe Tabela_Definicoes que armazena a tabela de Definicoes
		Tabela_Definicoes tabela_definicao;	
		// Objeto da classe Tabela_USO que armazena a tabela de uso
		Tabela_Uso tabela_de_uso;
		// Objeto da classe Tabela_Instrucoes que armazena a tabela de instrucoes
		Tabela_Instrucoes tabela_instrucao;
		// Objeto da classe Tabela_Diretivas que armazena a tabela de diretivas
		Tabela_Diretivas tabela_diretiva;
		// bool que vai indicar se o programa dado é um módulo
		bool modulo;
		// bool que vai indicar se, caso seja um módulo, já chegou na diretiva "END"
		bool modulo_aberto;
		// bool que vai indicar se a secao TEXT já foi declarada
		bool section_text;
		// bool que vai indicar se a secao DATA já foi declarada
		bool section_data;
		// bool que indica se a linha que esta sendo processada deve ser ignorada (caso o IF seja falso)
		bool ignorar_linha;
		// bool que indica se existe alguma diretiva STOP no programa
		bool existe_stop;
		// bool que indica se a linha já foi processada para que possa ser removida no vetor de linhas
		bool linha_processada;
		// bool que indica se o rótulo está apontando para uma linha vazia
		bool rotulo_sozinho;
		// bool que indica se há algum erro durante a execucao do programa
		bool erro;
		// string que armazena o rótulo encontrado anteriormente à linha que esta sendo processada
		std::string rotulo_anterior;
		// string onde será escrito o código final do programa em Assembly inventado
		std::string codigo;
		// string onde serao armazenados os a posicao dos enderecos relativos no codigo final
		std::string relativo;
		// corrige a posicao dos tokens da linha que esta sendo processada, devido a possiveis tokens extras
		int corretor_posicao;
		// utilizado para calcular o endereco em que sao usados argumentos do tipo EXTERN
		int endereco_uso; 

		// Métodos privados da classe Montador
		void tratar_EQU(Linha&);
		std::string identificar_rotulo(std::vector<Token> &);
		bool identificar_diretiva(std::vector<Token> &);
		void executar_diretiva(std::vector<Token> &,std::string,int &);
		void diretiva_section(std::string);
		void codificar_diretiva(std::vector<Token> tokens_linha);
		bool identificar_instrucao(std::vector<Token> &);
		void executar_instrucao(std::vector<Token> &,std::string,int &);
		void codificar_instrucao(std::vector<Token> tokens_linha);
		void gerar_erro(const std::invalid_argument&,int);
		std::string gerar_tabela_uso();
		std::string gerar_tabela_definicao();
	};

} // namespace Montador
#endif /* SB_MONTADOR */