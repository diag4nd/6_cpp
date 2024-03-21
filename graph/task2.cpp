#include<iostream>
#include"IntGraph.h"

int main(int argc, char* argv[])
{
	int n = 0;
	IntGraph a;
	a.AddNode(0);
	n++;
	a.AddNode(1);
	n++;
	a.AddNode(2);
	n++;
	a.AddNode(3);
	n++;
	a.AddNode(4);
	n++;

	a.AddEdge(1, 0, 1);
	a.AddEdge(1, 0, 2);
	a.AddEdge(1, 1, 3);
	a.AddEdge(1, 1, 4);
	a.get_table();
	std::cout << std::endl;
	std::vector<int> hp = a.get_hamilton_path(-1);
	if (hp.size() == n)
	{
		for (int i = 0; i < n; i++)
		{
			std::cout << hp[i] << "\t";
		}
		std::cout << std::endl;
	}
	else
	{
		std::cout << "!\n";
	}
	
	return 0;
}
