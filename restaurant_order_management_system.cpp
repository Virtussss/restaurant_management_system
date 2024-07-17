#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ORDERS 100
#define ORDER_LENGTH 100

typedef struct{
    int tableNumber;
    char dishName[ORDER_LENGTH];
} Order;

typedef struct{
    Order orders[MAX_ORDERS];
    int front;
    int rear;
    int size;
} Queue;

typedef struct{
    Order cancelledOrders[MAX_ORDERS];
    int top;
} Stack;

void initializeQueue(Queue* q){
    q->front = 0;
    q->rear = -1;
    q->size = 0;
}

void initializeStack(Stack* s){
    s->top = -1;
}

int isQueueFull(Queue* q){
    return q->size == MAX_ORDERS;
}

int isQueueEmpty(Queue* q){
    return q->size == 0;
}

int isStackFull(Stack* s){
    return s->top == MAX_ORDERS - 1;
}

int isStackEmpty(Stack* s){
    return s->top == -1;
}

void enqueue(Queue* q, Order* order){
    if(isQueueFull(q)){
        printf("Order queue is full. Cannot add more orders.\n");
        return;
    }
    q->rear = (q->rear + 1)%MAX_ORDERS;
    q->orders[q->rear] = *order;
    q->size++;
}

void dequeue(Queue* q, Order* order){
    if(isQueueEmpty(q)){
        printf("Order queue is empty. No orders to process.\n");
        return;
    }
    *order = q->orders[q->front];
    q->front = (q->front + 1)%MAX_ORDERS;
    q->size--;
}

void push(Stack* s, Order* order){
    if(isStackFull(s)){
        printf("Cancellation stack is full. Cannot undo more orders.\n");
        return;
    }
    s->cancelledOrders[++(s->top)] = *order;
}

void pop(Stack* s, Order* order){
    if(isStackEmpty(s)){
        printf("Cancellation stack is empty. No orders to undo.\n");
        return;
    }
    *order = s->cancelledOrders[(s->top)--];
}

void addOrder(Queue* orderQueue){
    Order order;
    printf("Enter the table number: ");
    scanf("%d", &order.tableNumber);
    getchar();
    printf("Enter the dish number: ");
    scanf("%[^\n]", order.dishName);
    getchar();
    enqueue(orderQueue, &order);
    printf("Order added: Table %d, Dish %s\n", order.tableNumber, order.dishName);
}

void processOrder(Queue* orderQueue){
    Order order;
    if(!isQueueEmpty(orderQueue)){
        dequeue(orderQueue, &order);
        printf("Processing order: Table %d, Dish %s\n", order.tableNumber, order.dishName);
    }
}

void cancelOrder(Queue* orderQueue, Stack* cancelStack){
    if(isQueueEmpty(orderQueue)){
        printf("No orders to cancel.\n");
        return;
    }
    Order lastOrder = orderQueue->orders[orderQueue->rear];
    orderQueue->rear = (orderQueue->rear - 1 + MAX_ORDERS)%MAX_ORDERS;
    orderQueue->size--;
    push(cancelStack, &lastOrder);
    printf("Order cancelled: Table %d, Dish %s\n", lastOrder.tableNumber, lastOrder.dishName);
}

int main(){
    Queue orderQueue;
    Stack cancelStack;
    initializeQueue(&orderQueue);
    initializeStack(&cancelStack);

    int choice;
    do{
        printf("\nRestaurant Order Management System\n");
        printf("1. Add Order\n");
        printf("2. Process Order\n");
        printf("3. Cancel Last Order\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice){
            case 1:
                addOrder(&orderQueue);
                break;
            case 2:
                processOrder(&orderQueue);
                break;
            case 3:
                cancelOrder(&orderQueue, &cancelStack);
                break;
            case 4:
                printf("Exiting...\n");
                break;
            default:
            printf("Invalid choice, Please try again.\n");
        }
    } 
    while(choice != 4);
    return 0;
}