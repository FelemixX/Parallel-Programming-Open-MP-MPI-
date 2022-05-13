#include "mpi.h"
#include <stdio.h>
#include <iostream>

using namespace std;

void main()
{	
	int myRank, numProcess, number;//process id,quantity of processes
	int arr[] = { -20, 88, 81, -3, 81, 61, 43, 93, -95, 75, 40, 13 };
	float number1, number2, number3;
	float arr1[] = {4.85, 4.36, 0.20, 2.13 ,4.9 ,-0.72 ,3.33 ,4.14 ,2.66 ,-2.36 ,0.07 ,0.09 };

	MPI_Init(NULL, NULL); //начало куска кода, который будет исполняться параллельно
	MPI_Comm_size(MPI_COMM_WORLD, &numProcess); //объявляем функцию, чтобы знать, сколько потоков у нас есть
	MPI_Comm_rank(MPI_COMM_WORLD, &myRank); //объявляем функцию, которая дает номер потока
	 //ДЕСЯТОЕ ЗАДАНИЕ
	if (myRank % 2 != 0 && myRank != 0) //нечетное
	{
		float max = arr1[0];
		for (int i = 0; i < myRank; i++)
		{
			if (max < arr1[i])
				max = arr1[i];
		}
		printf("[%d]:\t%f\n MAX", myRank, max);
	}
	
	else if (myRank % 2 == 0) //четный
	{
		int min = arr[0];
		for (int i = 0; i < myRank; i++)
		{
			if (arr[i] < min)
				min = arr[i];
		}
		printf("[%d]:\t%d\n MIN", myRank, min);
	} 
	
	/* ДЕВЯТОЕ ЗАДАНИЕ
	if (myRank % 2 == 0 && myRank != 0)
	{
		for (int i = 0; i < myRank; i++)
		{
			number1 += arr1[myRank];
		}
		printf("[%d]:\t%d\n", myRank, number1);
	}
	else if (myRank % 2 != 0 && myRank != 0)
	{
		for (int i = 0; i < myRank; i++)
		{
			number2 += arr1[myRank];
		}
		number2 = number2 / 12;
		printf("[%d]:\t%d\n", myRank, number2);
	}

	else if (myRank == 0)
	{
		for (int i = 0; i < myRank; i++)
		{
			number3 *= arr1[myRank];
		}
		printf("[%d]:\t%d\n", myRank, number3);
	} */

	/* ВОСЬМОЕ ЗАДАНИЕ
	if (myRank % 2 == 0 && arr1[myRank] > 0)
	{
		for (int i = 0; i < myRank; i++)
		{
			number1 += arr1[myRank];
		}
		printf("[%d]:\t%d\n", myRank, number1);
	}
	else
	{
		for (int i = 0; i < myRank; i++)
		{
			number2 += arr1[myRank];
		}
		number2 = number2 / 12;
		printf("[%d]:\t%d\n", myRank, number2);
	}
	*/
	/* СЕДЬМОЕ ЗАДАНИЕ 
	if (myRank % 2 == 0)
	{
		for (int i = 0; i < myRank; i++)
		{
			number1 += arr1[myRank];
		}
		printf("[%d]:\t%d\n", myRank, number1);
	}
	*/
	/* ШЕСТОЕ ЗАДАНИЕ
	if (myRank % 2 == 0 && myRank != 0)
	{
		number = arr[myRank] * 2;
		printf("[%d]:\t%d\n", myRank, number);
	}
	else if (myRank % 2 != 0 && myRank != 0)
	{
		number1 = arr1[myRank] * 2;
		printf("[%d]:\t%d\n", myRank, number1);
	}
	*/

	/* ПЯТОЕ ЗАДАНИЕ
	if (myRank % 2 == 0)
	{
		number = arr[myRank] * 2;
		printf("[%d]:\t%d\n", myRank, number);
	}
	else if (myRank % 2 != 0)
	{
		number1 = arr1[myRank] * 2;
		printf("[%d]:\t%d\n", myRank, number1);
	}
	*/
	/* ЧЕТВЕРТОЕ ЗАДАНИЕ 
	if (myRank % 2 == 0)
	{
		number = arr[myRank] * 2;
		printf("[%d]:\t%d\n", myRank, number);
	}
	*/
	/* ТРЕТЬЕ ЗАДАНИЕ 
	if (myRank == 0)
	{
		number = arr1[myRank] * -1;
		printf("[%d]:\t%d\n", myRank, number1);
	}
	else if (myRank != 0)
	{
		printf("\n[%d]\n", myRank);
	}
	*/
	/* ВТОРОЕ ЗАДАНИЕ
	if (myRank == 0)
	{
		printf("\n[%d]\n", numProcess);
	}
	else if (myRank != 0)
	{
		number = arr[myRank] * 2;
		printf("[%d]:\t%d\n", myRank, number);
	}

	/* ПЕРВОЕ ЗАДАНИЕ 
	number = arr[myRank] * (-1); //умножение числе на -1
	printf("[%d]:\t%f\n",myRank, number);
	*/
	MPI_Finalize(); // конец параллельного куска кода 
}
