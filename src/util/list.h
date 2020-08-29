#ifndef CNAKE_LIST_H
#define CNAKE_LIST_H

typedef struct segment_t {
  void *content;
  struct segment_t *next;
  struct segment_t *previous;
} segment_t;

typedef struct list_t {
  int length;
  segment_t *first;
  segment_t *last;
} list_t;

/* Basic list operations */
list_t* init_list_t();
void free_list_t(list_t** list);
void add_item(list_t* list, void* item);
void remove_item(list_t* list, void* item);

/* Basic segment operations */
segment_t* init_segment_t();
void free_segment_t(segment_t** segment);
#endif //CNAKE_LIST_H
