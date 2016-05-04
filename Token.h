#ifndef Token_h
#define Token_h

#include <iostream>
#include <stdexcept>
#include <string>

using namespace std;


class Token //recebe uma string e verifica se os tokens dados sao válidos, gera erro caso contrário.
{

public:

	Token(string) throw (invalid_argument);
	string get_str();
	bool verifica_rotulo();
	const bool is_numerico();

protected:
	string my_token;
	bool numerico;
};



#endif