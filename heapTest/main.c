//
//  main.c
//  heapTest
//
//  Created by 백대성 on 2/2/26.
//

#include <stdlib.h>
#include <stdio.h>

unsigned int a;     //0~(2^32)-1)
unsigned int b;
unsigned int c;


typedef unsigned int uint32;
typedef unsigned char uint8;

uint32 d;
uint8 sensor_temp1;


// 노드 정의
typedef struct ListNode {
    char data;
    struct ListNode* next;
} ListNode;

// 함수 시그니처 정의
struct List;
typedef void (*AppendFunc)(struct List*, char);
typedef void (*PrintFunc)(struct List*);
typedef char (*ReadByIndexFunc)(struct List*, int);
typedef void (*FreeFunc)(struct List*);

//구조체는 여러타입의 **변수**를 packing 한것.
typedef struct List {//구조체 안에는 함수를 선언하고 정의가 안됨
    ListNode* head;
    int size;
    AppendFunc append;
    PrintFunc print;
    ReadByIndexFunc readByIndex;
    FreeFunc free;
} List;



void List_append(List* list, char data) {
    ListNode* node = (ListNode*)malloc(sizeof(ListNode));
    node->data = data;
    node->next = NULL;
    if (!list->head) {
        list->head = node;
    } else {
        ListNode* temp = list->head;
        while (temp->next) temp = temp->next;
        temp->next = node;
    }
    list->size++;
}

void List_print(List* list) {
    ListNode* node = list->head;
    printf("[ ");
    while (node) {
        printf("%d ", node->data);
        node = node->next;
    }
    printf("]\n");
}

char List_readByIndex(List* list, int index) {
    if (index < 0 || index >= list->size) {
        printf("Index out of range!\n");
        return 0;
    }
    ListNode* node = list->head;
    for (int i = 0; i < index; ++i) node = node->next;
    return node->data;
}

void List_free(List* list) {
    ListNode* node = list->head;
    while (node) {
        ListNode* next = node->next;
        free(node);
        node = next;
    }
    list->head = NULL;
    list->size = 0;
}

void List_init(List* list) {
    list->head = NULL;
    list->size = 0;
    list->append = List_append;
    list->print = List_print;
    list->readByIndex = List_readByIndex;
    list->free = List_free;
}

int main(void) {
    List mylist;
    List_init(&mylist); // 함수 포인터가 정의한 함수의 주소를 저장
    
    
    mylist.append(&mylist, 7);
    mylist.append(&mylist, 8);
    mylist.append(&mylist, 9);
    mylist.append(&mylist, 12);

    mylist.print(&mylist);
    printf("Index 2: %d\n", mylist.readByIndex(&mylist, 2));

    mylist.free(&mylist);
    return 0;
}
