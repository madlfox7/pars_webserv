#include "Parser.hpp"

void parse_block(const std::string& block, 
                 const std::map<std::string, HandlerFunction>& directive_handlers,
                 const std::vector<std::string>& special_keywords) {
    static int depth = 0; // Static variable to track depth
    cout << std::string(depth * 2, ' ') << "Entering parse_block at depth: " << depth << endl;

    size_t index = 0;
    skip_ws(block, index);

    while (index < block.size()) {
        skip_ws(block, index);
        std::string directive;

        // Extract directive name
        while (index < block.size() && block[index] != ' ' && block[index] != '{' && block[index] != ';') {
            directive += block[index++];
        }

        skip_ws(block, index);

        // Check if the directive is a special keyword
        bool is_special_keyword = false;
        for (std::vector<std::string>::const_iterator it = special_keywords.begin(); it != special_keywords.end(); ++it) {
            if (*it == directive) {
                is_special_keyword = true;
                break;
            }
        }
        if (is_special_keyword)
        {
            // like "location", "if", etc.
            while (index < block.size() && block[index] != '{') {
                index++; // Skip to  '{'
            }

            if (index < block.size() && block[index] == '{') {
                index++; // Skip the '{'
                std::string nested_context;
                extract_context(block, index, nested_context); // Extract nested block
                depth++; // Increment depth for nested call
                parse_block(nested_context, directive_handlers, special_keywords); // Recursively parse nested block
                depth--; // Decrement depth after returning
            }
        } else if (!directive.empty()) {
            // Handle regular directives
            std::string args;
            while (index < block.size() && block[index] != ';' && block[index] != '{') {
                args += block[index++];
            }

            if (block[index] == ';') {
                index++; // Skip the ';'
                std::map<std::string, HandlerFunction>::const_iterator it = directive_handlers.find(directive);
                if (it != directive_handlers.end()) {
                    it->second(args); // Valid directive, call the handler with arguments
                } else {
                    cout << "Unknown directive encountered: " << directive << endl;
                    throw std::runtime_error("Unknown directive: " + directive);
                }
            } else if (block[index] == '{') {
                throw std::runtime_error("Unexpected '{' after directive: " + directive);
            } else {
                throw std::runtime_error("Missing ';' after directive: " + directive);
            }
        } else {
            break;
        }

        skip_ws(block, index);
    }

    cout << std::string(depth * 2, ' ') << "Leaving parse_block from depth: " << depth << endl;
}


void handle_context(const std::string& content,
                    const std::map<std::string, HandlerFunction>& directive_handlers,
                    const std::vector<std::string>& special_keywords) {
    cout << "Handling context: " << endl;
    cout << content << endl;
    cout << "___________" << endl;
    parse_block(content, directive_handlers, special_keywords); 
}
