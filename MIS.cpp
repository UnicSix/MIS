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
    //g1.RandG(30);

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
    BronKerbosch(R, P, X, N, MAXSET); 
    bool MIS[100];
    for(int i=0; i<100 ;i++)
        MIS[i] = 1;
    for (auto elem : MAXSET)
        MIS[elem] = 0;
    cout << endl << "Maximum Independent Set: ";
    for(int i=0; i<order; i++)
        if(MIS[i] != 0)
            cout << i << " ";
    g1.CopyG(vg1);
    g1=g1.ComplementG();
    g1.printGraph();
    cout << myGraph::ms(g1) << '\n';
    return 0;
}

