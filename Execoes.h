#ifndef SB_EXECOES
#define SB_EXECOES

#include <string>
#include <>

namespace Montador {

class Exception : public exception
{
public:
  using namespace std;
  Exception(string m="exception!") : msg(m) {}
  ~Exception() throw() {}
  const char* what() const throw() { return msg.c_str(); }

private:
  string msg;
};

} // namespace Montador
#endif /* SB_EXECOES */