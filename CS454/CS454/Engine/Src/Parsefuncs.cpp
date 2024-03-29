#include "../Include/Util/ParseFuncs.h"
#include <cassert>

#include "../Include/Util/Print.h"
using namespace nlohmann;

std::string conf_file_path;

void set_conf_path(std::string f) {
    std::string conf_file = f + "\\conf\\config.json";
    conf_file_path = conf_file;
}

auto get_json_file() {
    assert(!conf_file_path.empty());
    std::ifstream f(conf_file_path);
    return f;
}

using json_serialized = nlohmann::json_abi_v3_11_2::detail::iteration_proxy
<nlohmann::json_abi_v3_11_2::detail::iter_impl<nlohmann::json_abi_v3_11_2::json>>;

void update_map(std::map<std::string, std::any>& data, json_serialized prop) {
    for (auto it : prop) {
        std::any val;
       
        
        if (it.value().is_number_integer()) {
            val = it.value().get<int>();
        }
        else if (it.value().is_number_float()) {
            val = it.value().get<float>();
        }
        else if (it.value().is_boolean()) {
            val = it.value().get<bool>();
        }
        else if (it.value().is_string()) {
            val = it.value().get<std::string>();
        }
        else if (it.value().is_array()) {
            std::map<std::string, std::any> obj_map;
            update_map(obj_map, it.value().items());
            val = obj_map;
        }
        else if (it.value().is_object()) {
            std::map<std::string, std::any> obj_map;
            update_map(obj_map,it.value().items());
            val = obj_map;
        }
        else { return;  } //epifilaxi
        //std::cout << "key:" << it.key() << "value" << it.value()<<"\n";
        std::pair<std::string, std::any> pair = std::make_pair(it.key(), val);
        data.insert(pair);
    }
}

void parse_test(std::map<std::string, std::any>& data) {
    auto f = get_json_file();
	json js = json::parse(f);

    for (auto prop : js["engine"]["map"].items()) {
        auto ins = js["engine"]["map"][prop.key()].items();
        update_map(data, ins);
    }
    f.close();
}

void parse_layers(std::map<std::string, std::any>& data) {
    auto f = get_json_file();
    json js = json::parse(f);

    size_t idx = 0;
	for(auto ins :js["engine"]["Layers"].items()) {
		if(ins.value().is_array()) {
            update_map(data, ins.value().items());
		}
	}
    
    f.close();
    auto it = data.begin();
}

void parse_render(std::map<std::string, std::any>& data) {
    auto f = get_json_file();
    json js = json::parse(f);

    for (auto prop : js["engine"]["Render"].items()) {
        auto ins = js["engine"]["Render"][prop.key()].items();
        update_map(data, ins);
    }
    f.close(); 
}

void parse_sprites(std::map<std::string, std::any>& data) { //not used but just in case
    auto f = get_json_file();
    json js = json::parse(f);
    for (auto prop : js["engine"]["Sprites"].items()) {
        auto ins = js["engine"]["Sprites"].items();
        update_map(data, ins);
    }

    f.close();
}