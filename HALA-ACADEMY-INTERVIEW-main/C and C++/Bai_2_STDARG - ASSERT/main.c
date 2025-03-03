#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>  /* Thêm thư viện stdarg.h */
#include <assert.h>  /* Thêm thư viện assert.h */

/* 
 * Author: Nguyen Van Thanh
 * Date: 2024-11-11
 * Description: Example program for linked list operations with dynamic memory allocation, 
 *              and assert-based testing.
 */

/* Cấu trúc node */
typedef struct Node {
    int32_t data;
    struct Node *next;
} Node;

/* Biến toàn cục để lưu số lượng phần tử */
static uint32_t g_number_elements = 0;

/* Tạo node */
Node* CreateNode(int32_t value) {
    Node *ptr = (Node *)malloc(sizeof(Node));
    if (ptr != NULL) {
        ptr->data = value;
        ptr->next = NULL;
        g_number_elements++;
    }
    return ptr;
}

/* Thêm node vào cuối danh sách */
void PushBack(Node **ptr, int32_t value) {
    if (ptr == NULL) return;
    Node *new_ptr = CreateNode(value);
    assert(new_ptr != NULL);  // Kiểm tra nếu new_ptr không NULL
    if (*ptr == NULL) {
        *ptr = new_ptr;
        return;
    }
    Node *current = *ptr;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = new_ptr;
}

/* Thêm node vào đầu danh sách */
void PushFront(Node **ptr, int32_t value) {
    if (ptr == NULL) return;
    Node *new_ptr = CreateNode(value);
    assert(new_ptr != NULL);  // Kiểm tra nếu new_ptr không NULL
    if (new_ptr != NULL) {
        new_ptr->next = *ptr;
        *ptr = new_ptr;
    }
}

/* Thêm node vào vị trí bất kỳ */
void Insert(Node **ptr, int32_t value, uint32_t pos) {
    if (ptr == NULL || pos > g_number_elements) return;
    if (pos == 0) {
        PushFront(ptr, value);
    } else if (pos == g_number_elements) {
        PushBack(ptr, value);
    } else {
        Node *current = *ptr;
        for (uint32_t i = 0; i < pos - 1; i++) {
            current = current->next;
        }
        Node *new_node = CreateNode(value);
        assert(new_node != NULL);  // Kiểm tra nếu new_node không NULL
        if (new_node != NULL) {
            new_node->next = current->next;
            current->next = new_node;
        }
    }
}

/* Xóa node tại vị trí bất kỳ */
void DeleteNode(Node **ptr, uint32_t pos) {
    if (ptr == NULL || pos >= g_number_elements) return;
    if (pos == 0) {
        Node *temp = *ptr;
        *ptr = (*ptr)->next;
        free(temp);
    } else {
        Node *current = *ptr;
        for (uint32_t i = 0; i < pos - 1; i++) {
            current = current->next;
        }
        Node *temp = current->next;
        current->next = temp->next;
        free(temp);
    }
    g_number_elements--;
}

/* Lấy kích thước của danh sách */
int32_t Size(Node *ptr) {
    int32_t size = 0;
    Node *current = ptr;
    while (current != NULL) {
        size++;
        current = current->next;
    }
    return size;
}

/* Xóa toàn bộ danh sách */
void Clear(Node **ptr) {
    while (*ptr != NULL) {
        Node *temp = *ptr;
        *ptr = (*ptr)->next;
        free(temp);
    }
    g_number_elements = 0;
}

/* Hàm sử dụng stdarg.h để in các số nguyên */
void print_numbers(const char *prefix, int num_count, ...) {
    va_list args;
    va_start(args, num_count);

    printf("%s", prefix);  // In prefix

    for (int i = 0; i < num_count; i++) {
        int value = va_arg(args, int);
        printf("%d ", value);  // In số nguyên tiếp theo
    }

    va_end(args);
    printf("\n");
}

int main(void) {
    Node *list = NULL;

    /* Thao tác với danh sách liên kết */
    PushBack(&list, 10);
    PushBack(&list, 20);
    PushBack(&list, 30);
    Insert(&list, 25, 1);

    /* Kiểm tra kích thước danh sách */
    assert(Size(list) == 4);  // Kiểm tra số lượng phần tử trong danh sách (4)

    DeleteNode(&list, 2);
    assert(Size(list) == 3);  // Kiểm tra số lượng phần tử sau khi xóa 1 node

    Clear(&list);
    assert(Size(list) == 0);  // Kiểm tra danh sách trống sau khi xóa toàn bộ

    /* Thử in các số nguyên với print_numbers */
    print_numbers("Numbers: ", 5, 1, 2, 3, 4, 5);

    return 0;
}
