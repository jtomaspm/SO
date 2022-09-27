/*
 *
 * \author (2016) Artur Pereira <artur at ua.pt>
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <stdint.h>

#include "ull.h"

namespace ull
{
  /* ************************************************* */

  /* The information support data structure  */
  struct Register
  {
    uint32_t nmec;       //!< student number
    const char *name;    //!< student name
  };

  /* The linked-list support data structure */
  struct Node 
  {
    Register reg;
    struct Node *next;
  };

  static Node *head = NULL;

  /* ************************************************* */

  void reset()
  {
    head = NULL;
  }

  /* ************************************************* */

  void load(const char *fname)
  {
    FILE *fp = fopen(fname, "r");
    if(fp == NULL){
      perror("Can't open file!");
    }
    else{
      char *line = NULL;
      size_t len = 0;
      while(getline(&line, &len, fp) != -1){
        uint32_t nmec;
        char name[50];
        sscanf(line, "%[^;];%u[^\n]", &name[0], &nmec);
        insert(nmec, name);
      }
      free(line);
      fclose(fp);
      print();
    }

  }

  /* ************************************************* */

  void print()
  {
    struct Node *node_pointer = head;
    if(!node_pointer){
      printf("Empty List...");
    }
    else {
      while(node_pointer){
        printf("nmec: %d, nome: %s\n", node_pointer->reg.nmec, node_pointer->reg.name);
        node_pointer = node_pointer->next;
      }
    }
  }

  /* ************************************************* */

  void insert(uint32_t nmec, const char *name)
  {
    struct Node *temp_n = (struct Node *)malloc(sizeof(struct Node));
    temp_n->reg.name = name;
    temp_n->reg.nmec = nmec;

    struct Node *p1;
    p1 = head;
    do
    {
      if (head == NULL)
      {
        head = temp_n;
        head->next = NULL;
        break;
      }
      else
      {
        if (temp_n->reg.nmec < p1->reg.nmec)
        {
          temp_n->next = p1;
          p1 = temp_n;
          break;
        }
        else if (p1->next == NULL)
        {
          p1->next = temp_n;
          temp_n->next = NULL;
          break;
        }
        else if (temp_n->reg.nmec < (p1->next)->reg.nmec)
        {
          temp_n->next = p1->next;
          p1->next = temp_n;
          break;
        }
        p1 = p1->next;
      }
    } while (p1 != NULL);
  }

  /* ************************************************* */

  const char *query(uint32_t nmec)
  {
    struct Node *p1;
    p1 = head;
    while(p1 != NULL){
      if(p1->reg.nmec==nmec)
        return p1->reg.name;
      p1 = p1->next;
    }
    return NULL;
  }

  /* ************************************************* */

  void remove(uint32_t nmec)
  {
    struct Node *p1, *p2;
    p1 = head;
    p2 = NULL;
    while (p1 != NULL)
    {
      if (p1->reg.nmec == nmec){
        p2->next = p1->next;
        free(p1);
      }
      p2 = p1;
      p1 = p1->next;
    }
  }

  /* ************************************************* */

}
