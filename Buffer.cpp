#include "Buffer.h"
#include <string>
#include <fstream>
#include <iostream>
#include <stdexcept>

namespace Montador{
	Buffer::Buffer(std::string nome_arquivo){
		arquivo.open((nome_arquivo).c_str());
	}

	Buffer::~Buffer(){
		arquivo.close();
	}

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

	bool Buffer::fim(){
		return arquivo.eof();
	}

}