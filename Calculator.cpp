// Calculator Tutorial.cpp : This file contains the 'main' function. Program execution begins and ends there.

//Things to do: fix the arrangement of trig functions and log to be normal,
//Add algorithms to work out exact values of Pi and E (will be fun)

#include <iostream>
#include <string>
#include <sstream>
#include <list>
#include <vector>
#include <algorithm>
#include "Calc.h"

using namespace std;

//Tokeniser block
vector<string> tokenize(const string& input)
{
    vector<string> tokens;
    string current;

    for (size_t i = 0; i < input.size(); ++i)
    {
        char c = input[i];

        if (isspace(c)) continue;

        if (isdigit(c) || c == '.')
        {
            current.clear();
            while (i < input.size() && (isdigit(input[i]) || input[i] == '.'))
            {
                current += input[i];
                i++;
            }
            i--;
            tokens.push_back(current);
            continue;
        }

        if (isalpha(c))
        {
            current.clear();
            current += c;
            i++;

            if (current == "p" && i < input.size() && input[i] == 'i')
            {
                current += 'i';
                i++;
                if (i < input.size() && isalpha(input[i]))
                {
                    tokens.push_back(current);
                    i--;
                    continue;
                }
            }
            if (current == "e")
            {
                if (i < input.size() && isalpha(input[i]))
                {
                    tokens.push_back(current);
                    i--;
                    continue;
                }
            }
            while (i < input.size() && isalpha(input[i]))
            {
                current += input[i];
                i++;
            }
            i--;
            tokens.push_back(current);
            continue;
        }
        tokens.push_back(string(1, c));
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
    cout << "Normal maths. Add, subtract, multiply, divide, exponents, percents, roots, factorial, pi, e\n";
    cout << "You can take the previous answer either by just typing the operation if its the first number, or by using n in the second\n\n";
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

            if (first == "pi" || first == "Pi" || first == "PI") parsedX = PI;
            else if (first == "e") parsedX = e;
            else if (first == "n" || first == "N") parsedX = result;
            else
            {
                stringstream ss(first);
                if (!(ss >> parsedX))
                {
                    cout << "\nTHATS NOT HOW IT WORKS\n\n";
                    continue;
                }
            }

            if (second == "pi" || second == "Pi" || second == "PI") parsedY = PI;
            else if (second == "e") parsedY = e;
            else if (second == "n" || second == "N") parsedY = result;
            else
            {
                stringstream ss(second);
                if (!(ss >> parsedY))
                {
                    cout << "\nTHATS NOT HOW IT WORKS\n\n";
                    continue;
                }
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

                if (first == "pi" || first == "Pi" || first == "PI") parsedX = PI;
                else if (first == "e") parsedX = e;
                else if (first == "n" || first == "N") parsedX = result;
                else
                {
                    stringstream ss(first);
                    if (!(ss >> parsedX)) 
                    {
                        cout << "\nTHATS NOT HOW IT WORKS\n\n";
                        continue;
                    }
                }

                x = parsedX;
                oper = parsedOper;
                y = 0.0;
                isonenumber = true;
            }
            else if (first.size() == 1 && find(twonumber.begin(), twonumber.end(), first) != twonumber.end())
            {
                parsedOper = first[0];

                if (second == "pi" || second == "Pi" || second == "PI") parsedY = PI;
                else if (second == "e") parsedY = e;
                else if (second == "n" || second == "N") parsedY = result;
                else
                {
                    stringstream ss(second);
                    if (!(ss >> parsedY))
                    {
                        cout << "\nTHATS NOT HOW IT WORKS\n\n";
                        continue;
                    }
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
        if (!isonenumber && oper == '/' && y == 0)
        {
            cout << "You cant do that. Its undefined you fucking dumbarse\n\n";
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
