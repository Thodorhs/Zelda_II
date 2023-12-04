#ifndef PRINT_H
#define PRINT_H
#include <iostream>
#include <Windows.h>
constexpr auto DEFAULT_WHITE = 0xf;
void inline pr_start_msg()
{
    printf(" _____                                                                                           _____ \n");
    printf("( ___ )                                                                                         ( ___ )\n");
    printf(" |   |~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|   |\n");
    printf(" |   |                                                                                           |   |\n");
    printf(" |   |                                                                                           |   |\n");
    printf(" |   |                       _________________   ______  _______                                 |   |\n");
    printf(" |   |                      /                 \\ |      \\/       \\                                |   |\n");
    printf(" |   |                      \\______     ______//          /\\     \\                               |   |\n");
    printf(" |   |                         \\( /    /  )/  /     /\\   / /\\     |                              |   |\n");
    printf(" |   |                          ' |   |   '  /     /\\ \\_/ / /    /|                              |   |\n");
    printf(" |   |                            |   |     |     |  \\|_|/ /    / |                              |   |\n");
    printf(" |   |                           /   //     |     |       |    |  |                              |   |\n");
    printf(" |   |                          /___//      |\\____\\       |____|  /                              |   |\n");
    printf(" |   |                         |`   |       | |    |      |    | /                               |   |\n");
    printf(" |   |                         |____|        \\|____|      |____|/                                |   |\n");
    printf(" |   |                           \\(             \\(          )/                                   |   |\n");
    printf(" |   |                            '              '          '                                    |   |\n");
    printf(" |   |         ______  _____   ______         _____     ____  _____   ______        ______       |   |\n");
    printf(" |   |     ___|\\     \\|\\    \\ |\\     \\    ___|\\    \\   |    ||\\    \\ |\\     \\   ___|\\     \\      |   |\n");
    printf(R"( |   |    |     \     \\     \| \     \  /    /\    \  |    | \    \| \     \ |       \    \     |   |
)");
    printf(" |   |    |     ,_____/|\\|    \\  \\     ||    |  |____| |    |  \\|    \\  \\     ||     ,_____/|    |   |\n");
    printf(" |   |    |     \\--'\\_|/ |     \\  |    ||    |    ____ |    |   |     \\  |    ||     \\--'\\_|/    |   |\n");
    printf(" |   |    |     /___/|   |      \\ |    ||    |   |    ||    |   |      \\ |    ||     /___/|      |   |\n");
    printf(" |   |    |     \\____|\\  |    |\\ \\|    ||    |   |_,  ||    |   |    |\\ \\|    ||     \\____|\\     |   |\n");
    printf(" |   |    |____ '     /| |____||\\_____/||\\ ___\\___/  /||____|   |____||\\_____/||____ '     /|    |   |\n");
    printf(" |   |    |    /_____/ | |    |/ \\|   ||| |   /____ / ||    |   |    |/ \\|   |||    /_____/ |    |   |\n");
    printf(" |   |    |____|     | / |____|   |___|/ \\|___|    | / |____|   |____|   |___|/|____|     | /    |   |\n");
    printf(" |   |      \\( |_____|/    \\(       )/     \\( |____|/    \\(       \\(       )/    \\( |_____|/     |   |\n");
    printf(" |   |       '    )/        '       '       '   )/        '        '       '      '    )/        |   |\n");
    printf(" |   |            '                             '                                      '         |   |\n");
    printf(" |   |                                                                                           |   |\n");
    printf(" |   |                                                                                           |   |\n");
    printf(" |___|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|___|\n");
    printf("(_____)                                                                                         (_____)\n");


}

void inline def()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),DEFAULT_WHITE );
}
template<typename arg>
void  pr_info(const arg msg) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_GREEN);
	std::cout  << msg << "\n";
	def();
}

template<typename arg>
void  pr_warning(const arg msg) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE) , FOREGROUND_BLUE);
	std::cout  << msg << "\n";
	def();
}

template<typename arg>
void pr_error(const arg msg) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
	std::cout  << msg << "\n";
	def();
}

template<typename arg>
void pr_def(const arg msg)
{
	std::cout << msg << "\n";
}
#endif // PRINT_H
