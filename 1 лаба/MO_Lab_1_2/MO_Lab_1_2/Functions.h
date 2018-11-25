// Пункты 1 и 2 первой части

#pragma once

#include <iostream>
#include <cmath>
#include <vector>
#include <ctime>
#include <cstdlib>
#include "Header.h"

using namespace std;

 double Eps = 0.00000000000001; // Точность
const double delta = Eps / 2.0;

// Функция y = x^3 - x, первый вариант
double f(double x)
{
	return (pow(x, 3) - x);
}



// Границы заданной функции
const double max_x = 1.0;
const double min_x = 0.0;

// Метод Дихотомии
double dihotomia()
{
	double b0 = max_x;
	double a0 = min_x;
	double x1, x2;

	while (abs(b0 - a0) > Eps)
	{
		x1 = (b0 + a0) / 2.0 - delta;
		x2 = (b0 + a0) / 2.0 + delta;
		if (f(x1) < f(x2))
			b0 = x2;
		else if (f(x1) == f(x2))
		{
			b0 = x2;
			a0 = x1;
		}
		else
			a0 = x1;
	}
	return (a0 + b0) / 2.0;
}

// Метод Золотого сечения
double gold() {
	double b0 = max_x;
	double a0 = min_x;
	double x1, x2;

	while (abs(b0 - a0) > Eps)
	{
		x1 = a0 + (3 - sqrt(5)) / 2.0 * (b0 - a0);
		x2 = a0 + (sqrt(5) - 1) / 2.0 * (b0 - a0);

		if (f(x1) < f(x2)) {
			b0 = x2;
		}
		else if (f(x1) == f(x2)) {
			b0 = x2;
			a0 = x1;
		}
		else {
			a0 = x1;
		}
	}
	return (a0 + b0) / 2.0;
}

// Генерация массива для метода фиббоначи
void fibonacci_array(std::vector<int>& fib, double finish)
{
	fib.push_back(1);
	fib.push_back(1);
	while (fib[fib.size() - 1] < finish) {
		fib.push_back(fib[fib.size() - 1] + fib[fib.size() - 2]);
	}
}

// Метод Фибоначи
double fibonacсi()
{
	double b0 = max_x;
	double a0 = min_x;
	double x1, x2;

	vector<int> fib;
	double finish = (b0 - a0) / Eps;
	fibonacci_array(fib, finish);

	int n = fib.size() - 1;

	x1 = a0 + (b0 - a0) * ((double)fib[n - 2] / (double)fib[n]);
	x2 = a0 + (b0 - a0) * ((double)fib[n - 1] / (double)fib[n]);

	while (n > 1)
	{
		n -= 1;
		if (f(x1) < f(x2))
		{
			b0 = x2;
			x2 = x1;
			x1 = a0 + (b0 - x2);
		}
		else
		{
			a0 = x1;
			x1 = x2;
			x2 = b0 - (x1 - a0);
		}
	}
	return x1;
}


// Поиск минимума на прямой
pair<double, double> on_straight()
{
	double h;

	srand(time(0));
	double x = (rand() % 1000) / 1000.0;
	if (f(x) > f(x + delta)) {
		h = delta;
	}
	else if (f(x) > f(x - delta))
	{
		h = -delta;
	}
	while (f(x) > f(x + h))
	{
		x += h;
		h *= 2;
	}
	double left = x - h;
	double right = x + h;
	return{ left, right };
}

