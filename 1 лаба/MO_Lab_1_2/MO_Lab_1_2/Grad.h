#include "Nfunctions.h"


vector<double> gradient(const vector<double>& x)
{
	vector<double> ans;
	ans.push_back(400 * x[0] * (x[0] * x[0] - x[1]) + 2 * (x[0] - 1)); 
	ans.push_back(200 * (x[1] - x[0] * x[0])); 
	pair<vector<double>, vector<double>> seg1(vector<double>(ans.size(), 0.0), ans);


	/*for (int i = 0; i < x.size(); i++)
	{
		seg1.first.push_back(0);
		seg1.second.push_back(ans[i]);
	}*/

	double len = length(seg1);
	for (int i = 0; i < ans.size(); i++)
	{
		ans[i] /= len;
	}
	return ans;
}


std::vector<double> MyGradientSearch(double(*nfun)(const vector<double>&), vector<double>(*grad)(const vector<double>&), vector<double> &begin, double Ep)
{
	vector<double> direction = grad(begin) * (-1);
	double Eps = Ep;
	//direction = direction / length(seg1);
	vector<double> x_prev = begin;
	vector<double> x = Ndihotomia(n_mernoe(direction, begin, Eps), Eps);
	pair<vector<double>, vector<double>> seg;
	seg.first = x;
	seg.second = x_prev;
	unsigned long long int it = 0;
	while (length(seg) > Eps)
	{
		direction = gradient(x) * (-1);
		vector<double> t = x;
		x = Ndihotomia(n_mernoe(direction, x, Eps), Eps);
		x_prev = t;
		seg.first = x;
		seg.second = x_prev;
		double l = length(seg);
		it++;
	}
	return x;
	//return x;
}