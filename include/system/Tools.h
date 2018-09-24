#ifndef __TOOLS_H_INCLUDED__
#define __TOOLS_H_INCLUDED__

#include <string>
#include <vector>

class Tools
{
public:
	Tools() = default;
	~Tools() = default;

	static auto explodeString(std::string const&, char) -> std::vector<std::string>;
private:
};

#endif
