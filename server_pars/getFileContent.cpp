#include "Parser.hpp"


string get_filename(int argc, char **argv)
{
    if (argc > 2)
        throw std::exception();
    if (argc < 2)
        return DEFAULT_FILENAME; 
    return argv[1];
}

string pars_config(int argc, char **argv)
{
    try
    {
        string filename = get_filename(argc, argv); 
        string content = get_file_content(filename.c_str()); 
        content = remove_comments(content); 
        get_context(content);
        return content;
    }
    catch (const std::runtime_error &e)
    {
        cerr << e.what() << endl;
        throw; 
    }
    catch (const std::exception &e)
    {
        cerr << "Error: An unexpected exception occurred." << endl;
        throw; 
    }
}

string get_file_content(const char *filename)
{
    int fd = open(filename, O_RDONLY);
    if (fd < 0)
    {
        throw std::runtime_error("Error: Unable to open file.");
    }
    char buffer[BUFFER_SIZE];
    ssize_t bytesRead;
    string fileContent;
    while ((bytesRead = read(fd, buffer, BUFFER_SIZE)) > 0)
    {
        for (ssize_t i = 0; i < bytesRead; ++i)
        {
            if (!std::isspace(buffer[i]))
            {
                fileContent.append(buffer, bytesRead);
                break;
            }
        }
    }
    close(fd);
    if (bytesRead < 0)
        throw std::runtime_error("Error: Failed to read from file.");
    if (fileContent.empty())
        throw std::runtime_error("Error: Configuration file is empty or contains only whitespace.");
    return fileContent;
}

string remove_comments(const string &content)
{
    string result;
    bool in_comment = false;
    for (size_t i = 0; i < content.size(); ++i)
    {
        if (!in_comment && content[i] == '#') 
            in_comment = true;
        else if (in_comment && content[i] == '\n') 
            in_comment = false;
        else if (!in_comment)
            result += content[i];
    }
    return result;
}