#define CH 200
#define SIZE 1000
#include <stdio.h>
#include <cstdlib>
#include <time.h>
#include <iostream>
#include <thread>
#include <omp.h>
using namespace std;

void printMatrix(int** matrix, int size);
void fillMatrix(int** matrix, int size);

int main()
{
    srand(time(0));
    int** matrix;
    matrix = new int* [SIZE];
    for (int i = 0; i < SIZE; i++)
        matrix[i] = new int[SIZE];
    fillMatrix(matrix, SIZE);
    //printMatrix(matrix,SIZE);
#pragma omp parallel shared(matrix) num_threads (2)
    {
#pragma omp for schedule (dynamic, ch)
        for (int i = 0; i < SIZE; i++)
        {
            int sum = 0;
            for (int j = i; j < SIZE; j++)
            {
                sum += matrix[i][j];

            }
            printf("str[%d] sum: %d\n", i, sum);
        }
        return 0;
    }
}

void fillMatrix(int** matrix, int size)
{
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            matrix[i][j] = 0;

    for (int i = 0; i < size; i++)
        for (int j = i; j < size; j++)
            matrix[i][j] = 1;
}

void printMatrix(int** matrix, int size)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            cout << matrix[i][j] << '\t';
        }
        cout << endl;
    }
}