#include "Parser.hpp"


void skip_ws(const string &content, size_t &index)
{
    while (index < content.size() && isspace(content[index])) 
        ++index;
}

