// Calculator Tutorial.cpp : This file contains the 'main' function. Program execution begins and ends there.

//Things to do: fix the arrangement of trig functions and log to be normal,
//Add algorithms to work out exact values of Pi and e
//Fix tokeniser: VERY BROKEN. Subtract and multiply (using x) without spaces including negative numbers and n, in the second slot (without spaces) and pi and e without spaces in the second slot and first slots.

#include <iostream>
#include <string>
#include <sstream>
#include <list>
#include <vector>
#include <algorithm>
#include "Calc.h"

using namespace std;

double parseValue(const string& token, double PI, double e, double lastResult, bool& ok)
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
            while (i < input.size() && (isdigit(input[i]) || input[i] == '.')) {
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
            while (i < input.size() && isalpha(input[i]) && !isOpChar(input[i])) {
                id += input[i++];
            }
            tokens.push_back(id);
            last = VALUE;
            continue;
        }

        if (isdigit(c))
        {
            string num;
            while (i < input.size() && (isdigit(input[i]) || input[i] == '.')) {
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
            while (i < input.size() && isalpha(input[i]) && !isOpChar(input[i])) {
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
    const double PI = 3.14159265358979323846;
    const double e = 2.71828182845904523;
    double x = 0.0;
    double y = 0.0;
    double result = 0.0;
    char oper = '+';
    string input;

    list<string> onenumber = { "!", "s", "c", "t" };
    list<string> twonumber = { "+", "-", "*", "x", "/", "^", "%", "r", "l" };

    cout << "Its Morbin time, and then he morbed all over the place\n\n";
    cout << "Normal maths. Add, subtract, multiply, divide, exponents, percents, roots, factorial, pi, e, and more\n";
    cout << "You can take the previous answer either by typing the operation if its the first number, or by using n in the second\n\n";
    cout << "soz, but trig is backwards (sin(30) is 30s), and log2(8) is 2l8\n\n";
    cout << "Type \"end\" to quit\n\n";

    Calculator c;
    
    while (true)
    {
        cin >> ws;
        getline(cin, input);

        if (input == "end" || input == "End" || input == "END")
        {
            cout << "\nChikin\n";
            break;
        }

        //Tokeniser
        vector<string> tokens = tokenize(input);

        double parsedX = 0.0;
        double parsedY = 0.0;
        char parsedOper = 0;
        bool isonenumber = false;

        if (tokens.size() == 3)
        {
            string first = tokens[0];
            string op = tokens[1];
            string second = tokens[2];

            parsedOper = op[0];

            bool ok1 = false, ok2 = false;
            parsedX = parseValue(first, PI, e, result, ok1);
            parsedY = parseValue(second, PI, e, result, ok2);

            if (!ok1 || !ok2)
            {
                cout << "\nTHATS NOT HOW IT WORKS\n\n";
                continue;
            }

            x = parsedX;
            oper = parsedOper;
            y = parsedY;
            isonenumber = false;
        }

        else if (tokens.size() == 2)
        {
            string first = tokens[0];
            string second = tokens[1];

            if (second.size() == 1 && find(onenumber.begin(), onenumber.end(), second) != onenumber.end())
            {
                parsedOper = second[0];

                bool ok1 = false;
                parsedX = parseValue(first, PI, e, result, ok1);
                if (!ok1)
                {
                    cout << "\nTHATS NOT HOW IT WORKS\n\n";
                    continue;
                }

                x = parsedX;
                oper = parsedOper;
                y = 0.0;
                isonenumber = true;
            }
            else if (first.size() == 1 && find(twonumber.begin(), twonumber.end(), first) != twonumber.end())
            {
                parsedOper = first[0];

                bool ok2 = false;
                parsedY = parseValue(second, PI, e, result, ok2);
                if (!ok2)
                {
                    cout << "\nTHATS NOT HOW IT WORKS\n\n";
                    continue;
                }

                x = result;
                oper = parsedOper;
                y = parsedY;
                isonenumber = false;
            }
            else
            {
                cout << "\nTHATS NOT HOW IT WORKS\n\n";
                continue;
            }
        }
        else if (tokens.size() == 1)
        {
            string op = tokens[0];
            if (op.size() == 1 && find(onenumber.begin(), onenumber.end(), op) != onenumber.end())
            {
                x = result;  
                oper = op[0];
                y = 0.0;
                isonenumber = true;
            }
            else
            {
                cout << "\nTHATS NOT HOW IT WORKS\n\n";
                continue;
            }
        }
        else
        {
            cout << "\nTHATS NOT HOW IT WORKS\n\n";
            continue;
        }

        //Outputs
        if (!isonenumber && oper == '/' && y == 0 || oper == 't' && x == 90)
        {
            cout << "\nYou cant do that. Its undefined you dumbarse\n\n";
            continue;
        }
        if (oper == '!' && x == 0)
        {
            result = 1;
        }
        else
        {
            result = c.Calculate(x, oper, y);
        }
        if (isonenumber)
        {
            if (oper == 's')
            {
                cout << "\n" << "sin(" << x << ") = " << result << "\n\n";
            }
            else if (oper == 'c')
            {
                cout << "\n" << "cos(" << x << ") = " << result << "\n\n";
            }
            else if (oper == 't')
            {
                cout << "\n" << "tan(" << x << ") = " << result << "\n\n";
            }
            else if (oper == '!')
            {
                cout << "\n" << x << oper << " = " << result << "\n\n";
            }
            else
            {
                cout << "\n" << x << " " << oper << " = " << result << "\n\n";
            }
        }
        else if (oper == '%')
        {
            cout << "\n" << x << oper << " of " << y << " = " << result << "\n\n";
        }
        else if (oper == 'l')
        {
            cout << "\n" << "log" << x << "(" << y << ") = " << result << "\n\n";
        }
        else
        {
            cout << "\n" << x << " " << oper << " " << y << " = " << result << "\n\n";
        }
    }
}
