#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>

using namespace std;

float f(float x)
{
    return(1 + sin(x) / (1 + cos(x)));
}

float integral(int a, int b, int n) //трапецией
{
        float h, S, x;
        int i;
        h = (b - a) * 1.0 / n;
        S = 0;
#pragma omp parallel
        {
#pragma omp for
            for (i = 0; i < n - 1; i++)
            {
                x = a + i * h;
                S = S + f(x);
            }
            S = h * S;
        }
        return S;
}

void main()
{
    float  y;
    y = integral(1, 5, 10);
    cout << y;
    system("PAUSE");
}
