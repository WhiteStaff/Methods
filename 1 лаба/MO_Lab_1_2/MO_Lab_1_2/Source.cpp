#include "Functions.h"
#include "Nfunctions.h"
#include "Grad.h"

int main()
{
	/*double ans;
	int b;
	pair<double, double> a;
	pair <vector <double>, vector<double> > an;
	ans = dihotomia();
	cout << ans << endl;
	ans = gold();
	cout << ans << endl;
	ans = fibonacñi();
	cout << ans << endl;
	a = on_straight();
	std::cout << a.first << " " << a.second << endl;
	int n = 4;
	an = n_mernoe(n);
	n--;
	for (int i = 0; i < n; i++)
	{
		std::cout << an.first[i] << " ";
	}
	std::cout << endl;
	for (int i = 0; i < n; i++)
	{
		std::cout << an.second[i] << " ";
	}
	std::cin >> b;*/

	double Eps = 0.1;
	//ãğàäèåíò
	vector<double> begin(2);
	begin[0] = 100.0;
	begin[1] = 100.0;
	for (int i = 0; i < 10; i++)
	{
		//std::cout << h << ' ';
		

		begin = MyGradientSearch(nfunction, gradient, begin, Eps);
		cout << begin[0] << " " << begin[1] << endl;
		//std::cout << GradientDescentSearch(&ScaleFunction<double, func, 1, 50>, &ScaleFunction<MathVector<2>, g, 1, 50>, MathPoint<2>(100.0, 20.0), h) << std::endl;
		cout << endl;
		Eps /= 10.0;
	}
	cin >> Eps;
	return 0;
	
}