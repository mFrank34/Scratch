/*
 * File: File_Handler
 * Author: Michael Franks 
 * Description: A system designed to handle different file within memory
 */

#include "IOHandler.h"
#include <fstream>
#include "utils/Log.h"

bool IOHandler::write(TextDocument& data)
{
    std::ofstream file(data.get_filename());

    if (!file.is_open())
    {
        Log::error("Could not open file: " + data.get_filename());
        return false;
    }

    for (auto& line : data.get_all_lines())
    {
        file << line << std::endl;
    }
    file.close();
    return true;
}

TextDocument IOHandler::read(const std::string& path)
{
    std::ifstream ifs(path);
    TextDocument document(path);
    std::string line;

    if (!ifs.is_open())
    {
        Log::error("Couldn't open file: " + path);
        return document;
    }

    while (getline(ifs, line))
        document.add_line(line);

    ifs.close();
    return document;
}
