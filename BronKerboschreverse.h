#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <sstream>
#include <fstream>
#include <ctime>
#include <string>
using namespace std;

int numVertices = 0;

void GenerateMatrix(int vertex_num, int prob, vector<vector<int>> &matrix)
{
	srand(time(NULL));
	
	for(int i = 0; i < vertex_num; ++i)
	{
        vector<int> row(vertex_num, 0);
        matrix.push_back(row);
    }
	
	int ONE = (vertex_num * vertex_num - vertex_num) / 2 * prob / 100;
	
	int num = 0;
	while(num < ONE)
	{
		int x = rand() % vertex_num;
		int y = rand() % vertex_num;
		if(x == y)
			continue;
		else
		{
			if(matrix[x][y] == 1)
				continue;
			else
			{
				matrix[x][y] = 1;
				matrix[y][x] = 1;
				num++;
			}
		}
	}
}

void ReadMatrix(vector<vector<int>> &matrix, string filename)
{
	ifstream inputFile(filename);

    if (!inputFile.is_open()) 
	{
        cout << "Failed to open the file" << endl;
        return;
    }

    string line;
    while (getline(inputFile, line)) 
	{
        vector<int> row;
        for (char& c : line) 
		{
            int digit = c - '0';
            row.push_back(digit);
        }
        reverse(row.begin(), row.end());
        matrix.push_back(row);
    }	
    inputFile.close();
	
	numVertices = matrix.size();
	
	for(int i = 0; i < matrix.size(); i++)
		matrix[i][i] = 0;
}

// return a pivot from (P union X), pivot is a vertex that have most neighbors from PX
int getPivot(set<int> P, set<int> X, vector<set<int>>& N)
{
	set<int> PX;
	set_union(P.begin(), P.end(), X.begin(), X.end(), inserter(PX, PX.begin()));

	int pivot = *PX.begin();
	int max_size = N[pivot].size();

	for(auto elem : PX)
	{
		if(N[elem].size() > max_size) {
			max_size = N[elem].size();
			pivot = elem;
		}
	}
	return pivot;
}

void BronKerbosch(set<int> R, set<int> P, set<int> X, vector<set<int>>& N, set<int>& MAXSET)
{
	if(P.empty() && X.empty())
	{
		if(MAXSET.size() < R.size())
			MAXSET = R;
		cout << "Maximal clique: ";
		for (auto elem : R)
			cout << elem << " ";
		cout << endl;
		
		return;
	}

	int pivot = getPivot(P, X, N);
	set<int> PE;     //所有需要造訪的節點 
	set_difference(P.begin(), P.end(), N[pivot].begin(), N[pivot].end(), inserter(PE, PE.begin()));

	for(auto elem : PE)
	{
		R.insert(elem);
		set<int> PN, XN;
		set_intersection(P.begin(), P.end(), N[elem].begin(), N[elem].end(), inserter(PN, PN.begin()));
		set_intersection(X.begin(), X.end(), N[elem].begin(), N[elem].end(), inserter(XN, XN.begin()));
		BronKerbosch(R, PN, XN, N, MAXSET);
		R.erase(elem);
		P.erase(elem);
		X.insert(elem);
	}
}

