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
	std::function<void()> array[CONFIGS] ;
	~ConfiguratorManager(void) {
		for (auto it : configurator_map) {
			delete(it.second);
		}
	}
	ConfiguratorManager(void) = default;
public:

	

	
	static auto GetInstance(void) -> ConfiguratorManager* { 
		if (singleton == nullptr)
			singleton = new ConfiguratorManager();
		return singleton; 
	
	}
	void initialise(configurators_t type) {
		assert(type <= CONFIGS && type>=0);
		array[type]();
	}


	void initialise(void) {
		for (int i = 0; i < CONFIGS; i++) {
			if(array[i]!=NULL)
				array[i]();
		}
	}
	
	void register_conf(configurators_t type,Configurator* el ) {
		std::cout << "configurator of type:" << type << " registered\n";
		//auto ptr = std::unique_ptr<Configurator>(el);
		configurator_map.insert(std::make_pair(type,el));
	}

	template<typename TFunc> void register_init_funcs(TFunc& f, configurators_t type) { 
		assert(type <= CONFIGS && type>=0);
		array[type] = f; 
		std::cout << "functor configurator of type:" << type << " registered\n";
	}
	
	std::map<std::string, std::any >& get_configurator_data_map(configurators_t type) {
		assert(type <= CONFIGS && type >= 0);
		return configurator_map[type]->get_data();
	}

	template<typename Type> auto get_configurator_data_field(configurators_t type, std::string find_key)->Type {
		assert(type <= CONFIGS && type >= 0);
		auto map = configurator_map[type]->get_data_sw();
		return std::any_cast<Type>(map.at(find_key));

	}

	template<typename Tfunc> void set_configurator_parser(Tfunc& func, configurators_t type) {
		configurator_map[type]->set_parser(func);
	}

	void parse(configurators_t type) {
		assert(type <= CONFIGS && type >= 0);
		configurator_map[type]->parse_data();
	}

	void print_all() {
		
	}

};