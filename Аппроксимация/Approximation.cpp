#include "Approximation.h"

float* Approximation::Linear(float* x, float* y, int P)
{
    base b;
    float k[2] = {};                // k[0] = a, k[1] = b
    float x_, y_;                   // x и y с чертой
    float* xx = new float[P];       // x с черточкой        см. методичку Ламзина
    float* yy = new float[P];       // y с черточкой
    float* y1 = new float[P] {};	//вектор новых значений функции
    char a3 = 'y1';
    x_ = b.Sum(P, x, 1) / P;
    y_ = b.Sum(P, y, 1) / P;

    for (int i = 0; i < P; i++)
    {
        xx[i] = x[i] - x_;
        yy[i] = y[i] - y_;
    }

    k[1] = b.Sum_prois(P, xx, yy, 1) / b.Sum(P, xx, 2);
    k[0] = y_ - k[1] * x_;

    std::cout << "Полученная функция: \t\t" << k[0] << " + x * " << k[1] << std::endl;
    //полученнные значения функции от икс
    for (int i = 0; i < P; i++)
    {
        y1[i] = k[0] + k[1] * x[i];
    }
    b.Data_output(P, y1, a3);
    std::cout << "Суммарная квадратичная погрешность интерполяции равна:\t" << b.SquareInficity(y1, y, P) << std::endl;

    return k;
}

float* Approximation::Power(float* x, float* y, int P)
{
    base b;
    float k[2] = {};                // k[0] = a, k[1] = b
    float x_, y_;                   // x и y с чертой
    float* xx = new float[P];       // x с черточкой        см. методичку Ламзина
    float* yy = new float[P];       // y с черточкой
    float* y2 = new float[P] {};	//вектор новых значений функции
    float* x1 = new float[P];
    float* y1 = new float[P];
    char a3 = 'y1';
    float e = 2.718;

    for (int i = 0; i < P; i++)
    {
        x1[i] = log(x[i]);
        y1[i] = log(y[i]);
    }

    x_ = b.Sum(P, x1, 1) / P;
    y_ = b.Sum(P, y1, 1) / P;

    for (int i = 0; i < P; i++)
    {
        xx[i] = x1[i] - x_;
        yy[i] = y1[i] - y_;
    }

    k[1] = b.Sum_prois(P, xx, yy, 1) / b.Sum(P, xx, 2);
    k[0] = pow(e, y_ - k[1] * x_);

    std::cout << "Полученная функция: \t\t" << k[0] << " * x^" << k[1] << std::endl;
    //полученнные значения функции от икс
    for (int i = 0; i < P; i++)
    {
        y2[i] = k[0] * pow(x[i], k[1]);
    }
    b.Data_output(P, y1, a3);
    std::cout << "Суммарная квадратичная погрешность интерполяции равна:\t" << b.SquareInficity(y2, y, P) << std::endl;

    return k;
}

float* Approximation::Quadratic(float* x, float* y, int P)
{
    float* b1 = new float[P] {};	//вектор свободных коэффициентов
    float* k = new float[3] {};		//вектор искомых коэффициентов апроксимации
    float* y1 = new float[P] {};	//вектор новых значений функции
    char a3 = 'y1';
    char name = 'kv';
    base b;
    NumericalMethods nm;
    //обьявляем двумерный массив
    float A1[20][20];

    //задаем элементы матрицы
    //диагональные
    A1[0][0] = b.Sum(P, x, 4);
    A1[1][1] = b.Sum(P, x, 2);
    A1[2][2] = b.Sum(P, x, 0);
    //остальные
    A1[0][1] = A1[1][0] = b.Sum(P, x, 3);
    A1[0][2] = A1[2][0] = b.Sum(P, x, 2);
    A1[1][2] = A1[2][1] = b.Sum(P, x, 1);

    //значения вектора свободных коэффициентов
    b1[0] = b.Sum_prois(P, x, y, 2);
    b1[1] = b.Sum_prois(P, x, y, 1);
    b1[2] = b.Sum_prois(P, x, y, 0);

    //перезадание матрицы для вывода
    float* A2[3];
    for (int i = 0; i < 3; i++)
    {
        A2[i] = A1[i];
    }

    b.Matrix_output(A2, 3);
    k = nm.Gauss(A1, b1, 3);
    std::cout << "Полученная функция: \t\t" << "x^2 * " << k[0] << " + x * " << k[1] << " + " << k[2] << std::endl;
    //полученнные значения функции от икс
    for (int i = 0; i < P; i++)
    {
        y1[i] = pow(x[i], 2) * k[0] + x[i] * k[1] + k[2];
    }
    b.Data_output(P, y1, a3);
    std::cout << "Суммарная квадратичная погрешность интерполяции равна:\t" << b.SquareInficity(y1, y, P) << std::endl;

    return k;
}

float* Approximation::Logarithmic(float* x, float* y, int P)
{
    base b;
    float k[2] = {};                // k[0] = a, k[1] = b
    float x_, y_;                   // x и y с чертой
    float x_ln;
    float* xx = new float[P];       // x с черточкой        см. методичку Ламзина
    float* yy = new float[P];       // y с черточкой
    float* y1 = new float[P] {};	//вектор новых значений функции
    float S_xx = 0, S_xy = 0, S = 0, S1 = 0;
    char a3 = 'y1';

    x_ = b.Sum(P, x, 1) / P;        //среднее значение х
    y_ = b.Sum(P, y, 1) / P;
    x_ln = log(x_);

    for (int i = 0; i < P; i++)
    {
        xx[i] = log(x[i]) - x_ln;
        yy[i] = y[i] - y_;
    }

    for (int i = 0; i < P; i++)
    {
        S = S_xx;
        S_xx = S + pow(xx[i], 2);
    }

    for (int i = 0; i < P; i++)
    {
        S1 = S_xy;
        S_xy = S1 + yy[i] * xx[i];
    }

    k[0] = S_xy / S_xx;
    k[1] = y_ - k[0] * log(x_);

    std::cout << "Полученная функция: \t\t" << k[0] << " + x * " << k[1] << std::endl;
    //полученнные значения функции от икс
    for (int i = 0; i < P; i++)
    {
        y1[i] = k[0] * log(x[i]) + k[1];
    }
    b.Data_output(P, y1, a3);
    std::cout << "Суммарная квадратичная погрешность интерполяции равна:\t" << b.SquareInficity(y1, y, P) << std::endl;

    return k;
}

float* Approximation::Exponential(float* x, float* y, int P)
{
    base b;
    float* yln = new float[P];
    float k[2] = {};
    float* y1 = new float[P] {};
    char a3 = 'y1';

    for (int i = 0; i < P; i++)
    {
        yln[i] = log(y[i]);
    }

    k[0] = (b.Sum(P, yln, 1) * b.Sum(P, x, 2) - b.Sum(P, x, 1) * b.Sum_prois(P, x, yln, 1)) / (P * b.Sum(P, x, 2) * pow(b.Sum(P, x, 1), 2));
    k[1] = (P * b.Sum_prois(P, x, yln, 1) - b.Sum(P, x, 1) * b.Sum(P, yln, 1)) / (P * b.Sum(P, x, 2) - pow(b.Sum(P, x, 1), 2));

    std::cout << "Полученная функция: \t\t" << k[0] << " + x * " << k[1] << std::endl;
    //полученнные значения функции от икс
    for (int i = 0; i < P; i++)
    {
        y1[i] = k[0] * pow(2.718, k[1] * x[i]);
    }
    b.Data_output(P, y1, a3);
    std::cout << "Суммарная квадратичная погрешность интерполяции равна:\t" << b.SquareInficity(y1, y, P) << std::endl;

    return k;
}
