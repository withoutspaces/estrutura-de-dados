#include <stdio.h>
#include <stdlib.h>
#define MAX 10

int count = 0;

struct stack
{
  int items[MAX];
  int top;
};

typedef struct stack st;

void clear_screen()
{
  system("clear");
}

// criar nova pilha
void create_empty_stack(st *s)
{
  s->top = -1;
}

// isEmpty
int is_empty(st *s)
{
  if (s->top == -1)
    return 1;
  else
    return 0;
}

// isFull
int is_full(st *s)
{
  if (s->top == MAX - 1)
    return 1;
  else
    return 0;
}
// peek
// pop
void pop(st *s)
{
  if (is_empty(s))
    printf("STACK EMPTY\n");
  else
  {
    printf("Item popped = %d", s->items[s->top]);
    s->top--;
  }
  count--;
  printf("\n");
}
// push
void push(st *s, int new_element)
{
  if (is_full(s))
  {
    printf("STACK FULL\n");
    return;
  }
  else
  {
    s->top++;
    s->items[s->top] = new_element;
  }
  count++;
}

void print_stack(st *s)
{
  if (is_empty(s))
    return;

  for (int i = count - 1; i >= 0; i--)
  {
    printf("| ");
    printf("%d", s->items[i]);
    printf(" |\n");
  }
  printf("\n");
}

void menu(st *s)
{
  print_stack(s);
  printf(" [1] Inserir na pilha\n [2]Remover da pilha\n [3]Encerrar\n");
  printf("Digite a opcao: ");
  return;
}

int main()
{
  int choice = 1, new_element;
  st *s = (st *)malloc(sizeof(st));

  create_empty_stack(s);

  while (choice != 3)
  {
    menu(s);
    scanf("%d", &choice);
    switch (choice)
    {
    case 1:
      printf("\nDigite o valor: ");
      scanf("%d", &new_element);
      push(s, new_element);
      break;
    case 2:
      pop(s);
      break;
    case 3:
      return 0;
    default:
      break;
    }
    clear_screen();
  }
}
