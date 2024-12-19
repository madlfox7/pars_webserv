#include "Parser.hpp"


////////////////////////////////////////////////// parsing server blocks

string find_word_block(const string &content, const string &word, size_t &index)
{
    skip_ws(content, index);
    size_t word_length = word.size();

    if (content.compare(index, word_length, word) == 0)
    {
        index += word_length;
        skip_ws(content, index);

        if (index >= content.size() || content[index] != '{') 
            throw runtime_error("Expected '{' after the word: " + word);
        size_t block_start = ++index; 
        size_t brace_count = 1;
        while (index < content.size() && brace_count > 0)
        {
            if (content[index] == '{') 
                ++brace_count;
            else if (content[index] == '}') 
                --brace_count;
            ++index;
        }
        if (brace_count != 0) 
            throw runtime_error("Missing closing '}' for block starting with word: " + word);
        size_t block_end = index - 1; 
        return content.substr(block_start, block_end - block_start);
    }
    throw runtime_error("Expected block starting with word: " + word);
}


string get_context(const string &content)
{
    size_t index = 0;
    skip_ws(content, index);

    while (index < content.size())
    {
        if (content.compare(index, 6, "server") == 0)
        {
            string directive = find_word_block(content, "server", index);
            if (!directive.empty()) 
                ParseServerBlock(directive);
        } 
        else
        {
            size_t directive_start = index;
            while (index < content.size() && !isspace(content[index]) && content[index] != '{') 
                ++index;
            string unknown_directive = content.substr(directive_start, index - directive_start);
            throw runtime_error("Unknown directive: " + unknown_directive);
        }
        skip_ws(content, index);
    }
    return content;
}

void ParseServerBlock(const string &block)
{
    cout << "!!!!!!!!!!!!!!!!!!!!!!!!!Parsed server block!!!!!!!!!!!!!!!" << block << endl;
}

