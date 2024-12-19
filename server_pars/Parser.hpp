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

//getting content and cleaning up
string get_filename(int argc, char **argv);
string pars_config(int argc, char **argv);
string get_file_content(const char *filename);
string remove_comments(const string &content);


//starting server block parsing
void ParseServerBlock(const string &block);
void skip_ws(const string &content, size_t &index);
string find_word_block(const string &content, const string &word, size_t &index);
string get_context(const string &content);



#endif