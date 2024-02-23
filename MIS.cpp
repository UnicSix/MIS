#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>
#include <chrono>

#include "myGraph.h"
#include "BronKerboschreverse.h"

using namespace std;


int main()
{
    int order;
    //cin >> order;
    order = 50;
    int prob = 80;	//0~100
    // myGraph g1("test.txt");
    //g1.RandG(30);

    set<int> R, P, X, MAXSET;
    vector<set<int>> N;
    float sum_time=0;
    for(int i=0; i<100; i++)
    {
        vector<vector<int>> vg1;
        myGraph g1(order);
        GenerateMatrix(order, prob, vg1);
        g1.CopyG(vg1);
        g1=g1.ComplementG();
        // g1.printGraph();
        //count runtime of ms function using chrono library
        auto start = chrono::high_resolution_clock::now();
        cout << myGraph::ms(g1) << '\n';
        auto end = chrono::high_resolution_clock::now();
        float time = chrono::duration_cast<chrono::microseconds>(end - start).count();
        sum_time += time/1000000;
        cout << "Time: " << time/1000000 << " second\n";
    }
    cout << "Average time: " << sum_time/100<< " second\n";
    // for(auto i:vg1)
    // {
        // for(auto j:i)
        // {
            // cout << j << "";
        // }
        // cout << '\n';
    // }
    // cout << '\n';

    //initial setting P
    // for(int i = 0; i < order; i++)
        // P.insert(i);
    //initial setting N
    // for(int i = 0; i < order; i++)
    // {
        // set<int> neighbor;
        // for(int j = 0; j < order; j++)
        // {
            // if(vg1[i][j]==1)
                // neighbor.insert(j);
        // }
        // N.push_back(neighbor);
    // }	
    //run Bron Kerbosch
    // BronKerbosch(R, P, X, N, MAXSET); 
    // bool MIS[100];
    // for(int i=0; i<100 ;i++)
        // MIS[i] = 1;
    // for (auto elem : MAXSET)
        // MIS[elem] = 0;
    // cout << endl << "Maximum Independent Set: ";
    // for(int i=0; i<order; i++)
        // if(MIS[i] != 0)
            // cout << i << " ";
    return 0;
}

