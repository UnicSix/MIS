#include "myGraph.h"
#include <bitset>
#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <vector>
#include <math.h>


myGraph::myGraph(int m){
  order = m;
  degree = 0;
  long long unit=1;
  for(int i=0; i<m; i++){
    long long temp_v=0;
    temp_v = 1LL << i;
    adj.push_back(temp_v);
    vertex_degree.push_back(0);
  }
  countGrhDeg();
  countVtxDeg();
  return;
}

myGraph::myGraph(int m, int zero){
  if(zero!=0){
    throw runtime_error("invalid argument");
  }
  order = 0;
  degree = 0;
  for(size_t i=0; i<m; i++){
    adj.push_back(0);
  }
  countGrhDeg();
  countVtxDeg();

  return;
}

bool myGraph::edge(int v1, int v2){
  long long temp = (adj[v1]>>v2)%2&1;
  return temp;
}

void myGraph::printGraph(){
  cout << endl;
  for(size_t i=0; i<adj.size(); i++){
    cout << bitset<64>(adj[i]) << endl;
  }
  return;
}

void myGraph::RandG(int cnt_rate){
  srand(time(NULL));
  for(size_t i=0; i<adj.size(); i++){
    for(size_t j=i; j<adj.size(); j++){
      int cnt = rand()%100;
      if(cnt < cnt_rate && i!=j){
        adj[i] |= 1LL<<j;
        adj[j] |= 1LL<<i;
      }
    }
  }
  /*Set degree properties*/
  countGrhDeg();
  countVtxDeg();
  return;
}

void myGraph::printVtxDeg(){
    cout << "size: " << vertex_degree.size() << endl;
    for(int i:vertex_degree) cout << i << " ";
}

void myGraph::countVtxDeg(){
  int d=0;
  long long temp;
  for(size_t i=0; i<adj.size(); i++){
    if(adj[i]!=0)
    {
        temp=adj[i];
        while(temp!=0){
          if((temp%2)&1) d++;
          temp>>=1;
        }
      vertex_degree[i]=d-1;
      d=0;
    }
    else
    {
      vertex_degree[i]=-1;
    }
  }
}

void myGraph::countGrhDeg(){
  int dg=0;
  long long cur_v;
  for(size_t i=0; i<adj.size(); i++){
    if(adj[i]!=0)
    {
      cur_v = adj[i];
      for(size_t j=i; j>0; j--){
        dg+=cur_v%2&1;
        cur_v>>=1;
      }
    }
  }
  degree = dg;
}

myGraph myGraph::NeighbourSubG2(int v){
  myGraph sub2Graph(adj.size());
  sub2Graph = *this;
  for(size_t i=0; i<adj.size(); i++){
    if(edge(v,i))
      sub2Graph=sub2Graph-i;
  }
  return sub2Graph;
}

myGraph myGraph::NeighbourSubG(int v){
  myGraph subGraph(adj.size());
  subGraph.adj = adj;
  subGraph.order=0;
  for(size_t i=0; i<adj.size(); i++){
    //vertex v is connected with vertex i
    if(!edge(v, i) || v==int(i)){ 
      subGraph.adj[i]=0;      
      for(size_t j=0; j<adj.size(); j++){
        subGraph.adj[j] &= ~(1LL<<i);
      }
    }
    else if(edge(v, i)){
      subGraph.adj[i] &= ~(1LL<<v);
      subGraph.order++;
    }
  }
  subGraph.countGrhDeg();
  subGraph.countVtxDeg();
  return subGraph;
}

myGraph& myGraph::operator=(const myGraph &other){
  vertex_degree = other.vertex_degree;
  order = other.order;
  degree = other.degree;
  adj = other.adj;
  return *this;
}
myGraph myGraph::operator+(myGraph &other){
  myGraph addition(order);
  for(size_t i=0; i<adj.size(); i++){
    
  }
  return addition;
}

myGraph myGraph::operator-(vector<int> v){
  //remove vertex from graph
  myGraph new_graph = *this;
  for(size_t i=0; i<adj.size(); i++){
    for(int j:v){
      new_graph.adj[i]&=~(1LL<<j);
      new_graph.adj[j]=0;
      if(((adj[i]>>i)%2)&1 && i==j)
        new_graph.order--;
    }
  }
  new_graph.countGrhDeg();
  new_graph.countVtxDeg();
  return new_graph;
}

myGraph myGraph::operator-(int v){
  //remove vertex from graph
  myGraph new_graph = *this;
  for(size_t i=0; i<adj.size(); i++){
    new_graph.adj[i]&=~(1LL<<v);
  }
  new_graph.order--;
  new_graph.adj[v]=0;
  new_graph.countGrhDeg();
  new_graph.countVtxDeg();
  return new_graph;
}

myGraph myGraph::operator-(const myGraph &other){
  myGraph submission(adj.size());
  vector<int> exc_vtx;
  for(size_t i=0; i<adj.size(); i++){
    if(other.adj[i]!=0){
      submission.adj[i] = 0;
      exc_vtx.push_back(i);
    }
    else{
      submission.adj[i] = adj[i];
    }
  }
  for(int i:exc_vtx){
      for(size_t k=0; k<adj.size(); k++){
        submission.adj[k]&=~(1LL<<i);
        submission.order--;
      }   
  }
  submission.countGrhDeg();
  submission.countVtxDeg();
  return submission;
}

vector<int> myGraph::sortVtxSet(vector<int> S){
    vector<int> v = vertex_degree;
    vector<int> s = S;
    sort(s.begin(), s.end(), [&v](int s1, int s2){return v[s1]<v[s2];});
    return s;
}

vector<int> myGraph::N_Intersec(int s1, int s2){
    vector<int> intersec;
    vector<int> Ns1=N(s1);
    vector<int> Ns2=N(s2);
    sort(Ns1.begin(), Ns1.end());
    sort(Ns2.begin(), Ns2.end());
    set_intersection(Ns1.begin(), Ns1.end(), Ns2.begin(), Ns2.end(), intersec.begin());
    return intersec;
}



int myGraph::ms(myGraph G){
    if(!G.isConnected()) {
      int g_size=int(G.order);
      int prnt_size=int(G.adj.size()); 
      vector<int> C_set = G.LeastCntG(g_size, prnt_size);
      // myGraph C = G.VertexSetSubG(C_set);
      myGraph C = G.VertexSetSubG(C_set);
      if(C.order<=2) return ms(G-C_set)+1;
      else            return ms(G-C_set)+ms(C);
    }
    if(G.order<=1) return int(G.order);
    int A = G.MinimalDegreeVertex();
    int B = G.GreatestNeighbourVtx(A);
    int dg = G.getVtxDeg(A);
    if(dg==1){ return 1+ms(G-G.Nbar(A)); }
    else if(dg==2){
        int B2=0;
        for(size_t i=0; i<G.adj.size(); i++){
          if(G.edge(i,A)&&i!=B)
          {
              B2=i;
              break;
          }
        }
        if(G.edge(B,B2)) return 1+ms(G-G.Nbar(A));
        return max(2+ms(G-G.Nbar(B)-G.Nbar(B2)), 1+ms2(G-G.Nbar(A),G.N2(A)));
    }
    else if(dg==3){
        return max(ms2(G-A, G.N(A)), 1+ms(G-G.Nbar(A)));
    }
    else if(dominate(G.N(A), G.N(B))){
        return ms(G-B);
    }
    return max(ms(G-B), 1+ms(G-G.Nbar(B)));
    return 0;
}

bool myGraph::dominate(vector<int> NA, vector<int> NB){
    vector<int>::iterator it = NA.begin();
    for(size_t i=0; i<NB.size(); i++){
        it = find(NA.begin(), NA.end(), NB[i]);
        if(it == NA.end()) return false;
    }
    return true;
}


int myGraph::ms(myGraph G, vector<int> S){
    S = G.sortVtxSet(S);
    int s1=S[0], s2=S[1];
    vector<int> intersec = G.N_Intersec(s1, s2);
    if(G.vertex_degree[s1]<=1) return ms(G);
    else if(G.edge(s1,s2)){
        if(G.getVtxDeg(s1)<=3) return ms(G);
        else return max(ms(G-G.Nbar(s1)), ms(G-G.Nbar(s2)))+1;
    }
    // Intersection of Ns1 and Ns2 is not empty
    else if(!intersec.empty()){
        return 1+ms(G-G.N(s1)-G.N(s2), S);
    }
    else if(G.getVtxDeg(s2)==2){
        vector<int> Ns1=G.N(s1);
        int E=Ns1[0], F=Ns1[1];
        if(G.edge(E, F)) return 1+ms(G-G.Nbar(s1));
        vector<int> NF=G.N(F);
        vector<int> collection=G.N(E);
        for(int i:NF)
          if(find(collection.begin(),collection.end(), i)!=collection.end())
            collection.push_back(i);
        vector<int>::iterator it=find(collection.begin(),collection.end(), s1);
        if(it!=collection.end()) collection.erase(it);
        if(!dominate(G.N(s2),collection)) return 3+ms(G-G.Nbar(s1)-G.Nbar(s2));
        return max(1+ms(G-G.Nbar(s1)), 3+ms(G-G.Nbar(E)-G.Nbar(F)-G.Nbar(s2)));
    }
  return max(1+ms(G-G.Nbar(s2)), ms2(G-G.Nbar(s1)-s2, G.N(s2)))+1;
}

int myGraph::ms2(myGraph G, vector<int> S){
    size_t sz = S.size();
    sort(S.begin(), S.end());
    if(sz<=1) return 0;
    else if(sz==2){
        if(G.edge(S[0], S[1])) return 0;
        else return 2+ms(G-G.Nbar(S[0])-G.Nbar(S[1]));
    }
    else if(sz==3){
        if(G.getVtxDeg(S[0])==0) {
            S.erase(S.begin());
            return ms(G-S[0],S);        
        }
        else if(G.edge(S[0],S[1])&&G.edge(S[0],S[2])&&G.edge(S[1],S[2]))
            return 0;
        else if(G.edge(S[0],S[1])&&G.edge(S[0],S[2])&&!G.edge(S[1],S[2]))
            return 2+ms(G-G.Nbar(S[1])-G.Nbar(S[2]));
        else if(G.edge(S[1],S[0])&&G.edge(S[1],S[2])&&!G.edge(S[0],S[2]))
            return 2+ms(G-G.Nbar(S[0])-G.Nbar(S[2]));
        else if(G.edge(S[2],S[0])&&G.edge(S[2],S[1])&&!G.edge(S[0],S[1]))
            return 2+ms(G-G.Nbar(S[0])-G.Nbar(S[1]));
        else if(G.edge(S[0],S[1])) {
            return ms(G-G.Nbar(S[2]),S);
        }
        else if(G.edge(S[0],S[1])) return 1+ms(G-G.Nbar(S[2]),S);
        else if(G.edge(S[0],S[2])) return 1+ms(G-G.Nbar(S[1]),S);
        else if(G.edge(S[1],S[2])) return 1+ms(G-G.Nbar(S[0]),S);
        //else if v belongs to the intersection of Ns1 and Ns2
        else if(G.getVtxDeg(S[0])==1) {
            S.erase(S.begin());
            return 1+ms(G-G.Nbar(S[0]),S);
        }
        else {
            int s1=S[0], s2=S[1], s3=S[2];
            S.erase(S.begin());
            return max(1+ms(G-G.Nbar(s1),S), ms2(G-G.Nbar(s2)-G.Nbar(s3)-s1, G.N(s1)));
        }
    }
    else if(sz==4){
        for(int i:G.vertex_degree){
            if(i<=3) 
                return ms(G);
            else {
                S.erase(S.begin());
                return max(1+ms(G-G.Nbar(S[0])),ms2(G-S[0],S));
            }
        }
    }
    return ms(G);
}

myGraph myGraph::VertexSetSubG(vector<int> vset)
{
  vector<int> exc_set;
  for(size_t i=0; i<adj.size(); i++)
  {
    vector<int>::iterator it;
    if(find(vset.begin(), vset.end(), i)==vset.end())
    {
      exc_set.push_back(int(i));
    }
  }
  return *this-exc_set;
}

myGraph myGraph::NbarSubG(int v){
  myGraph subGraph(adj.size());
  subGraph.adj = adj;
  subGraph.order=0;
  for(size_t i=0; i<adj.size(); i++){
    //vertex v is connected with vertex i
    if(!edge(v, i)){ 
      subGraph.adj[i]=0;      
      for(size_t j=0; j<adj.size(); j++){
        subGraph.adj[j] &= ~(1LL<<i);
      }
    }
    //else if(edge(v, i)){
    //  subGraph.adj[i] &= ~(1LL<<v);
    //  subGraph.order++;
    //}
  }
  subGraph.countGrhDeg();
  subGraph.countVtxDeg();
  return subGraph;
}

int myGraph::GreatestNeighbourVtx(int A){
  int greatest=0;
  for(size_t i=0; i<adj.size(); i++){
    if(edge(A,i) && vertex_degree[i]>=greatest&&i!=A){
      greatest=i;
    }
  }
  return greatest;
}

bool myGraph::dominate(myGraph other){
  for(size_t i=0; i<adj.size(); i++){
    if(adj[i]==0 && other.adj[i]!=0){
      return false;
    }
  }
  return true;
}

bool myGraph::isConnected(){
  long long visited=0;
  int src=-1;
  for(size_t i=0;i<adj.size(); i++)
  {
    if(((adj[i]>>i)%2)&1){
      src=i;
      break;
    }
  }
  if(src==-1) return true;
  else DFS(src, &visited);

  int count=0;
  // count visited vertices
  for(size_t i=0; i<adj.size(); i++){
    if(visited%2==1) count++;
    visited>>=1;
  }
  return count == int(order);
}

int myGraph::MinimalDegreeVertex(){
  int min=0;
  for(size_t i=0; i<order; i++){
    if(min<=vertex_degree[i]){
      min=vertex_degree[i];
    }
  }
  return min;
}

int myGraph::MaxDegreeVtx(){
  int max=0;
  for(size_t i=0; i<order; i++){
    if(max>=vertex_degree[i]){
      max=vertex_degree[i];
    }
  }
  return max;
}

void myGraph::DFS(int src, long long *visited){
  *visited|=1LL<<src;
  for(size_t i=0; i<adj.size(); i++){
    // if vertex i is not visited and i is connected to vertex src
    if(!(((*visited>>i)%2)&1) && edge(i,src)){
      DFS(i, visited);
    }
  }
}

void myGraph::DFS(int src, vector<int> &new_set, long long* vtx_set){
  new_set[src]=1;
  *vtx_set|=1LL<<src;
  for(size_t i=0; i<new_set.size(); i++){
    // if vertex i is not new_set and i is connected to vertex src
    if(new_set[i]!=1 && edge(i,src)){
      DFS(i, new_set, vtx_set);
    }
  }
}

vector<int> myGraph::LeastCntG(int g_size, int prnt_size){
  vector<int> min_vtc={};
  long long vtx_set=0;
  int count=0, min_count=INT_MAX, total=0;
  int src=0; bool chosen=false;
  // select first exist vertex
  for(int i=0; i<prnt_size; i++)
  {
    // if(((adj[i]>>i)%2)&1)
    if(vertex_degree[i]>-1)
    {
      src=i;
      break;
    }
  }
  //while(vtx_set<=pow(2,int(adj.size()))-1){
  while(total < g_size){
    vector<int> new_set(g_size,0);
    DFS(src, new_set, &vtx_set);
    for(int i:new_set)
    {
      if(i==1)
        count++;
    }
    for(size_t i=0; i<g_size; i++){
      if(((vtx_set>>i)%2)&0 && !chosen){
        src=i;
        chosen=true;
      }
    }

    if(count<min_count) {
      min_count = count;
      min_vtc = vector<int>();
      for(size_t i=0; i<new_set.size(); i++)
      {
        if (new_set[i]==1)
          min_vtc.push_back(i);
      }
    }
    total += count;
    chosen=false;
    count=0;
  }
  return min_vtc;
}

vector<int> myGraph::N(int v){
    vector<int> S;
    for(size_t i=0; i<adj.size(); i++){
        if(v!=i && edge(i,v)) S.push_back(i);
    }
    return S;
}
vector<int> myGraph::Nbar(int v){
    vector<int> S;
    for(size_t i=0; i<adj.size(); i++){
        if(edge(i,v)) S.push_back(i);
    }
    return S;
}
vector<int> myGraph::N2(int v){
    vector<int> S;
    for(size_t i=0; i<adj.size(); i++){
        if(v!=i && edge(i,v)) { // i is a neighbour of v
            for(size_t j=0; j<adj.size(); j++){ //collect neighbour of i exclude v
                if(j!=v && edge(j,i) && find(S.begin(),S.end(), j)==S.end()){
                    S.push_back(j);
                }
            }
        }
    }
    return S;
}

int myGraph::getGrhDeg()
{
  return degree;
}
int myGraph::getVtxDeg(int v)
{
  return vertex_degree[v];
}
