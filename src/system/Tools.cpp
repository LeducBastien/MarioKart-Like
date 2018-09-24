#include <string>
#include <vector>
#include <sstream>

#include "Tools.h"

std::vector<std::string> Tools::explodeString(std::string const& str, char delimiter)
{
	std::vector<std::string> string_array;
	std::istringstream iss(str);
	std::string buffer;

	while(std::getline(iss, buffer, delimiter))
	{
		string_array.push_back(buffer);
	}

	return string_array;
}
