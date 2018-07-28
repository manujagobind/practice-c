#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


struct Node {
    int data;
    struct Node *next;
};

struct Node* get_new_node(int data) {
    struct Node *node = malloc(sizeof(struct Node));
    if(node == NULL) {
        printf("\nERROR: Unable to allocate memory.\n");
        exit(1);
    }
    node->data = data;
    node->next = NULL;
    return node;
}

void destroy_node(struct Node *node) {
    free(node);
}


struct Node *HEAD = NULL;


void print_list() {
    struct Node *cur = HEAD;
    while(cur) {
        printf("%d --> ", cur->data);
        cur = cur->next;
    }
    printf("\b\b\b\n");
}

void push_front(int data) {
    struct Node *node = get_new_node(data);
    node->next = HEAD;
    HEAD = node;
}

int pop_front() {
    int data = -1;
    if(HEAD) {
        struct Node *next = HEAD->next;
        data = HEAD->data;
        destroy_node(HEAD);
        HEAD = next;
    }
    return data;
}

void push_back(int data) {
    struct Node *node = get_new_node(data);
    if(!HEAD) {
        HEAD = node;
    } else {
        struct Node *cur = HEAD;
        while(cur->next) {
            cur = cur->next;
        }
        cur->next = node;
    }
}

int pop_back() {
    int data = -1;
    if(HEAD) {
        struct Node *cur = HEAD, *prev = NULL;
        while(cur->next) {
            prev = cur;
            cur = cur->next;
        }
        data = cur->data;
        destroy_node(cur);
        if(prev) {
            prev->next = NULL;
        } else {
            HEAD = NULL;
        }
    }
    return data;
}

int size() {
    struct Node *cur = HEAD;
    int count = 0;
    while(cur) {
        ++count;
        cur = cur->next;
    }
    return count;
}

int value_at(int index) {
    int count = 0;
    struct Node *cur = HEAD;
    while(cur) {
        if(count == index) {
            return cur->data;
        }
        ++count;
        cur = cur->next;
    }
    printf("ERROR: Invalid index.\n");
    return -1;
}

void insert_at(int index, int data) {
    struct Node *node = get_new_node(data), *cur = HEAD, *prev = NULL;
    int count = 0;
    while(cur && count < index) {
        prev = cur;
        ++count;
        cur = cur->next;
    }
    if(count == index) {
        if(prev) {
            prev->next = node;
        } else {
            HEAD = node;
        }
        node->next = cur;
    } else {        
        printf("ERROR: Invalid index. Cannot Insert.\n");
    }    
}

int erase_at(int index) {
    struct Node *cur = HEAD, *prev = NULL;
    int count = 0, data = -1;
    while(cur && count < index) {
        prev = cur;
        ++count;
        cur = cur->next; 
    }
    if(HEAD && cur && count == index) {
        data = cur->data;
        if(prev) {
            prev->next = cur->next;
        } else {
            HEAD = cur->next;
        }
        destroy_node(cur);
    } else {
        printf("ERROR: Invalid index. Cannot erase node.\n");
    }
    return data;
}

int value_from_end(int index) {
    struct Node *fast = HEAD, *slow = HEAD;
    int count = 0, data = -1;
    while(fast && count < index) {
        fast = fast->next;
        ++count;
    }
    if(fast) {
        while(fast->next) {
            fast = fast->next;
            slow = slow->next;
        }
        data = slow->data;
    } else {
        printf("ERROR: Invalid index.\n");
    }
    return data;
}

void rotate(int k) {
    assert(k > 0 && k < size());
    struct Node *cur = HEAD, *prev = NULL, *end = HEAD;
    int count = 0;
    while(cur && cur->next && count < k) {
        prev = cur;
        cur = cur->next;
        ++count;
        end = end->next;
    }
    while(end->next) {
        end = end->next;
    }
    end->next = HEAD;
    prev->next = NULL;
    HEAD = cur;
}

void destroy_list() {
    struct Node *cur = HEAD, *next;
    while(cur) {
        next = cur->next;
        destroy_node(cur);
        cur = next;
    }
    HEAD = NULL;
}

void reverse() {
	if(HEAD && HEAD->next) {		
    	struct Node *prev = HEAD, *cur = HEAD->next, *next;
		prev->next = NULL;	
	    while(cur->next){
			next = cur->next;
			cur->next = prev;
			prev = cur;
			cur = next;
		}	
		cur->next = prev;
		HEAD = cur;
	}
}

int main() {
    HEAD = NULL;
    push_back(5);
    push_front(9);
    push_back(7);
    push_front(2);
    insert_at(0, 1);
    print_list();
	reverse();
    print_list();
#if 0
    rotate(3);
    print_list();
    for(int i = 0; i < 6; ++i) {     
        printf("Value at index %d from end is %d\n", i, value_from_end(i));
    }
    for(int i = 0; i < 6; ++i) {
        printf("Value at %d is %d\n", i, value_at(i));
        printf("%d erased at index %d\n", erase_at(i), i);
    }
    print_list();
    printf("Size: %d\n", size());
    printf("%d erased at index %d\n", erase_at(2), 2);
    printf("%d erased at index %d\n", erase_at(0), 0);
    print_list();
    printf("%d popped!\n", pop_back());
    printf("%d popped!\n", pop_front());
    printf("Size: %d\n", size());
    print_list();
    destroy_list();
    printf("Size: %d\n", size());
    return 0;
#endif
}
