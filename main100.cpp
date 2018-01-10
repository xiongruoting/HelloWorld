#include <iostream>
#include <stdlib.h>
#include <iomanip>

#include<string>
#include <limits.h>
#include <cstdlib>
#include<fstream>
#include <sstream>
int DefaultVertices=30;
using namespace std;
class Edge
{
public:
string dest;//路由器终点号 
string netnumber;
string yanma; 
int cost;
Edge*link;	
};
class Vertex
{ 
    public:
 	string start;//路由器号 
	Edge*adj;
};
class Graphlnk
{
	public:
	int maxVertices;  //图中结点最大数 
	int numEdges;   
	int numVertices;
	Graphlnk();
	Graphlnk(int sz);
	int getWeight(int v1,int v2);
	bool insertVertex();//插入一个结点 
	bool insertEdge(int v1,int v2,int cost,string v3,string v4);//插入一条边 
	int getFirstNeighbor(int v);//v的第一个相邻结点
	int getNextNeighbor(int v,int w);
	bool removeVertex(int v);
	bool removeEdge(int v1,int v2);
	int getVertexPos(const string vertex)
	{
		for(int i=0;i<30;i++)
		{
			if(NodeTable[i].start==vertex) return i;
		
		}	return -1;
	}	 
	Vertex *NodeTable;
	
 };

int Graphlnk::getWeight(int v1,int v2)
{
	if( v1 != -1 && v2 != -1)
	{
		Edge *p = NodeTable[v1].adj;
		while (p!= NULL && p->dest!= NodeTable[v2].start)
		{
			p = p->link;
		}
		if(p != NULL) 
			return p->cost;
		else return DefaultVertices+1;
	}
}
 int Graphlnk::getNextNeighbor(int v,int w)
 {
 if(v!=-1)
 {
 Edge*p=NodeTable[v].adj;
 while(p!=NULL&&p->dest!=NodeTable[w].start)
 p=p->link;
 if(p!=NULL&&p->link!=NULL)
 return getVertexPos(p->link->dest);//返回位置 
}
return -1;
}; 
 //查询第一结点 
int Graphlnk::getFirstNeighbor(int v)
 {
 if(v!=-1)//有v这个站点 
 {
 	Edge*p=NodeTable[v].adj;
 	if(p!=NULL) return getVertexPos(p->dest);
	 }	
return -1;	 
 };
 //函数的实现 
Graphlnk::Graphlnk(int sz)
 {
 	maxVertices=sz;
 	numVertices=0;
 	numEdges=0;
 	NodeTable=new Vertex[sz];
 	for(int i=0;i<maxVertices;i++)
 	NodeTable[i].adj=NULL;
 	
 };
 bool Graphlnk::removeEdge(int v1,int v2)//图上删一条边 
 {
 	 if(v1!=-1&&v2!=-1)
	  {
	  	Edge*p=NodeTable[v1].adj,*q=NULL,*s=p;
	  	while(p!=NULL&&p->dest!=NodeTable[v2].start)
	  	{q=p;p=p->link;
		  }
		  if(p!=NULL){ //找到被删结点
		  if(p==s) NodeTable[v1].adj=p->link;
		  else q->link=p->link;
		  delete p; 
	   } 
 	else
	 {
	 	cout<<"两点间没有边"<<endl;
	 return false;
}
 	p=NodeTable[v2].adj; q=NULL; s=p;
 	while(p->dest!=NodeTable[v1].start)
 	{
 		q=p;p=p->link;
	 }
	 if(p==s) NodeTable[v2].adj=p->link;
	 else q->link=p->link;
	 delete p;
	 return true;
  } return false;
}
bool Graphlnk::removeVertex(int v)
{
	if(v<0||v>=numVertices) 
{
	cout<<"该结点错误"<<endl;	
	return false;
}
Edge*p,*s,*t;
int i,j;
string k;
while(NodeTable[v].adj!=NULL)
{
	p=NodeTable[v].adj;
	k=p->dest;
	j=getVertexPos(k);
	s=NodeTable[j].adj;
	t=NULL;
	while(s!=NULL &&s->dest!=NodeTable[v].start)
	{
	t=s;s=s->link;
	}
	if(s!=NULL)
	{
		if(t==NULL) NodeTable[j].adj=s->link;
		else t->link=s->link;
		delete s;
	}
	NodeTable[v].adj=p->link;
	delete p;
	numEdges--;
}

numVertices--;
NodeTable[v].start=NodeTable[numVertices].start;
p=NodeTable[v].adj=NodeTable[numVertices].adj;
if(p!=NULL)
{
	
	s=NodeTable[getVertexPos(p->dest)].adj;
	while(s!=NULL)
	
	if(getVertexPos(s->dest)==numVertices)
	{
		
		s->dest=NodeTable[v].start;break;
	}
	else s=s->link;

}
cout<<"删除成功"<<endl;
return true;
}
bool Graphlnk::insertVertex()//插入一个结点 
	{	 
ifstream fin("C:\\1.txt", std::ios::in);
char line[1024]={0};
 numVertices=0;
string x = "";
while(fin.getline(line, sizeof(line)))
{
stringstream word(line);
word >> x;
NodeTable[numVertices].start=x;
 numVertices++;
}

fin.clear();
fin.close();
cout<<"插入结点成功"<<endl;
return true;
	 };	 
bool Graphlnk::insertEdge(int v1,int v2,int cost,string v3,string v4)
{

	if(v1>=0&&v1<=numVertices&&v2>=0&&v2<=numVertices)//v1,v2合法 
		{
			string a;
			int b,c;
		 Edge*q,*p;
		 p=NodeTable[v1].adj;
		 while(p!=NULL&&p->dest!=NodeTable[v2].start)
		 p=p->link;
		 if(p!=NULL) 
		 {
		 return false;
		 } //找到此边不插入
		 p=new Edge(); q=new Edge();
		 p->dest=NodeTable[v2].start;    p->cost=cost; 
		 p->netnumber=v3;p->yanma=v4;
		 p->link=NodeTable[v1].adj;
		 NodeTable[v1].adj=p;//链入v1表 
		 q->dest=NodeTable[v1].start;    q->cost=cost;
		 q->netnumber=v3;q->yanma=v4;
		 q->link=NodeTable[v2].adj;
		 NodeTable[v2].adj=q; 
		 numEdges++;
		 return true;
		}
		return false;

	 } ;
void printPath(Graphlnk& G, int v, int dist[], int path[])
{
//输出path数组中存储的图G从顶点v到其余各顶点的路径和距离
	cout  << G.NodeTable[v].start << "的路由表为" << endl;
	int i, j, k, n = G.numVertices;
	int * d = new int[n];
	for (i = 0; i<n; i++)
	{
		if (i != v)
		{
			j = i;
			k = 0;
			while (j != v)
			{
				d[k++] = j;
				j = path[j];
			}
		//	cout << "顶点" << G.NodeTable[i].start << "的最短路径为：" << G.NodeTable[v].start << " ";
		        
				cout << "目的网络"<<G.NodeTable[d[0]].start<< " ";
				if(k==1) 
				cout<<"直接交付"<<" ";
				else
				cout<<"下一跳"<<G.NodeTable[d[k-1]].start<<" ";

			 cout << "最短路径长度为：" << dist[i] << endl;
		}
	}
	delete[] d;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////Dijkstra最短路径///////////////////////////////////////////////////////////////////
void ShortestPath(Graphlnk& G, int v, int dist[], int path[])
{//Graph是一个带权有向图，本算法建立一个数组，dist[j],0<=j<n;是当前求到的从顶点v到顶点j的最短路径长度，同时用数组path存放求到的最短路径
	int n = G.numVertices;
	bool *S = new bool[n];
	int i, j, k;
	int w, min;
	for (i = 0; i<n; i++)
	{
		dist[i] = G.getWeight(v, i);
		S[i] = false;
		
		if (i != v && dist[i] <100)
			path[i] = v;
		else
		{
			path[i] = -1;
		}
	}
	S[v] = true;
	dist[v] = 0;
	for (i = 0; i<n - 1; i++)
	{
		min = 100;
		int u = v;
		for (j = 0; j<n; j++)
		{
			if (S[j] == false && dist[j] < min)
			{
				u = j;
				min = dist[j];
			}
		}
		S[u] = true;
		for (k = 0; k<n; k++)
		{
			w = G.getWeight(u, k);
			if (S[k] == false && w <100&& dist[u] + w<dist[k])
			{
				dist[k] = dist[u] + w;
				path[k] = u;
			}
		}
	}
	printPath(G, v, dist, path);
}
 int main()
{
Graphlnk G(30);
cout<<"读取文件插入站点" <<endl;
G.insertVertex();
cout<<"总站点数为"<<G.numVertices<<endl;
int i,j,weight;
ifstream fin("C:\\2.txt", std::ios::in);
char line[1024]={0};
string x = "";
string y="";
string m="";
string n="";
int z;
while(fin.getline(line, sizeof(line)))
{
stringstream word(line);
word >> x;//路由起点 
word >> y;//路由终点 
word >> z;//权值 
word >> m;//网络号 
word >> n;//子网掩码 
i=G.getVertexPos(x);
j=G.getVertexPos(y);
weight=z;
G.insertEdge(i,j,weight,m,n);
}

fin.clear();
fin.close();
cout<<"总边数数为"<<G.numEdges<<endl;
 
	//查询函数
	int *dist= new int[G.numVertices];
	 int *path= new int[G.numEdges];
	 string v,u;
	 cout<<"输入路由器"<<endl;
	 cin>>v;
	 int h;
	 int r=G.getVertexPos(v);
	 if(r==-1)
	 {
	 	cout<<"没有该路由"<<endl;
	 }
	 else
	 {	 
	 ShortestPath(G, r, dist, path);
     }
	cout<<"删除路由器"<<endl;
	cin>>v;
	int w=G.getVertexPos(v);
	G.removeVertex(w);
	cout<<"输入路由器"<<endl;
	 cin>>v;
	  r=G.getVertexPos(v);
	 if(r==-1)
	 {
	 	cout<<"没有该路由"<<endl;
	 }
	 else
	 {	 
	 ShortestPath(G, r, dist, path);
     }
     cout<<"删除一条边"<<endl;
		cin>>v;
		cin>>u;
		r=G.getVertexPos(v);
		h=G.getVertexPos(u);
		while(!G.removeEdge(r,h))
		{
			cout<<"删除一条边"<<endl;
			 cin>>v;
		cin>>u;
		r=G.getVertexPos(v);
		h=G.getVertexPos(u);
		}
		cout<<"输入路由器"<<endl;
	 cin>>v;
	  r=G.getVertexPos(v);
	 if(r==-1)
	 {
	 	cout<<"没有该路由"<<endl;
	 }
	 else
	 {	 
	 ShortestPath(G, r, dist, path);
     }	
	 
}
