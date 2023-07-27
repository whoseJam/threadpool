#ifndef JOB_H
#define JOB_H

#include <functional>

class Job {
public:
    template<typename F, typename ...Args>
    Job(F func, Args... args) {
        m_wrapper = [=]() {
            func(args...);
        };
        m_priority = 0;
    }
	~Job() = default;
    Job& set_priority(int priority);
    void run();
	bool operator <(const Job& other);
private:
	int m_priority;
    std::function<void()> m_wrapper;
};

#endif