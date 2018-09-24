#ifndef __LOG_H_INCLUDED__
#define __LOG_H_INCLUDED__

#include <string>
#include <fstream>

namespace id
{
namespace log
{
    enum LogOutput
    {
        NONE = 0,
        TERMINAL,
        IN_FILE,
        BOTH,
    };

    class Log
    {
        private:
            static std::ofstream fileStream;
            static std::string pathToFile;
            static unsigned int observerCount;
            std::string identifier;
            int output;

        public:
            Log();
            Log(Log const&) = delete;
            ~Log();

            Log& operator =(Log const&) = delete;

            auto info(std::string) -> void;
            auto alert(std::string) -> void;
            auto error(std::string) -> void; 
            auto endLog() -> void;

            auto setOutput(int wantedOutput) -> void;
            auto setIdentifier(std::string id) -> void
            {identifier = id;}
    };
}
}

#endif
