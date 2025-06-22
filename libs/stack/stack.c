#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "stack.h"
stack *head = NULL, *tail = NULL;
stack *create_node(char *p_data, int *p_quantity)
{
   stack *p = (stack *)malloc(sizeof(stack));
   if (p == NULL)
   {
      puts("Ошибка выделения памяти.");
      exit(1);
   }
   p->symbol = *p_data;
   p->count = *p_quantity;
   p->next = NULL;
   p->prev = NULL;
   return p;
}
bool isEmpty()
{
   return head == NULL && tail == NULL ? true : false;
}
bool isOne()
{
   return head == tail ? true : false;
}
void push(char data, int quantity)
{
   stack *p = create_node(&data, &quantity);
   if (isEmpty())
   {
      head = p;
      tail = p;
   }
   else
   {
      tail->next = p;
      p->prev = tail;
      tail = p;
   }
   return;
}
void pop()
{
   stack *p = NULL;
   if (isOne())
   {
      free(head);
      head = tail = NULL;
      return;
   }
   if (isEmpty())
   {
      puts("stack is empty.");
      return;
   }
   else
   {
      p = tail->prev;
      free(tail);
      tail = p;
      tail->next = NULL;
   }
   return;
}
void clear_stack()
{
   while (!isEmpty())
   {
      pop();
   }
   return;
}
void print_to_file(FILE *f)
{
   stack *p = head;
   int check = 0;
   while (p != NULL)
   {
      check = fprintf(f, "%d%c", p->count, p->symbol);
      p = p->next;
   }
   if (check == 0)
   {
      perror("Ошибка. Запись не произведена.");
      exit(1);
   }
}