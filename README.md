# thread-pool-pthread
A thread pool based on pthread. att. I am a new learner and not sure the correctness of my code.

### intro
Init and destroy a thread is time-comsuming.To avoid frequent init/destroy , I write a thread pool to help me manage these trivals.
A thread pool contain a group of threads waiting for jobs.Before go to the detail , we should first declare some defination:

##### workers
Threads in thread-pool , waiting for coming job.

##### jobs
Jobs that you give . Noted that the jobs doesn't nessarily have to be based on the same function. Maybe job1 is connected with function1(args1) and job2 is connected with function2(args2) and so.However,after a worker done job1 it can continue to work on job2. 

##### pool
The thread-pool,which contain a group of workers(threads).
