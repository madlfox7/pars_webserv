# ifndef PARSER_HPP
# define PARSER_HPP


#include <iostream>
#include <exception>
#include <fcntl.h>
#include <unistd.h>
#include <cctype>
#include <string>
#include <stdexcept>

#define BUFFER_SIZE 1024
#define DEFAULT_FILENAME "default_conf"

using namespace std;


string get_filename(int argc, char **argv);
string pars_config(int argc, char **argv);
string get_file_content(const char *filename);
string remove_comments(const string &content);



#endif