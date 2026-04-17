/*
 * File: Text_Document
 * Author: Michael Franks 
 * Description:
 */

#include "Text_Document.h"

#include <utility>


Text_Document::Text_Document(std::string filename)
{
    this->filename = std::move(filename);
}

void Text_Document::set_filename(std::string filename)
{
    filename = std::move(filename);
}

void Text_Document::add_line(std::string line)
{
    lines.push_back(std::move(line));
}

std::string Text_Document::edit_line(const int index, std::string line)
{
    lines.at(index) = std::move(line);
    return get_line(index);
}

std::vector<std::string> Text_Document::get_all_lines()
{
    return lines;
}

std::string Text_Document::get_line(const int index)
{
    if (index < lines.size())
        return lines.at(index);
    return "";
}

std::string Text_Document::get_filename()
{
    return filename;
}
