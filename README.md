Experiments with lockless RingBuffer. 

time and context switches required to iterate over 10000000 items:

Lockfree RingBuffer:
dtrace: pid 35227 has exited
CPU     ID                    FUNCTION:NAME
  0    123              thread_switch:entry 
  0    123              thread_switch:entry 

sudo dtrace -n thread_switch:entry -c ./RingBuffer  1.82s user 0.14s system 34% cpu 5.718 total

Just 2 context switches and 1.82 user time.

Regular RingBuffer:

dtrace: description 'thread_switch:entry' matched 1 probe
CPU     ID                    FUNCTION:NAME
  0    123              thread_switch:entry 
  0    123              thread_switch:entry 
  0    123              thread_switch:entry 
  0    123              thread_switch:entry 
  0    123              thread_switch:entry 
  0    123              thread_switch:entry 
  0    123              thread_switch:entry 
  0    123              thread_switch:entry 
  0    123              thread_switch:entry 
  0    123              thread_switch:entry 
  0    123              thread_switch:entry 
  0    123              thread_switch:entry 
  0    123              thread_switch:entry 
dtrace: pid 35311 has exited
  0    123              thread_switch:entry 

sudo dtrace -n thread_switch:entry -c ./RingBuffer  0.87s user 3.01s system 49% cpu 7.902 total

13 context switches and almost 4 seconds of run time.


for 1B elements:
1 B elements
81.24s user 287.78s system 97% cpu 6:18.81 total
5758

180.87s user 1.05s system 187% cpu 1:36.94 total
3957
