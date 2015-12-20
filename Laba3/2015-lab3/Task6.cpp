#include "stdafx.h"
#include <immintrin.h>


// Скласти функції для обчислення  x[i] = √ (y[i])  (i = 0.. n-1) для даних з плаваючою
// крапкою звичайної та подвійної точності без використання та з використанням SIMD
// команд.

void doTask6() {
}

template <typename T> void count(T* arr, T* res, int size) {
	/*for (int i = 0; i < size; i +=4) {
		res[i] = _mm_sqrt_ps(_mm_mul_ps(arr));
	}*/
}