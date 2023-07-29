#include "thpool.h"
#include <iostream>
#include <ctime>
#include <mutex>

using namespace std;

thpool pool(4);
mutex mut;

int R(int a,int b){
	return (rand()%(b-a+1)+a);
}

vector<int> G[100];

struct Data{
	int ID;
	int inDegree;
	string str;
}D[100];

void Task(Data* myData){
	cout<<(*myData).ID<<"\n";

	lock_guard<mutex> lock(mut);
	for(int i=0;i<G[(*myData).ID].size();i++){
		int v=G[(*myData).ID][i];
		D[v].inDegree--;
		if(D[v].inDegree==0){
			Job tmp(Task, &D[v]);
			pool.add(tmp);
		}
	}
}

void Link(int u,int v){
	G[u].push_back(v);
	D[v].inDegree++;
}
int n;

int main(int argc,char** args){
	srand(time(NULL));

	n = atoi(args[1]);
	for(int i=1; i<=n; i++) {
		D[i].ID=i;
		D[i].str="helloworld";
	}
	for(int i=2; i<=n; i++) {
		while(R(1,4)<=3){
			Link(R(1,i-1),i);
		}
	}
	for(int i=1;i<=n;i++)
		if(D[i].inDegree==0){
			Job tmp(Task, &D[i]);
			pool.add(tmp);
		}
	pool.wait();
	cout<<"all have been done\n";
	return 0;
}