#include <stdio.h>
#include <stdlib.h>

/* 
 * Author: Nguyen Van Thanh
 * Date: 2024-11-11
 * Description: Example program for implementing a circular queue with dynamic memory allocation in C.
 *              Includes operations for enqueue, dequeue, front element access, and queue overflow/underflow handling.
 */

/* Cấu trúc node */
typedef struct Queue
{
    int *items; // chứa địa chỉ của Queue
    int size;   // kích thước hàng đợi
    int front, rear;
} Queue;

void initialize(Queue *queue, int size){
    queue->items = (int*) malloc(sizeof(int) * size); // cấp phát bộ nhớ động cho mảng
    queue->size = size;
    queue->front = -1;
    queue->rear = -1;
}

void destroy(Queue *queue){
    free(queue->items); // giải phóng bộ nhớ đã cấp phát
    queue->items = NULL; // tránh lỗi nếu truy cập sau khi giải phóng
}

int is_empty(Queue queue){
    return queue.front == -1;
}

int is_full(Queue queue){
    return ((queue.rear + 1) % queue.size) == queue.front; // kiểm tra đầy
}

void enqueue(Queue *queue, int value){
    if (!is_full(*queue)){
        if (is_empty(*queue)){
            queue->front = queue->rear = 0; // trường hợp hàng đợi rỗng
        }
        else{
            queue->rear = (queue->rear + 1) % queue->size; // vòng lại nếu đạt kích thước
        }
        queue->items[queue->rear] = value;
    }
    else{
        printf("Queue overflow\n"); // hàng đợi đầy
    }
}

int dequeue(Queue *queue){
    if (!is_empty(*queue)){
        int dequeue_value = queue->items[queue->front]; // lấy giá trị front
        if (queue->front == queue->rear){
            queue->front = queue->rear = -1; // trường hợp chỉ còn một phần tử
        }
        else{
            queue->front = (queue->front + 1) % queue->size; // vòng lại nếu cần
        }
        return dequeue_value;
    }
    else{
        printf("Queue underflow\n"); // hàng đợi rỗng
        return -1;
    }
}

int front(Queue queue) {
    if (!is_empty(queue)) {
        return queue.items[queue.front]; // trả về phần tử đầu
    } else {
        printf("Queue is empty\n");
        return -1;
    }
}

int main()
{
    Queue queue;
    initialize(&queue, 3); // khởi tạo hàng đợi với kích thước 3

    enqueue(&queue, 10);
    enqueue(&queue, 20);
    enqueue(&queue, 30);

    printf("Front element: %d\n", front(queue));

    printf("Dequeue element: %d\n", dequeue(&queue));
    printf("Dequeue element: %d\n", dequeue(&queue));

    printf("Front element: %d\n", front(queue));

    enqueue(&queue, 40);
    enqueue(&queue, 50);
    printf("Dequeue element: %d\n", dequeue(&queue));
    printf("Front element: %d\n", front(queue));

    destroy(&queue); // Giải phóng bộ nhớ khi không còn sử dụng hàng đợi

    return 0;
}
