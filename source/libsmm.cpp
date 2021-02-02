#include <libsmm.h>
#include <switch.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <cmath>
#include <sys/stat.h>
#include <dirent.h>
#include <iostream>
#include <fstream>
#include <functional>
#include <iomanip> // stringstream
#include <sstream>
#include <filesystem> // cpp 17 functions -> does not work
#include <exception>
#include <chrono>
void smmInit()
{
    envSetNextLoad("sdmc:/switch/SimpleModManager/SimpleModManager.nro", "sdmc:/switch/SimpleModManager/SimpleModManager.nro");
}
void smmExit()
{
}
std::string smmModPathForCfwPath(std::string path)
{
    std::string result;
    for(std::string ipath : get_list_of_subfolders_in_folder("sdmc:/mods"))
    {
        for(std::string jpath : get_list_of_subfolders_in_folder("sdmc:/mods/" + ipath))
        {
            std::regex target("(sdmc:/atmosphere)+");
            result = ("sdmc:/mods/" + ipath + "/" + jpath + std::regex_replace(path, target, ""));
            if (do_path_is_valid(result))
            {
                return result;
            }
        }
    }
}

std::vector<std::string> get_list_of_subfolders_in_folder(std::string folder_path_) 
{
    std::vector<std::string> subfolders_list;
    if(not do_path_is_folder(folder_path_)) return subfolders_list;
    DIR* directory;
    directory = opendir(folder_path_.c_str()); //Open current-working-directory.
    if( directory == nullptr ) 
    {
        std::cout << "Failed to open directory : " << folder_path_ << std::endl;
        return subfolders_list;
    } 
    else 
    {
        struct dirent* entry;
        while ( (entry = readdir(directory)) ) 
        {
            std::string folder_candidate = folder_path_ + "/" + std::string(entry->d_name);
            if(do_path_is_folder(folder_candidate))
            {
                subfolders_list.emplace_back(entry->d_name);
            }
        }
        closedir(directory);
        return subfolders_list;
    }
    return subfolders_list;
}
bool do_path_is_folder(std::string &folder_path_)
{
    struct stat info{};
    stat( folder_path_.c_str(), &info );
    return bool(S_ISDIR(info.st_mode));
}
bool do_path_is_file(std::string &file_path_) 
{
    if(not do_path_is_valid(file_path_)) return false;
    return (not do_path_is_folder(file_path_));
}
bool do_path_is_valid(std::string &path_)
{
    struct stat buffer{};
    return (stat (path_.c_str(), &buffer) == 0);    
}
