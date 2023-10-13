#include "FileMaker.hpp"

//TODOO 
// -language and name can be one arg faster usecase
// -for example ./FileMaker main.cpp || find_x.c ...

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        std::cout << "Invalid args! Example below:" << std::endl;
        std::cout << "./file_maker --language=c --datatype=int --name=main" << std::endl;
        std::cout << "./file_maker --language=cpp --datatype=int --name=test" << std::endl;
        return (1);
    }
    FileMaker A((const char**)(argv + 1));
    if (A._language[0] != 'c')
    {
        std::cout << A._language << " is not handled, quitt programm" << std::endl;
        return (1);
    }
    return (A.create_file());
}

FileMaker::FileMaker(const char** argv)
{
    get_params(argv);
    std::cout << "starting FileMaker..." << std::endl;
}

FileMaker::~FileMaker()
{
    std::cout << "quit FileMaker" << std::endl;
}

void FileMaker::get_params(const char** argv)
{
    int i = 0;
    while (argv[i] != NULL)
    {
        if (std::string(argv[i]).compare(0, 11, "--language=") == 0 && std::string(argv[i]).size() > 11)
            _language = argv[i] + 11;
        else if (std::string(argv[i]).compare(0, 11, "--datatype=") == 0 && std::string(argv[i]).size() > 11)
            _datatype = argv[i] + 11;
        else if (std::string(argv[i]).compare(0, 7, "--name=") == 0 && std::string(argv[i]).size() > 7)
            _functionname = argv[i] + 7;
        else if (std::string(argv[i]).compare(0, 8, "--count=") == 0 && std::string(argv[i]).size() > 8)
            _count = atoi(argv[i] + 8);
        else
            std::cout << "Invalid arg gets ignored:(" << argv[i] << ")" << std::endl;
        i++;
    }
}

int FileMaker::create_file()
{
    std::ofstream outputFile(_functionname + "." + _language);
    if (outputFile.is_open())
    {
        if (_functionname.compare("main") == 0)
            create_main(outputFile);
        else
            create_custom(outputFile);
        outputFile.close();
        std::cout << "File created and written successfully." << std::endl;
    }
    else
    {
        std::cerr << "Unable to create the file. (permissions)" << std::endl;
        return (1);
    }
    return (0);
}

void FileMaker::create_main(std::ofstream& outputFile)
{
    // Generate the main function for the given language
    if (_language == "cpp")
    {
        outputFile << "#include <string>\n\n" << _datatype << " main(int argc, char** argv)\n{\n" << std::endl;
        outputFile << "\treturn (0);\n}" << std::endl;
    }
    else if (_language == "c")
    {
        outputFile << "#include <string.h>\n\n" << _datatype << " main(int argc, char** argv)\n{\n" << std::endl;
        if (_datatype != "void")
        {
            outputFile << "\treturn (0);\n}" << std::endl;
        }
        else
            outputFile << "\n}" << std::endl;     
    }
}

void FileMaker::create_custom(std::ofstream& outputFile)
{
    outputFile << "\n\n" << _datatype << " " << _functionname << "()\n{\n" << std::endl;
    if (_datatype != "void")
    {
        outputFile << "\treturn (0);\n}" << std::endl;
    }
    else
        outputFile << "\n}" << std::endl;  
}