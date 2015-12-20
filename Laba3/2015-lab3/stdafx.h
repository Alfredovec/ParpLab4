#pragma once

#include "targetver.h"
#include <stdio.h>
#include <tchar.h>
#include <INTRIN.H>

void withoutSse(int* up, int* ures);
void withSse(int* up, int* ures);
void doTask9();

int doTask1();