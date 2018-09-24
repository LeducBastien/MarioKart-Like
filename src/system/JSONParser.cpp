#include <fstream>
#include <sstream>
#include <cstdlib>
#include "JSONParser.h"

namespace
{
    auto parseString(std::ofstream& file, std::string const& key, std::string const& value, bool isEnd = false) -> void
    {
        file << "\"" << key << "\"" << ": " << "\"" << value << "\"";
        if (!isEnd)
            file << "," << std::endl;
        else
            file << std::endl;
    }

    auto parseFloat(std::ofstream& file, std::string const& key, float value, bool isEnd = false) -> void
    {
        file << "\"" << key << "\"" << ": " << "\"" << value << "\""; 
        if (!isEnd)
            file << "," << std::endl;
        else
            file << std::endl;

    }

    auto parseBool(std::ofstream& file, std::string const& key, bool value, bool isEnd = false) -> void
    {
	file << "\"" << key << "\"" << ": " << "\"" << value << "\"";
        if (!isEnd)
            file << "," << std::endl;
        else
            file << std::endl;
    }

    auto readString(std::ifstream& file) -> std::string
    {
        std::string line, token;
        std::getline(file, line);
        std::stringstream tokenizer(line);

        while(tokenizer >> token)
        {}

        token.erase(0,1);
        token.erase(token.size()-2, token.size()-1);

        return token;
    }

    auto readFloat(std::ifstream& file) -> float
    {
        std::string line, token;
        std::getline(file, line);
        std::stringstream tokenizer(line);

        while(tokenizer >> token)
        {}

        token.erase(0,1);
        token.erase(token.size(), token.size()-1);

        return stof(token);
    }

    auto readBool(std::ifstream& file) -> bool
    {
	std::string line, token;
        std::getline(file, line);
        std::stringstream tokenizer(line);

        while(tokenizer >> token)
        {}

        token.erase(0,1);
        token.erase(token.size(), token.size()-1);

        return atoi(token.c_str());
    }
}

namespace id
{
namespace core
{
    SaveData::SaveData(std::string const& model_name, std::string const& shader_name, std::string const& texture_path, float R, float G, float B, float A, bool colors_mode)
    {
	this->model_name = model_name;
	this->shader_name = shader_name;
	this->texture_path = texture_path;
	this->R = R;
	this->G = G;
	this->B = B;
	this->A = A;
	this->colors_mode = colors_mode;
    }

    JSONParser::JSONParser() 
    {
        log.setIdentifier("JSON Parser");
        log.setOutput(id::log::BOTH);
        log.info("JSON parser has been initialised !");
    }

    auto JSONParser::parseData(std::string const& filename, SaveData const& data) -> void
    {
        log.info("JSON parser trying to parse datas into " + filename + "...");
        std::ofstream file(filename);
        file << "{\n"; 
        
        if (data.shader_name == "")
            log.alert("Trying to parse empty Shader name !");
        if (data.texture_path == "")
            log.alert("Trying to parse empty Texture path !");

	parseString(file, "model", data.model_name);
        parseString(file, "shaderName", data.shader_name);
        parseString(file, "texturePath", data.texture_path);
        parseFloat(file, "R", data.R);
        parseFloat(file, "G", data.G);
        parseFloat(file, "B", data.B);
	parseFloat(file, "A", data.A);
	parseBool(file, "colors_mode", data.colors_mode, true);
        
        file << "}\n"; 
        file.close();


        log.info("Parsed the following data:\n-Shader Name:" + data.shader_name + "\n"
                + "-Texture Path: " + data.texture_path + "\n"
                + "-Red value: " + std::to_string(data.R) + "\n"
                + "-Blue value: " + std::to_string(data.G) + "\n"
                + "-Green value: " + std::to_string(data.B) + "\n"
		+ "-Alpha value: " + std::to_string(data.A) + "\n\n");
        log.info("JSON parser has finished to parse datas into " + filename + " !");
    }

    auto JSONParser::readData(std::string const& path) -> SaveData*
    {
        log.info("JSON parser is reading datas from " + path + "...");

        std::ifstream file(path);
        file.seekg(2, file.beg);

	auto* data = new SaveData();

	data->model_name = readString(file);

        data->shader_name = readString(file);
        if (data->shader_name == "")
            log.alert("Parser has read empty datas for Shader name !");

        data->texture_path = readString(file); 
        if (data->texture_path == "")
            log.alert("Parser has read empty datas for Texture path !");

        data->R = readFloat(file);
        data->G = readFloat(file);
        data->B = readFloat(file);
	data->A = readFloat(file);
	
	data->colors_mode = readBool(file);

        log.info("JSON parser has finished to read datas from " + path + " !");
        log.info("Parsed the following data:\n-Shader Name:" + data->shader_name + "\n"
                + "-Texture Path: " + data->texture_path + "\n"
                + "-Red value: " + std::to_string(data->R) + "\n"
                + "-Blue value: " + std::to_string(data->G) + "\n"
                + "-Green value: " + std::to_string(data->B) + "\n"
		+ "-Alpha value: " + std::to_string(data->A) + "\n\n");

	return data;
    }
}
}
