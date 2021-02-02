#pragma once
#include <string>
#include <vector>
#include <regex>

void smmInit();
void smmExit();
std::string smmModPathForCfwPath(std::string path);
std::vector<std::string> get_list_of_subfolders_in_folder(std::string folder_path_);
bool do_path_is_folder(std::string &folder_path_);
bool do_path_is_file(std::string &file_path_);
bool do_path_is_valid(std::string &path_);

