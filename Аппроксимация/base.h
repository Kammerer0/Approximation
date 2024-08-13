#pragma once
#include <iostream>

class base
{
public:
	float* Data_input(int P);
	float* Data_output(int P, float* x, char a);
	float Sum(int P, float* x, float power);
	float Sum_prois(int P, float* x, float* y, float power);
	float SquareInficity(float* y1, float* y, int P);
	void Matrix_output(float* A[], int P);
};

