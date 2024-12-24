#include "Parser.hpp"


void handle_fastcgi_pass(const string& args) {
    cout << "Handling fastcgi_pass with args: " << args << endl;
}

// Handler for the rewrite directive
void handle_rewrite(const string& args) {
    cout << "rewrite with arguments: " << args << endl;
}

// // Handler for the return directive
// void handle_return(const string& args) {
//     cout << "return with arguments: " << args << endl;
// }

// // Handler for the try_files directive
void handle_try_files(const string& args) {
    cout << "try_files with arguments: " << args << endl;
}

// // Handler for the add_header directive
void handle_add_header(const string& args) {
    cout << "add_header with arguments: " << args << endl;
}

// // Handler for the expires directive
void handle_expires(const string& args) {
    cout << "expires with arguments: " << args << endl;
}

// // Handler for the limit_rate directive
void handle_limit_rate(const string& args) {
    cout << "limit_rate with arguments: " << args << endl;
}

// Handler for the client_max_body_size directive
void handle_client_max_body_size(const string& args) {
    cout << "client_max_body_size with arguments: " << args << endl;
}

// // Handler for the error_page directive
// void handle_error_page(const string& args) {
//     cout << "error_page with arguments: " << args << endl;
// }

// // Handler for the log directive (handles both access_log and error_log)
void handle_log(const string& args)
{
    cout << "log with arguments: " << args << endl;
}

// void parse_location(const string& block) {
//     static int depth = 0; // Static variable to track depth
//     cout << string(depth * 2, ' ') << "Entering parse_location at depth: " << depth << endl;

//     // Define directive handlers using function pointers
//     std::map<string, HandlerFunction> directive_handlers;
//     directive_handlers["proxy_pass"] = handle_proxy_pass;
//     directive_handlers["fastcgi_pass"] = handle_fastcgi_pass;
//     directive_handlers["rewrite"] = handle_rewrite;
//     directive_handlers["return"] = handle_return;
//     directive_handlers["try_files"] = handle_try_files;
//     directive_handlers["add_header"] = handle_add_header;
//     directive_handlers["expires"] = handle_expires;
//     directive_handlers["limit_rate"] = handle_limit_rate;
//     directive_handlers["client_max_body_size"] = handle_client_max_body_size;
//     directive_handlers["error_page"] = handle_error_page;
//     directive_handlers["access_log"] = handle_log;
//     directive_handlers["error_log"] = handle_log;

//     size_t index = 0;
//     skip_ws(block, index);

//     while (index < block.size()) {
//         skip_ws(block, index);
//         string directive;

//         // Extract directive name
//         while (index < block.size() && block[index] != ' ' && block[index] != '{' && block[index] != ';') {
//             directive += block[index++];
//         }

//         skip_ws(block, index);

//         if (directive == "location") {
//             // Extract nested location block
//             while (index < block.size() && block[index] != '{') {
//                 index++; // Skip to the opening '{'
//             }
//             if (index < block.size() && block[index] == '{') {
//                 index++; // Skip the '{'
//                 string nested_context;
//                 extract_context(block, index, nested_context); // Extract nested block
//                 depth++; // Increment depth for nested call
//                 parse_location(nested_context); // Recursively parse nested location block
//                 depth--; // Decrement depth after returning
//             }
//         } else if (!directive.empty()) {
//             // Handle other directives
//             string args;
//             while (index < block.size() && block[index] != ';' && block[index] != '{') {
//                 args += block[index++];
//             }

//             if (block[index] == ';') {
//                 index++; // Skip the ';'
//                 std::map<string, HandlerFunction>::iterator it = directive_handlers.find(directive);
//                 if (it != directive_handlers.end()) {
//                     it->second(args); // Valid directive, call the handler with arguments
//                 } else {
//                     cout << "Unknown directive encountered: " << directive << endl;
//                     throw std::runtime_error("Unknown directive: " + directive);
//                 }
//             } else if (block[index] == '{') {
//                 throw std::runtime_error("Unexpected '{' after directive: " + directive);
//             } else {
//                 throw std::runtime_error("Missing ';' after directive: " + directive);
//             }
//         } else {
//             break;
//         }

//         skip_ws(block, index);
//     }

//     cout << string(depth * 2, ' ') << "Leaving parse_location from depth: " << depth << endl;
// }

void handle_location(const string& content) 
{
    std::map<string, HandlerFunction> directive_handlers = setup_location_directives();
    std::vector<string> special_keywords = setup_special_keywords();
    handle_context(content, directive_handlers, special_keywords);
}

void handle_if(const string& content) 
{
    std::map<string, HandlerFunction> directive_handlers = setup_if_directives();
    std::vector<string> special_keywords = setup_special_keywords();
    handle_context(content, directive_handlers, special_keywords);
}

std::map<string, HandlerFunction> setup_location_directives() 
{
    std::map<string, HandlerFunction> directive_handlers;
    directive_handlers["proxy_pass"] = handle_proxy_pass;
    directive_handlers["fastcgi_pass"] = handle_fastcgi_pass;
    directive_handlers["rewrite"] = handle_rewrite;
    directive_handlers["try_files"] = handle_try_files;
    directive_handlers["add_header"] = handle_add_header;
    directive_handlers["expires"] = handle_expires;
    directive_handlers["limit_rate"] = handle_limit_rate;
    directive_handlers["client_max_body_size"] = handle_client_max_body_size;
    directive_handlers["access_log"] = handle_log;
    directive_handlers["error_log"] = handle_log;
    return directive_handlers;
}

std::map<string, HandlerFunction> setup_if_directives()
{
    std::map<string, HandlerFunction> directive_handlers;
    directive_handlers["return"] = handle_return;
    directive_handlers["rewrite"] = handle_rewrite;
    directive_handlers["proxy_pass"] = handle_proxy_pass;
    directive_handlers["add_header"] = handle_add_header;
    return directive_handlers;
}



std::vector<string> setup_special_keywords()
{
    std::vector<string> special_keywords;
    special_keywords.push_back("location");
    special_keywords.push_back("if");
    return special_keywords;
}
