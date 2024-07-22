#include <iostream>
#include <cctype>
#include <fstream>
#include <cstring>
#include <vector>

#ifndef ANALIZADORLEXICO_H

enum class Token
{
    ID,
    NUM,
    MAYORIGUAL,
    MENORIGUAL,
    IGUAL,
    DOBLEIGUAL,
    WHILE,
    RESERVED,
    ABRELLAVE,
    CIERRALLAVE,
    COMA,
    ABRECORCHETE,
    CIERRACORCHETE,
    ABREPARENTESIS,
    CIERRAPARENTESIS,
    MAYOR,
    MENOR,
    PUNTOYCOMA,
    SUMA,
    RESTA,
    MULTIPLICACION,
    DIVISION,
    EOF_TOKEN,
    UNKNOWN
};

Token scaner();
void mostrar(Token);
void send(Token);
Token espalres();
std::vector<std::string> analizadorLexico();

std::ifstream f;
char lexema[80];
std::vector<std::string> tokens;

std::vector<std::string> analizadorLexico()
{
    Token token;
    f.open("file.txt");
    if (!f.is_open())
    {
        std::cerr << "ERROR (Analisis Lexico) - Abrir el archivo\n";
    }

    while (true)
    {
        token = scaner();
        if (token == Token::EOF_TOKEN)
            break;
        send(token);
    }

    f.close();

    return tokens;
}

Token scaner()
{
    int c;
    int i;
    while (true)
    {
        c = f.get();
        if (c == EOF)
            return Token::EOF_TOKEN;

        if (isspace(c))
            continue;

        if (c == '/')
        {
            c = f.get();
            if (c == '/')
            {
                while (c != '\n' && c != EOF)
                {
                    c = f.get();
                }
                continue;
            }
            else if (c == '*')
            {
                while (true)
                {
                    c = f.get();
                    if (c == EOF)
                        return Token::EOF_TOKEN;
                    if (c == '*')
                    {
                        c = f.get();
                        if (c == '/')
                            break;
                        f.unget();
                    }
                }
                continue;
            }
            f.unget();
            c = '/';
        }
        break;
    }

    // regla del ID
    if (isalpha(c))
    {
        i = 0;
        do
        {
            lexema[i++] = c;
            c = f.get();
        } while (isalnum(c) || c == '_');

        lexema[i] = 0;
        f.unget();
        Token token = espalres();
        if (token != Token::UNKNOWN)
            return token;
        return Token::ID;
    }

    // regla del NUM
    if (isdigit(c))
    {
        i = 0;
        do
        {
            lexema[i++] = c;
            c = f.get();
        } while (isdigit(c));

        lexema[i] = 0;
        f.unget();
        return Token::NUM;
    }

    // reglas de los operadores
    if (c == '+')
        return Token::SUMA;
    if (c == '-')
        return Token::RESTA;
    if (c == '*')
        return Token::MULTIPLICACION;
    if (c == '/')
        return Token::DIVISION;

    // reglas de los delimitadores
    if (c == ';')
        return Token::PUNTOYCOMA;
    if (c == '(')
        return Token::ABREPARENTESIS;
    if (c == ')')
        return Token::CIERRAPARENTESIS;
    if (c == '{')
        return Token::ABRELLAVE;
    if (c == '}')
        return Token::CIERRALLAVE;
    if (c == ',')
        return Token::COMA;
    if (c == '[')
        return Token::ABRECORCHETE;
    if (c == ']')
        return Token::CIERRACORCHETE;

    // reglas de los operadores relacionales
    if (c == '>')
    {
        c = f.get();
        if (c == '=')
        {
            lexema[0] = '>';
            lexema[1] = '=';
            lexema[2] = 0;
            return Token::MAYORIGUAL;
        }
        f.unget();
        return Token::MAYOR;
    }

    if (c == '<')
    {
        c = f.get();
        if (c == '=')
        {
            lexema[0] = '<';
            lexema[1] = '=';
            lexema[2] = 0;
            return Token::MENORIGUAL;
        }
        f.unget();
        return Token::MENOR;
    }

    if (c == '=')
    {
        c = f.get();
        if (c == '=')
        {
            lexema[0] = '=';
            lexema[1] = '=';
            lexema[2] = 0;
            return Token::DOBLEIGUAL;
        }
        f.unget();
        return Token::IGUAL;
    }

    return Token::UNKNOWN;
}

// regla de palabra reservada
Token espalres()
{
    if (strcmp(lexema, "while") == 0)
        return Token::RESERVED;
    if (strcmp(lexema, "if") == 0)
        return Token::RESERVED;
    if (strcmp(lexema, "else") == 0)
        return Token::RESERVED;
    if (strcmp(lexema, "int") == 0)
        return Token::RESERVED;
    if (strcmp(lexema, "float") == 0)
        return Token::RESERVED;
    if (strcmp(lexema, "char") == 0)
        return Token::RESERVED;
    if (strcmp(lexema, "double") == 0)
        return Token::RESERVED;
    if (strcmp(lexema, "void") == 0)
        return Token::RESERVED;
    if (strcmp(lexema, "return") == 0)
        return Token::RESERVED;
    if (strcmp(lexema, "for") == 0)
        return Token::RESERVED;
    if (strcmp(lexema, "do") == 0)
        return Token::RESERVED;
    if (strcmp(lexema, "break") == 0)
        return Token::RESERVED;
    if (strcmp(lexema, "continue") == 0)
        return Token::RESERVED;
    if (strcmp(lexema, "switch") == 0)
        return Token::RESERVED;
    if (strcmp(lexema, "case") == 0)
        return Token::RESERVED;
    if (strcmp(lexema, "default") == 0)
        return Token::RESERVED;
    if (strcmp(lexema, "struct") == 0)
        return Token::RESERVED;
    if (strcmp(lexema, "enum") == 0)
        return Token::RESERVED;
    if (strcmp(lexema, "static") == 0)
        return Token::RESERVED;
    if (strcmp(lexema, "auto") == 0)
        return Token::RESERVED;
    if (strcmp(lexema, "const") == 0)
        return Token::RESERVED;

    return Token::UNKNOWN;
}

void mostrar(Token token)
{
    switch (token)
    {
    case Token::ID:
        std::cout << "token = ID [" << lexema << "] \n";
        break;
    case Token::NUM:
        std::cout << "token = NUM [" << lexema << "] \n";
        break;
    case Token::MAYORIGUAL:
        std::cout << "token = MAYORIGUAL [>=] \n";
        break;
    case Token::RESERVED:
        std::cout << "token = RESERVED [" << lexema << "] \n";
        break;
    case Token::ABRELLAVE:
        std::cout << "token = ABRELAVE [{] \n";
        break;
    case Token::CIERRALLAVE:
        std::cout << "token = CIERRALLAVE [}] \n";
        break;
    case Token::COMA:
        std::cout << "token = COMA [,] \n";
        break;
    case Token::ABRECORCHETE:
        std::cout << "token = ABRECORCHETE [[ \n";
        break;
    case Token::CIERRACORCHETE:
        std::cout << "token = CIERRACORCHETE [] \n";
        break;
    case Token::ABREPARENTESIS:
        std::cout << "token = ABREPARENTESIS [(] \n";
        break;
    case Token::CIERRAPARENTESIS:
        std::cout << "token = CIERRAPARENTESIS [)] \n";
        break;
    case Token::MAYOR:
        std::cout << "token = MAYOR [>] \n";
        break;
    case Token::PUNTOYCOMA:
        std::cout << "token = PUNTOYCOMA [;] \n";
        break;
    case Token::MENOR:
        std::cout << "token = MENOR [<] \n";
        break;
    case Token::MENORIGUAL:
        std::cout << "token = MENORIGUAL [<=] \n";
        break;
    case Token::IGUAL:
        std::cout << "token = IGUAL [=] \n";
        break;
    case Token::DOBLEIGUAL:
        std::cout << "token = DOBLEIGUAL [==] \n";
        break;
    case Token::SUMA:
        std::cout << "token = SUMA [+] \n";
        break;
    case Token::RESTA:
        std::cout << "token = RESTA [-] \n";
        break;
    case Token::MULTIPLICACION:
        std::cout << "token = MULTIPLICACION [*] \n";
        break;
    case Token::DIVISION:
        std::cout << "token = DIVISION [/] \n";
        break;
    case Token::EOF_TOKEN:
        std::cout << "token = EOF \n";
        break;
    default:
        std::cout << "token desconocido \n";
        break;
    }
}

void send(Token token)
{
    switch (token)
    {
    case Token::ID:
        tokens.push_back("ID");
        break;
    case Token::NUM:
        tokens.push_back("NUM");
        break;
    case Token::MAYORIGUAL:
        tokens.push_back("MAYORIGUAL");
        break;
    case Token::RESERVED:
        tokens.push_back("RESERVED");
        break;
    case Token::ABRELLAVE:
        tokens.push_back("ABRELLAVE");
        break;
    case Token::CIERRALLAVE:
        tokens.push_back("CIERRALLAVE");
        break;
    case Token::COMA:
        tokens.push_back("COMA");
        break;
    case Token::ABRECORCHETE:
        tokens.push_back("ABRECORCHETE");
        break;
    case Token::CIERRACORCHETE:
        tokens.push_back("CIERRACORCHETE");
        break;
    case Token::ABREPARENTESIS:
        tokens.push_back("ABREPARENTESIS");
        break;
    case Token::CIERRAPARENTESIS:
        tokens.push_back("CIERRAPARENTESIS");
        break;
    case Token::MAYOR:
        tokens.push_back("MAYOR");
        break;
    case Token::PUNTOYCOMA:
        tokens.push_back("PUNTOYCOMA");
        break;
    case Token::MENOR:
        tokens.push_back("MENOR");
        break;
    case Token::MENORIGUAL:
        tokens.push_back("MENORIGUAL");
        break;
    case Token::IGUAL:
        tokens.push_back("IGUAL");
        break;
    case Token::DOBLEIGUAL:
        tokens.push_back("DOBLEIGUAL");
        break;
    case Token::SUMA:
        tokens.push_back("SUMA");
        break;
    case Token::RESTA:
        tokens.push_back("RESTA");
        break;
    case Token::MULTIPLICACION:
        tokens.push_back("MULTIPLICACION");
        break;
    case Token::DIVISION:
        tokens.push_back("DIVISION");
        break;
    case Token::EOF_TOKEN:
        tokens.push_back("EOF");
        break;
    default:
        tokens.push_back("UNKNOWN");
        break;
    }
}
//sin
#endif // ARBOLLEXICO_H
