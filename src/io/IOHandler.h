/*
 * File: File_Handler
 * Author: Michael Franks 
 * Description: A system designed to handle different file within memory
 */

#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H

#pragma once
#include "format/TextDocument.h"


/**
 * A system to handle different file types and manage the layers between the IO
 * for application to handle save and writes
 */
class IOHandler
{
public:
    /**
     * object recreation for io handler, for reading and writing to files
     */
    IOHandler() = delete;
    ~IOHandler() = default;

    /**
     * A system designed to write to file destination with location of place.
     * @param data the data that needs to be output to physical file.
     * @return statement to know if application successes in writing.
     */
    static bool write(TextDocument &data);

    /**
     * A system designed to read a text file at a set point
     * @param path location to read from.
     * @return data that was locally stored on path.
     */
    static TextDocument read(const std::string& path);
};


#endif // FILE_HANDLER_H
