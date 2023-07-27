
#include "job.h"

Job& Job::set_priority(int priority) {
    m_priority = priority;
    return *this;
}

void Job::run() {
    m_wrapper();
}

bool Job::operator<(const Job& other) {
    return m_priority < other.m_priority;
}