#include <omp.h>
#include <stdio.h>
#include <iostream>
#include <windows.h>

using namespace std;

void main()
{
	int reader, writer;

	omp_lock_t lock;
	omp_init_lock(&lock);

	printf_s("Input number of readers: ");
	scanf_s("%d", &reader);
	omp_set_num_threads(reader);
	printf_s("Input number of writers: ");
	scanf_s("%d", &writer);
	
	printf_s("\nReading starts...\n");

#pragma omp parallel 
	{
		printf_s("\nThread %d is entering the shared memory\n", omp_get_thread_num());
		Sleep(2);
		printf_s("\nThread %d is entering the shared memory\n", omp_get_thread_num());
		Sleep(2);
		printf_s("\nThread %d is entering the shared memory\n", omp_get_thread_num());
		Sleep(2);
	}
	omp_set_num_threads(writer);
	printf_s("\n\nWriting starts\n");
#pragma omp parallel
	{
		omp_set_lock(&lock);

		printf_s("\nThread %d is entering the shared memory\n", omp_get_thread_num());
		Sleep(2);
		printf_s("\nThread %d is entering the shared memory\n", omp_get_thread_num());
		Sleep(2);
		printf_s("\nThread %d is entering the shared memory\n", omp_get_thread_num());
		Sleep(2);
		omp_unset_lock(&lock);
	}
	omp_destroy_lock(&lock);
	printf_s("\n");
}
