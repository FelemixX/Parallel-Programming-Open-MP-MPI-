#include "mpi.h"
#include <stdio.h>
#include <iostream>

using namespace std;

void main()
{
	int myRank, numProcess, number;//process id,quantity of processes
	int arr[] = { -20, 88, 81, -3, 81, 61, 43, 93, -95, 75, 40, 13 };
	int buffer;
	
	MPI_Init(NULL, NULL); //начало куска кода, который будет исполняться параллельно
	MPI_Comm_size(MPI_COMM_WORLD, &numProcess); //объявляем функцию, чтобы знать, сколько потоков у нас есть
	MPI_Comm_rank(MPI_COMM_WORLD, &myRank); //объявляем функцию, которая дает номер потока
	if (myRank == 0)
	{
		//MPI_Status status;
		for (int i = 1; i < numProcess; i++)
		{
			int sent = arr[i];
			//MPI_Recv(&buffer, 1, MPI_INT, i, 1, MPI_COMM_WORLD, &status);
			MPI_Send(&sent, 1, MPI_INT, i, 1, MPI_COMM_WORLD);
			//printf("Rank[%d]: %d\n", i, buffer);
		}
	}
	else
	{
		MPI_Status status;
		//int sent = 1;
		MPI_Recv(&buffer, 1, MPI_INT, 0, 1, MPI_COMM_WORLD, &status);
		printf("Rank[%d]: %d\n", myRank, buffer);
		//MPI_Send(&sent, 1, MPI_INT, 0, 1, MPI_COMM_WORLD);
	}
		
		/*(if (myRank % 2 == 0) //четный
	{
		int min = arr[0];
		for (int i = 0; i < myRank; i++)
		{
			if (arr[i] < min)
				min = arr[i];
		}
		printf("[%d]:\t%d\n MIN", myRank, min);
	} 
	*/
	MPI_Finalize(); // конец параллельного куска кода 
}
