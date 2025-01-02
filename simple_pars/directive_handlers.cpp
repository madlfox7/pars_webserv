#include "Parser.hpp"

///location_handlers
void handleAllowMethods(const string& line) 
{
    cout << "Handling 'allow_methods': " << line << endl;
}

void handleReturn(const string& line) 
{
    cout << "Handling 'return': " << line << endl;
}

void handleRoot(const string& line)
 {
    cout << "Handling 'root': " << line << endl;
}

void handleAutoindex(const string& line) 
{
    cout << "Handling 'autoindex': " << line << endl;
}

void handleIndex(const string& line) 
{
    cout << "Handling 'index': " << line << endl;
}

void handleLocation(std::ifstream& file, const string& locationArg, int& serverBlockDepth) 
{
    cout << "Handling 'location': " << locationArg << endl;
    const string locationDirectives[] = 
    {
        "allow_methods", "return", "root", "autoindex", "index"
    };

    std::map<string, void(*)(const string&)> locationDirectiveHandlers;
    locationDirectiveHandlers["allow_methods"] = &handleAllowMethods;
    locationDirectiveHandlers["return"] = &handleReturn;
    locationDirectiveHandlers["root"] = &handleRoot;
    locationDirectiveHandlers["autoindex"] = &handleAutoindex;
    locationDirectiveHandlers["index"] = &handleIndex;

    string innerLine;
    while (std::getline(file, innerLine)) 
    {
        if (innerLine == "}") 
        {
            --serverBlockDepth;
            cout << "End of 'location' block." << endl;
            return;
        }

        std::vector<string> words = splitLine(innerLine);
        if (words.empty())
            continue;

        const string& directive = words[0];
        if (!isAllowedDirective(directive, locationDirectives, sizeof(locationDirectives) / sizeof(locationDirectives[0]))) 
            throw std::runtime_error("Unknown directive in 'location': " + directive);
        std::map<string, void(*)(const string&)>::iterator it = locationDirectiveHandlers.find(directive);
        if (it != locationDirectiveHandlers.end()) 
            it->second(innerLine);
        else 
            cout << "Generic handling for directive '" << directive << "' in 'location' block." << endl;
    }
    throw std::runtime_error("Expected '}' to close 'location' block.");
}

//////server_handlers

void handleListenDirective(const string& line, std::ifstream&, int&) 
{
    cout << "Handling 'listen': " << line << endl;
}

void handleServerNameDirective(const string& line, std::ifstream&, int&) 
{
       cout << "Handling 'server_name': " << line << endl;
}


void handleReturnDirective(const string& line, std::ifstream&, int&) 
{
    cout << "Handling 'return': " << line << std::endl;
}

void handleErrorPageDirective(const string& line, std::ifstream&, int&)
 {
    cout << "Handling 'error_page': " << line << std::endl;
}

void handleClientMaxBodySizeDirective(const string& line, std::ifstream&, int&)
 {
    cout << "Handling 'client_max_body_size': " << line << std::endl;
}

void handleLocationDirective(const string& line, std::ifstream& file, int& serverBlockDepth) 
{
    std::vector<string> words = splitLine(line);
    if (words.size() < 2)
        throw std::runtime_error("Directive 'location' must have an argument.");
    string nextLine;
    if (!std::getline(file, nextLine) || nextLine != "{")
        throw std::runtime_error("Expected '{' after 'location' directive.");
    ++serverBlockDepth;
    handleLocation(file, words[1], serverBlockDepth);
}