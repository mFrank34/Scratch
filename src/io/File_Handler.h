/*
 * File: File_Handler
 * Author: Michael Franks 
 * Description: A system designed to handle different file within memory
 */

#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H

#include "format/Text_Document.h"


/**
 * A system to handle different file types and manage the layers between the IO
 * for application to handle save and writes
 */
class File_Handler
{
private:
    Text_Document current_document;
    Text_Document cached_document;

public:
    File_Handler();
    ~File_Handler() = default;

    int write(std::string location);
    int read(std::string location);
};


#endif // FILE_HANDLER_H
