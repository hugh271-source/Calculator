#include "Calc.h"

const double PI = 3.14159265358979323846;

//Square stuff
double sqrthing(double base, int exp)
{
    double result = 1.0;
    for (int i = 0; i < exp; i++)
        result *= base;
    return result;
}

//Root stuff
double rootintootin(double x, double y)
{
    double rtlow = 0.0;
    double rthigh = (y >= 1) ? y : 1.0;
    double rtreso = 1e-5;

    while (rthigh - rtlow > rtreso)
    {
        double rtmid = (rtlow + rthigh) / 2.0;

        if (sqrthing(rtmid, (int)x) > y)
            rthigh = rtmid;
        else
            rtlow = rtmid;
    }

    return (rtlow + rthigh) / 2.0;
}


double fakefabs(double v)
{
    return v < 0.0 ? -v : v;
}

//Log stuff
double logthingy(double a)
{
    if (a <= 0.0)
        return 0.0;

    double logz = (a - 1.0) / (a + 1.0);
    double logzthesequel = logz * logz;
    double logterm = logz;
    double logsum = logterm;

    for (int k = 1; k < 100; ++k)
    {
        logterm *= logzthesequel;
        double logadd = logterm / (double)(2 * k + 1);
        logsum += logadd;
        if (fakefabs(logadd) < 1e-15)
            break;
    }

    return 2.0 * logsum;
}
double logybogy(double x, double y)
{
    if (x <= 0.0 || x == 1.0 || y <= 0.0)
        return 0.0;

    double logy = logthingy(y);
    double logx = logthingy(x);

    if (logx == 0.0)
        return 0.0;

    return logy / logx;
}


//factorial stuff
double factodoobydoo(double x)
{
    double facto = x - 1;
    while (facto > 1)
    {
        x *= facto;
        facto -= 1;
    }
    return x;
}

//Trig stuff
double sineywiney(double x)
{
    double rad = x * PI / 180.0;
    double sinthing = rad;
    double sinsum = sinthing;
    const double sinreso = 1e-12;

    for (int n = 1; n < 30; ++n)
    {
        sinthing *= -(rad * rad) / ((2.0 * n) * (2.0 * n + 1.0));
        sinsum += sinthing;
        if (fakefabs(sinthing) < sinreso)
            break;
    }

    return sinsum;
}
double cosywosy(double x)
{
    double rad = x * PI / 180.0;
    double costhing = 1.0;
    double cossum = costhing;
    const double cosreso = 1e-12;

    for (int n = 1; n < 30; ++n)
    {
        costhing *= -(rad * rad) / ((2.0 * n - 1.0) * (2.0 * n));
        cossum += costhing;
        if (fakefabs(costhing) < cosreso)
            break;
    }

    return cossum;
}
double tanybany(double x)
{
    double s = sineywiney(x);
    double c = cosywosy(x);

    if (fakefabs(c) < 1e-15)
        return (c >= 0.0) ? 1e308 : -1e308;

    return s / c;
}


double Calculator::Calculate(double x, char oper, double y)

{
    switch (oper)
    {
    case '+': // add
        return x + y;
    case '-': // minus
        return x - y;
    case '*': // multiply
    case 'x':
        return x * y;
    case '/': // divide
        return x / y;
    case '^': // to the power of
        return sqrthing(x, y);
    case 'r': // root
        return rootintootin(x, y);
    case '%': // percent of
        return x / 100.0 * y;
    case '!': // factorial
        return factodoobydoo(x);
    case 's': // sin 
        return sineywiney(x);
    case 'c': // cos 
        return cosywosy(x);
    case 't': // tan 
        return tanybany(x);
    case 'l':
        return logybogy(x, y);
    }
}