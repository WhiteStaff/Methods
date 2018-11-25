#pragma once

#include <vector>

std::vector< double> operator+(std::vector<double> a, std::vector<double> b)
{
	std::vector<double> s(a.size());
	for (int i = 0; i < a.size(); i++)
	{
		s[i] = a[i] + b[i];
	}
	return s;
}

std::vector< double> operator-(std::vector<double> a, std::vector<double> b)
{
	std::vector<double> s(a.size());
	for (int i = 0; i < b.size(); i++)
	{
		s[i] = a[i] - b[i];
	}
	return s;
}

std::vector< double> operator*(std::vector<double> a, int b)
{
	std::vector<double> s(a.size());
	for (int i = 0; i < a.size(); i++)
	{
		s[i] = a[i] * b;
	}
	return s;
}

std::vector<double> ABS(std::vector<double> a)
{
	std::vector<double> s(a.size());
	for (int i = 0; i < a.size(); i++)
	{
		s[i] = abs(a[i]);
	}
	return s;
}

std::vector< double> operator/(std::vector<double> a, double b)
{
	std::vector<double> s(a.size());
	for (int i = 0; i < a.size(); i++)
	{
		s[i] = a[i] / b;
	}
	return s;
}
#pragma once
