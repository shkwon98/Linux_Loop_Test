# Linux Loop Test

Loop tasks with three different linux scheduling policies: sched_normal, sched_fifo, sched_deadline

---

### SCHED_NORMAL:
+ Default Linux time-sharing scheduler that is intended for all threads that do not require the special real-time mechanisms. (Non Real-time)

### SCHED_FIFO:
+ First in-first out scheduling.
+ Scheduling policy used to run a thread with true real-time priority and a minimum worst-case scheduling latency. (Real-time)

### SCHED_DEADLINE:
+ Since version 3.14, Linux provides a deadline scheduling policy.
+ Real-time scheduling policy that enables predictable task scheduling with higher priority than NORMAL and FIFO/RR. (Real-time)
