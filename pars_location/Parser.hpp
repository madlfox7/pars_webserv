# ifndef PARSER_HPP
# define PARSER_HPP

#include <vector>
#include <iostream>
#include <exception>
#include <fcntl.h>
#include <unistd.h>
#include <cctype>
#include <string>
#include <stdexcept>
#include <fstream>
#include <cstdlib> 
#include <cstring> 
#include <sys/stat.h> 
#include <map>

#define BUFFER_SIZE 1024
#define DEFAULT_FILENAME "default_conf"

using namespace std;

enum FileType
{
    FileType_RegularFile,
    FileType_Directory,
    FileType_CharacterDevice,
    FileType_BlockDevice,
    FileType_FIFO,
    FileType_SymbolicLink,
    FileType_Socket,
    FileType_Unknown,
    FileType_Error
};

//getting and checking file path 
bool isAbsolutePath(const char* path);
string resolvePath(const char* path);
FileType checkFileType(const char* path);

//getting content and cleaning up
string get_filename(int argc, char **argv);
string pars_config(int argc, char **argv);
string get_file_content(const char *filename);
string remove_comments(const string &content);


//starting server block parsing
void skip_ws(const string &content, size_t &index);
string find_word_block(const string &content, const string &word, size_t &index);
string get_context(const string &content);

//directive handlers;

typedef void (*HandlerFunction)(const std::string&);

void extract_context(const string &block, size_t &index, string &context);
typedef void (*HandlerFunction)(const string&);
void ParseServerBlock(const string &block);
void handle_listen(const string &directive);
void handle_server_name(const string &directive);
void handle_root(const string &directive);
void handle_proxy_pass(const string &directive);
void handle_return(const string &directive);
void handle_error_page(const string &directive);
void handle_location(const string &directive);
void handle_if(const string &content);
//void handle_proxy_pass(const std::string& args);
void handle_fastcgi_pass(const std::string& args);
void handle_rewrite(const std::string& args);
//void handle_return(const std::string& args);
void handle_try_files(const std::string& args);
void handle_add_header(const std::string& args);
void handle_expires(const std::string& args);
void handle_limit_rate(const std::string& args);
void handle_client_max_body_size(const std::string& args);
//void handle_error_page(const std::string& args);
void handle_log(const std::string& args); //access_log and error_log


//pars location

void handle_location(const string &content);
void parse_location(const std::string& block);



///generic block

void handle_generic_block(const std::string& content, 
                          const std::map<std::string, HandlerFunction>& directive_handlers,
                          const std::vector<std::string>& special_keywords);

void handle_context(const std::string& content,
                    const std::map<std::string, HandlerFunction>& directive_handlers,
                    const std::vector<std::string>& special_keywords);





                    std::map<std::string, HandlerFunction> setup_location_directives();
std::map<std::string, HandlerFunction> setup_if_directives();
std::vector<std::string> setup_special_keywords();

#endif