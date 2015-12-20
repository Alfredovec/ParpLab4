#include "stdafx.h"
#include <stdint.h>
#include <cmath>
#include <Windows.h>
#include <INTRIN.H>

void doTask1() {
	PROCERRORTYPE proc = GetProcessorType();

	switch (proc) {
	case UNKNOWN:
		printf("UNKNOWN");
		break;
	case INTEL:
		printf("INTEL");
		break;
	case AMD:
		printf("AMD");
		break;
	}

	printf("\n");
}

PROCERRORTYPE GetProcessorType() {
	PROCERRORTYPE ProcessorType = UNKNOWN;
	char Etalons[2][13] = { "GenuineIntel", "AuthenticAMD" };
	int Regs[4]; Regs[0] = MaxFunctionNumber(0);
	if (Regs[0] != -1) {
		__cpuid(Regs, 0); int iVendor[3];
		iVendor[0] = Regs[1]; iVendor[1] = Regs[3]; iVendor[2] = Regs[2];
		char *cVendor = (char *)iVendor;
		if (strncmp(cVendor, Etalons[0], 12) == 0){
			ProcessorType = INTEL;
		}
		else if (strncmp(cVendor, Etalons[1], 12) == 0) {
			ProcessorType = AMD;
		}
	}
	return ProcessorType;
}

int MaxFunctionNumber(int *ExtMaxFunctionNumber) {
	int res = -1;
	if (CPUIDSupport())
	{
		int b = 0x80000000;
		int a[4];
		if (ExtMaxFunctionNumber) {
			__cpuid(a, b); 
			*ExtMaxFunctionNumber = a[0];
		}

		b = 0; __cpuid(a, b);
		res = a[0];
	}

	return res;
}

inline bool CPUIDSupport() {
	__asm{
		pushfd
			pop eax
			or eax, 1 SHL 21
			push eax
			popfd
			pushfd
			pop eax
			and eax, 1 SHL 21
			shr eax, 21
	}
}


int SIMDSupport(){
	SIMDSUPPORT res = (SIMDSUPPORT)0;
	int cpuInfo[4];
	__cpuidex(cpuInfo, 1, 0);

	if (((cpuInfo[2] >> 26) & 15) == 15) {
		res = AVX2SUPPORT;
	}

	else if (((cpuInfo[2] >> 26) & 7) == 7) {
		res = AVXSUPPORT;
	}

	if (res != (SIMDSUPPORT)0){
		unsigned XCR0Value = GetXCR0();
		if (((XCR0Value >> 2) & 1) == 1) {
			return res;
		}
		res = (SIMDSUPPORT)0;
	}
}