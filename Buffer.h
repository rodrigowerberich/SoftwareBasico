#ifndef SB_BUFFER
#define SB_BUFFER

#include <string>
#include <fstream>

namespace Montador {

class Buffer
{
public:
	Buffer(std::string);
	~Buffer();
	std::string proxima_linha();
	bool fim();

private:
	std::ifstream arquivo;
};

} // namespace Montador
#endif /* SB_BUFFER */
