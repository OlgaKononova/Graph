#include <vector>
#include <iostream>
#include <set>
#include <list>
#include <ctime>
#include <queue>
#include <stack>
#include <deque>
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
    vector<int>  dijkstra(int s);
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

vector< vector<int> > Graph::floyd()//агоритм ‘лойда
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
	cin >> k;//количество вершин в графе
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