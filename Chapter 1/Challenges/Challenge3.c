#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node{
    struct Node * next;
    struct Node * prev;
    char * data;
};

typedef struct List{
    struct Node * head;
    struct Node * tail;
    int length;
};

struct List push_front(char * val, struct List l) {
    struct Node * head = l.head;

    if(head == NULL) {
        struct Node * n = malloc(sizeof(struct Node));
        n->data = malloc(10);
        strcpy(n->data, val);
        n->next = NULL;
        n->prev = NULL;
        l.head = n;
        l.tail = n;
        l.length = 1;
        return l;
    } else {
        struct Node * n = malloc(sizeof(struct Node));
        n->data = malloc(10);
        strcpy(n->data, val);
        n->next = l.head;
        l.head = n;
        n->prev = NULL;
        l.length++;
        return l;
    }
}

struct List push_back(char * val, struct List l) {
    struct Node * tail = l.tail;

    if(tail == NULL) {
        struct Node * n = malloc(sizeof(struct Node));
        n->data = malloc(10);
        strcpy(n->data, val);

        n->next = NULL;
        n->prev = NULL;
        l.head = n;
        l.tail = n;
        l.length = 1;
        return l;
    } else {
        struct Node * n = malloc(sizeof(struct Node));
        n->data = malloc(10);
        strcpy(n->data, val);

        l.tail->next = n;
        n->next = NULL;
        n->prev = l.tail;
        l.tail = n;
        l.length++;
        return l;
    }
}

struct List insert_at_pos(char * val, int pos, struct List l) {
    if(pos == 0) {
        return push_front(val, l);
    } else if(l.length == pos) {
        return push_back(val, l);
    } else {
        struct Node * ptr = l.head;
        while(pos - 1 > 0) {
            ptr = ptr->next;
            pos--;
        }

        struct Node * n = malloc(sizeof(struct Node));
        n->data = malloc(10);
        strcpy(n->data, val);
        
        struct Node * temp = ptr->next;
        ptr->next = n;
        n->next = temp;
        l.length++;
        return l;
    }
}

int search(char * target, struct List l) {
    printf("%s", target);
    printf("\n");
    struct Node * temp = l.head;
    int index = 0;
    
    while(temp != NULL) {
        if(strcmp(target, temp->data) == 0) {
            return index;
        }
        temp = temp->next;
        index++;
    }

    return -1;
}

struct List delete_head(struct List l) {
    if(l.head != NULL) {
        struct Node * temp = l.head;
        l.head = l.head->next;
        temp->next = NULL;
        l.length--;
        free(temp);
    }

    return l;
}

struct List delete_tail(struct List l) {
    if(l.tail != NULL) {
        struct Node * ptr = l.tail->prev;
        struct Node * temp = ptr->next;

        ptr->next = NULL;
        l.length--;
        free(temp);
    }

    return l;
}

struct List delete_pos(int pos, struct List l) {
    if(pos == 0) {
        return delete_head(l);
    } else if(pos == l.length) {
        return delete_tail(l);
    } else {
        struct Node * ptr = l.head;

        while(pos-1 > 0) {
            ptr = ptr->next;
            pos--;
        }

        struct Node * temp = ptr->next;

        ptr->next = ptr->next->next;
        l.length--;
        free(temp);
    }
}

void print_list_forward(struct List l) {
    struct Node * ptr = l.head;

    while(ptr != NULL) {
        printf("%s", ptr->data);
        printf("-->");
        ptr = ptr->next;
    }
}

void print_list_backward(struct List l) {
    struct Node * ptr = l.tail;

    while(ptr != NULL) {
        printf("%s", ptr->data);
         printf("-->");
        ptr = ptr->prev;
    }
}

int main() {

    struct List l;
    l.head = NULL;
    l.tail = NULL;
    l.length = 0;

    l = push_back("1", l);
    for(int i=2; i<=5; i++) {
        char snum[5];
        sprintf(snum, "%d", i);
        l = push_back(snum, l);
    }

    print_list_forward(l);   
    printf("%s", "\n");
    print_list_backward(l);
    printf("%s", "\n");
    insert_at_pos("69", 2, l);
    print_list_forward(l); 

    printf("%s", "\n");

    int pos = search("69", l);
    printf("%d", pos);
    printf("\n");

    l = delete_head(l);
    print_list_forward(l); 
    printf("\n");

    delete_tail(l);
    print_list_forward(l);
    printf("\n");

    delete_pos(2, l);
    print_list_forward(l);

    return 0;
}