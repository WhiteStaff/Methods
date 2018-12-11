#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <queue>

using namespace std;



class TransportTable
{
public:
	TransportTable(const vector<vector<double>>& _prices, const vector<double>& _a, const vector<double>& _b) : table(_a.size(), vector<double>(_b.size())), prices(_prices), a(_a), b(_b)
	{
		double a_sum = 0, b_sum = 0;
		for (double x : a)
		{
			a_sum += x;
		}
		for (double x : b)
		{
			b_sum += x;
		}
		if (a_sum > b_sum)
		{
			for (size_t i = 0; i < table.size(); i++)
			{
				table[i].push_back(0);
				prices[i].push_back(0);
			}
			b.push_back(a_sum - b_sum);
		}
		else if (a_sum < b_sum)
		{
			table.push_back(vector<double>(b.size(), 0));
			prices.push_back(vector<double>(b.size(), 0));
			a.push_back(b_sum - a_sum);
		}
		GetFirstPlan();
		Solve();
	}
	vector<vector<double>>& GetSolution()
	{
		return table;
	}
	double GetResult()
	{
		double result = 0.0;
		for (size_t i = 0; i < table.size(); i++)
		{
			for (size_t j = 0; j < table[i].size(); j++)
			{
				result += table[i][j] * prices[i][j];
			}
		}
		return result;
	}
private:
	void GetFirstPlan()
	{
		size_t i = 0, j = 0;
		double a_left, b_left = b[0];
		for (; i < a.size(); i++)
		{
			a_left = a[i];
			for (; ;)
			{
				if (a_left >= b_left)
				{
					table[i][j] = b_left;
					a_left -= b_left;
					basis_row[i].insert(j);
					basis_column[j].insert(i);
					j++;
					if (j >= b.size())
						break;
					b_left = b[j];
				}
				else
				{
					table[i][j] = a_left;
					b_left -= a_left;
					basis_row[i].insert(j);
					basis_column[j].insert(i);
					break;
				}
			}
		}
	}
	void Solve()
	{
		while (true)
		{
			vector<double> u(a.size()), v(b.size());
			vector<bool> u_checked(a.size()), v_checked(b.size());
			u_checked[0] = true;
			queue<size_t> q;
			q.push(0);

			while (!q.empty())
			{
				size_t s = q.size();
				for (size_t i = 0; i < s; i++)
				{
					for (auto col : basis_row[q.front()])
					{
						if (!v_checked[col])
						{
							v_checked[col] = true;
							q.push(col);
							v[col] = prices[q.front()][col] - u[q.front()];
						}
					}
					q.pop();
				}
				s = q.size();
				for (size_t i = 0; i < s; i++)
				{
					for (auto row : basis_column[q.front()])
					{
						if (!u_checked[row])
						{
							u_checked[row] = true;
							q.push(row);
							u[row] = prices[row][q.front()] - v[q.front()];
						}
					}
					q.pop();
				}
			}

			double min = 0;


			for (size_t i = 0; i < prices.size(); i++)
			{
				for (size_t j = 0; j < prices[i].size(); j++)
				{
					if (prices[i][j] - u[i] - v[j] < min)
					{
						min = prices[i][j] - u[i] - v[j];
						row = i;
						col = j;
					}
				}
			}
			if (min == 0)
			{
				return;
			}

			Redestribution();
		}
	}
	void Redestribution()
	{
		basis_row[row].insert(col);
		basis_column[col].insert(row);
		cycle.clear();
		cycle.push_back(col);
		cycle.push_back(row);
		LookUpHorizontal(row);
		size_t r = row, c, min_r = row, min_c = cycle[2];
		double min = table[row][cycle[2]];
		for (size_t i = 2; ; i++)
		{
			c = cycle[i];
			if (table[r][c] < min)
			{
				min = table[r][c];
				min_r = r;
				min_c = c;
			}
			i++;
			if (i >= cycle.size())
			{
				break;
			}
			r = cycle[i];
		}
		table[row][col] = min;
		r = row;
		for (size_t i = 2; ; i++)
		{
			c = cycle[i];
			table[r][c] -= min;
			i++;
			if (i >= cycle.size())
			{
				break;
			}
			r = cycle[i];
			table[r][c] += min;
		}
		basis_row[min_r].erase(min_c);
		basis_column[min_c].erase(min_r);

	}
	bool LookUpHorizontal(size_t r)
	{
		for (auto c : basis_row[r])
		{
			if (c == cycle[cycle.size() - 2])
			{
				continue;
			}
			if (r == row && c == col)
			{
				return true;
			}
			cycle.push_back(c);
			if (LookUpVertical(c))
			{
				return true;
			}
			cycle.pop_back();
		}
		return false;
	}
	bool LookUpVertical(size_t c)
	{

		for (auto r : basis_column[c])
		{
			if (r == cycle[cycle.size() - 2])
			{
				continue;
			}
			if (r == row && c == col)
			{
				return true;
			}
			cycle.push_back(r);
			if (LookUpHorizontal(r))
			{
				return true;
			}
			cycle.pop_back();
		}
		return false;
	}

	size_t row = 0, col = 0;
	vector<size_t> cycle;
	map<size_t, set<size_t>> basis_row;
	map<size_t, set<size_t>> basis_column;
	vector<vector<double>> table;
	vector<double> a;
	vector<double> b;
	vector<vector<double>> prices;
};

int main()
{
	vector<double> a = { 50, 30, 10 }, b = { 30, 20, 10 , 20 };
	vector<vector<double>> c = { {1, 2, 4, 1}, {2, 3, 1, 5}, {3, 2, 4, 4} };
	TransportTable t(c, a, b);
	vector<vector<double>> res = t.GetSolution();
	for (size_t i = 0; i < res.size(); i++)
	{
		for (size_t j = 0; j < res[i].size(); j++)
		{
			cout << res[i][j] << ' ';
		}
		cout << endl;
	}
	cout << endl << t.GetResult() << endl;
	int x;
	cin >> x;
	return 0;
}