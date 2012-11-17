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

#if defined(_MSC_VER) && (_MSC_VER >= 1500) // Visual Studio 2008 or higher
    #include <random>
#endif//для random
 #if defined(__GNUC__) && (__GNUC__ * 100 + __GNUC_MINOR__ >= 402) // GCC 4.2 or higher
    #include <tr1/random>
#endif//для random

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
	bool used[100];vector<int> ans;// для топологической сортировки
    //методы
    public:
    int numVertex();
    Graph();//конструктор
    Graph(int n);//конструктор
	Graph(int n,int j);//конструктор
    vector< vector<int> > show_graph();
    vector< vector<int> > floyd(); 
	vector<int>  dijkstra(int s);
	vector<int>  Levit(int v);
	vector<int> topological_sort(int v); 
	void dfs(int v);
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
Graph::Graph(int n,int j)//заполняет слуайным образом матрицу смежности
{
	///typedef std::tr1::ranlux64_base_01            ENG;    // subtract_with_carry_01
    typedef std::tr1::mt19937                     ENG;    // Mersenne Twister
    typedef std::tr1::uniform_int<unsigned int> DIST;   // Normal Distribution
    typedef std::tr1::variate_generator<ENG,DIST> GEN;    // Variate generator
    //typedef std::tr1::minstd_rand gen;
    ENG  eng;
    DIST dist(0,j);
    GEN  gen(eng,dist); 
    for(int k=0;k<n;++k){
        vector<int> v(n,0);
        for(int i=0;i<n;++i){if (k==i) v[i]=0; else v[i]=gen();}
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
vector<int> Graph::dijkstra(int s)//агоритм Дейкстры
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
	d[v1] = 0;//длина пути до самой себя
vector<int> id (n,0);//состояния m1 m2 m0
	deque<int> q;//очередь
q.push_back (v1);//
	vector<int> p (n, -1);//предки
	while(!q.empty())
	{
int v = q.front();  q.pop_front();
	id[v] = 1;//вычисляется
	for (int to=0;to<n;to++)
	{
	int len=adjMatr[v][to];
if (d[to] > d[v] + len)
			{
				d[to] = d[v] + len;
				if (id[to] == 0)//Если T принадлежит M2,
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
	int k,s,v,l;
    cout<<"Razmer i max znachenie"<<endl;
	cin>>k>>l;//k-количество вершин,l-максимальное значесние в матрице,т.е. от 0 до l
    //Graph g(k);// содает граф g с k вершинами
	Graph g(k,l);//создает граф g с k вершинами 
    cout<<g.show_graph()<<endl;
	cout<<"Algoritm Floyda"<<endl;
   	g.floyd();
	cout<<g.show_graph();
	cout<<endl;
	cout<<"Nomer vershini,s kotooi njno nachat poisk algoritm Dijkstri";
	cin>>s;//поиск от вершины s
	cout<<g.dijkstra (s-1)<<endl;
	cout<<"Nomer vershini,s kotooi njno nachat poisk algoritm Levita";
	cin>>v;
	cout << g.Levit(v-1)<<"\n \n";// Алгоритм Левита
	cout<<"Nomer veshini dlya topologicheskoi sortirvki";
	cin>>v;
    cout <<g.topological_sort(v-1)<<endl;// Топологическая сортировка
    system("pause");
    return 0;
}
