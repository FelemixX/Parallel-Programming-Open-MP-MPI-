#include <stdio.h> 
#include <omp.h>
//58 номер
// n = 500
long double wallis_product(int count)
{
    long double pi = 1.0;
#pragma omp parallel for
    for (int i = 1; i < count; i++)
    {
        long double num = 4.0 * i * i;
        pi *= num / (num - 1);
        printf_s("\nIteration [%d] || Pi [%f]\n", i, pi);
    }
    return pi * 2;
}

int main() {
    int input_count = 0;
    printf_s("Input iteration count: ");
    scanf_s("%d",&input_count);
    long double result = wallis_product(input_count);
    printf_s("\n\nFINAL ITERATION [%f]", result);
}
