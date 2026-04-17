/*
 * File: logger
 * Author: Michael Franks 
 * Description: A system design for making custom application logging
 */

#ifndef LOG_H
#define LOG_H

#pragma once
#include <string>

/**
 * A system to help with creating application logging information
 */
class Log
{
private:
    /**
     * get the current time for log message
     * @return return current time as string
     */
    static std::string GetTimeStamp();

public:
    /**
     * Prevent the US from creating multiple instances of log
     */
    Log() = delete;

    /**
     * Logging information
     * @param message message for console
     */
    static void info(std::string message);

    /**
     * Logging warning
     * @param message message for console
     */
    static void warn(std::string message);

    /**
     * Logging error
     * @param message message for console
     */
    static void error(std::string message);
};
#endif // LOG_H
