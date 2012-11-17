#include <vector>
#include <iostream>
#include <set>
#include <list>
#include <ctime>
#include <queue>
#include <deque>
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
    //пол€
    vector< vector<int> > adjMatr;
		bool used[100];vector<int> ans;// дл€ топологической сортировки
    //методы
    public:
    int numVertex();
    Graph();//конструктор
    Graph(int n);//конструктор
    vector< vector<int> > show_graph();
    vector< vector<int> > floyd(); 
	vector<int>  Levit(int v);
	  vector<int> topological_sort(int v); void dfs(int v);
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
        for(int i=0;i<n;++i){if (i==k) v[i]=0; else v[i]=rand_int(1,100);}
        //cout<<v<<endl;
        adjMatr.push_back(v);
    }
}


    vector<int > Graph::Levit(int v1)
{
	int n=numVertex();
const int inf = 1000*1000*1000;

vector<int> d (n, inf);//текущие кратчайшие длины путей
	d[v1] = 0;//длина пути до самой себ€
vector<int> id (n,0);//состо€ни€ m1 m2 m0
	deque<int> q;//очередь
q.push_back (v1);//
	vector<int> p (n, -1);//предки
	while(!q.empty())
	{
int v = q.front();  q.pop_front();
	id[v] = 1;//вычисл€етс€
	for (int to=0;to<n;to++)
	{
	int len=adjMatr[v][to];
if (d[to] > d[v] + len)
			{
				d[to] = d[v] + len;
				if (id[to] == 0)//≈сли T принадлежит M2,
					// то T переносим во множество M1 в конец очереди. 
					//DT полагаем равным DV + L.
					q.push_back (to);
				else if (id[to] == 1)
					q.push_front (to);
				p[to] = v;
				id[to] = 1;
			}
	}
	}
	return d;
}

    void Graph::dfs(int v)
{	
	int n=numVertex();


 	used[v] = true;
	for (int i=0; i<n; ++i) {
		int to = adjMatr[v][i];
		if (!used[to])
			dfs (to);
	}
	ans.push_back (v);
	
}

    vector<int > Graph::topological_sort(int v1)
 {	int n=numVertex();
	for (int i=0; i<n; ++i)
		used[i] = false;
	ans.clear();
	for (int i=0; i<n; ++i)
		if (!used[i])
			dfs (i);
	reverse (ans.begin(), ans.end());
	return ans;
 }

  
  int main()
{
	int k; cin >> k;//количество вершин в графе
    srand ( ( time (NULL) ) );
    Graph g(k);
    ///cout<<g.numVertex();
    cout<<g.show_graph();
    ///    cout<<g;
	int v;	cin >> v;//задаем вершину
cout <<"\n " << g.Levit(v);// јлгоритм Ћевита
cout <<"\n " << g.topological_sort(v);// “опологическа€ сортировка
	system ("pause");
    return 0;
}