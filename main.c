#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <stdio.h>
#include <stdlib.h>

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

#include "AnalisadorLexico.h"    
#include "AnalisadorSintactico.h"


int main() {
    system("cls");
    std::vector<std::string>tokens  = analizadorLexico();

    printf( ANSI_COLOR_BLUE "\t\t\t\t\tANALIZADOR LEXICO\n\n" ANSI_COLOR_RESET);

    printf(ANSI_COLOR_MAGENTA "[" ANSI_COLOR_RESET);
    for (size_t i = 0; i < tokens.size(); ++i) {
        printf(ANSI_COLOR_CYAN "%s" ANSI_COLOR_RESET, tokens[i].c_str());
        if (i < tokens.size() - 1) {
            printf(ANSI_COLOR_CYAN ", " ANSI_COLOR_RESET);
        }
    }
    printf(ANSI_COLOR_MAGENTA "]\n\n\n" ANSI_COLOR_RESET);

    printf(ANSI_COLOR_BLUE "\t\t\t\t\tANALIZADOR SINTACTICO\n" ANSI_COLOR_RESET);

    bool success = parseTokens(tokens);
    if (!success) {
        std::cerr << ANSI_COLOR_RED << "\n\nEXPRESION RECHAZADA!" << std::endl;
        return 1;
    }

    std::cout << ANSI_COLOR_GREEN << "\n\nEXPRESION ACEPTADA!" << std::endl;
    return 0;
}


