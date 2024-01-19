#include "../Include/Util/ConfigFuncs.h"
#include "../Include/Util/ParseFuncs.h"

ConfiguratorManager* ConfiguratorManager::singleton;

template<typename Derived_type,typename  Tfunc>
void test_init(ConfiguratorManager* cf,Tfunc &parser,configurators_t type)
{
	
	std::function<void(configurators_t)> init = [&](configurators_t config_type) {
		config_creator<Derived_type, Configurator> my_creator;
		factory<Derived_type, Configurator> my_factory;
		my_factory.register_type(config_type, &my_creator);
		Configurator* obj = my_factory.create(config_type);
		
		cf->register_conf(config_type, obj);
		cf->set_configurator_parser(parser,config_type);
		};
	
	cf->register_init_funcs(init, type);
}

using Parser = Configurator::ParseFunc;

void init_configurators(const std::string& conf_path) {
	set_conf_path(conf_path);
	ConfiguratorManager* cf = ConfiguratorManager::GetInstance();
	Parser map = parse_test;
	Parser ren = parse_render;
	Parser layer = parse_layers;
	Parser sprites = parse_sprites;

	test_init<map_config, Configurator::ParseFunc>(cf,map , configurators_t::MAP_CONFIG);
	test_init<Render_config,Configurator::ParseFunc>(cf, ren, configurators_t::RENDER_CONFIG);
	test_init<Layer_config,Configurator::ParseFunc>(cf, layer, configurators_t::LAYER_CONFIG);
	test_init<Layer_config,Configurator::ParseFunc>(cf, sprites, configurators_t::SPRITE_CONFIG);
	
	cf->initialise();
	cf->parse();
	cf->print_all();
}