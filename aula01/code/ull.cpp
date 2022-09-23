/*
 *
 * \author (2016) Artur Pereira <artur at ua.pt>
 */

#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
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

void reset() {}

/* ************************************************* */

void load(const char *fname) {}

/* ************************************************* */

void print() {
  Node temp_node;
  if (!head) {
    std::cout << "List is empty!\n";
  } else {
    temp_node = *head;
    while (temp_node.next) {
      std::cout << temp_node.reg.name;
      std::cout << "   ";
      std::cout << temp_node.reg.nmec;
      std::cout << "\n" << std::endl;
    }
  }
}

/* ************************************************* */

void insert(uint32_t nmec, const char *name) {
  // allocate register
  struct Register *new_register =
      (struct Register *)malloc(sizeof(struct Register));

  // allocate node
  struct Node *new_node = (struct Node *)malloc(sizeof(struct Node));

  // allocate Data
  new_register->name = name;
  new_register->nmec = nmec;
  new_node->reg = *new_register;

  if (head) {
    head->next = new_node;
  }
  head = new_node;
}

/* ************************************************* */

const char *query(uint32_t nmec) { return NULL; }

/* ************************************************* */

void remove(uint32_t nmec) {}

/* ************************************************* */

} // namespace ull
