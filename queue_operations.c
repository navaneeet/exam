#include <stdio.h>
#define MAX 100

// Structure for Queue
struct Queue {
    int front, rear;
    int array[MAX];
};

// Structure for Deque
struct Deque {
    int front, rear;
    int array[MAX];
};

// Structure for Circular Queue
struct CircularQueue {
    int front, rear;
    int array[MAX];
};

// Queue Operations
void initQueue(struct Queue *q) {
    q->front = q->rear = -1;
}

int isQueueEmpty(struct Queue *q) {
    return (q->front == -1);
}

int isQueueFull(struct Queue *q) {
    return (q->rear == MAX - 1);
}

void enqueue(struct Queue *q, int value) {
    if (isQueueFull(q)) {
        printf("Queue Overflow\n");
        return;
    }
    if (isQueueEmpty(q))
        q->front = 0;
    q->array[++q->rear] = value;
}

int dequeue(struct Queue *q) {
    if (isQueueEmpty(q)) {
        printf("Queue Underflow\n");
        return -1;
    }
    int value = q->array[q->front];
    if (q->front == q->rear)
        initQueue(q);
    else
        q->front++;
    return value;
}

// Deque Operations
void initDeque(struct Deque *d) {
    d->front = d->rear = -1;
}

int isDequeEmpty(struct Deque *d) {
    return (d->front == -1);
}

int isDequeFull(struct Deque *d) {
    return (d->rear == MAX - 1);
}

void insertFront(struct Deque *d, int value) {
    if (isDequeFull(d)) {
        printf("Deque Overflow\n");
        return;
    }
    if (isDequeEmpty(d)) {
        d->front = d->rear = 0;
    } else {
        for (int i = d->rear; i >= d->front; i--)
            d->array[i + 1] = d->array[i];
        d->rear++;
    }
    d->array[d->front] = value;
}

void insertRear(struct Deque *d, int value) {
    if (isDequeFull(d)) {
        printf("Deque Overflow\n");
        return;
    }
    if (isDequeEmpty(d))
        d->front = 0;
    d->array[++d->rear] = value;
}

int deleteFront(struct Deque *d) {
    if (isDequeEmpty(d)) {
        printf("Deque Underflow\n");
        return -1;
    }
    int value = d->array[d->front];
    if (d->front == d->rear)
        initDeque(d);
    else
        d->front++;
    return value;
}

int deleteRear(struct Deque *d) {
    if (isDequeEmpty(d)) {
        printf("Deque Underflow\n");
        return -1;
    }
    int value = d->array[d->rear];
    if (d->front == d->rear)
        initDeque(d);
    else
        d->rear--;
    return value;
}

// Circular Queue Operations
void initCircularQueue(struct CircularQueue *cq) {
    cq->front = cq->rear = -1;
}

int isCircularQueueEmpty(struct CircularQueue *cq) {
    return (cq->front == -1);
}

int isCircularQueueFull(struct CircularQueue *cq) {
    return ((cq->rear + 1) % MAX == cq->front);
}

void circularEnqueue(struct CircularQueue *cq, int value) {
    if (isCircularQueueFull(cq)) {
        printf("Circular Queue Overflow\n");
        return;
    }
    if (isCircularQueueEmpty(cq))
        cq->front = 0;
    cq->rear = (cq->rear + 1) % MAX;
    cq->array[cq->rear] = value;
}

int circularDequeue(struct CircularQueue *cq) {
    if (isCircularQueueEmpty(cq)) {
        printf("Circular Queue Underflow\n");
        return -1;
    }
    int value = cq->array[cq->front];
    if (cq->front == cq->rear)
        initCircularQueue(cq);
    else
        cq->front = (cq->front + 1) % MAX;
    return value;
}

int main() {
    struct Queue q;
    struct Deque d;
    struct CircularQueue cq;
    int choice, value;

    initQueue(&q);
    initDeque(&d);
    initCircularQueue(&cq);

    while (1) {
        printf("\n1. Queue Operations");
        printf("\n2. Deque Operations");
        printf("\n3. Circular Queue Operations");
        printf("\n4. Exit");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("\n1. Enqueue");
                printf("\n2. Dequeue");
                printf("\n3. Back to main menu");
                printf("\nEnter choice: ");
                scanf("%d", &choice);
                
                switch (choice) {
                    case 1:
                        printf("Enter value: ");
                        scanf("%d", &value);
                        enqueue(&q, value);
                        break;
                    case 2:
                        value = dequeue(&q);
                        if (value != -1)
                            printf("Dequeued: %d\n", value);
                        break;
                }
                break;

            case 2:
                printf("\n1. Insert Front");
                printf("\n2. Insert Rear");
                printf("\n3. Delete Front");
                printf("\n4. Delete Rear");
                printf("\n5. Back to main menu");
                printf("\nEnter choice: ");
                scanf("%d", &choice);
                
                switch (choice) {
                    case 1:
                        printf("Enter value: ");
                        scanf("%d", &value);
                        insertFront(&d, value);
                        break;
                    case 2:
                        printf("Enter value: ");
                        scanf("%d", &value);
                        insertRear(&d, value);
                        break;
                    case 3:
                        value = deleteFront(&d);
                        if (value != -1)
                            printf("Deleted from front: %d\n", value);
                        break;
                    case 4:
                        value = deleteRear(&d);
                        if (value != -1)
                            printf("Deleted from rear: %d\n", value);
                        break;
                }
                break;

            case 3:
                printf("\n1. Enqueue");
                printf("\n2. Dequeue");
                printf("\n3. Back to main menu");
                printf("\nEnter choice: ");
                scanf("%d", &choice);
                
                switch (choice) {
                    case 1:
                        printf("Enter value: ");
                        scanf("%d", &value);
                        circularEnqueue(&cq, value);
                        break;
                    case 2:
                        value = circularDequeue(&cq);
                        if (value != -1)
                            printf("Dequeued: %d\n", value);
                        break;
                }
                break;

            case 4:
                return 0;
        }
    }

    return 0;
}