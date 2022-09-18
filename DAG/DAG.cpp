#include<thpool.hpp>
#include<iostream>
#include<ctime>

using namespace std;

thpool pool;
pthread_mutex_t mut;

int R(int a,int b){
	return (rand()%(b-a+1)+a);
}

vector<int> G[100];

struct data{
	int ID;
	int inDegree;
	string str;
}D[100];

void* Task(void* d){
	data* myData=reinterpret_cast<data*>(d);
	cout<<(*myData).ID<<"\n";

	pthread_mutex_lock(&mut);
	for(int i=0;i<G[(*myData).ID].size();i++){
		int v=G[(*myData).ID][i];
		D[v].inDegree--;
		if(D[v].inDegree==0){
			Job tmp;tmp.init(Task,&D[v],1);
			pool.addJob(tmp);
		}
	}
	pthread_mutex_unlock(&mut);
}

void Link(int u,int v){
	G[u].push_back(v);
	D[v].inDegree++;
}
int n;

int main(int argc,char** args){
	srand(time(NULL));
	pthread_mutex_init(&mut,nullptr);

	pool.init(16);n=atoi(args[1]);
	for(int i=1;i<=n;i++){
		D[i].ID=i;
		D[i].str="helloworld";
	}
	for(int i=2;i<=n;i++){
		while(R(1,4)<=3){
			Link(R(1,i-1),i);
		}
	}
	for(int i=1;i<=n;i++)
		if(D[i].inDegree==0){
			Job tmp;
			tmp.init(Task,&D[i],1);
			pool.addJob(tmp);
		}
	pool.waitJob();
	cout<<"all have been done\n";
	
	pthread_mutex_destroy(&mut);
	return 0;
}