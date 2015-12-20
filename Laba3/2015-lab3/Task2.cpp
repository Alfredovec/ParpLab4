#include "stdafx.h"
#include <stdint.h>
#include <cmath>
#include <Windows.h>

template <typename T> void print(T* arr, int size) {
	for (int i = 0; i < size; i++) {
		printf("%d ", arr[i]);
	}
}

template <typename T> T* getFilledArray(int size) {
	T* arr = new T[size];

	for (int i = 0; i < size; i++) {
		// отприцательные значения?
		arr[i] = rand() % MAX_AVAILABLE_VALUE;
	}

	return arr;
}

// Скласти функції для обчислення: x[i] = |y[i]| + |z[i]|  (i = 0.. n-1) 
template <typename T> void count(T* a, T* b, T* res, int size) {
	for (int i = 0; i < size; i++) {
		//res[i] = abs(a[i]) + abs(b[i]);
		res[i] = a[i] + b[i];
	}
}

void doTask2() {
	int size = 4096 * 4096;

	// проверить битность!
	int8_t* bit8a = getFilledArray<int8_t>(size);
	int8_t* bit8b = getFilledArray<int8_t>(size);
	int8_t* bit8res = new int8_t[size];

	startClock();
	count<int8_t>(bit8a, bit8b, bit8res, size);
	finishClock("8bit -> Time = ");

	int16_t* bit16a = getFilledArray<int16_t>(size);
	int16_t* bit16b = getFilledArray<int16_t>(size);
	int16_t* bit16res = new int16_t[size];

	startClock();
	count<int16_t>(bit16a, bit16b, bit16res, size);
	finishClock("16bit -> Time = ");

	int* bit32a = getFilledArray<int>(size);
	int* bit32b = getFilledArray<int>(size);
	int* bit32res = new int[size];

	startClock();
	count<int32_t>(bit32a, bit32b, bit32res, size);
	finishClock("32bit -> Time = ");

	long long* bit64a = getFilledArray<long long>(size);
	long long* bit64b = getFilledArray<long long>(size);
	long long* bit64res = new long long[size];

	startClock();
	count<long long>(bit64a, bit64b, bit64res, size);
	finishClock("64bit -> Time = ");

	float* floatA = getFilledArray<float>(size);
	float* floatB = getFilledArray<float>(size);
	float* floatRes = new float[size];

	startClock();
	count<float>(floatA, floatB, floatRes, size);
	finishClock("float -> Time = ");

	double* doubleA = getFilledArray<double>(size);
	double* doubleB = getFilledArray<double>(size);
	double* doubleRes = new double[size];

	startClock();
	count<double>(doubleA, doubleB, doubleRes, size);
	finishClock("double -> Time = ");

}