/*
 * File: Text_Document
 * Author: Michael Franks 
 * Description: An object file design to hold information around the text document format.
 */

#ifndef TEXT_DOCUMENT_H
#define TEXT_DOCUMENT_H
#include <string>
#include <vector>

/**
 * text document container for
 * storing information around .txt format
 */
class Text_Document
{
private:
    std::vector<std::string> lines;
    std::string filename;

public:
    /**
     * set up a new file, with a name
     * @param filename location to file and name of it.
     */
    Text_Document(std::string filename);

    ~Text_Document() = default;

    /**
     * allows for the changing of file name
     * @param filename file name to change to or replace
     */
    static void set_filename(std::string filename);

    /**
     * adding lines to the doc type
     * @param line data to be added
     */
    void add_line(std::string line);

    /**
     * edit a line within the file
     * @param index selected line
     * @param line new line to replace
     * @return return the values of that line.
     */
    std::string edit_line(int index, std::string line);

    /**
     * get all lines in current document
     * @return return all data stored in file
     */
    std::vector<std::string> get_all_lines();

    /**
     * selector for lines within the document
     * @param index line to select
     * @return returns the string on that line
     */
    std::string get_line(int index);

    /**
     * get the file name of file
     * @return return file name
     */
    std::string get_filename();
};


#endif // TEXT_DOCUMENT_H
