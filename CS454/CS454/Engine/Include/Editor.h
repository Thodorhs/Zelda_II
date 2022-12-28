#pragma once
#include <string>
#include <vector>
#include <sstream>

namespace MapEditor {

	class Editor {
	private:
		std::vector<std::vector<std::string>> content;

	public:

		void update_content(std::vector<std::string> v);
		void parse(const std::string path);
		void print();
	};

}
