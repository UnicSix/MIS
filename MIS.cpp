#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

#include "myGraph.h"

using namespace std;

int Probability = 90;	//0~100
void test(int*);                      

int main()
{
    int order;
    cout << "Graph order: ";
    //cin >> order;
    order = 5;
    myGraph g1(order);
    myGraph g2(order);
    g2.RandG(30);
    vector<long long> v = { 9,6,6,25,24 };
    vector<long long> v1 = { 0,0,0,0,0 };
    g1.CreateG(v);
    
    cout << '\n';
    g2.printGraph();
    //vector<int> vset=g1.LeastCntG(g1.getOrder(), g1.getGrhSize());
    //for(int i: vset)
	//	cout << i << ' ';
    // (g1-vset).printGraph();
    // g1.LeastCntG(g1.getGrhSize());
    // (g1-(g1-vset)).printGraph();
    cout << myGraph::ms(g2) << '\n';
    // int A = g1.MaxDegreeVtx();
    // myGraph::test(g1-g1.Nbar(A));

    
    return 0;
}

