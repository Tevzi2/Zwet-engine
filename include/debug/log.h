#pragma once

#include <core.h>
#include <utils.h>

// kalsa uporabljena za logiranje

namespace ZWET
{
    class Log
    {   
        public:
            Log();

            ~Log();

            static UniquePtr<Log> createLogService();

            void info(std::string message);

            void error(std::string message);

            void message(std::string message);

            void warn(std::string message);
    };
}

// logging service
#define ZWET_INFO(args)    ::ZWET::Log::createLogService()->info(args)
#define ZWET_ERROR(args)   ::ZWET::Log::createLogService()->error(args)
#define ZWET_MESSAGE(args) ::ZWET::Log::createLogService()->message(args)
#define ZWET_WARN(args)    ::ZWET::Log::createLogService()->warn(args)