#ifndef INTGRAPH_H
#define INTGRAPH_H
#include <vector>

class IntGraph
{
private:
	int n_m;
	int** connect_m;
	std::vector<std::vector<int>> table; 
	bool hamilton(int curr, std::vector<bool>& visited, std::vector<int>& path);
public:
	void AddNode(int var);

	void DelNode(int var);

	void AddEdge(int var, int node_1, int node_2);

	void DelEdge(int node_1, int node_2);

	void operator=(IntGraph& G);

	void print_connect();

	void get_table();

	void get_path();
	
	IntGraph(): n_m(0), connect_m(nullptr){}

	void CleanUp();

	std::vector<int> get_hamilton_path(int curr);

	~IntGraph()
	{
		(*this).CleanUp();
	}
};

std::vector<int> append(int idx, std::vector<int>& v);

#endif
