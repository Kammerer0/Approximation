#pragma once
#include <iostream>
#include "base.h"
#include "NumericalMethods.h"
#include <cmath>

class Approximation
{
public:
	float* Linear(float* x, float* y, int P);
	float* Power(float* x, float* y, int P);
	float* Quadratic(float* x, float* y, int P);
	float* Logarithmic(float* x, float* y, int P);
	float* Exponential(float* x, float* y, int P);
};

