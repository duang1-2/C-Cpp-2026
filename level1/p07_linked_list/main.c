
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node *next;
} Node;

Node *createNode(int value) {
    Node *node = (Node *)malloc(sizeof(Node));
    if (node == NULL) {
        printf("内存分配失败！\n");
        exit(1);
    }
    node->value = value;
    node->next = NULL;
    return node;
}

void append(Node **head, int value) {
    Node *newNode = createNode(value);
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    Node *cur = *head;
    while (cur->next != NULL) {
        cur = cur->next;
    }
    cur->next = newNode;
}

void printList(Node *head) {
    Node *cur = head;
    while (cur != NULL) {
        printf("%d -> ", cur->value);
        cur = cur->next;
    }
    printf("NULL\n");
}

Node *reverseList(Node *head) {
    Node *prev = NULL;
    Node *cur  = head;
    Node *next = NULL;

    while (cur != NULL) {
        next = cur->next;
        cur->next = prev;
        prev = cur;
        cur  = next;
    }
    return prev;
}

int findFirst(Node *head, int target) {
    int index = 0;
    Node *cur = head;
    while (cur != NULL) {
        if (cur->value == target) {
            return index;
        }
        cur = cur->next;
        index++;
    }
    return -1;
}


int findNext(Node *head, int target, int startIndex) {
    if (startIndex < 0) return -1;

    Node *cur = head;
    int index = 0;
    while (cur != NULL && index < startIndex) {
        cur = cur->next;
        index++;
    }
    if (cur == NULL) return -1;


    cur = cur->next;
    index = startIndex + 1;
    while (cur != NULL) {
        if (cur->value == target) {
            return index;
        }
        cur = cur->next;
        index++;
    }
    return -1;
}

void freeList(Node *head) {
    Node *cur = head;
    while (cur != NULL) {
        Node *tmp = cur->next;
        free(cur);
        cur = tmp;
    }
}

int main() {
    Node *head = NULL;

    int values[] = {1, 3, 5, 7, 5, 9, 5, 2};
    int n = sizeof(values) / sizeof(values[0]);
    for (int i = 0; i < n; i++) {
        append(&head, values[i]);
    }

    printf("原始链表：");
    printList(head);


    head = reverseList(head);
    printf("反序后  ：");
    printList(head);

    int idx = findFirst(head, 5);
    if (idx != -1)
        printf("第一个 5 的序号：%d\n", idx);
    else
        printf("未找到 5，返回：%d\n", idx);


    printf("查找所有 5 的位置：");
    int searchFrom = idx;
    while (searchFrom != -1) {
        printf("%d ", searchFrom);
        searchFrom = findNext(head, 5, searchFrom);
    }
    printf("\n");


    freeList(head);
    return 0;
}


