#include <iostream>
#include <vector>
#include "IntGraph.h"

void IntGraph::AddNode(int var)
{
	for(int i = 0; i < n_m; i++)
	{
		if(connect_m[i][0] == var)
		{
			std::cerr << "Node already exists\n";
			//return;
			exit(-1);
		}
	}

	int** new_p = new int*[n_m+1];
	/*
	for(int i = 0; i < n_m; i++)
	{
			new_p[i] = connect_m[i];
	}
	*/
	new_p[n_m] = new int(n_m+1);
	std::vector<std::vector<int>> tempo (n_m + 1, 0);
	new_p[n_m][0] = var;
	for (int i = 0; i < n_m; i++)
	{
		new_p[i] = connect_m[i];
		new_p[n_m][i + 1] = 0;

	}
	delete[] connect_m;
	connect_m = new_p;
	n_m++;
	
}

void IntGraph::DelNode(int var)
{
	int ind, c = 1;
	for(int i = 0; i < n_m; i++)
	{
		if(connect_m[i][0] == var)
		{
			ind = i;
			c = 0;
		}
	}
	if(c)
	{
		std::cerr << "No such node in graph\n";
		//return;
		exit(-1);
	}
	for(int i = ind; i < n_m-1; i++ )
	{
		delete[] connect_m[i];
		connect_m[i] = new int[i+1];
		for(int j = 0; j < ind+1; j++)
		{
			connect_m[i][j] = connect_m[i+1][j];
		}
		for(int j = ind+1; j < i+1; j++)
		{
			connect_m[i][j] = connect_m[i+1][j+1];
		}
	}
	delete[] connect_m[n_m-1];
	int** new_p = new int*[n_m-1];
	for(int i = 0; i < n_m-1; i++)
	{
		new_p[i] = connect_m[i];
	}
	delete[] connect_m;
	connect_m = new_p;
	n_m--;
}

void IntGraph::AddEdge(int var, int node_1, int node_2)
{
	int ind_1 = -1, ind_2 = -1, c1 = 1, c2 = 1;
	for(int i = 0; i < n_m; i++)
	{
		if(connect_m[i][0] == node_1)
		{
			ind_1 = i;
			c1 = 0;
		}
		if(connect_m[i][0] == node_2)
		{
			ind_2 = i;
			c2 = 0;
		}
	}
	if( (c1 != 0) || (c2 != 0) )
	{
		std::cerr << "No such edge in graph\n";
		//return;
		exit(-1);
	}
	
	if(ind_1 < ind_2)
	{
		connect_m[ind_2][ind_1+1] = var;
	}
	else if (ind_1 > ind_2)
	{
		connect_m[ind_1][ind_2+1] = var;
	}
	
	else
	{
		std::cerr << "Can not do this\n";
		exit(-1);
	}
}

void IntGraph::DelEdge(int node_1, int node_2)
{	
	AddEdge(0, node_1, node_2);
}

void IntGraph::operator=(IntGraph& G)
{
	(*this).CleanUp();
	n_m = G.n_m;
	connect_m = new int*[n_m];
	for(int i = 0; i < n_m; i++)
	{
		connect_m[i] = new int[i+1];
		for(int j = 0; j < i+1; j++)
		{
			connect_m[i][j] = G.connect_m[i][j];
		}
	}
}

void IntGraph::print_connect()
{
	for(int i = 0; i < n_m; i++)
	{
		for(int j = 0; j < i+1; j++)
		{
			std::cout << connect_m[i][j] << " ";
		}
		std::cout << std::endl;
	}
}

void IntGraph::get_table()
{
	std::vector<std::vector<int>> tempo(n_m, std::vector<int>(n_m, 0));
	for (int i = 0; i < n_m; i++)
	{
		for (int j = n_m - 1; j > i; j--)
		{
			tempo[i][j] = connect_m[j][i + 1];
			tempo[j][i] = tempo[i][j];
		}
	}

	table = tempo;
	for (int i = 0; i < n_m; i++)
	{
		for (int j = 0; j < n_m; j++)
		{
			std::cout << table[i][j] << "\t";
		}
		std::cout << std::endl;
	}
}

bool IntGraph::hamilton(int idx, std::vector<bool>& visited, std::vector<int>& path)
{
	path.insert(path.end(), idx);
	if (path.size() == n_m)
	{
		return true;
	}
	visited[idx] = true;
	for (int nxt = 0; nxt < n_m; nxt++)
	{
		if (table[idx][nxt] != 0 && !visited[nxt])
		{
			if (hamilton(nxt, visited, path))
			{
				return true;
			}
		}
	}
	visited[idx] = false;
	path.pop_back();
	return false;
}

std::vector<int> IntGraph::get_hamilton_path(int curr)
{
	std::vector<bool> visited (n_m, 0);
	std::vector<int> path;

	for (int i = 0; i < n_m; i++)
	{
		if (curr == -1)
		{
			hamilton(i, visited, path);
			if (path.size() == n_m)
			{
				return path;
			}
			continue;
		}
		else if (curr >= 0 )
		{
			if (i == curr)
			{
				hamilton(i, visited, path);
				if (path.size() == n_m)
				{
					return path;
				}
				std::cout << "No way found\n";
				exit(-1);
			}
			else
			{
				continue;
			}
		}
		else
		{
			std::cerr << "Incorrect argument\n";
			exit(-1);
		}
	}
	std::cout << "No way found\n";
	exit(-1);
	
}

void IntGraph::CleanUp()
{
	for(int i = 0; i < n_m; i++)
	{
		delete[] connect_m[i];
	}
	delete[] connect_m;
}
