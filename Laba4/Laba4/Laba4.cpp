#include "stdafx.h"
#include <sys/types.h>
#include <WinSock2.h>
#include <stdio.h>
#include <conio.h>
#include <iostream>
#include <omp.h>

using namespace std;

void task1() {
	#ifdef _OPENMP
		printf("OPENMP is active\n");
	#else
		printf("OPENMP is not active\n");
	#endif
}



void task2_1() {
	SYSTEM_INFO sysinfo;
	GetSystemInfo(&sysinfo);

	DWORD numCPU = sysinfo.dwNumberOfProcessors;
	printf("Cores count = %i\n", numCPU);
}

void task2_2() {
	printf("Cores count = %i\n", omp_get_max_threads());
}

void task3_1(long n)
{
	double p;
	double s = 0;
	double sign = 1;
	long j = 1;
	for (long i = 1; i < n; i++) {
		s += sign / j;
		j += 2;
		sign *= -1;
	}
	p = 4 * s;
	printf("Pi = %10.10f\n", p);
}

void task3_2(long n)
{
	double p;
	double s = 0.;
	double dx = 1. / n;
	double x = 0.;
	for (long i = 0; i < n; i++) {
		s += sqrt(1 - x * x) * dx;
		x += dx;
	}
	p = 4 * s;
	printf("Pi = %10.10f\n", p);
}

void task3_3(long n) {
	double p;
	double s = 1;
	for (long i = 1; i < n; i++) {
		double ch = i*2;
		double zn = ch - 1;
		s = s*(ch / zn);
		s = s*(ch / (zn + 2));
	}
	p = 2*s;
	printf("Pi = %10.10f\n", p);
}

typedef struct {
	double begin;
	double end;
	double value;
} range;

DWORD WINAPI func(LPVOID a) {
	range* par = (range*)a;
	double s = 1.;	
	int i = par->begin + 1;
	int end = par->end;
	for (; i <= end; i++) {
		double ch = i * 2.;
		double zn = ch - 1.;
		s = s*(ch / zn);
		s = s*(ch / (zn + 2));
		
	}
	par->value = s;	
	return 1;
}

void task4(double n) {
	SYSTEM_INFO sysinfo;
	GetSystemInfo(&sysinfo);

	DWORD numCPU = sysinfo.dwNumberOfProcessors;
	int CoresCount = numCPU;
	double p;

	range* par = new range[CoresCount];
	for(int i = 0; i < CoresCount; i++) {
		par[i].begin = i * n / CoresCount;
		par[i].end =  (i+1) * n / CoresCount;		
	}

	HANDLE* thrd = new HANDLE[CoresCount];

	int i = 0;
	for (i = 0; i < CoresCount; i++) {
		thrd[i] = CreateThread(0, 0, func, &par[i], 0, 0);
	}
	WaitForMultipleObjects(CoresCount, thrd, true, INFINITE);
	double sum = 1.;
	for (int i = 0; i < CoresCount; i++) {
		sum *= par[i].value;
		CloseHandle(thrd[i]);
	}
	p = (2 * sum);
	printf("Pi = %10.10f\n", p);
}
 
void task6(long n) {
	double p;
	double s = 1.;
	//double x = 0.;

	#pragma omp parallel for reduction(*:s)
	for (int i = 1; i < n; i++) {
		double ch = i * 2.;
		double zn = ch - 1.;
		s = s*(ch / zn);
		s = s*(ch / (zn + 2));
	}

	p = 2 * s;
	printf("Pi = %10.10f\n", p);
}

void DrawLine()
{
	printf("--------------------------------------------------------------------\n");
}

int _tmain(int argc, _TCHAR* argv[])
{
	long accuracy = 100000000;

	setlocale(LC_ALL, "RUSSIAN");
	DrawLine();
	printf("1. Check Open MP.\n"); 
	task1();
	DrawLine();

	DrawLine();
	printf("2.1 Thread count without Open MP.\n");
	task2_1();
	DrawLine();

	DrawLine();
	printf("2.2 Threads count with Open MP.\n");
	task2_2();
	DrawLine();
	
	DrawLine();
	printf("Pi computing (1st method) with %i iterations\n", accuracy);
	DWORD start = GetTickCount();
	task3_1(accuracy);
	DWORD stop = GetTickCount() - start;
	printf("Time count = %i\n", stop);
	DrawLine();

	DrawLine();
	printf("Pi computing (2nd method) with %i iterations\n", accuracy);
	start = GetTickCount();
	task3_2(accuracy);
	stop = GetTickCount() - start;
	printf("Time count = %i\n", stop);
	DrawLine();

	DrawLine();
	printf("Pi computing (3rd method) with %i iterations\n", accuracy);
	start = GetTickCount();
	task3_3(accuracy);
	stop = GetTickCount() - start;
	printf("Time count = %i\n", stop);
	DrawLine();
	
	DrawLine();
	printf("Pi computing (3th method parallel) with %i iterations\n", accuracy);
	start = GetTickCount();
	task4(accuracy);
	stop = GetTickCount() - start;
	printf("Time count = %i\n", stop);
	DrawLine();
		
	DrawLine();
	printf("Pi computing (3th method parallel including OpenMP) with %i iterations\n", accuracy);
	start = GetTickCount();
	task6(accuracy);
	stop = GetTickCount() - start;
	printf("Time count = %i\n", stop);
	DrawLine();

	system("pause");
	return 0;
}

