#ifndef THPOOLCPP
#define THPOOLCPP

#include<pthread.h>
#include<iostream>
#include<unistd.h>
#include<signal.h>

#include"thpool.hpp"

void Job::init(decltype(routine) r,void* a,int p){
	routine=r;args=a;priority=p;
}
bool operator <(Job a,Job b){
	return a.priority<b.priority;
}
auto Job::getRoutine()->decltype(routine){
	return routine;
}
auto Job::getArgs()->decltype(args){
	return args;
}

void* threadWork(void* args){
	thpool* pool=reinterpret_cast<thpool*>(args);
	while(true){
		pthread_mutex_lock(&((*pool).mut));
		while((*pool).queueSize==0){
			pthread_cond_wait(&((*pool).condWorker),&((*pool).mut));
		}
		auto job=(*pool).getHead();
		(*pool).popHead();
		(*pool).activeWorker++;
		pthread_mutex_unlock(&((*pool).mut));
		
		auto routine=job.getRoutine();
		auto args=job.getArgs();
		routine(args);

		pthread_mutex_lock(&((*pool).mut));
		(*pool).activeWorker--;
		pthread_mutex_unlock(&((*pool).mut));
		pthread_cond_signal(&((*pool).condPool));
	}
}

void thpool::init(int size){
	if(maxSize){
		std::cout<<"size have been set\n";
		return;
	}
	activeWorker=0;
	queueSize=0;
	pthread_mutex_init(&mut,nullptr);
	pthread_cond_init(&condWorker,nullptr);
	pthread_cond_init(&condPool,nullptr);
	th.resize(maxSize=size);
	for(int i=0;i<maxSize;i++)
		pthread_create(&th[i],nullptr,threadWork,reinterpret_cast<void*>(this));
}

void thpool::destroy(){
	for(int i=0;i<maxSize;i++)
		pthread_cancel(th[i]);
	pthread_mutex_destroy(&mut);
	pthread_cond_destroy(&condWorker);
	pthread_cond_destroy(&condPool);
}

int thpool::getMaxSize(){
	return maxSize;
}

void thpool::addJob(Job j){
	pthread_mutex_lock(&mut);
	q.push(j);queueSize++;
	pthread_mutex_unlock(&mut);
	pthread_cond_signal(&condWorker);
}

void thpool::waitJob(){
	pthread_mutex_lock(&mut);
	while(activeWorker>0||queueSize>0){
		pthread_cond_wait(&condPool,&mut);
	}
	pthread_mutex_unlock(&mut);
}

Job thpool::getHead(){
	return q.top();
}

void thpool::popHead(){
//	mut is working (queueSize)
	q.pop();queueSize--;
}

#endif
