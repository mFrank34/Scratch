/*
 * File: Log
 * Author: Michael Franks 
 * Description: A system body for log, to help with application logging.
 */

#include "Log.h"

#include <chrono>
#include <iostream>

std::string Log::GetTimeStamp()
{
    auto now = std::chrono::system_clock::now();
    auto time = std::chrono::system_clock::to_time_t(now);
    std::tm tm{};

#ifdef _WIN32
    localtime_s(&tm, &time);
#else
    localtime_r(&time, &tm);
#endif
    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y-%m-%d %H-%M-%S");
    return oss.str();
}

void Log::info(std::string message)
{
    std::cout << "[" << GetTimeStamp() << "] " << "[INFO]" << message << std::endl;
}

void Log::warn(std::string message)
{
    std::cout << "[" << GetTimeStamp() << "] " << "[WARN]" << message << std::endl;
}

void Log::error(std::string message)
{
    std::cout << "[" << GetTimeStamp() << "] " << "[ERROR]" << message << std::endl;
}
