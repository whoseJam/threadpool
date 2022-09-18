#include<thpool.hpp>
#include<iostream>
#include<unistd.h>

using namespace std;

thpool p;

struct data{
	int sec;
	int id;
	string word;
};

void* fun(void* mdata){
	data* tmp=reinterpret_cast<data*>(mdata);
	for(int i=1;i<=tmp->sec;i++){
		std::cout<<(tmp->word);
		// sleep(1);
	}
}

int main(){
	p.init(4);

	data d1={2,1,"hello\n"};
	data d2={10,2,"bye\n"};
	data d3={2,3,"good\n"};
	data d4={5,4,"english\n"};
	data d5={1,5,"dish\n"};
	Job j1;j1.init(fun,reinterpret_cast<void*>(&d1),2);
	Job j2;j2.init(fun,reinterpret_cast<void*>(&d2),10);
	Job j3;j3.init(fun,reinterpret_cast<void*>(&d3),2);
	Job j4;j4.init(fun,reinterpret_cast<void*>(&d4),5);
	Job j5;j5.init(fun,reinterpret_cast<void*>(&d5),1);
	std::cout<<"job is init\n";
	p.addJob(j1);
	p.addJob(j2);
	p.addJob(j3);
	p.addJob(j4);
	p.addJob(j5);
	p.waitJob();
	std::cout<<"all have been done\n";

	p.destroy();
	return 0;
}
