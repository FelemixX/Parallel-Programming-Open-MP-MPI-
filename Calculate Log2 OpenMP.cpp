#include <stdio.h>
#include <math.h>

void main()
{
	//(-1)^n+1 / n    || n = 1
	double logarithm = 0.;
	int max = 100;
#pragma omp parallel for
	for (int n = 1; n < max; n++)
	{ 
		logarithm = pow(-1, n + 1) / n;
		printf_s("\nIteration [%d] || Logarithm = [%f]\n", n, logarithm);
	}
}
