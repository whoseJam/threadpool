#include "thpool.h"
#include <iostream>

using namespace std;

thpool p(4);

struct Message{
	int sec;
	int id;
	string word;
};

void fun(int sec, int id, string word){
	for(int i = 1; i <= sec; i++){
		std::cout << word;
	}
}

int main(){
	Job j1(fun, 2, 1, "hello\n");
	Job j2(fun, 10, 2,"bye\n");
	Job j3(fun, 2, 3, "good\n");
	Job j4(fun, 5, 4, "english\n");
	Job j5(fun, 1, 5, "dish\n");
	std::cout << "job is init\n";
	p.add(j1);
	p.add(j2);
	p.add(j3);
	p.add(j4);
	p.add(j5);
	p.wait();
	std::cout << "all have been done\n";
	return 0;
}
