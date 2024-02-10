#ifndef MYGRAPH_H
#define MYGRAPH_H
#include <cstddef>
#include <vector>
#include <bitset>
#include <list>
#include <ctime>
#include <iostream>

using namespace std;

class myGraph{
  public:
    myGraph(int); //set graph size
    myGraph(int, int); // set graph and init all edge 0
    myGraph operator-(const myGraph &other);
    myGraph operator-(int v);
    myGraph operator-(vector<int>);
    myGraph operator+(myGraph &other);
    myGraph& operator=(const myGraph &other);
    myGraph VertexSetSubG(vector<int>);
    //create a induced subgragph with neighbours of vertex v
    myGraph NeighbourSubG(int v);  //N
    myGraph NeighbourSubG2(int v); //N2
    myGraph NbarSubG(int v);
    vector<int> N(int v);
    vector<int> N2(int v);
    vector<int> Nbar(int v);
    void RandG(int);     //return randomized Graph
    void CreateG(vector<long long>);    //return a graph with a given vector
    void printGraph();
    void printVtxDeg();
    bool edge(int, int); //is vertex m, n connected to each other
    bool dominate(myGraph);
    bool isConnected();
    bool cmpEdge(int s1, int s2);
    int getOrder(){return order;}
    // static int ms(myGraph&);
    // static int ms(myGraph&, vector<int>);
    // static int ms2(myGraph&, vector<int>);
    static int ms(myGraph);
    static int ms(myGraph, vector<int>);
    static int ms2(myGraph, vector<int>);
    int MinimalDegreeVertex();
    int MaxDegreeVtx();
    int GreatestNeighbourVtx(int);
    int getGrhDeg();
    int getVtxDeg(int v);
    int getGrhSize() const {return int(adj.size());}
    vector<int> LeastCntG(int g_size, int prnt_size);
    vector<int> sortVtxSet(vector<int>);
    vector<int>N_Intersec(int, int);
  
    static bool dominate(vector<int>, vector<int>);
    static void test(myGraph);

  private:
    /*Variables*/
    vector<long long> adj;
    vector<int> vertex_degree;
    int degree;
    size_t order;

    /*Functions*/
    void countVtxDeg();                         
    void countGrhDeg();
    void DFS(int, vector<int>&, long long*);
    void DFS(int, long long*);
};

#endif 
