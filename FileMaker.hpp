#pragma once

#include <iostream>
#include <fstream>
#include <string>

class FileMaker
{
private:
    FileMaker();

public:
    std::string _language;
    std::string _datatype;
    std::string _functionname;
    int         _count;

    FileMaker(const char** argv);
    ~FileMaker();

    void get_params(const char** argv);
    int create_file();
    void create_custom(std::ofstream& outputFile);
    void create_main(std::ofstream& outputFile);
};
