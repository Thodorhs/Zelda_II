#include "../../../ThirdParty/json.hpp"
#include <map>
#include <iostream>
#include <fstream>
#include <filesystem>

void set_conf_path(std::string f);
void parse_test(std::map<std::string, std::any> &data);
void parse_render(std::map<std::string, std::any>& data);
void parse_layers(std::map<std::string, std::any>& data);