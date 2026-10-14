#include <stddef.h>
#include <stdlib.h>
Node* n = (Node*)malloc(sizeof(Node));
n->data = val;
n->next = NULL;
return n;
}
// 头插
void push_front(Node** head, int val) {
      Node* n = create_node(val);
      n->next = *head;     // 建立一个新节点
      *head = n;
  }
// 尾插
void push_back(Node** head, int val) {
    Node* n = create_node(val);

    if (*head == NULL) {
        *head = n;
        return;
    }
    //找到尾节点
    Node* prev = *head;
    while (prev->next != NULL) {
        prev = prev->next;
        
    }prev->next = n;
}