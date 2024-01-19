#include "Config_Factory.h"

#include <functional>
#include <vector>
#include <memory>
#include <set>
#include <assert.h>
#include <any>
#define CONFIGS 5

class ConfiguratorManager {
private:
	static ConfiguratorManager* singleton;
	std::map < configurators_t, Configurator*> configurator_map;
	std::function<void(configurators_t)> array[CONFIGS] ;
	~ConfiguratorManager(void) {
		for (auto& val : configurator_map | std::views::values) {
			delete(val);
		}
	}
	ConfiguratorManager(void) = default;
public:
	
	static auto GetInstance(void) -> ConfiguratorManager* { 
		if (singleton == nullptr)
			singleton = new ConfiguratorManager();
		return singleton; 
	
	}
	void initialise(configurators_t en_type) {
		size_t type = static_cast<unsigned>(en_type);
		assert(type <= CONFIGS && type>=0);
		array[type](en_type);
	}


	void initialise(void) {
		for (size_t i = 0; i < CONFIGS; i++) {
			if(array[i]!=nullptr)
				array[i](static_cast<configurators_t>(i));
		}
	}
	
	void register_conf(configurators_t type,Configurator* el ) {
		//std::cout << "configurator of type:" << type << " registered\n";
		//auto ptr = std::unique_ptr<Configurator>(el);
		configurator_map.insert(std::make_pair(type,el));
	}

	template<typename TFunc> void register_init_funcs(TFunc& f, configurators_t en_type) {
		assert(f);
		size_t type = static_cast<unsigned>(en_type);
		assert((size_t)type <= CONFIGS && (size_t)type>=0);
		array[type] = f;
	}
	
	std::map<std::string, std::any >& get_configurator_data_map(configurators_t type) {
		
		assert((size_t)type <= CONFIGS && (size_t)type >= 0);
		return configurator_map[type]->get_data();
	}

	template<typename Type> auto get_configurator_data_field(configurators_t type, std::string find_key)->Type {

		assert((size_t)type <= CONFIGS && (size_t)type >= 0);
		auto map = configurator_map[type]->get_data_sw();
		return std::any_cast<Type>(map.at(find_key));
	}

	template<typename Tfunc> void set_configurator_parser(Tfunc& func, configurators_t type) {
		assert(func);
		configurator_map[type]->set_parser(func);
	}

	void parse(configurators_t type) {
		assert((size_t)type <= CONFIGS && (size_t)type >= 0);
		configurator_map[type]->parse_data();
	}

	void parse()
	{
		for (size_t i = 0; i < CONFIGS; i++) {
			if (configurator_map[static_cast<configurators_t>(i)] != nullptr)
				configurator_map[static_cast<configurators_t>(i)]->parse_data();
				
		}
	}

	void print_all() {
		
	}
};