#include"Graph.h"
#include<iostream>
#include<fstream>
#include <sstream>
using namespace std;
bool Graphlnk::removeEdge(int v1,int v2)//ͼ��ɾһ���� 
 {
 	 if(v1!=-1&&v2!=-1)
	  {
	  	Edge*p=NodeTable[v1].adj,*q=NULL,*s=p;
	  	while(p!=NULL&&p->dest!=NodeTable[v2].start)
	  	{q=p;p=p->link;
		  }
		  if(p!=NULL){ //�ҵ���ɾ���
		  if(p==s) NodeTable[v1].adj=p->link;
		  else q->link=p->link;
		  delete p; 
	   } 
 	else
	 {
	 	cout<<"�����û�б�"<<endl;
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
	 cout<<"ɾ���ɹ�"<<endl;
	 return true;
  }
  else
  {
 cout<<"������ɾ��ʧ��"<<endl;   
  return false;
}
}
bool Graphlnk::removeVertex(int v)
{
	if(v<0||v>=numVertices) 
{	
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
cout<<"ɾ��·�����ɹ�"<<endl;
return true;
}
