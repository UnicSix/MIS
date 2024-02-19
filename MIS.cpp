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
    order = 30;
    // myGraph g1("test.txt");
    myGraph g1(order);
    myGraph g2(order);
    g1.RandG(30);
    vector<long long> v = { 321,646,70,328,240,48,93,914,393,642 };
    vector<long long> v1 = { 0,0,0,0,0 };
    
    cout << '\n';
    //delete nodes except 12 ,13 ,18;
    // g1 = g1 - 0 - 1 - 2 - 3 - 4 - 5 - 6 - 7 - 8 - 9 - 10 - 11 - 14 - 15 - 16 - 17 - 19;
    g1.printGraph();
    //test the result of N_intersec function. call the function and print the result
    
    //g2.printGraph();
    //vector<int> vset=g1.LeastCntG(g1.getOrder(), g1.getGrhSize());
    //for(int i: vset)
	//	cout << i << ' ';
    // (g1-vset).printGraph();
    // g1.LeastCntG(g1.getGrhSize());
    // (g1-(g1-vset)).printGraph();
    cout << myGraph::ms(g1) << '\n';
    // int A = g1.MaxDegreeVtx();
    // myGraph::test(g1-g1.Nbar(A));

    
    return 0;
}

