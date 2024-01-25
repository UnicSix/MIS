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
    g1.RandG(100);
    g1.printGraph();
    cout << endl ;
    cout << myGraph::ms(g1) << endl;
    return 0;
}

