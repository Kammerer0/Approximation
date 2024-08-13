#include "base.h"

//функция ввода данных в одномерный массив
float* base::Data_input(int P)
{
	float* x = new float[P];

	for (int i = 0; i < P; i++)
	{
		std::cin >> x[i];
	}
	return x;
}
//функция вывода элементов одномерного массива
float* base::Data_output(int P, float* x, char a)
{
	std::cout << a << ":\t";
	for (int i = 0; i < P; i++)
	{
		std::cout << x[i] << "\t";
	}
	std::cout << "\n\n\n";
	return nullptr;
}
//функция суммирования элементов вектора в заданной степени
float base::Sum(int P, float* x, float power)
{
	float sum = 0, sum1 = 0;
	for (int i = 0; i < P; i++)
	{
		sum1 = sum;
		sum = sum1 + pow(x[i], power);
	}
	return sum;
}
//нахождение суммы произведений икс в степени на игрек
float base::Sum_prois(int P, float* x, float* y, float power)
{
	float sum = 0, sum1 = 0;
	for (int i = 0; i < P; i++)
	{
		sum1 = sum;
		sum = sum1 + pow(x[i], power) * y[i];
	}
	return sum;
}
//функция расчета суммарной квадратичной погрешности
float base::SquareInficity(float* y1, float* y, int P)
{
	float S = 0, inficity = 0;
	for (int i = 0; i < P; i++)
	{
		S = inficity;
		inficity = S + pow((y1[i] - y[i]), 2);
	}
	return inficity;
}

void base::Matrix_output(float* A[], int P)
{
	for (int i = 0; i < P; i++)
	{
		for (int j = 0; j < P; j++)
		{
			std::cout << A[i][j] << "    ";
		}
		std::cout << "\n";
	}
	std::cout << "\n\n\n";
}
