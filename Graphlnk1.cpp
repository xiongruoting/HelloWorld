#include"Graph.h"
#include<iostream>
#include<fstream>
#include <sstream>
using namespace std;
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
		else return 100;
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
 return getVertexPos(p->link->dest);//����λ�� 
}
return -1;
}; 
 //��ѯ��һ��� 
int Graphlnk::getFirstNeighbor(int v)
 {
 if(v!=-1)//��v���վ�� 
 {
 	Edge*p=NodeTable[v].adj;
 	if(p!=NULL) return getVertexPos(p->dest);
	 }	
return -1;	 
 };
 //������ʵ�� 
Graphlnk::Graphlnk(int sz)
 {
 	maxVertices=sz;
 	numVertices=0;
 	numEdges=0;
 	NodeTable=new Vertex[sz];
 	for(int i=0;i<maxVertices;i++)
 	NodeTable[i].adj=NULL;
 	
 };
 
bool Graphlnk::insertVertex()//����һ����� 
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
cout<<"������ɹ�"<<endl;
return true;
	 };	 
bool Graphlnk::insertEdge(int v1,int v2,int cost,string v3,string v4)
{

	if(v1>=0&&v1<=numVertices&&v2>=0&&v2<=numVertices)//v1,v2�Ϸ� 
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
		 } //�ҵ��˱߲�����
		 p=new Edge(); q=new Edge();
		 p->dest=NodeTable[v2].start;    p->cost=cost; 
		 p->netnumber=v3;p->yanma=v4;
		 p->link=NodeTable[v1].adj;
		 NodeTable[v1].adj=p;//����v1�� 
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
//���path�����д洢��ͼG�Ӷ���v������������·���;���
	cout  << G.NodeTable[v].start << "��·�ɱ�Ϊ" << endl;
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
		//	cout << "����" << G.NodeTable[i].start << "�����·��Ϊ��" << G.NodeTable[v].start << " ";
		        
			
				if(k==1) 
				{
				cout << "Ŀ������"<<G.NodeTable[d[0]].start<< " ";
				cout<<"ֱ�ӽ���"<<" ";
			}
				else
				{
					cout << "Ŀ������"<<G.NodeTable[d[0]].start<< " ";
				cout<<"��һ��"<<G.NodeTable[d[k-1]].start<<" ";
}
			 cout << "���·������Ϊ��" << dist[i] << endl;
		}
	}
	delete[] d;
}

void ShortestPath(Graphlnk& G, int v, int dist[], int path[])
{//Graph��һ����Ȩ����ͼ�����㷨����һ�����飬dist[j],0<=j<n;�ǵ�ǰ�󵽵ĴӶ���v������j�����·�����ȣ�ͬʱ������path����󵽵����·��
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
