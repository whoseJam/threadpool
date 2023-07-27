#ifndef POOL_H
#define POOL_H

#include <condition_variable>
#include <thread>
#include <vector>
#include <queue>

#include "job.h"

class thpool{
public:
	thpool(int size);
	~thpool() = default;
	int capacity();
	int pending_job_size();
	void add(const Job& job);
	void wait();
private:
	friend void work(thpool* pool);

	int m_capacity;

	std::mutex m_pending_job_mutex;
	int m_pending_jobs_size;
	std::priority_queue<Job> m_pending_jobs;
    
	std::mutex m_worker_mutex;
	std::condition_variable m_free_workers;
	int m_free_worker_size;

	std::condition_variable m_master;
};

#endif