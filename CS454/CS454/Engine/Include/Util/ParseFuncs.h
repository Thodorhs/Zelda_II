#include "../../../ThirdParty/json.hpp"
#include <map>
#include <iostream>
#include <fstream>
#include <filesystem>

void parse_test(std::map<std::string, std::any> &data);
void parse_render(std::map<std::string, std::any>& data);