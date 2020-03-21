#include <stdio.h>
 #include <stdlib.h>
 #include <math.h>
 typedef struct node *node;
 typedef struct queue *queue;
 typedef struct processList processList;
 typedef struct process process;
 void findAWTValues(double awtValues[],processList processes);
 double averageWaitingTimeFor(processList processes,int q);
 int checkIfSamePriority(processList processes,int i);
 processList readFile();
 queue insert(double item, queue Q);
 int isFull(queue aQueue);
 int maximumTimeArrival(processList processes);
 int isEmpty(queue aQueue);
 void fillCharArrayWith(char charToFill,char array[]);
 queue makeEmpty(queue aQueue);
 double findMin(queue aQueue);
 static void destroyTree(node tree);
 void destroy(queue aQueue);
 double convertCharArrayToDouble(char array[]);
 queue initialize();
 queue merge(queue Q1,queue Q2);
 node combineTrees(node firstNode,node secondNode);
 double deleteMin(queue H);
 #define maximumIntSize 500
 #define maximumIdSize 500
 #define E 2.71828
 #define qValueLimit 10
 #define maximumTreeSize 500
 #define CAPACITY 4000
 #define INFINITE (6000000000L)
 #define maximumProcessSize 700
