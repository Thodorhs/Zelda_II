#include <iostream>
#include <Windows.h>
constexpr auto DEFAULT_WHITE = 0xf;


void inline def()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),DEFAULT_WHITE );
}

void inline pr_info(const std::string& msg) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_GREEN);
	std::cout  << msg << "\n";
	def();
}


void inline pr_warning(const std::string& msg) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE) , FOREGROUND_BLUE);
	std::cout  << msg << "\n";
	def();
}


void inline pr_error(const std::string& msg) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
	std::cout  << msg << "\n";
	def();
}