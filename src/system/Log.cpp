#include <sys/stat.h>
#include <ctime>
#include <iostream>
#include <sstream>
#include "Log.h"



namespace id
{
namespace log
{
    unsigned int Log::observerCount = 0;
    std::ofstream Log::fileStream;
    std::string Log::pathToFile;


    Log::Log()
    {
        mkdir("logs/", 0741);
        
        if (++Log::observerCount == 1)
        {
            time_t rawTime;
            struct tm* timeinfo;
            char buffer[20];

            time(&rawTime);
            timeinfo = localtime(&rawTime);
            strftime(buffer, 20, "%a%b%d-%H%M%S", timeinfo);
            
            Log::pathToFile = "logs/";
            Log::pathToFile.append(buffer);
            Log::pathToFile.append(".log");
            Log::fileStream.open(Log::pathToFile, std::ios_base::app);
        }
        identifier = "Anonymous";
    	output = NONE;
     }
/**-----------------------*/    
    auto Log::info(std::string message) -> void
    {
        switch (output)
        {
            case BOTH:
                Log::fileStream << "[INFO](" << identifier << "): " << message << "." << std::endl;
                std::cout << "\033[34m[INFO]\033[39m(" << identifier << "): " << message << "." << std::endl;
                break;

            case TERMINAL:
                std::cout << "\033[34m[INFO]\033[39m(" << identifier << ")]: " << message << ")." << std::endl;
                break;

            case IN_FILE:
                Log::fileStream << "[INFO](" << identifier << "): " << message << "." << std::endl;
                break;

            default:
                break;
        }
    }
/**-----------------------*/
    auto Log::alert(std::string message) -> void
    {
        switch (output)
        {
            case BOTH:
                Log::fileStream << "[ALERT](" << identifier << "): " << message << "." << std::endl;
                std::cout << "\033[33m[ALERT]\033[39m(" << identifier << "): " << message << "." << std::endl;
                break;

            case TERMINAL:
                std::cout << "\033[33m[ALERT]\033[39m(" << identifier << "): " << message << "." << std::endl;
                break;

            case IN_FILE:
                Log::fileStream << "[ALERT](" << identifier << "): " << message << "." << std::endl;
                break;

            default:
                break;
        }

    }
/**-----------------------*/    
    auto Log::error(std::string message) -> void
    {
        switch (output)
        {
            case BOTH:
                Log::fileStream << "[ERROR](" << identifier << "): " << message << "." << std::endl;
                std::cout << "\033[31m[ERROR]\033[39m(" << identifier << "): " << message << "." << std::endl;
                break;

            case TERMINAL:
                std::cout << "\033[31m[ERROR]\033[39m(" << identifier << "): " << message << "." << std::endl;
                break;

            case IN_FILE:
                Log::fileStream << "[ERROR](" << identifier << "): " << message << "." << std::endl;
                break;

            default:
                break;
        }
    }
/**-----------------------*/
    auto Log::setOutput(int wantedOutput) -> void
    {
        if (wantedOutput != output)
            output = wantedOutput;

        if ((output == IN_FILE || output == BOTH) && Log::fileStream.is_open())
        {
            Log::fileStream << "[BEGIN](" << identifier << "): " << Log::pathToFile << " log file opened. Ready to log !\n";
            std::cout << "\033[34m[INFO]\033[39m(" << identifier << "): " << Log::pathToFile << " log file opened. Ready to log !\n";

        }

        if ((output == TERMINAL) && Log::fileStream.is_open())
        {
            std::cout << "\033[34m[INFO]\033[39m(" << identifier << "): Switched to TERMINAL only mode for " << Log::pathToFile << ".\n";
            Log::fileStream << "[INFO](" << identifier << "): Switched to TERMINAL only mode.\n";
        }


    }
/**-----------------------*/
    Log::~Log()
    {
        using namespace std;
        Log::fileStream << "[END](" << identifier << "):\tLog stopped for " << Log::pathToFile << ".\n" << endl;
        std::cout << "\033[35m[END]\033[39m: Stopping log for " << identifier << ".\n"; 

        if (--Log::observerCount == 0)
            Log::fileStream.close();
    }
/**-----------------------*/
} // log::
} // id::

