# Binomial_heaps
Binomial-heaps-to-implement-a-priority-queue
In this project, you are to use binomial heaps to implement a priority queue in a preemptive
scheduling system. A preemptive scheduling mechanism, shown in Fig. 1, operates as follows:
Processes bound to run are put in a priority queue (in this project a binomial heap (BH)) by a
priority mechanism (in this project a function f (e , t (i)) i arr of the execution time, ei, and arrival time,
tarr(i), of the process). Whenever the processor (P) is available, it is allocated for the process with the
highest priority waiting in BH to run. Any running process can use P only for a limited span of time
called a time slice or quantum, q. If the current process runs to completion within q, then the next
process with the highest priority waiting in BH attains the right to use P. Otherwise (i.e., if the
process is not finished), it is preempted (i.e., it releases P, its status saved for the next use of P and
P is allocated to the next highest priority process in BH). This switch of the right of use of P from
one process to another is known as “context switching.” The process that is preempted, is reenqueued,
after its new priority is calculated based on its new arrival time so as to reallocate P later
and run to completion. This flow of events iterates until there are no more processes left in BH
waiting for P.
What you are expected to do is to
1. implement the preemptive scheduling system with BH as explained above (and shown in
Fig. 1) and
2. optimize the quantum q; i.e., find the quantum value q, such that the average waiting time
of BH (AWT) is minimized.
Process criteria
The waiting time per process i, WTi, is defined by the sum of all spans of time passed from each arrival
time tarr of process i (assumed to be the time point process i is enqueued) until the time point tdeq it is
dequeued (DeleteMined) and starts/continues running.
New process
requests μP
Binomial
Heap (BH)
Process
Finished?
No
End
Yes
Lower priority by new arrival time,
and re-enqueue by new priority
Process preempted since
quantum size exceeded
Figure. 1: Preemptive scheduling with a binomial queue
2
This is mathematically expressed as follows:
where
 i is the process index,
 k is the index for the BH visits of process i and
 Ki denotes the number of times process i is enqueued (i.e., visited BH).
AWT, in turn, is the averaged sum of all individual waiting times, WTi, or
with I the total number of processes under consideration over the analysis period.
Input:
1. You will be given a list of (i, ei, tarr(i),tchange, enew) with i the process id, ei, the execution time
and tarr(i), the arrival time of process i, tchange shows if there is a change in the execution time of
the process (i.e., it its value is -1 it means that there will be no change, if its value is greater
than 0, this value shows the change time) and enew presents the new execution time of the
process at tchange. The lines in the list specifies the order in which the processes request for
processor allocation. You will use the input to compute the priority values f (e , t (i)) i arr . These
priority values will, in turn, determine the location of each process in BH.
2. Source code for a sample binomial heap is available for you. You may modify, compile and
use it for your project.
The computation of f (e , t (i)) i arr :
The piecewise continuous function below is used to compute the priority value of process i.
What this formula says is that, as long as the execution time of process i, ei, is different than the
execution time of any other process j, ej, the priority of process i is its execution time. In case the
execution times of two processes i and j are the same, then the arrival time tarr(i) of process i becomes
its priority among those jobs with the same execution time ei. If process i is inserted to BH for the first
time, the factor c(ei)=1. Otherwise (i.e., for further insertions), c(ei) is calculated using the above
formula and multiplied to the new execution time, ei
new, of process i (i.e., (ei
new = ei
pre- q)). Note as a
programming detail that the original execution time should be stored in the node record. To determine
( ( , ) ( , ))
1
WT t i k t i k arr
K
k
i deq
i
 

(( , ) ( , ))
1 1
1 1 1
 
  
  
I
i
arr
K
k
deq
I
i
i t i k t i k
I
WT
I
AWT
i
 



  

 


 




  


, for further insertions to BH
)
3
2
exp(
1
1 , for first insertion to BH
( )
( )
( )*
, ( )
3
max e
e
with c e
t i otherwise
c e e for e e
f e t i
i
i
arr
i i i j
i arr
3
the priority of processes i and j, their arrival times tarr(i) and tarr(j) are compared. The sooner the
arrival of a process in BH, the higher its priority.
The factor of ei, c(ei), when ei ≠ ej, slightly diminishes the priority value of process i with respect to the
remaining execution time of process i in case it is preempted before it can finish its execution and reinserted
into BH.
Algorithm:
 Initialize parameters such as q, emax;
 While there exist processes in the input list
o Put the next process i arrived in P
o While P allocated
 Enqueue incoming processes by their priority
 If ei > q
 Preempt current process
 Reassign new priority
 Re-insert process into BH
 Else release P
 For each process i in BH
 Update WTi
 DeleteMin (i.e., remove most prior process from BH)
 Assign P to this process
o End of While
 End of While
One potential algorithm is given above for a specific quantum value. You may, but do not have to, use
it.
To accomplish the minimization of AWT over a variety of quantum values, q, you have to iterate the
whole run for many increasing/decreasing q values and store the corresponding AWT values. The q
value providing the minimum AWT is the value we are looking for. This iteration is not considered in
the algorithm given above.
A Sample Scenario:
The input file (PID, e, tarr, tchange, enew):
P1 3 0 -1 0
P2 1 2 -1 0
P3 2 3 -1 0
P4 2 5 -1 0
P5 2 6 -1 0
P6 4 7 11 1
The allocation sequence of P for different q values(emax=4):
q=1
0 1 2 3 4 5 6 7 8 9 10 11 12
P1 P1 P2 P1 P3 P3 P4 P4 P5 P5 P6 P6
P
4
Time Processes in BH Priority value of processes in BH
0 P1 P1: 3
1 P1 P1: (1/exp-(2*2/3*4)3)*2 = 2.075
2 P1, P2 P1: (1/exp-(2*1/3*4)3)*1 = 1.005, P2: 1
3 P1, P3 P1: (1/exp-(2*1/3*4)3)*1 = 1.005, P3: 2
4 P3 P3: 2
5 P3, P4 P3: (1/exp-(2*1/3*4)3)*1 = 1.005, P4: 2
6 P4, P5 P4: 5, P5:6 (both have the same e value, so priority is tarr)
7 P4, P5 P4: (1/exp-(2*1/3*4)3)*1 = 1.005, P5: 2
8 P5, P6 P5: 2, P6: 4
9 P5, P6 P5: (1/exp-(2*1/3*4)3)*1 = 1.005, P6: 4
10 P6 P6: 4
11 P6 P6: (1/exp-(2*1/3*4)3)*1 = 1.005
12 EMPTY
PID Waiting time
P1 1
P2 0
P3 1
P4 1
P5 2
P6 3
AWT = 8/6 = 1.33
q=2
0 2 3 4 6 8 10 11 12
P1 P2 P1 P3 P4 P5 P6 P6
Time Processes in BH Priority value of processes in BH
0 P1 P1: 3
2 P1, P2 P1: (1/exp-(2*1/3*4)3)*1 = 1.005, P2: 1
3 P1, P3 P1: (1/exp-(2*1/3*4)3)*1 = 1.005, P3: 2
4 P3 P3: 2
6 P4, P5 P4: 5, P5:6 (both have the same e value, so priority is tarr)
8 P5, P6 P5: 2, P6: 4
10 P6 P6: 4
11 P6 P6: (1/exp-(2*1/3*4)3)*1 = 1.005
12 EMPTY
PID Waiting time
P1 1
P2 0
P3 1
P4 1
P5 2
P6 3
AWT = 8/6 = 1.33
P
5
q=3
0 3 4 6 8 10 11 12
P1 P2 P3 P4 P5 P6 P6
Time Processes in BH Priority value of processes in BH
0 P1 P1: 3
3 P2, P3 P2: 1, P3: 2
4 P3 P3: 2
6 P4, P5 P4: 5, P5:6 (both have the same e value, so priority is tarr)
8 P5, P6 P5: 2, P6: 4
10 P6 P6: 4
11 P6 P6: (1/exp-(2*1/3*4)3)*1 = 1.005
12 EMPTY
PID Waiting time
P1 0
P2 0
P3 1
P4 1
P5 2
P6 3
AWT = 7/6 = 1.17
