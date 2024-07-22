#include <stack>
#include <stdexcept>
#include <iostream>
#include <vector>
#include <sstream>
#include <string>

using namespace std;

bool esOperador(const string &token)
{
    return token == "+" || token == "-" || token == "*" || token == "/";
}

int precedencia(const string &op)
{
    if (op == "+" || op == "-")
        return 1;
    if (op == "*" || op == "/")
        return 2;
    return 0;
}

double aplicarOperador(double a, double b, const string &op)
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
            cerr << "Error de semántica: División por cero" << endl;
            throw runtime_error("División por cero");
        }
        return a / b;
    }
    throw invalid_argument("Operador desconocido");
}

double evaluarExpresion(const vector<string> &tokens)
{
    stack<double> valores;
    stack<string> operadores;

    for (const auto &token : tokens)
    {
        if (isdigit(token[0]))
        {
            valores.push(stod(token));
        }
        else if (esOperador(token))
        {
            while (!operadores.empty() && operadores.top() != "(" && precedencia(operadores.top()) >= precedencia(token))
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
        else if (token == "(")
        {
            operadores.push(token);
        }
        else if (token == ")")
        {
            while (!operadores.empty() && operadores.top() != "(")
            {
                double b = valores.top();
                valores.pop();
                double a = valores.top();
                valores.pop();
                valores.push(aplicarOperador(a, b, operadores.top()));
                operadores.pop();
            }
            operadores.pop(); // Eliminar el '(' de la pila
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

vector<string> getTokens(const string &expression)
{
    stringstream ss(expression);
    string s;
    vector<string> tokens;
    while (ss >> s)
        tokens.push_back(s);
    return tokens;
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