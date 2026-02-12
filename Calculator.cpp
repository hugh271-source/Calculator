// Calculator Tutorial.cpp : This file contains the 'main' function. Program execution begins and ends there.

//Things to do: fix the arrangement of trig functions and log to be normal,
//Add more than two number ability. things to work out. dooododododo


#include <iostream>
#include <string>
#include <sstream>
#include <list>
#include <vector>
#include <algorithm>
#include <map>
#include "Calc.h"
#include "RPN.h"
#include "AST.h"
#include "ASTBuilder.h"
#include "ASTEval.h"


using namespace std;

double parseValue(const string& token,
    double PI, double e, double lastResult,
    const map<string, double>& vars,
    bool& ok)

{
    ok = true;
    if (token.empty()) 
    {
        ok = false;
        return 0.0;
    }

    bool neg = false;
    string t = token;

    if (t[0] == '-') 
    {
        neg = true;
        t = t.substr(1);
        if (t.empty()) 
        {
            ok = false;
            return 0.0;
        }
    }

    double value = 0.0;

    if (t == "pi" || t == "Pi" || t == "PI") 
    {
        value = PI;
    }
    else if (t == "e")
    {
        value = e;
    }
    else if (t == "n" || t == "N")
    {
        value = lastResult;
    }
    else if (vars.count(t))
    {
        value = vars.at(t);
    }
    else
    {
        stringstream ss(t);
        if (!(ss >> value)) 
        {
            ok = false;
            return 0.0;
        }
    }

    if (neg) value = -value;
    return value;
}

//Tokeniser block
vector<string> tokenize(const string& input)
{
    vector<string> tokens;
    size_t i = 0;

    enum LastType { NONE, VALUE, OP };
    LastType last = NONE;

    auto isOpChar = [](char c) {
        return c == '+' || c == '-' || c == '*' || c == 'x' || c == '/' ||
            c == '^' || c == '%' || c == 'r' || c == 'l';
        };

    while (i < input.size())
    {
        char c = input[i];

        if (isspace(c)) {
            i++;
            continue;
        }

        bool canUnaryMinus = (c == '-' &&
            (last == NONE || last == OP) &&
            i + 1 < input.size());

        if (canUnaryMinus && isdigit(input[i + 1]))
        {
            string num = "-";
            i++;
            while (i < input.size() && (isdigit(input[i]) || input[i] == '.')) 
            {
                num += input[i++];
            }
            tokens.push_back(num);
            last = VALUE;
            continue;
        }

 
        if (canUnaryMinus && isalpha(input[i + 1]))
        {
            string id = "-";
            i++;
            while (i < input.size() && (isalnum(input[i])) && !isOpChar(input[i])) 
            {
                id += input[i++];
            }
            tokens.push_back(id);
            last = VALUE;
            continue;
        }


        if (isdigit(c))
        {
            string num;
            while (i < input.size() && (isdigit(input[i]) || input[i] == '.'))
            {
                num += input[i++];
            }
            tokens.push_back(num);
            last = VALUE;
            continue;
        }

        if (isOpChar(c))
        {
            tokens.push_back(string(1, c));
            i++;
            last = OP;
            continue;
        }

        if (isalpha(c))
        {
            string id;
            while (i < input.size() && isalpha(input[i]) && !isOpChar(input[i]))
            {
                id += input[i++];
            }
            tokens.push_back(id);
            last = VALUE;
            continue;
        }

        tokens.push_back(string(1, c));
        i++;
        last = OP;
    }

    return tokens;
}

//Main
int main()
{
    const double PI = piinafly();
    const double e = eulerboiler();
    double x = 0.0;
    double y = 0.0;
    double result = 0.0;
    char oper = '+';
    string input;

    list<string> onenumber = { "!", "s", "c", "t" };
    list<string> twonumber = { "+", "-", "*", "x", "/", "^", "%", "r", "l" };

    cout << "Its Morbin time, and then he morbed all over the place\n\n";
    cout << "Normal maths. Add, subtract, multiply, divide, exponents, percents, roots, factorial, pi, e, assign variable values and more\n";
    cout << "You can take the previous answer either by typing the operation if its the first number, or by using n in the second\n\n";
    cout << "soz, but trig is backwards (sin(30) is 30s), and log2(8) is 2l8\n\n";
    cout << "Type \"end\" to quit,\n\n";

    Calculator c;
    map<string, double> vars;


    while (true)
    {
        cin >> ws;
        getline(cin, input);

        if (input == "end" || input == "End" || input == "END")
        {
            cout << "\nChikin\n";
            break;
        }

        // Tokeniser
        // Tokeniser
        vector<string> tokens = tokenize(input);

        try
        {
            // 1) convert to RPN
            vector<string> rpn = ReversedPoland(tokens);

            // 2) build AST
            ASTNode* root = AbstractTree(rpn);

            // 3) evaluate AST
            double newResult = RealAbstractTree(root, c, PI, e, result, vars);

            // 4) update last result
            result = newResult;

            cout << "\n" << input << " = " << result << "\n\n";

        }
        catch (const std::exception& ex)
        {
            cout << "\nTHATS NOT HOW IT WORKS (" << ex.what() << ")\n\n";
        }
    }
}