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
    cin >> order;
    myGraph g1(order);
    //g1.RandG(100);
    g1.printGraph();
    
    cout << endl ;
    // vector<int> vset=g1.LeastCntG();
    // (g1-vset).printGraph();
    // g1.LeastCntG(g1.getGrhSize());
    // (g1-(g1-vset)).printGraph();
    cout << myGraph::ms(g1) << endl;
    // int A = g1.MaxDegreeVtx();
    // myGraph::test(g1-g1.Nbar(A));
    return 0;
}

