#include "Parser.hpp"


/////check path 
//[

bool isAbsolutePath(const char* path)
{
    if (path == NULL) return false;
    return path[0] == '/';
}

string resolvePath(const char* path)
{
    if (isAbsolutePath(path)) 
        return string(path);
    else
    {
        char cwd[1024];
        if (getcwd(cwd, sizeof(cwd)) != NULL)
        {
            string fullPath(cwd);
            fullPath += "/";
            fullPath += path;
            return fullPath;
        } 
        else
        {
            cerr << "Error getting current working directory" << endl;
            exit(1);
        }
    }
}

string checkFileType(const char* path)
{
    struct stat statbuf;
    if (stat(path, &statbuf) != 0) 
        return "Error: Unable to access";
    if (S_ISREG(statbuf.st_mode)) 
        return "regular file";
    else if (S_ISDIR(statbuf.st_mode)) 
        return "directory";
    else if (S_ISCHR(statbuf.st_mode)) 
        return "character device";
    else if (S_ISBLK(statbuf.st_mode))
        return "block device";
    else if (S_ISFIFO(statbuf.st_mode)) 
        return "FIFO (pipe)";
    else if (S_ISLNK(statbuf.st_mode)) 
        return "symbolic link";
    else if (S_ISSOCK(statbuf.st_mode)) 
        return "socket";
    else 
        return "unknown type";
}
/// ]