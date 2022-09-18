#ifndef THPOOLHPP
#define THPOOLHPP

#include<pthread.h>
#include<vector>
#include<queue>

class Job{
private:
	void* (*routine)(void*);
	void* args;
public:
	int priority;
	Job()=default;
	~Job()=default;
	void init(decltype(routine) r,void* a,int p);
	// bool operator <(const Job& other);
	decltype(routine) getRoutine();
	decltype(args) getArgs();
};

class thpool{
private:
	int maxSize;
	std::priority_queue<Job>q;
	std::vector<pthread_t> th;
public:
	pthread_cond_t condWorker;
	//for worker to use: to inform worker that queueSize is changed
	
	pthread_cond_t condPool;
	//for pool   to use: to inform pool that activeWorker/queueIsEmpty is changed

	int queueSize;		//pool/worker change queueSize , signal to worker
	int activeWorker;	//worker change activeWorker,signal to pool
	
	pthread_mutex_t mut;//on queueSize and activeWorker

	thpool()=default;
	~thpool()=default;
	void init(int size);
	void destroy();
	int getMaxSize();
	void addJob(Job);
	void waitJob();
	Job getHead();
	void popHead();
};

#endif