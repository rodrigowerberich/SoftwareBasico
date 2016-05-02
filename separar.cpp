#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <vector>
#include <stdexcept>

int main() {
    using namespace std;
    string sentence = "And I feel fine...";
    istringstream iss(sentence);
	vector<string> tokens;
	copy(istream_iterator<string>(iss),
	     istream_iterator<string>(),
	     back_inserter(tokens));
	for(int i=0;i<tokens.size();i++){
		cout << tokens[i] << endl;
	}
}