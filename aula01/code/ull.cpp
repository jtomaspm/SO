/*
 *
 * \author (2016) Artur Pereira <artur at ua.pt>
 */
#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "ull.h"

// My imports
#include <iostream>

namespace ull {
/* ************************************************* */

/* The information support data structure  */
struct Register {
  uint32_t nmec;    //!< student number
  const char *name; //!< student name
};

/* The linked-list support data structure */
struct Node {
  Register reg;
  struct Node *next;
};

static Node *head = NULL;

/* ************************************************* */

void reset() {
  while (head->next) {
    struct Node *p = head->next;
    free(head);
    head = p;
  }
  free(head);
  head = NULL;
}

/* ************************************************* */

void load(const char *fname) {}

/* ************************************************* */

void print() {
  struct Node *temp_node = head;
  if (!head) {
    std::cout << "List is empty!\n" << std::endl;
  } else {
    while (temp_node) {
      printf("%d,%s\n", temp_node->reg.nmec, temp_node->reg.name);
      temp_node = temp_node->next;
    }
  }
}

/* ************************************************* */

void insert(uint32_t nmec, const char *name) {
  struct Node *temp_n = (struct Node *)malloc(sizeof(struct Node));
  temp_n->reg.name = strdup(name);
  temp_n->reg.nmec = nmec;

  struct Node *p1;
  p1 = head;
  do {
    if (!head) {
      head = temp_n;
      head->next = NULL;
      break;
    } else {
      if (temp_n->reg.name < p1->reg.name) {
        temp_n->next = p1;
        p1 = temp_n;
        break;
      } else if (p1->next == NULL) {
        p1->next = temp_n;
        temp_n->next = NULL;
        break;
      } else if (temp_n->reg.nmec < (p1->next)->reg.nmec) {
        temp_n->next = p1->next;
        p1->next = temp_n;
        break;
      }
      p1 = p1->next;
    }
  } while (p1);
}

/* ************************************************* */

const char *query(uint32_t nmec) {
  struct Node *p1 = head;
  while (p1) {
    if (p1->reg.nmec == nmec) {
      return p1->reg.name;
    }
    p1 = p1->next;
  }
  return NULL;
}

/* ************************************************* */

void remove(uint32_t nmec) {
  struct Node *current, *previous;
  current = head;
  previous = NULL;
  while (current) {
    if (current->reg.nmec == nmec) {
      previous->next = current->next;
      free(current);
    }
    previous = current;
    current = current->next;
  }
}

/* ************************************************* */

} // namespace ull
