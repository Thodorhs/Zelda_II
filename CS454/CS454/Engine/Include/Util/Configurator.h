#pragma once
#include <iostream>
#include <map>
#include <any>
#include <functional>
#include <ranges>
#include <assert.h>

typedef  enum class configurators_t {
	MAP_CONFIG = 1,
	RENDER_CONFIG = 2,
	LAYER_CONFIG = 3,
	SPRITE_CONFIG = 4
} ;

typedef std::map<std::string, std::any> Config_data_t;

class Configurator {
protected:
	Config_data_t data;
	public:
	using ParseFunc = std::function<void(std::map < std::string, std::any>&)>;
	virtual void parse_data() = 0;
	virtual void serialize() = 0;
	virtual void init() = 0;
	virtual std::map<std::string, std::any>& get_data() = 0;
	virtual std::map<std::string, std::any> get_data_sw() = 0;
    virtual void set_parser(const ParseFunc& f) = 0;
	virtual void print_data() = 0;

		
};

class map_config : public Configurator {
private:
	
	Configurator::ParseFunc parser;
public:
	map_config() =default;
	void parse_data() override{
		assert(parser);
		parser(this->data);
	}

	std::map<std::string, std::any>& get_data()override {
		return this->data;
	}
	std::map<std::string, std::any> get_data_sw()override {
		return this->data;
	}

	void set_parser(const Configurator::ParseFunc& f) override { parser = f; }

	void serialize() override{}
	void init() override{}

	void print_data() override {
		for (auto it : data) {
			std::cout << "value:" << std::any_cast<int>(it.second);
		}
	}
	
	};


class Render_config : public Configurator {
private:
	
	Configurator::ParseFunc parser;
public:
	Render_config() = default;
	void parse_data() override{
		assert(parser);
		parser(this->data);
	}

	std::map<std::string, std::any>& get_data() override{
		return this->data;
	}
	std::map<std::string, std::any> get_data_sw()override {
		return this->data;
	}

	void set_parser(const Configurator::ParseFunc& f) override { parser = f; }

	void serialize() override{}
	void init() override{}

	void print_data() override {
		for (auto it : data) {
			std::cout << "value:" << std::any_cast<int>(it.second);
		}
	}

	};


class Layer_config : public Configurator {
private:

	Configurator::ParseFunc parser;
public:
	Layer_config() = default;
	void parse_data() override {
		assert(parser);
		parser(this->data);
	}

	std::map<std::string, std::any>& get_data() override{
		return this->data;
	}
	
	std::map<std::string, std::any> get_data_sw()override {
		return this->data;
	}

	void set_parser(const Configurator::ParseFunc& f) override { parser = f; }

	void serialize() override {}
	void init() override {}

	void print_data() override {
		for (auto val : data | std::views::values) {
			std::cout << "value:" << std::any_cast<int>(val);
		}
	}
};


class Sprite_config : public Configurator { //not used but just in case 
private:

	Configurator::ParseFunc parser;
public:
	Sprite_config() = default;
	void parse_data() override {
		assert(parser);
		parser(this->data);
	}

	std::map<std::string, std::any>& get_data() override {
		return this->data;
	}

	std::map<std::string, std::any> get_data_sw()override {
		return this->data;
	}

	void set_parser(const Configurator::ParseFunc& f) override { parser = f; }

	void serialize() override {}
	void init() override {}

	void print_data() override {
		for (auto val : data | std::views::values) {
			std::cout << "value:" << std::any_cast<int>(val);
		}
	}
};