#include <vector>
#include <iostream>
#include <set>
#include <list>
#include <ctime>
#include <queue>
#include <stack>
#include <algorithm>
#include <sstream>
#include <cstdio>

using namespace std;

int rand_int(int max){return rand()%max;}
int rand_int(int min,int max){return rand_int(max-min)+min;}

template<typename T>
inline ostream& operator<<(ostream &os, vector<T> v){
    for(unsigned int i=0;i<v.size();++i) os<<v[i]<<" ";
    return os;
}

template<typename T>
inline ostream& operator<<(ostream &os, vector< vector<T> > v){
    for(unsigned int i=0;i<v.size();++i) {
        for(unsigned int j=0;j<v.size();++j) {
            os<<v[i][j]<<" ";
        }
        os<<endl;
    }
    return os;
}
class Graph{
    //поля
    vector< vector<int> > adjMatr;

    //методы
    public:
    int numVertex();
    Graph();//конструктор
    Graph(int n);//конструктор
    vector< vector<int> >show_graph();
    vector< vector<int> > floyd();

};
vector< vector<int> > Graph::show_graph(){
    return adjMatr;
}
int Graph::numVertex(){
    return adjMatr.size();
}
Graph::Graph(){
    int numVertex=0;
    vector< vector<int> > adjMatr;
}

Graph::Graph(int n){
    for(int k=0;k<n;++k){
        vector<int> v(n,0);
        for(int i=0;i<n;++i){v[i]=rand_int(1,100);}
        //cout<<v<<endl;
        adjMatr.push_back(v);
    }
}


vector< vector<int> > Graph::floyd(){
}

int main()
{
    srand ( ( time (NULL) ) );
    Graph g(7);
    //cout<<g.numVertex();

    cout<<g.show_graph();
    cout<<g;
    return 0;
}
