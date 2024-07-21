#include <stack>
#include <stdexcept>
#include <iostream>
using namespace std;

bool esOperador(const std::string &token)
{
    return token == "+" || token == "-" || token == "*" || token == "/";
}

int precedencia(const std::string &op)
{
    if (op == "+" || op == "-")
        return 1;
    if (op == "*" || op == "/")
        return 2;
    return 0;
}

double aplicarOperador(double a, double b, const std::string &op)
{
    if (op == "+")
        return a + b;
    if (op == "-")
        return a - b;
    if (op == "*")
        return a * b;
    if (op == "/")
    {
        if (b == 0)
        {
            std::cerr << ANSI_COLOR_RED << "Error de semantica: Division por cero" << ANSI_COLOR_RESET << std::endl;
            throw std::runtime_error("Division por cero");
        }
        return a / b;
    }
}

double evaluarExpresion(const std::vector<std::string> &tokens = {"1", "+", "1"})
{
    std::stack<double> valores;
    std::stack<std::string> operadores;

    for (const auto &token : tokens)
    {
        if (std::isdigit(token[0]))
        {
            valores.push(std::stod(token));
        }
        else if (esOperador(token))
        {
            while (!operadores.empty() && precedencia(operadores.top()) >= precedencia(token))
            {
                double b = valores.top();
                valores.pop();
                double a = valores.top();
                valores.pop();
                valores.push(aplicarOperador(a, b, operadores.top()));
                operadores.pop();
            }
            operadores.push(token);
        }
    }

    while (!operadores.empty())
    {
        double b = valores.top();
        valores.pop();
        double a = valores.top();
        valores.pop();
        valores.push(aplicarOperador(a, b, operadores.top()));
        operadores.pop();
    }

    return valores.top();
}

std::string getExpression()
{
    std::ifstream file;
    file.open("file.txt", ios::in);
    std::string expression;
    while (getline(file, expression))
        if (expression.empty())
            continue;
    cout << "Expresion: " << expression << endl;
    file.close();
    return expression;
}

vector<string> getTokens(const string &expression)
{
    std::stringstream ss(expression);
    std::string s;
    std::vector<std::string> tokens;
    while (getline(ss, s, ' '))
        tokens.push_back(s);
    return tokens;
}