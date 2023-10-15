#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <signal.h>

const std::string RESET_COLOR = "\033[0m";
const std::string BOLD_YELLOW = "\033[1;33m";
const std::string RED = "\033[1;31m";
const std::string GREEN = "\033[1;32m";  // Added green color
const std::string BLUE = "\033[1;34m";   // Added blue color
const std::string PURPLE = "\033[1;35m";

class FileMaker
{
public:
    std::string _language;
    std::string _return_type;
    std::string _function_name;
    int         _count;

    FileMaker();
    ~FileMaker();

    int init();
    int create_files();
    int create_cpp_c();
    int create_h();
    int create_hpp();
    
    void create_main(std::ofstream &output);
    void create_custom(std::ofstream &output);
};
