#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

#include "myGraph.h"
#include "BronKerboschreverse.h"

using namespace std;

int prob = 20;	//0~100

int main()
{
    int order;
    //cin >> order;
    order = 30;
    // myGraph g1("test.txt");
    myGraph g1(order);
    // myGraph g2(order);
    //g1.RandG(30);
    vector<long long> v = { 321,646,70,328,240,48,93,914,393,642 };
    vector<long long> v1 = { 0,0,0,0,0 };
    //delete nodes except 12 ,13 ,18;
    // g1 = g1 - 0 - 1 - 2 - 3 - 4 - 5 - 6 - 7 - 8 - 9 - 10 - 11 - 14 - 15 - 16 - 17 - 19;
    //test the result of N_intersec function. call the function and print the result
    
    //g2.printGraph();
    //vector<int> vset=g1.LeastCntG(g1.getOrder(), g1.getGrhSize());
    //for(int i: vset)
	//	cout << i << ' ';
    // (g1-vset).printGraph();
    // g1.LeastCntG(g1.getGrhSize());
    // (g1-(g1-vset)).printGraph();
    // int A = g1.MaxDegreeVtx();
    // myGraph::test(g1-g1.Nbar(A));

    vector<vector<int>> vg1;
    set<int> R, P, X, MAXSET;
    vector<set<int>> N;
    GenerateMatrix(order, prob, vg1);
    for(auto i:vg1)
    {
        for(auto j:i)
        {
            cout << j << "";
        }
        cout << '\n';
    }
    cout << '\n';

    //initial setting P
    for(int i = 0; i < order; i++)
        P.insert(i);
    //initial setting N
    for(int i = 0; i < order; i++)
    {
        set<int> neighbor;
        for(int j = 0; j < order; j++)
        {
            if(vg1[i][j]==1)
                neighbor.insert(j);
        }
        N.push_back(neighbor);
    }	
    //run Bron Kerbosch
    //BronKerbosch(R, P, X, N, MAXSET); 
    // bool MIS[100];
    // for(int i=0; i<100 ;i++)
        // MIS[i] = 1;
    // for (auto elem : MAXSET)
        // MIS[elem] = 0;
    // cout << endl << "Maximum Independent Set: ";
    // for(int i=0; i<order; i++)
        // if(MIS[i] != 0)
            // cout << i << " ";
    g1.CopyG(vg1);
    g1.printGraph();
    g1= g1.ComplementG();
    g1.printGraph();
    cout << myGraph::ms(g1) << '\n';
    return 0;
}

