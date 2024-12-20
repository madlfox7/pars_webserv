#include "Parser.hpp"



int main(int argc, char **argv)
{
    try
    {
        string content = pars_config(argc, argv);
        cout << "Parsed content: " << content << endl;
    }
    catch (const std::exception &e)
    {
        cerr << "Failed to parse configuration file." << endl;
        return 1; 
    }
    cout << "Program continues with parsed configuration." << endl;

    //execve part
    return 0; 
}
