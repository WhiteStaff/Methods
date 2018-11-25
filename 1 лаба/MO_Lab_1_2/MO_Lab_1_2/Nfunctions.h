#pragma once
#include "Functions.h"

using namespace std;

//N-мерная функция
double nfunction(const vector<double>& x)
{
	//double res = (100 * pow(x[1] - x[0] * x[0], 2) + pow((1 - x[0]), 2));
	return (100*pow(x[1]-x[0]*x[0],2)+pow((1-x[0]), 2));
}

//длина сегмента
double length(pair<vector<double>, vector<double>> seg)
{
	double res = 0.0;
	for (int i = 0; i < seg.first.size(); i++)
	{
		res += (seg.first[i] - seg.second[i]) * (seg.first[i] - seg.second[i]);
	}
	return sqrt(res);
}

//N-мерная дихотомия
vector<double> Ndihotomia(pair< vector <double>, vector<double>> frag, double Ep)
{
	vector<double> b0(frag.second), x1, x2, a0(frag.first), del(frag.first.size());
	double Eps = Ep;
	//cout << "Enter vector:";
	//b0 = frag.second;
	//a0 = frag.first;
	for (int i = 0; i < b0.size(); i++)
	{
		//cin >> s[i];
		//b0[i] = 1.0;
		//a0[i] = 0.0;
		del[i] = (b0[i] - a0[i])/length(frag) * Ep;
		//ep[i] = Eps;
	}
	//double l = length(frag);
	while (length(frag) > Eps)
	{
		x1 = ((b0 + a0) / 2.0) - del / 8;
		x2 = ((b0 + a0) / 2.0) + del / 8;
		if (nfunction(x1) < nfunction(x2))
			b0 = x2;
		else if (nfunction(x1) == nfunction(x2))
		{
			b0 = x2;
			a0 = x1;
		}
		else
			a0 = x1;
		frag.second = b0;
		frag.first = a0;
		//l = length(frag);
	}
	return (a0 + b0) / 2.0;
}

// Метод N-мерного Золотого сечения
vector<double> Ngold(int n)
{
	n--;
	vector<double> b0(n), x1(n), x2(n), s(n), a0(n), ep(n), del(n);
	cout << "Enter vector:";
	for (int i = 0; i < 0; i++)
	{
		cin >> s[i];
		b0[i] = 1.0;
		a0[i] = 0.0;
		del[i] = delta * s[i];
		ep[i] = Eps;
	}

	while (ABS(b0 - a0) > ep)
	{
		x1 = a0 + (b0 - a0) * (3 - sqrt(5)) / 2.0;
		x2 = a0 + (b0 - a0) * (sqrt(5) - 1) / 2.0;

		if (nfunction(x1) < nfunction(x2)) {
			b0 = x2;
		}
		else if (nfunction(x1) == nfunction(x2)) {
			b0 = x2;
			a0 = x1;
		}
		else {
			a0 = x1;
		}
	}
	return (a0 + b0) / 2.0;
}

// Метод N - мерного Фибоначи
vector<double> fibonacсi(int n1)
{
	n1--;
	vector<double> b0(n1), x1(n1), x2(n1), s(n1), a0(n1), ep(n1), del(n1);
	cout << "Enter vector:";
	for (int i = 0; i < 0; i++)
	{
		cin >> s[i];
		b0[i] = 1.0;
		a0[i] = 0.0;
		del[i] = delta * s[i];
		ep[i] = Eps;
	}
	double finish = (b0[0] - a0[0]) / Eps;
	vector<int> fib;
	
	fibonacci_array(fib, finish);

	int n = fib.size() - 1;

	x1 = a0 + (b0 - a0) * ((double)fib[n - 2] / (double)fib[n]);
	x2 = a0 + (b0 - a0) * ((double)fib[n - 1] / (double)fib[n]);

	while (n > 1)
	{
		n -= 1;
		if (nfunction(x1) < nfunction(x2))
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

//Поиск минимума в n мерном пространстве в направлении вектора s
pair<vector<double>, vector<double>> n_mernoe(const vector<double>& vect, const vector<double>& begin, double Ep)
{
	vector<double> s = vect, x = begin;
	vector<double> del(s);
	/*for (int i = 0; i < n; i++)
	{
		del[i] = s[i];
	}*/
	if (nfunction(x) > nfunction(x - del))
	{
		for (int i = 0; i < del.size(); i++)
		{
			del[i] = del[i] * (-1);
		}
	}
	x = x + del;
	while (nfunction(x) > nfunction(x + del))
	{
		x = x + del;
		for (int i = 0; i < del.size(); i++)
		{
			del[i] = del[i] * 2;
		}
	}
	vector<double> left = x - del;
	vector<double> right = x + del;
	return pair<vector<double>, vector<double>>(left, right);
}

