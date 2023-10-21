#include "limits.h"
#include "./choose.h"

unsigned long long
gcd(unsigned long long x, unsigned long long y)
{
    while (y != 0)
    {
        unsigned long long t = x % y;
        x = y;
        y = t;
    }
    return x;
}

struct Choose
choose(unsigned long long n, unsigned long long m)
{
    struct Choose nm;
    if (m > n){
        nm.opcode=-2;
        return nm;
    }
    unsigned long long r = 1;
    for (unsigned long long d = 1; d <= m; ++d, --n)
    {
        unsigned long long g = gcd(r, d);
        r /= g;
        unsigned long long t = n / (d / g);
        if (r > (ULLONG_MAX) / t){
            nm.opcode=-1;
           return nm;
        }
        r *= t;
    }
    nm.opcode=0;
    nm.result=r;
    return nm;
}