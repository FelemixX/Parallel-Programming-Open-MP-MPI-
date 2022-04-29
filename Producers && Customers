#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#define jobs 1000
#define sz 102000

#if defined(_WIN32) && defined(_MSC_VER)
#include <windows.h>
double abtic() {
    __int64 freq;
    __int64 clock;
    QueryPerformanceFrequency((LARGE_INTEGER*)&freq);
    QueryPerformanceCounter((LARGE_INTEGER*)&clock);
    return (double)clock / freq * 1000 * 1000;
}
#else
#include <time.h>
#include <sys/time.h>
double abtic() {
    double result = 0.0;
    struct timeval tv;
    gettimeofday(&tv, NULL);
    result = tv.tv_sec * 1000 * 1000 + tv.tv_usec;
    return result;
}
#endif /* _WIN32 */

#if 1
double timer;
#define ABTMS timer=abtic();fprintf(stdout,"%4d  ",__LINE__)
#define ABTME fprintf(stdout,"%4d  %8.8fms\n",__LINE__,(abtic()-timer)/1000.0f)
#else
#define ABTMS
#define ABTME
#endif

int main()
{
    char* jbNotReady;
    double* a;
    double* as;
    double* pa;
    int j, k;
    char jbnr;

    a = (double*)malloc(sz * jobs * sizeof(double));
    as = (double*)malloc(jobs * sizeof(double));
    jbNotReady = (char*)malloc(jobs * sizeof(char));

    for (j = 0; j < jobs; j++)
    {
        jbNotReady[j] = 1;

    }
    memset(a, 0, sz * jobs * sizeof(double));
    memset(as, 0, jobs * sizeof(double));
    ABTMS;
#pragma omp parallel sections private(j,k,pa) shared(jbNotReady,as,a)
    {
        // producer
#pragma omp section
        {
            for (j = 0; j < jobs; j++)
            {
                pa = a + j * sz;
                for (k = 0; k < sz; k++)
                {
                    pa[k] = 1.0;
                }
                jbNotReady[j] = 0;
#pragma omp flush
            }
        }
        // consumer
#pragma omp section
        {
            for (j = 0; j < jobs; j++)
            {
#pragma omp flush
                while (jbNotReady[j]) {
#pragma omp flush
                }
                as[j] = 0.0;
                pa = a + j * sz;
                for (k = 0; k < sz; k++)
                {
                    as[j] += pa[k];
                }
                if ((int)(as[j]) != sz)fprintf(stdout, "job id %3d :%f\n", j, as[j]);
            }
        }
    }
    ABTME;
    free(a);
    free(as);
    free(jbNotReady);
    return 0;
}
