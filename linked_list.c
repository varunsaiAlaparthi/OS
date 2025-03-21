#include <stdlib.h>
#include "linked_list.h"

// Creates and returns a new list
// If compare is NULL, list_insert just inserts at the head
list_t* list_create(compare_fn compare)
{
    /* IMPLEMENT THIS */
    list_t* init_list = (list_t*)malloc(sizeof(list_t));
    init_list->head = NULL;
    init_list->tail = NULL;
    init_list->compare = compare;
    init_list->count = 0;
    return init_list;
}

// Destroys a list
void list_destroy(list_t* list)
{
    list_node_t* curr_head = list->head;
    while(curr_head != NULL) {
        list_node_t* next_node = curr_head->next;
        free(curr_head);
        curr_head = next_node;
    }
    free(list);
}

// Returns head of the list
list_node_t* list_head(list_t* list)
{
    /* IMPLEMENT THIS */
    return list->head;
}

// Returns tail of the list
list_node_t* list_tail(list_t* list)
{
    /* IMPLEMENT THIS */
    return list->tail;
}

// Returns next element in the list
list_node_t* list_next(list_node_t* node)
{
    /* IMPLEMENT THIS */
    return node->next;
}

// Returns prev element in the list
list_node_t* list_prev(list_node_t* node)
{
    /* IMPLEMENT THIS */
    return node->prev;
}

// Returns end of the list marker
list_node_t* list_end(list_t* list)
{
    /* IMPLEMENT THIS */
    return NULL;
}

// Returns data in the given list node
void* list_data(list_node_t* node)
{
    /* IMPLEMENT THIS */
    return node->data;
}

// Returns the number of elements in the list
size_t list_count(list_t* list)
{
    /* IMPLEMENT THIS */
    return list->count;
}

// Finds the first node in the list with the given data
// Returns NULL if data could not be found
list_node_t* list_find(list_t* list, void* data)
{
    /* IMPLEMENT THIS */
    list_node_t* curr_head = list->head;
    while(curr_head != NULL) {
        if(curr_head->data == data) {
            return curr_head;
        }
        curr_head = curr_head->next;
    }
    return NULL;
}

// Inserts a new node in the list with the given data
// Returns new node inserted
list_node_t* list_insert(list_t* list, void* data)
{
    /* IMPLEMENT THIS */
    list_node_t* curr_block = list->head;
    list_node_t* new_block = (list_node_t*)malloc(sizeof(list_node_t));
    
    new_block->data=data;
    new_block->next = NULL;
    new_block->prev = NULL;
    
    // list is empty
    if(curr_block == NULL) {
        list->head = new_block;
        list->tail = new_block;
        list->count++;
        return new_block;
    }

    if(list->compare == NULL) {
        // insert at head
        list->head->prev = new_block;
        new_block->next = list->head;
        new_block->prev = NULL;
        list->head = new_block;
        list->count++;
        return new_block;
    }

    while (curr_block != NULL && list->compare(new_block->data, curr_block->data) > 0) {
        curr_block = curr_block->next;
    }

    if(curr_block == NULL) {
        // new_block is added at end
        new_block->prev = list->tail;
        list->tail->next = new_block;
        list->tail = new_block;
    } else if(curr_block == list->head) {
        // new_block goes at start
        new_block->next = list->head;
        list->head->prev = new_block;
        list->head=new_block;
    } else {
        // new_block goes in middle
        new_block->next = curr_block;
        new_block->prev = curr_block->prev;
        curr_block->prev->next = new_block;
        curr_block->prev = new_block;
    }

    list->count++;

    return new_block;
}

list_node_t* list_insert_tail(list_t* list, void* data) {
    list_node_t* new_block = (list_node_t*)malloc(sizeof(list_node_t));
    
    if (new_block == NULL) {
        return NULL;
    }
    new_block->data = data;
    new_block->next = NULL;
    new_block->prev = NULL;

    if (list->tail == NULL) {
        list->head = new_block;
        list->tail = new_block;
    } else {
        // Non-empty list
        new_block->prev = list->tail;
        list->tail->next = new_block;
        list->tail = new_block;
    }
    list->count++;
    return new_block;
}



// Removes a node from the list and frees the node resources
void list_remove(list_t* list, list_node_t* node)
{
    /* IMPLEMENT THIS */
    list_node_t* curr_block = list->head;
    while(curr_block != NULL) {
        if(curr_block == node) {
            list_node_t* next_block = curr_block->next;
            list_node_t* prev_block = curr_block->prev;

            if(prev_block) {
                prev_block->next = next_block;
            } else {
                // prev block is null, which means block that we want remove is the head. In this case, we need to update head of the list
                list->head = next_block;
            }

            if(next_block) {
                next_block->prev = prev_block;
            } else {
                // next block is null, which means block that we want to remove is the tail. In this case, we need to update the tail of the list
                list->tail = prev_block;
            }
            
            curr_block->prev = NULL;
            curr_block->next = NULL;
            
            free(curr_block);
            list->count--;
            return;
        }
        curr_block = curr_block->next;
    }
    return;
}
