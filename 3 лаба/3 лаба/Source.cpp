#include <vector>
#include <iostream>


class SimplexTable
{
public:
	SimplexTable(const std::vector<double>& functional, const std::vector<std::vector<double>>& inequalities, const std::vector<double>& b1, const std::vector< std::vector<double>>& equalities, const std::vector<double>& b2, const std::vector<bool>& positive) :
		f(functional),
		table(inequalities.size() + equalities.size(),
			std::vector<double>(functional.size())),
		b(b1.size() + b2.size()),
		basis(b1.size() + b2.size())
	{
		initial_variables = functional.size();
		LoadInequalities(inequalities, b1);
		LoadEqualities(equalities, b2, inequalities.size());
		for (size_t i = 0; i < positive.size(); i++)
		{
			if (!positive[i])
			{
				for (size_t j = 0; j < table.size(); j++)
				{
					table[j].push_back(-table[i][j]);
					f.push_back(-f[i]);
				}
			}
		}
		FirstPhase();
		Solve();
	}
	std::vector<double> GetPlan()
	{
		std::vector<double> res(initial_variables);
		for (size_t i = 0; i < basis.size(); i++)
		{
			if (basis[i] < initial_variables)
			{
				res[basis[i]] = b[i];
			}
		}
		return res;
	}
	double GetResult()
	{
		double result = 0;
		for (size_t i = 0; i < basis.size(); i++)
		{
			result += b[i] * f[basis[i]];
		}
		return result;
	}
private:
	void JordanElimination(size_t row, size_t column)
	{
		double element = table[row][column];
		for (size_t j = 0; j < table[row].size(); j++)
		{
			table[row][j] /= element;
		}
		b[row] /= element;
		for (size_t i = 0; i < row; i++)
		{
			for (size_t j = 0; j < column; j++)
			{
				table[i][j] -= table[row][j] * table[i][column];
			}
			for (size_t j = column + 1; j < table[i].size(); j++)
			{
				table[i][j] -= table[row][j] * table[i][column];
			}
			b[i] -= table[i][column] * b[row];
		}
		for (size_t i = row + 1; i < table.size(); i++)
		{
			for (size_t j = 0; j < column; j++)
			{
				table[i][j] -= table[row][j] * table[i][column];
			}
			for (size_t j = column + 1; j < table[i].size(); j++)
			{
				table[i][j] -= table[row][j] * table[i][column];
			}
			b[i] -= table[i][column] * b[row];
		}
		for (size_t i = 0; i < table.size(); i++)
		{
			table[i][column] = 0;
		}
		table[row][column] = 1;
		basis[row] = column;
	}
	void Solve()
	{
		while (true)
		{
			size_t column = 0;
			double min = 0;
			for (size_t j = 0; j < f.size(); j++)
			{
				double assessment = f[j];
				for (size_t i = 0; i < table.size(); i++)
				{
					assessment -= table[i][j] * f[basis[i]];
				}
				if (assessment < min)
				{
					column = j;
					min = assessment;
				}
			}
			if (min == 0.0)
			{
				return;
			}
			size_t row = 0;
			min = -1;
			for (size_t i = 0; ; i++)
			{
				if (b[i] / table[i][column] > 0)
				{
					row = i;
					min = b[i] / table[i][column];
					break;
				}
			}
			for (size_t i = row + 1; i < table.size(); i++)
			{
				if (b[i] / table[i][column] > 0 && b[i] / table[i][column] < min)
				{
					row = i;
					min = b[i] / table[i][column];
				}
			}
			if (min == -1)
			{
				throw std::exception("Functional is not bounded");
			}
			JordanElimination(row, column);
		}
	}
	void LoadInequalities(const std::vector<std::vector<double>>& inequalities, const std::vector<double>& b1)
	{
		for (size_t i = 0; i < inequalities.size(); i++)
		{
			if (b1[i] >= 0)
			{
				b[i] = b1[i];
				for (size_t j = 0; j < inequalities[i].size(); j++)
				{
					table[i][j] = inequalities[i][j];
				}
				basis[i] = table[i].size();
				for (size_t j = 0; j < table.size(); j++)
				{
					table[j].push_back(0);
				}
				table[i].back() = 1;
				f.push_back(0);
			}
			else
			{
				b[i] = -b1[i];
				for (size_t j = 0; j < inequalities[i].size(); j++)
				{
					table[i][j] = -inequalities[i][j];
				}
				for (size_t j = 0; j < table[i].size(); j++)
				{
					table[j].push_back(0);
				}
				table[i].back() = -1;
				slack_variables.push_back(i);
			}
		}
	}
	void LoadEqualities(const std::vector<std::vector<double>>& equalities, const std::vector<double>& b2, size_t ineq_count)
	{
		for (size_t i = 0; i < equalities.size(); i++)
		{
			if (b2[i] >= 0)
			{
				b[ineq_count + i] = b2[i];
				for (size_t j = 0; j < equalities[i].size(); j++)
				{
					table[ineq_count + i][j] = equalities[i][j];
				}
			}
			else
			{
				b[ineq_count + i] = -b2[i];
				for (size_t j = 0; j < equalities[i].size(); j++)
				{
					table[ineq_count + i][j] = -equalities[i][j];
				}
			}
			slack_variables.push_back(ineq_count + i);
		}
	}
	void FirstPhase()
	{
		if (slack_variables.size() != 0)
		{
			std::vector<double> temp = f;
			f.resize(table[0].size() + slack_variables.size());
			for (size_t i = 0; i < table[0].size(); i++)
			{
				f[i] = 0;
			}
			for (size_t i = table[0].size(); i < f.size(); i++)
			{
				f[i] = 1;
			}
			for (unsigned int i : slack_variables)
			{
				basis[i] = table[i].size();
				for (auto& v : table)
				{
					v.push_back(0);
				}
				table[i].back() = 1;
			}
			Solve();
			if (GetResult() != 0)
			{
				throw std::exception("No solution");
			}
			for (auto& v : table)
			{
				v.resize(v.size() - slack_variables.size());
			}
			f = temp;
		}
	}
	std::vector<unsigned int> slack_variables;
	size_t initial_variables;
	std::vector<unsigned int> basis;
	std::vector<double> b;
	std::vector<std::vector<double>> table;
	std::vector<double> f;
};

int main()
{
	std::vector<double> f = { 1, -3 , 2 , 1, 4 };
	std::vector<std::vector<double>> i = { {1, 2, -1, 2, 4}, {0, -1, 2, 1, 3}, {1, -3, 2, 2, 0} }, e = {};
	std::vector<double> b1 = { 1, 3, 4 }, b2 = {};
	std::vector<bool> p = { true, true, true, true, true };
	SimplexTable s(f, i, b1, e, b2, p);
	std::vector<double> plan = s.GetPlan();
	for (auto& x : plan)
	{
		std::cout << x << ' ';
	}
	std::cout << std::endl << s.GetResult();
	int k;
	std::cin >> k;
	return 0;
}