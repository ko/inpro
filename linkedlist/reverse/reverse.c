#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "list.h"

#define LIST_SIZE 5
#define DEBUG 7
#define LOG_LEVEL 3

void init(LIST_ITEM * head) {

    int i;
    LIST_ITEM * current;

    if (head == NULL) {
        fprintf(stderr, "%s:%d:head is null\n", __FUNCTION__, __LINE__);
        return;
    }

    current = head;
    for (i = 1; i <= LIST_SIZE; i++) {
        LIST_ITEM * item = malloc(sizeof(LIST_ITEM));
        item->val = i;
        current->next = item;
        current = item;
    }

    // for the tail
    current->next = NULL;
}

void print_list(LIST_ITEM * head) {
    
    int i;
    LIST_ITEM * current = head;

    for (i = 0; i < LIST_SIZE; i++) {
        
        printf("%s:%d list[%d]->val = %d\n", __FUNCTION__, __LINE__,
                                             i, current->val);
        current = current->next;
    }
    printf("%s:%d list[%d]->val = %d\n", __FUNCTION__, __LINE__,
                                         i, current->val);

}

void print_list_r(LIST_ITEM * node) {

    if (node == NULL) {
        return;
    }

    print_list_r(node->next);
    fprintf(stdout, "%s:%d: node->val = %d\n", __FUNCTION__, __LINE__,
                                               node->val);
}

void reverse_iterate(LIST_ITEM ** head) {

    LIST_ITEM * current = *head;
    LIST_ITEM * next = NULL;
    LIST_ITEM * prev = NULL;

    while (current != NULL) {

        if (DEBUG <= LOG_LEVEL) {
            printf("%s:%d current->val = %d\n", __FUNCTION__, __LINE__,
                                                current->val);
            if (prev != NULL) {
                printf("%s:%d: prev->val = %d\n", __FUNCTION__, __LINE__,
                                                  prev->val);
            }
        }

        printf("\n");

        /*
         *    NULL -- [0] -- [1] -- [2]
         *  0.         c
         *  1.         c  ->  n  
         *  2. p   <-  c  --  n
         *  3.     <- p,c --  n
         *  4.     <-  p  -- c,n
         */
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    // current is NULL, so prev is [2]
    *head = prev;
}

void reverse_recurse(LIST_ITEM ** head) {

    LIST_ITEM * first;
    LIST_ITEM * other;

    if (*head == NULL) {
        fprintf(stderr, "%s:%d head null\n", __FUNCTION__, __LINE__);
        return;
    }

    first = *head;
    other = first->next;

    if (other == NULL) {
        fprintf(stderr, "%s:%d list is single element\n", __FUNCTION__,
                                                          __LINE__);
        return;
    }

    reverse_recurse(&other);

    /*
     * NULL -- [0] -- [1] -- [2]
     *          f      o
     *          f  <-  o
     *      <-  f  <-  o   
     */
    first->next->next = first;
    first->next = NULL;
    
    // reset head
    *head = other;
}

/* 
 * uncomment lines in body for recursive or iterative 
 */
void reverse(LIST_ITEM ** head) {
    
    reverse_recurse (head);
    //reverse_iterate (head);
}

int main(void) {

    printf("%s: hi\n", __FUNCTION__); 

    LIST_ITEM * list_head = malloc (sizeof(LIST_ITEM));
    list_head->val = 0;
    assert (list_head);
    init(list_head);

    // NOTE: pass in &list_head because we want to
    //       actually modify list_head (pass by
    //       reference) rather than passing just
    //       the value.
    reverse(&list_head);

    print_list(list_head);
    print_list_r(list_head);
}
