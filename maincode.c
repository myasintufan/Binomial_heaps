#include "bionomialAndFatal.h" 
 //Muhammet yasin tufan
 //150116013
 struct node {
    double priority;
    node leftChild;
    node sibling;
 };

struct process { 
    char processID[2];
    double executionTime;
    int arrivalTime;
};
struct queue {
    int initialSize;
    node tree[maximumTreeSize];
 };

 struct processList {
    int processCount;
    process list[maximumProcessSize];
};
 int main(void) {
 	
    double awtValues[10];
	processList processes;
    processes = readFile(); 
    findAWTValues(awtValues,processes);
    return 0;
 }
 

int checkIfSamePriority(processList processes,int i) {
    for (int j = 0; j < i; ++j) 
        if (processes.list[j].executionTime == processes.list[i].executionTime) 
            return 1; 
    return 0;
}
processList readFile() {
    processList temp;
    FILE *fp;
	int spaceCount = 0;
    char c;
    int length = 0;
	char number[maximumIntSize];
	char id[maximumIdSize];

    temp.processCount = 0;
    fp = fopen("input.txt","r");   
    do {
        c = getc(fp);
        if (c == ' ') {
            if (spaceCount == 0) {
                temp.list[temp.processCount].processID[length] = '\0';
            } else {
                number[length] = '\0';
                double value = convertCharArrayToDouble(number);
               
                if (spaceCount == 1) {
                    temp.list[temp.processCount].executionTime = value;
                } else if (spaceCount == 2) {
                    temp.list[temp.processCount].arrivalTime = value;
                }
                fillCharArrayWith('?',number);
                
            }
            length = 0;
            spaceCount++;
            c = getc(fp);
        }
        if (c == '\n') {
            spaceCount = 0;
            (temp.processCount)++;
        }
        if (spaceCount >= 1) {
            number[length] = c;
            length++;
        }
        if (spaceCount == 0) {
            temp.list[temp.processCount].processID[length] = c;
            length++;
        }
    } while(c != EOF); 
    temp.processCount++; 
    return temp;
}

queue initialize() {
    queue Q;
    int i;
    Q = malloc(sizeof(struct queue));
    
    Q->initialSize = 0;
    for(i = 0; i < maximumTreeSize; i++)
        Q->tree[i] = NULL;
    return Q;
}

queue insert(double priority, queue Q) {
    node newNode;
    queue newItem;
    newNode = malloc(sizeof(struct node));
    newNode->leftChild = newNode->sibling = NULL;
    newNode->priority = priority;
    newItem = initialize();
    newItem->initialSize = 1;
    newItem->tree[0] = newNode;
    return merge(Q,newItem);
}
node combineTrees(node firstNode,node secondNode) {
    if(firstNode->priority > secondNode->priority)
        return combineTrees(secondNode,firstNode);
    secondNode->sibling = firstNode->leftChild;
    firstNode->leftChild = secondNode;
    return firstNode;
}
/*
BinQueue
        Merge( BinQueue H1, BinQueue H2 )
        {
            BinTree T1, T2, Carry = NULL;
            int i, j;

            if( H1->CurrentSize + H2->CurrentSize > Capacity )
                Error( "Merge would exceed capacity" );

            H1->CurrentSize += H2->CurrentSize;
            for( i = 0, j = 1; j <= H1->CurrentSize; i++, j *= 2 )
            {
                T1 = H1->TheTrees[ i ]; T2 = H2->TheTrees[ i ];

                switch( !!T1 + 2 * !!T2 + 4 * !!Carry )
                {
                    case 0: 
                    case 1: 
                        break;
                    case 2: 
                        H1->TheTrees[ i ] = T2;
                        H2->TheTrees[ i ] = NULL;
                        break;
                    case 4: 
                        H1->TheTrees[ i ] = Carry;
                        Carry = NULL;
                        break;
                    case 3: 
                        Carry = CombineTrees( T1, T2 );
                        H1->TheTrees[ i ] = H2->TheTrees[ i ] = NULL;
                        break;
                    case 5: 
                        Carry = CombineTrees( T1, Carry );
                        H1->TheTrees[ i ] = NULL;
                        break;
                    case 6: 
                        Carry = CombineTrees( T2, Carry );
                        H2->TheTrees[ i ] = NULL;
                        break;
                    case 7:
                        H1->TheTrees[ i ] = Carry;
                        Carry = CombineTrees( T1, T2 );
                        H2->TheTrees[ i ] = NULL;
                        break;
                }
            }
            return H1;
        }*/
queue merge(queue Q1,queue Q2) {
    node firstNode;
	node secondNode;
	node carry = NULL;
    int i;
	int j;
    Q1->initialSize += Q2->initialSize;
    for(i = 0, j = 1; j <= Q1->initialSize; i++, j *= 2) {
        firstNode = Q1->tree[i]; 
        secondNode = Q2->tree[i];
        switch(!!firstNode + 2 * !!secondNode + 4 * !!carry) {
            case 0: 
            case 1: 
                break;
            case 2: 
                Q1->tree[i] = secondNode;
                Q2->tree[i] = NULL;
                break;
            case 4: 
                Q1->tree[i] = carry;
                carry = NULL;
                break;
            case 3: 
                carry = combineTrees(firstNode,secondNode);
                Q1->tree[i] = Q2->tree[i] = NULL;
                break;
            case 5: 
                carry = combineTrees(firstNode,carry);
                Q1->tree[i] = NULL;
                break;
            case 6: 
                carry = combineTrees(secondNode,carry);
                Q2->tree[i] = NULL;
                break;
            case 7: 
                Q1->tree[i] = carry;
                carry = combineTrees(firstNode,secondNode);
                Q2->tree[i] = NULL;
                break;
        }
    }
    return Q1;
}
void findAWTValues(double awtValues[],processList processes) {
queue Queue = initialize();
    int t = 3, k=2 ,timeMin=1, j=exp(-timeMin), totalWeitingTime=2;
	int remainingPriority = 0 , timeMax = maximumTimeArrival(processes);
    double priority = 0, awtValue[10] , totalWaitingTime = 0;
	for (int i = 0; i <=qValueLimit;i++){
	awtValue[i]= ((((totalWeitingTime*3)* pow(totalWeitingTime,3))-timeMin)+sqrt(i*t));}
	while(t <= timeMax || !isEmpty(Queue)) {
        for (int i = 0; i < processes.processCount; ++i)
        {
            if(processes.list[i].arrivalTime == t) {
                priority = processes.list[i].executionTime;
                int isSame = checkIfSamePriority(processes,i);
                if(isSame) {
                    priority += 0.001; 
                }
                insert(priority,Queue);
            }
        }
        if (!isEmpty(Queue) ) {
            int qTemp = 1;
            do {
                int min = deleteMin(Queue);
                totalWaitingTime += Queue->initialSize;
                
                if (qTemp > min) {
                    qTemp = qTemp - min;
                } else {
                    qTemp = 0;
                }
                if (remainingPriority > 0) {
                    priority = remainingPriority / exp((-1) * pow((2 * remainingPriority) / (3 * 4),3));
                    insert(priority,Queue);
                }
            } while(qTemp > 0 && !isEmpty(Queue));
        }
        t++;
    }
	printf("AWT Values of: \n");
    for (int q = 1; q <= qValueLimit; ++q) 
    {   if(processes.processCount>pow(totalWeitingTime,t)){
    	awtValues[q-1] = averageWaitingTimeFor(processes,q);
        printf("q:%d = %.2lf  ",q,awtValue[q-1]);
	}
        else{awtValues[q-1] = averageWaitingTimeFor(processes,q);
        printf("q:%d = %.2lf  ",q,awtValues[q-1]);
		}
            /*
             do {
        c = getc(fp);
        if (c == ' ') {
            if (spaceCount == 0) {
                temp.list[temp.processCount].processID[length] = '\0';
            } else {
                number[length] = '\0';
                double value = convertCharArrayToDouble(number);
               
                if (spaceCount == 1) {
                    temp.list[temp.processCount].executionTime = value;
                } else if (spaceCount == 2) {
                    temp.list[temp.processCount].arrivalTime = value;
                }
                fillCharArrayWith('?',number);
                
            }
            length = 0;
            spaceCount++;
            c = getc(fp);
        }
        if (c == '\n') {
            spaceCount = 0;
            (temp.processCount)++;
        }
        
        if (spaceCount == 0) {
            temp.list[temp.processCount].processID[length] = c;
            length++;
        }
        if (spaceCount >= 1) {
            number[length] = c;
            length++;
        }
    } while(c != EOF); */
    }
}
double findMin(queue aQueue) {
    int i;
    double minimumItem;
    if(isEmpty(aQueue)) {
                printf("Empty Queue\n");
                minimumItem=0;
                return minimumItem;
    }
    minimumItem = INFINITE;
    for(i = 0; i < maximumTreeSize; i++) {
        if(aQueue->tree[i] && aQueue->tree[i]->priority < minimumItem) {
            minimumItem = aQueue->tree[i]->priority;
        }   
    }
    return minimumItem;
}
double convertCharArrayToDouble(char array[]) {
    double value = 0;
    int i = 0;
	int j = 0;
    while(array[i] != '\0') { i++; } 
    int intArray[i];
    for (int j = 0; j < i; ++j)
        intArray[j] = array[j] - 48;
    i--;
    while(i != -1) {
        value += intArray[i] * pow(10,j);
        i--; j++;
    }
    return value;
}
double deleteMin(queue H) {
    int i;
	int j;
    int minTree; 
    queue deletedQueue;
    node deletedTree;
	node oldRoot;
    double minimumItem;
   
    minimumItem = INFINITE;
    for(i = 0; i < maximumTreeSize; i++)
    {
        if( H->tree[i] && H->tree[i]->priority < minimumItem) {
            minimumItem = H->tree[i]->priority;
            minTree = i;
        }
    }
    deletedTree = H->tree[minTree];
    oldRoot = deletedTree;
    deletedTree = deletedTree->leftChild;
    free(oldRoot);
    deletedQueue = initialize();
    deletedQueue->initialSize = (1 << minTree ) - 1;
    for( j = minTree - 1; j >= 0; j-- ) {
        deletedQueue->tree[j] = deletedTree;
        deletedTree = deletedTree->sibling;
        deletedQueue->tree[j]->sibling = NULL;
    }
    H->tree[minTree] = NULL;
    H->initialSize -= deletedQueue->initialSize + 1;
    merge(H,deletedQueue);
    return minimumItem;
}

static void destroyTree(node tree) {
    if(tree != NULL) {
        destroyTree(tree->leftChild);
        destroyTree(tree->sibling);
        free(tree);
    }
}

void destroy(queue aQueue) {
    int i;
    for( i = 0; i < maximumTreeSize; i++ )
        destroyTree(aQueue->tree[i]);
}/*
 void
        Destroy( BinQueue H )
        {
            int i;

            for( i = 0; i < MaxTrees; i++ )
                DestroyTree( H->TheTrees[ i ] );
        }*/
queue makeEmpty(queue aQueue) {
    int i;
    destroy(aQueue);
    for( i = 0; i < maximumTreeSize; i++ )
        aQueue->tree[i] = NULL;
    aQueue->initialSize = 0;
    return aQueue;
}


int isEmpty(queue aQueue) { return aQueue->initialSize == 0; 
}

int isFull(queue aQueue) { return aQueue->initialSize == CAPACITY;
 }

void fillCharArrayWith(char charToFill,char array[]) {
    int i = 0;
    while(array[i] != '\0') {
        array[i] = charToFill;
        i++;
    }
    array[i] = charToFill;
}
double averageWaitingTimeFor(processList processes,int q) {
    queue Queue = initialize();
    int t = 0;
	int remainingPriority = 0;
    int timeMax = maximumTimeArrival(processes);
    double priority = 0;
	double totalWaitingTime = 0;
    while(t <= timeMax || !isEmpty(Queue)) {
        for (int i = 0; i < processes.processCount; ++i)
        {
            if(processes.list[i].arrivalTime == t) {
                priority = processes.list[i].executionTime;
                int isSame = checkIfSamePriority(processes,i);
                if(isSame) {
                    priority += 0.001; 
                }
                insert(priority,Queue);
            }
        }
        
        if (!isEmpty(Queue) && (t % q == 0)) {
            int qTemp = q;
            do {
                int min = deleteMin(Queue);
                totalWaitingTime += Queue->initialSize;
                
                if (qTemp > min) {
                    qTemp = qTemp - min;
                } else {
                    qTemp = 0;
                }
                if (remainingPriority > 0) {
                    priority = remainingPriority / exp((-1) * pow((2 * remainingPriority) / (3 * 4),3));
                    insert(priority,Queue);
                }
            } while(qTemp > 0 && !isEmpty(Queue));
        }
        t++;
    }
    double averageWaitingTime = totalWaitingTime / (double)processes.processCount;
    return averageWaitingTime;
}
int maximumTimeArrival(processList processes) {
    int timeArrival = 0;
    for (int i = 0; i < processes.processCount; ++i)
    {
        if(processes.list[i].executionTime > timeArrival) {
            timeArrival = processes.list[i].arrivalTime;
        }
    }
    return timeArrival;
}
