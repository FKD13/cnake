#include <stdlib.h>
#include <stdio.h>

#include "list.h"

list_t* init_list_t() {
  list_t *list = malloc(sizeof(list_t));
  if (list == NULL) {
    printf("Failed to malloc");
  }
  return list;
}

void free_list_t(list_t** list) {
  segment_t* segment = (*list)->first;
  while (segment != NULL) {
    segment_t* n_segment = segment->next;
    free_segment_t(&segment);
    segment = n_segment;
  }
  (*list)->first = NULL;
  (*list)->last = NULL;
  *list = NULL;
}

segment_t* init_segment_t() {
  segment_t* segment = malloc(sizeof(segment_t));
  if (segment == NULL) {
    printf("Failed to malloc");
  }
  return segment;
}

/*
 * Free a segment.
 * Note we do NOT free the content, this should be handled by the caller.
 */
void free_segment_t(segment_t** segment) {
  (*segment)->content = NULL;
  (*segment)->previous = NULL;
  (*segment)->next = NULL;
  free(*segment);
}

void add_item(list_t* list, void* item) {
  if(list == NULL) {
    return;
  }
  /* Check item is not already in list */
  segment_t* segment = list->first;
  while(segment != NULL) {
    if (segment->content == item) {
      return;
    }
    segment = segment->next;
  }
  /* Add item to list */
  segment = init_segment_t();
  segment->content = item;
  if (list->first != NULL && list->last != NULL) {
    segment->previous = list->last;
    list->last->next = segment;
    list->last = segment;
  } else if (list -> first == NULL && list->last == NULL) {
    list->last = segment;
    list->first = segment;
  }
  list->length++;
}

void remove_item(list_t* list, void* item) {
  if(list == NULL) {
    return;
  }
  segment_t* segment = list->first;
  while (segment != NULL && segment->content != item) {
    segment = segment->next;
  }
  if (segment != NULL) {
    if (segment == list->first) {
      list->first = segment->next;
    }
    if (segment == list->last) {
      list->last = segment->previous;
    }
    if (segment->next != NULL) {
      segment->next->previous = segment->previous;
    }
    if (segment->previous != NULL) {
      segment->previous->next = segment->next;
    }
    free_segment_t(&segment);
    list->length--;
  }
}
