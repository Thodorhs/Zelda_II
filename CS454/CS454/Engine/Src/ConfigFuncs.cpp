#include "../Include/Util/ConfigFuncs.h";
#include "../Include/Util/ParseFuncs.h";

ConfiguratorManager* ConfiguratorManager::singleton;


void init_map(ConfiguratorManager* cf) {
	std::function<void()> init_map = [&]() {
		config_creator<map_config, Configurator> my_creator;
		factory<map_config, Configurator> my_factory;
		my_factory.register_type(configurators_t::MAP_CONFIG, &my_creator);
		auto obj = my_factory.create(configurators_t::MAP_CONFIG);
		cf->register_conf(configurators_t::MAP_CONFIG, obj);
		cf->set_configurator_parser(parse_test, configurators_t::MAP_CONFIG);
		};


	cf->register_init_funcs(init_map, configurators_t::MAP_CONFIG);
}

void init_render(ConfiguratorManager* cf) {
	
	std::function<void()> init_render = [&]() {
		config_creator<Render_config, Configurator> my_creator;
		factory<Render_config, Configurator> my_factory;
		my_factory.register_type(configurators_t::RENDER_CONFIG , &my_creator);
		auto obj = my_factory.create(configurators_t::RENDER_CONFIG);
		cf->register_conf(configurators_t::RENDER_CONFIG, obj);
		cf->set_configurator_parser(parse_render, configurators_t::RENDER_CONFIG);
		};


	cf->register_init_funcs(init_render, configurators_t::RENDER_CONFIG);
	
}

void init_configurators() {
	ConfiguratorManager* cf = ConfiguratorManager::GetInstance();
	init_render(cf);
	init_map(cf);
	
	cf->initialise();
	cf->parse(configurators_t::RENDER_CONFIG);
	cf->parse(configurators_t::MAP_CONFIG);

	cf->print_all();
}