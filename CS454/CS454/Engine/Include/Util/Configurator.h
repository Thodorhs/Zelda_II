#pragma once
#include <iostream>
#include <map>
#include <any>
#include <functional>

typedef  enum {
	MAP_CONFIG = 0,
	RENDER_CONFIG =1
} configurators_t;

class Configurator {
protected:
	std::map<std::string, std::any>data;
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


#include <assert.h>
class map_config : public Configurator {
private:
	
	Configurator::ParseFunc parser;
public:
	map_config() {};
	void parse_data() override{
		assert(parser);
		parser(this->data);
	}

	std::map<std::string, std::any>& get_data() {
		return this->data;
	}
	std::map<std::string, std::any> get_data_sw() {
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
	Render_config() {};
	void parse_data() override{
		assert(parser);
		parser(this->data);
	}

	std::map<std::string, std::any>& get_data() {
		return this->data;
	}
	std::map<std::string, std::any> get_data_sw() {
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


