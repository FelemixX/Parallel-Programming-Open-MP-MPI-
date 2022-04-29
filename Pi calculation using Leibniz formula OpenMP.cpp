#include <math.h>
#include <stdio.h>
#include <omp.h>
#include <iostream>

using namespace std;

void main()
{
	long double seed = 1.; //нижняя дробная часть
	long double pi = 0., pi1, pi2, pi3; 
	double t1, t2, t3;
	t1 = omp_get_wtime();
#pragma omp parallel for
	for (int i = 1000000000; i > 0; i--)
	{
		pi1 = (4 / seed) - (4 / (seed + 2));
		pi2 = (4 / (seed + 4)) - (4 / (seed + 6));
		pi3 = pi1 + pi2;
		pi = pi + pi3;
		seed = seed + 8;
	}
	t2 = omp_get_wtime();
	t3 = t2 - t1;
	long long int seedprint = seed;
	printf_s("Approximate value: %1.64Lf\n", pi);
	printf_s("Last seed was: %lli\n", seedprint);
	printf_s("Calculation time is: %f", t3);
}
