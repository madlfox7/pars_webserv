#include "Parser.hpp"

void handle_listen(const string &directive)
{
    (void) directive;
    //cout << "Handling listen directive: |||||||" << directive <<"||||||" << endl;
}

void handle_server_name(const string &directive)
{
      (void) directive;
   // cout << "Handling server name directive: |||||||" << directive <<"||||||" << endl;
}

void handle_root(const string &directive)
{
      (void) directive;
 //   cout << "Handling root directive: |||||||||" << directive <<"||||||" << endl;
}

void handle_proxy_pass(const string &directive)
{
      (void) directive;
    //cout << "Handling proxy pass directive: |||||" << directive <<"||||||" << endl;
}

void handle_return(const string &directive)
{
      (void) directive;
    //cout << "Handling return directive: |||||||" << directive <<"||||||" << endl;
}

void handle_error_page(const string &directive)
{
      (void) directive;
   // cout << "Handling error page directive: ||||||||" << directive <<"||||||" << endl;
}


// void handle_if(const string &content)
// {
//     (void) content;
//    // cout << "Handling if context: ||||||||" << content <<"||||||" << endl;
// }



void extract_context(const string &block, size_t &index, string &context)
{
    int brace_count = 1;
    index++;
    size_t start = index;

    while (index < block.size() && brace_count > 0)
    {
        if (block[index] == '{') 
            brace_count++;
        else if (block[index] == '}') 
            brace_count--;
        index++;
    }
    if (brace_count == 0) 
        context = block.substr(start, index - start - 1);
    else 
    {
        cout << "Error: Mismatched braces in the configuration." << endl;
        context = "";
    }
    cout << "\nBBBBBB" <<context<<endl;
}



void ParseServerBlock(const string &block)
{
    size_t index = 0;
    map<string, HandlerFunction> directive_handlers;
    directive_handlers["listen"] = handle_listen;
    directive_handlers["server_name"] = handle_server_name;
    directive_handlers["root"] = handle_root;
    directive_handlers["proxy_pass"] = handle_proxy_pass;
    directive_handlers["return"] = handle_return;
    directive_handlers["error_page"] = handle_error_page;

    while (index < block.size())
    {
        skip_ws(block, index);
        string directive;
        while (index < block.size() && block[index] != ' ' && block[index] != '{' && block[index] != ';') 
             directive += block[index++];
        skip_ws(block, index);
        if (directive == "location")
        {
            // Skip location path, later I'll save it somewhere
            while (index < block.size() && block[index] != '{') 
                index++;  
            string context;
            extract_context(block, index, context);
            handle_location(context);
        } 
        else if (directive == "if")
        {
            //(condition) arg part to be implemented???
            string context;
            extract_context(block, index, context);
            handle_if(context);
        } 
        else 
        {
            string args;
            while (index < block.size() && block[index] != ';') 
                args += block[index++];
            index++; 
            map<string, HandlerFunction>::iterator it = directive_handlers.find(directive);
            if (it != directive_handlers.end()) 
                it->second(args);
            else 
            {
              //  cout << "Unknown directive: " << directive << endl;
                throw std::runtime_error("Unknown directive");
            }
        }
        skip_ws(block, index);
    }
}