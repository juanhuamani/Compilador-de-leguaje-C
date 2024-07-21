#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>

#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_RESET "\x1b[0m"

#ifndef ANALIZADORSINTACTICO_H

size_t current_token = 0;

void error(const std::string &message)
{
    std::cerr << ANSI_COLOR_RED << "Error de sintaxis: " << ANSI_COLOR_RESET << message << std::endl;
    throw std::runtime_error("Error de sintaxis");
}

void parea(const std::string &expected)
{
    if (current_token < tokens.size() && tokens[current_token] == expected)
    {
        ++current_token;
    }
    else
    {
        error("Se esperaba '" + expected + "'");
    }
}

void Factor();
void Term();
void Resto();
void Expr();

void Factor()
{
    if (current_token < tokens.size() && (tokens[current_token] == "NUM" || tokens[current_token] == "ID"))
    {
        std::cout << ANSI_COLOR_GREEN << "ACEPTADO : " << ANSI_COLOR_RESET << tokens[current_token] << std::endl;
        ++current_token;
    }
    else if (current_token < tokens.size() && tokens[current_token] == "ABREPARENTESIS")
    {
        parea("ABREPARENTESIS");
        Expr();
        parea("CIERRAPARENTESIS");
    }
    else
    {
        error("Factor invalido");
    }
}

void Term()
{
    Factor();
    while (current_token < tokens.size() && (tokens[current_token] == "MULTIPLICACION" || tokens[current_token] == "DIVISION"))
    {
        std::cout << ANSI_COLOR_GREEN << "ACEPTADO : " << ANSI_COLOR_RESET << tokens[current_token] << std::endl;
        ++current_token;
        Factor();
    }
}

void Resto()
{
    if (current_token < tokens.size() && (tokens[current_token] == "SUMA" || tokens[current_token] == "RESTA"))
    {
        std::cout << ANSI_COLOR_GREEN << "ACEPTADO : " << ANSI_COLOR_RESET << tokens[current_token] << std::endl;
        ++current_token;
        Term();
        Resto();
    }
}

void Expr()
{
    Term();
    Resto();
}

bool parseTokens(const std::vector<std::string> &input_tokens)
{
    tokens = input_tokens;
    current_token = 0;
    try
    {
        Expr();
        if (current_token == tokens.size())
        {
            return true;
        }
        else
        {
            error("Tokens adicionales después de la expresion");
            return false;
        }
    }
    catch (const std::runtime_error &)
    {
        return false;
    }
}

#endif