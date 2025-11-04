#include <stdio.h>
#include <stdlib.h>

// 栈的定义
#define MAX_SIZE 100

typedef struct {
    int data[MAX_SIZE];
    int top;
} Stack;

// 初始化栈
void initStack(Stack *stack) {
    stack->top = -1;
}

// 判断栈是否为空
int isStackEmpty(Stack *stack) {
    return stack->top == -1;
}

// 判断栈是否已满
int isStackFull(Stack *stack) {
    return stack->top == MAX_SIZE - 1;
}

// 入栈
void push(Stack *stack, int value) {
    if (isStackFull(stack)) {
        printf("栈已满，无法入栈\n");
        return;
    }
    stack->data[++stack->top] = value;
}

// 出栈
int pop(Stack *stack) {
    if (isStackEmpty(stack)) {
        printf("栈为空，无法出栈\n");
        return -1;
    }
    return stack->data[stack->top--];
}

// 获取栈顶元素
int peek(Stack *stack) {
    if (isStackEmpty(stack)) {
        printf("栈为空\n");
        return -1;
    }
    return stack->data[stack->top];
}

// 用两个栈实现队列
typedef struct {
    Stack stack1;  // 用于入队操作
    Stack stack2;  // 用于出队操作
} QueueUsingStacks;

// 初始化队列
void initQueue(QueueUsingStacks *queue) {
    initStack(&queue->stack1);
    initStack(&queue->stack2);
}

// 判断队列是否为空
int isQueueEmpty(QueueUsingStacks *queue) {
    return isStackEmpty(&queue->stack1) && isStackEmpty(&queue->stack2);
}

// 入队操作
void enqueue(QueueUsingStacks *queue, int value) {
    // 直接将元素压入stack1
    push(&queue->stack1, value);
}

// 出队操作
int dequeue(QueueUsingStacks *queue) {
    // 如果stack2为空，则将stack1中的所有元素倒入stack2
    if (isStackEmpty(&queue->stack2)) {
        while (!isStackEmpty(&queue->stack1)) {
            push(&queue->stack2, pop(&queue->stack1));
        }
    }
    
    // 如果stack2仍然为空，说明队列为空
    if (isStackEmpty(&queue->stack2)) {
        printf("队列为空，无法出队\n");
        return -1;
    }
    
    // 从stack2出栈一个元素
    return pop(&queue->stack2);
}

// 获取队首元素
int queueFront(QueueUsingStacks *queue) {
    // 如果stack2为空，则将stack1中的所有元素倒入stack2
    if (isStackEmpty(&queue->stack2)) {
        while (!isStackEmpty(&queue->stack1)) {
            push(&queue->stack2, pop(&queue->stack1));
        }
    }
    
    // 如果stack2仍然为空，说明队列为空
    if (isStackEmpty(&queue->stack2)) {
        printf("队列为空\n");
        return -1;
    }
    
    // 返回stack2的栈顶元素
    return peek(&queue->stack2);
}

// 主函数，用于测试
int main() {
    QueueUsingStacks queue;
    initQueue(&queue);
    
    // 测试入队操作
    enqueue(&queue, 1);
    enqueue(&queue, 2);
    enqueue(&queue, 3);
    
    printf("队首元素: %d\n", queueFront(&queue));
    
    // 测试出队操作
    printf("出队元素: %d\n", dequeue(&queue));
    printf("出队元素: %d\n", dequeue(&queue));
    
    // 继续入队
    enqueue(&queue, 4);
    enqueue(&queue, 5);
    
    // 依次出队并打印
    printf("剩余元素依次出队: ");
    while (!isQueueEmpty(&queue)) {
        printf("%d ", dequeue(&queue));
    }
    printf("\n");
    
    return 0;
}