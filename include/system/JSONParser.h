#ifndef __JSON_PARSER_INCLUDED__
#define __JSON_PARSER_INCLUDED__

#include <string>
#include "Log.h"

namespace id
{
namespace core
{

    struct SaveData
    {
	SaveData() = default;
	SaveData(std::string const&, std::string const&, std::string const&, float, float, float, float, bool);
	~SaveData() = default;

	std::string model_name;
	std::string shader_name;
	std::string texture_path;
	float R = 0.f;
	float G = 0.f;
	float B = 0.f;
	float A = 1.f;
	bool colors_mode = false;
    };

    class JSONParser
    {
        public:
            JSONParser();

            JSONParser(JSONParser const&) = default;
            ~JSONParser() = default;

            JSONParser& operator =(JSONParser const&) = default;

            auto parseData( std::string const& filename,
			    SaveData const& data) -> void;
            
            auto readData(  std::string const& path ) -> SaveData*;

        private:
            id::log::Log log;

    };
} // core::
} // id::

#endif
