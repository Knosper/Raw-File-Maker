#include "FileMaker.hpp"

static std::string prepare_name(std::string s)
{
    std::string tmp;
    int i = 0;
    int len = s.size();
    while (i < len)
    {
        if (!isalpha(s[i]) && !isdigit(s[i]))
            tmp[i] = toupper(s[i]);
        else
            tmp[i] = s[i];
        i++;
    }
    return (tmp);
}

static int check_str(const std::string s)
{
    int i = 0;
    int len = s.size();
    while (i < len)
    {
        if (!isdigit(s[i]) || i > 2)
            return (1);
        i++;
    }
    return (0);
}

static int handler(int sig)
{
    static int ex;
    if (sig == SIGINT)
        ex = 42;
    return (ex);
}

int main(int argc, char** argv)
{
    FileMaker A;
    signal(SIGINT, (sighandler_t)handler);

    while (1)
    {
        sleep(1);
        if (handler(0) == 42)
            break ;
        if (A.init())
            continue ;
        if (A.create_files())
            continue ;
    }
    return (0);
}

FileMaker::FileMaker()
{
    std::cout << GREEN << "starting FileMaker..." << std::endl;
    std::cout << RESET_COLOR;
}

FileMaker::~FileMaker()
{
    std::cout << RED << "quit FileMaker" << std::endl;
    std::cout << RESET_COLOR;
}

int FileMaker::init()
{
    std::cout << PURPLE << "Which file.extension you want create? (c/cpp/h/hpp)\n\n";
    std::cin >> _language;
    std::cout << RESET_COLOR;
    if (handler(0) == 42)
        return (1);
    if (_language == "c" || _language == "cpp")
    {
        std::cout << GREEN << "Which function_name? (main/new_name/empty)\n\n";
        std::cin >> _function_name;
        std::cout << "Which return type? (int/char/void/???)\n\n";
        std::cin >> _return_type;
        std::cout << RESET_COLOR;
    }
    else if (_language == "hpp" || _language == "h")
    {
        std::cout << BLUE << "Which file/class_name? (Name/A/B/empty)\n\n";
        std::cin >> _function_name;
        std::cout << RESET_COLOR;
    }
    else
    {
        std::cout << RED << "File type not handled: " << _language << std::endl;
        std::cout << RESET_COLOR;
        return (1); 
    }
    std::string tmp;
    std::cout << BOLD_YELLOW << "Create multiple ones? How many?\n\n";
    std::cin >> tmp;
    std::cout << RESET_COLOR;
    if (check_str(tmp))
        _count = atoi(tmp.c_str());
    else
        _count = 1;
    return (0);
}

void FileMaker::create_main(std::ofstream &output)
{
    if (_language == "cpp")
    {
        output << "#include <string>\n\n" << _return_type << " main(int argc, char** argv)\n{\n" << std::endl;
        output << "\treturn (0);\n}" << std::endl;
    }
    else if (_language == "c")
    {
        output << "#include <string.h>\n\n" << _return_type << " main(int argc, char** argv)\n{\n" << std::endl;
        if (_return_type != "void")
        {
            output << "\treturn (0);\n}" << std::endl;
        }
        else
            output << "\n}" << std::endl;
    }
}

void FileMaker::create_custom(std::ofstream &output)
{
    output << "#include <>\n\n" << _return_type << " " << _function_name << "()\n{\n" << std::endl;
    if (_return_type != "void")
    {
        output << "\treturn (0);\n}" << std::endl;
    }
    else
        output << "\n}" << std::endl;
}

int FileMaker::create_cpp_c()
{
    std::ofstream output(_function_name + "." + _language);
    if (output.is_open())
    {
        if (_function_name == "main")
            create_main(output);
        else
            create_custom(output);
        output.close();
        return (0);
    }
    return (1);
}


int FileMaker::create_h()
{
    std::ofstream output(_function_name + "." + _language);
    if (output.is_open())
    {
        std::string capitalized = prepare_name(_language);
        output << "#ifndef " << capitalized << "_H\n" << "# define " << capitalized << "_H\n\n\n" << "#endif";
    }
    return (0);
}

int FileMaker::create_hpp()
{
    return (0);
}

int FileMaker::create_files()
{
    int ret = 0;
    if (_language[0] == 'c')
        ret = create_cpp_c();
    else if (_language == "h")
        ret = create_h();
    else
        ret = create_hpp();
    if (ret == EXIT_SUCCESS)
        std::cout << "File created and written successfully." << std::endl;
    else
        std::cout << "File creation failed." << std::endl;
    return (0);
}
