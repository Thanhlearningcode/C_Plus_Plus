#include "linked_list.h"
#include <stdlib.h>

/* Biến toàn cục để lưu số lượng phần tử */
static uint32 g_number_elements = 0;

/* Tạo node */
Node* CreateNode(int32 value) {
    Node *ptr = (Node *)malloc(sizeof(Node));
    if (ptr != NULL) {
        ptr->data = value;
        ptr->next = NULL;
        g_number_elements++;
    }
    return ptr;
}

/* Thêm node vào cuối danh sách */
void PushBack(Node **ptr, int32 value) {
    if (ptr == NULL) return;
    Node *new_ptr = CreateNode(value);
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
void PushFront(Node **ptr, int32 value) {
    if (ptr == NULL) return;
    Node *new_ptr = CreateNode(value);
    if (new_ptr != NULL) {
        new_ptr->next = *ptr;
        *ptr = new_ptr;
    }
}

/* Xóa node cuối */
void PopBack(Node **ptr) {
    if (ptr == NULL || *ptr == NULL) return;
    Node *current = *ptr;
    if (current->next == NULL) {
        free(current);
        *ptr = NULL;
    } else {
        while (current->next->next != NULL) {
            current = current->next;
        }
        free(current->next);
        current->next = NULL;
    }
    g_number_elements--;
}

/* Xóa node đầu */
void PopFront(Node **ptr) {
    if (ptr == NULL || *ptr == NULL) return;
    Node *temp = *ptr;
    *ptr = (*ptr)->next;
    free(temp);
    g_number_elements--;
}

/* Thêm node vào vị trí bất kỳ */
void Insert(Node **ptr, int32 value, uint32 pos) {
    if (ptr == NULL || pos > g_number_elements) return;
    if (pos == 0) {
        PushFront(ptr, value);
    } else if (pos == g_number_elements) {
        PushBack(ptr, value);
    } else {
        Node *current = *ptr;
        for (uint32 i = 0; i < pos - 1; i++) {
            current = current->next;
        }
        Node *new_node = CreateNode(value);
        if (new_node != NULL) {
            new_node->next = current->next;
            current->next = new_node;
        }
    }
}

/* Xóa node tại vị trí bất kỳ */
void DeleteNode(Node **ptr, uint32 pos) {
    if (ptr == NULL || pos >= g_number_elements) return;
    if (pos == 0) {
        PopFront(ptr);
    } else {
        Node *current = *ptr;
        for (uint32 i = 0; i < pos - 1; i++) {
            current = current->next;
        }
        Node *temp = current->next;
        current->next = temp->next;
        free(temp);
        g_number_elements--;
    }
}

/* Xóa toàn bộ danh sách */
void Clear(Node **ptr) {
    while (*ptr != NULL) {
        PopFront(ptr);
    }
}

