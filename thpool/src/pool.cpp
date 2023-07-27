
#include "pool.h"
#include <cstdlib>
#include <mutex>
#include <iostream>
using namespace std;

void work(thpool* pool) {
    while(!pool->m_finished) {
        unique_lock<mutex> lk(pool->m_pending_job_mutex);
        while(pool->m_pending_jobs_size == 0 && 
              !pool->m_finished) {
            pool->m_free_workers.wait(lk);
        }
        if (pool->m_finished && pool->m_pending_jobs_size == 0)
            break;
        Job job = pool->m_pending_jobs.front();
        pool->m_pending_jobs.pop();
        pool->m_pending_jobs_size--;
        lk.unlock();
        {   lock_guard<mutex> lk(pool->m_worker_mutex);
            pool->m_free_worker_size++;
        }

        job.run();

        {   lock_guard<mutex> lk(pool->m_worker_mutex);
            pool->m_free_worker_size--;
        }
        pool->m_master.notify_all();
    }
}

thpool::thpool(int size) {
    m_capacity = size;
    m_pending_jobs_size = 0;
    m_free_worker_size = size;
    for (int i = 0; i < size; i++) {
        std::thread t(work, this);
        m_workers.push_back(std::move(t));
    }
}

thpool::~thpool() {
    m_finished = true;
    m_free_workers.notify_all();
    for (int i = 0; i < m_capacity; i++) {
        m_workers[i].join();
    }
}

int thpool::capacity() {
    return m_capacity;
}

int thpool::pending_job_size() {
    return m_pending_jobs_size;
}

void thpool::add(const Job& job) {
    lock_guard<mutex> lk(m_pending_job_mutex);
    m_pending_jobs.push(job);
    m_pending_jobs_size++;
}

void thpool::wait() {
    unique_lock<mutex> lk1(m_pending_job_mutex);
    while(m_pending_jobs_size != 0) {
        m_master.wait(lk1);
    }
    unique_lock<mutex> lk2(m_worker_mutex);
    while(m_free_worker_size != m_capacity) {
        m_master.wait(lk2);
    }
}