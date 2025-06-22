typedef struct stack
{
   char symbol;
   int count;
   struct stack *next;
   struct stack *prev;
} stack;
stack *create_node(char* data, int* count);
void push(char symbol, int count);
void pop();
void clear_stack();