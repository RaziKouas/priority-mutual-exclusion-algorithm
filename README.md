Priority-based Mutual Exclusion Algorithm
This is an implementation of a priority-based mutual exclusion algorithm designed to manage access to a critical section. The algorithm uses a priority queue and mutex locking mechanism to control process access in a fair and efficient way.

Overview
This algorithm provides a way to grant and release access to a critical section based on the priority of processes. It ensures that:

Processes are granted access in a way that respects both their priority and the time they requested access.

Mutual exclusion is maintained, meaning no two processes can execute in the critical section at the same time.

The system prevents starvation by granting access to processes in a fair manner.

Features
FIFO Queue: The algorithm uses a priority queue (FIFO by default) to manage processes.

Priority-based Scheduling: Processes are granted access based on their priority. If two processes have the same priority, the one with the earliest timestamp is granted access first.

Mutex Locking: A mutex lock is used to ensure that the queue is accessed safely and no race conditions occur.

Functions
request_access(process_id, priority)
This function allows a process to request access to the critical section. The process is added to the queue with its priority and timestamp.

grant_access()
This function continuously checks the queue for processes that are waiting for access. It grants access based on the priority, and if multiple processes have the same priority, the one with the earliest timestamp is chosen.

release_access(process_id)
This function is called when a process has finished executing in the critical section, releasing its access.

How It Works
A process calls request_access() to join the queue with its ID, priority, and timestamp.

The grant_access() function grants access to the highest-priority process, considering the timestamp if there are ties.

Once a process is done executing in the critical section, it calls release_access().

Usage
You can integrate this algorithm into your projects to handle process synchronization and mutual exclusion in a priority-based manner. Just include the algorithm code and call the functions as needed to manage critical section access.

License
This project is open source and released under the MIT License. Feel free to use, modify, and distribute the code!
