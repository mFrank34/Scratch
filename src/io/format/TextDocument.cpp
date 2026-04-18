/*
 * File: Text_Document
 * Author: Michael Franks 
 * Description:
 */

#include "TextDocument.h"
#include <utility>


TextDocument::TextDocument(std::string filename)
{
    this->filename = std::move(filename);
}

void TextDocument::set_filename(std::string filename)
{
    filename = std::move(filename);
}

void TextDocument::add_line(std::string data)
{

    lines.push_back(std::move(data));
}

std::string TextDocument::edit_line(const int index, std::string line)
{
    lines.at(index) = std::move(line);
    return get_line(index);
}

std::vector<std::string>& TextDocument::get_all_lines()
{
    return lines;
}

std::string TextDocument::get_line(const int index)
{
    if (index < lines.size())
        return lines.at(index);
    return "";
}

std::string TextDocument::get_filename()
{
    return filename;
}
