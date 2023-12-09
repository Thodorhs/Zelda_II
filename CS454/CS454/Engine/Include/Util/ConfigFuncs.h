#include "../Util/ConfiguratorManager.h"

void init_configurators(std::string conf_path);
template<typename T> auto get_config_value(configurators_t type, std::string key)->T{
	ConfiguratorManager* cf = ConfiguratorManager::GetInstance();
	return cf->get_configurator_data_field<T>(type, key);
}
