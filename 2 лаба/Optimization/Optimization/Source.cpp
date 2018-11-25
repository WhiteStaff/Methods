#include <iostream>
int main()
{
	int a;
	int graph[9][10] = {
	{0,7,9,4,0,0,0,0,0,0},
	{0,0,0,0,0,5,0,8,0,0},
	{0,0,0,0,6,0,0,0,0,0},
	{0,0,0,0,0,7,0,0,0,0},
	{0,0,0,0,0,0,7,0,0,0},
	{0,0,0,0,0,0,5,0,2,0},
	{0,0,0,0,0,0,0,0,0,9},
	{0,0,0,0,0,0,0,0,6,0},
	{0,0,0,0,0,0,0,0,0,8}
	};
	int min[10] = {0,0,0,0,0,0,0,0,0,0};

	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (graph[i][j] > 0)
			{
				graph[i][j] += min[i];
				if (min[j] == 0)
				{
					min[j] = graph[i][j];
				}
				else
				{
					if (min[j] > graph[i][j])
					{
						min[j] = graph[i][j];
					}
				}
			}
		}
	}
	std::cout << min[9];
	std::cin >> a;
	return 0;
}