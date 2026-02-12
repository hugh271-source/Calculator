#include "Calc.h"

double fakefabs(double v)
{
    return v < 0.0 ? -v : v;
}

//factorial stuff
double factodoobydoo(double x)
{
    if (x < 0.0)
        return 0.0;

    int n = (int)x;

    if (n == 0 || n == 1)
        return 1.0;

    double result = 1.0;
    for (int i = 2; i <= n; ++i)
        result *= i;

    return result;
}
//Square stuff
double exponentwentowent(double x)
{
    double expsum = 1.0;
    double expterm = 1.0;

    for (int n = 1; n < 40; ++n)
    {
        expterm *= x / (double)n;
        expsum += expterm;

        if (fakefabs(expterm) < 1e-10)
            break;
    }

    return expsum;
}

double doobiedoobiedoo(double x)
{
    if (x <= 0.0)
        return 0.0;

    double lntry = 1.0;

    for (int i = 0; i < 30; ++i)
    {
        double eguess = exponentwentowent(lntry);
        lntry = lntry - 1.0 + x / eguess;
    }

    return lntry;
}

double sqrthing(double a, double b)
{
    if (a < 0.0)
    {
        a *= -1;
        double lnpart = doobiedoobiedoo(a);
        double expart = b * lnpart;
        return exponentwentowent(expart);
    }
    else if (b == 0)
        return 1;
    else
    {
        double lnpart = doobiedoobiedoo(a);
        double expart = b * lnpart;
        return exponentwentowent(expart);
    }
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

double eulerboiler()
{
    double sum = 1.0;
    double term = 1.0;
    for (int n = 1; n < 100; ++n)
    {
        term /= (double)n;
        sum += term;
        if (fakefabs(term) < 1e-10)
            break;
    }
    return sum;
}

//double arctanwithoutaplan(double x)
//{
//    double term = x;
//    double sum = term;
//    double x2 = x * x;
//    const double reso = 1e-12;
//
//    for (int n = 1; n < 200; ++n)
//    {
//        term *= -x2;
//        double add = term / (2 * n + 1);
//        sum += add;
//
//        if (fakefabs(add) < reso)
//            break;
//    }
//
//    return sum;
//}
//double piinafly()
//{
//    double a = arctanwithoutaplan(1.0 / 5.0);
//    double b = arctanwithoutaplan(1.0 / 239.0);
//
//    return 16.0 * a - 4.0 * b;
//}


double piinafly()
{
    double sum = 0.0;
    int terms = 10;

    for (int k = 0; k < terms; ++k)
    {
        double fourk = factodoobydoo(4 * k);
        double kfact = factodoobydoo(k);

        double kfact4 = kfact * kfact * kfact * kfact;

        double pow396 = sqrthing(396, 4 * k);

        double num = fourk * (1103 + 26390 * k);
        double den = kfact4 * pow396;

        sum += num / den;
    }

    double sqrt2 = rootintootin(2, 2);

    double invpi = (2 * sqrt2 / 9801) * sum;
    return 1 / invpi;
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
        if (fakefabs(logadd) < 1e-10)
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


//Trig stuff
double sineywiney(double x)
{
    double rad = x * piinafly() / 180.0;
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
    double rad = x * piinafly() / 180.0;
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

    if (fakefabs(c) < 1e-12)
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
    case 'l': // logarithms
        return logybogy(x, y);
    }
}