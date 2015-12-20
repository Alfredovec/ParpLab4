#include "stdafx.h"
#include <immintrin.h>
#include <Windows.h>
#include <time.h>

void print(int* mas)
{
	for (int i = 0; i < 16; i++)
	{
		printf("%d ", mas[i]);
	}
	printf("\n");
}

void doTask9() {
	int* up = new int[16];
	for (int i = 0; i < 16; i++) up[i] = 2;

	int* uresWithout = new int[16];
	int* uresWith = new int[16];

	int itrWithout = 0, itrWith = 0;

	DWORD timeToCount = 2000, start, finish;
	start = GetTickCount();

	do {
		withoutSse(up, uresWithout);		
		finish = GetTickCount();
		itrWithout++;
	} while (finish - start <= timeToCount);
	printf("without => %d\n", itrWithout);


	start = GetTickCount();
	do {
		withSse(up, uresWith);
		finish = GetTickCount();
		itrWith++;
	} while (finish - start <= timeToCount);
	printf("with => %d\n", itrWith);

	printf("res => %f\n", (double)itrWithout / itrWith);
}

void withoutSse(int* up, int* ures) {
	for (int i = 15; i >= 1; i--) {
		ures[i] = (up[i] << 1) |  (up[i - 1] >> 31);
	}
	ures[0] = up[0] << 1;
}

void withSse(int* up, int* ures) {
	__m128i* p = reinterpret_cast<__m128i*>(up);
	__m128i* res = reinterpret_cast<__m128i*>(ures);
	__m128i a = _mm_set1_epi32(0x80000000);
	__m128i dop[3];

	dop[0] = _mm_cvtsi32_si128(up[3] >> 31);
	dop[1] = _mm_cvtsi32_si128(up[7] >> 31);
	dop[2] = _mm_cvtsi32_si128(up[11] >> 31);

	__m128i t = _mm_and_si128(a, p[0]);

	res[0] = _mm_or_si128(_mm_slli_epi32(p[0], 1),
		_mm_srli_epi32(_mm_slli_si128(t, 4), 31)); 

	res[1] = _mm_or_si128(_mm_or_si128(_mm_slli_epi32(p[1], 1),
		_mm_srli_epi32(_mm_slli_si128(_mm_and_si128(a, p[1]), 4), 31)),
		dop[0]);

	res[2] = _mm_or_si128(_mm_or_si128(_mm_slli_epi32(p[2], 1),
		_mm_srli_epi32(_mm_slli_si128(_mm_and_si128(a, p[2]), 4), 31)),
		dop[1]);

	res[3] = _mm_or_si128(_mm_or_si128(_mm_slli_epi32(p[3], 1),
		_mm_srli_epi32(_mm_slli_si128(_mm_and_si128(a, p[3]), 4), 31)),
		dop[2]);

	// _mm_and_si128 - Compute the bitwise AND of 128 bits (representing integer data) in a and b, and store the result in dst.
	// _mm_slli_epi32 - Shift packed 32-bit integers in a left by imm8 while shifting in zeros, and store the results in dst.
	// _mm_or_si128 - Compute the bitwise OR of 128 bits (representing integer data) in a and b, and store the result in dst.
	// _mm_srli_epi32 - Shift packed 32-bit integers in a right by imm8 while shifting in zeros, and store the results in dst.
}