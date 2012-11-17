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
inline ostream& operator<<(ostream &os, const vector<T>& v){
    for(unsigned int i=0;i<v.size();++i) os<<v[i]<<" ";
    return os;
}

template<typename T>
inline ostream& operator<<(ostream &os, const vector< vector<T> >& v){
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
	vector<int>  dijkstra(int s);
};
vector< vector<int> > Graph::show_graph()//возвращает саму матрицу
{
    return adjMatr;
}
int Graph::numVertex()//размер
{
    return adjMatr.size();
}
Graph::Graph()//создает граф
{
    int numVertex=0;
    vector< vector<int> > adjMatr;
}
Graph::Graph(int n)//заполняет слуайным образом матрицу смежности
{
    for(int k=0;k<n;++k){
        vector<int> v(n,0);
        for(int i=0;i<n;++i){if (k==i) v[i]=0; else v[i]=rand_int(1,100);}
        //cout<<v<<endl;
        adjMatr.push_back(v);
    }
}
vector< vector<int> > Graph::floyd()//агоритм Флойда
{
   for (int k=0; k<adjMatr.size(); ++k)
	for (int i=0; i<adjMatr.size(); ++i)
		for (int j=0; j<adjMatr.size(); ++j)
			adjMatr[i][j] = min (adjMatr[i][j], adjMatr[i][k] + adjMatr[k][j]);
   return adjMatr;
}

vector<int> Graph::dijkstra(int s)
{
	int n = adjMatr.size();

	const int INF = 1e9;

	vector<int> d (n, INF), p(n);
	d[s] = 0;
	vector<bool> u (n);

	for (int i=0; i<n; ++i) {
		int v = -1;
		for (int j=0; j<n; ++j)
			if (!u[j] && (v == -1 || d[j] < d[v]))
				v = j;
		if (d[v] == INF)
			break;
		u[v] = true;

		for (int to = 0; to<n; ++to) {
			if(adjMatr[v][to] == 0)
				continue;
			int len = adjMatr[v][to];
			if (d[v] + len < d[to]) {
				d[to] = d[v] + len;
				p[to] = v;
			}
		}
	}
	//for (int i=0;i<n;++i) cout<<d[i]<<" ";
	return d;
}

int main()
{
    srand ( ( time (NULL) ) );
	int k,s;
	cin>>k;//количество вершин
    Graph g(k);
    cout<<g.show_graph();
   /// cout << g;
	g.floyd();
	cout<<endl;
	cout<<g.show_graph();
	cout<<endl;
	cin>>s;
	cout<<g.dijkstra (s-1);
	system("pause");
    return 0;
}
