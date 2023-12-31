#include "list.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Node Node;

struct Node {
  void *data;
  Node *next;
  Node *prev;
};

struct List {
  Node *head;
  Node *tail;
  Node *current;
};

typedef List List;

Node *createNode(void *data) {
  Node *new = (Node *)malloc(sizeof(Node));
  assert(new != NULL);
  new->data = data;
  new->prev = NULL;
  new->next = NULL;
  return new;
}

List *createList() {
  List *newList = (List *)malloc(sizeof(List));
  newList->head = NULL;
  newList->current = NULL;
  newList->tail = NULL;
  return newList;
}

void *firstList(List *list) {
  if (list == NULL || list->head == NULL) {
    return NULL; // Return NULL if the list is empty or invalid
  }

  list->current = list->head;

  return list->current->data;
}

void *nextList(List *list) {
  void *response;
  if (list->current != NULL && list->current->next != NULL) {
    list->current = list->current->next;
    response = list->current->data;
  } else {
    response = NULL;
  }
  return response;
}

void *lastList(List *list) {
  void *response1;
  if (list != NULL && list->current != NULL) {
    while (list->current->next != NULL) {
      list->current = list->current->next;
    }
    response1 = list->current->data;
  } else {
    response1 = NULL;
  }
  return response1;
}

void *prevList(List *list) {
  void *response;
  if (list->current != NULL && list->current->prev != NULL) {
    list->current = list->current->prev;
    response = list->current->data;
  } else {
    response = NULL;
  }
  return response;
}

void pushFront(List *list, void *data) {
  Node *newNode = createNode(data);
  if (list->head != NULL) {
    newNode->next = list->head;
    list->head->prev = newNode;
    list->head = newNode;
  } else {
    list->head = newNode;
    list->tail = newNode;
  }
}

void pushBack(List *list, void *data) {
  list->current = list->tail;
  pushCurrent(list, data);
}

void pushCurrent(List *list, void *data) {
  Node *newNode = createNode(data);
  if (list->current != list->tail) {
    newNode->prev = list->current;
    newNode->next = list->current->next;
    list->current->next = newNode;
  } else {
    newNode->prev = list->current;
    list->tail = newNode;
    list->current->next = newNode;
  }
}

void *popFront(List *list) {
  list->current = list->head;
  return popCurrent(list);
}

void *popBack(List *list) {
  list->current = list->tail;
  return popCurrent(list);
}

void *popCurrent(List *list) {
  Node *stbGone = createNode(list->current->data);
  if (list->current != list->head && list->current != list->tail) {
    list->current->prev->next = list->current->next;
    list->current->next->prev = list->current->prev;
    list->current = list->current->next;
  } else if (list->current == list->head && list->current != list->tail) {
    list->head = list->current->next;
    list->head->prev = NULL;
  } else if (list->current != list->head && list->current == list->tail) {
    list->tail = list->current->prev;
    list->tail->next = NULL;
  } else {
    list = NULL;
  }

  return stbGone->data;
}

void cleanList(List *list) {
  while (list->head != NULL) {
    popFront(list);
  }
}