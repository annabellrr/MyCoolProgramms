#include <stdio.h>
#include <stdlib.h>

#define STRING_SIZE 255

typedef struct fields {
 char name[STRING_SIZE];
 char lastname[STRING_SIZE];
 int phone;
}fields;

struct llist;

typedef struct llist {
 fields field;
 struct llist *next;
}llist;

void init_list(llist **list) {
 *list = NULL;
}

void enter_element(llist **list) {
 llist *temp = (llist *)malloc(sizeof(llist));
 printf("name: ");
 scanf("%s", temp->field.name);
 printf("lastname: ");
 scanf("%s", temp->field.lastname);
 printf("phone: ");
 scanf("%d", &(temp->field.phone));
 printf("\n");
 temp->next = *list;
 *list = temp;
}

void add_element(llist **list, fields new_data) {
 llist *temp = (llist *)malloc(sizeof(llist));
 temp->field = new_data;
 temp->next = *list;
 *list = temp;
}

void insert_element(llist **list, fields new_data, int num) {
 llist *temp = (llist *)malloc(sizeof(llist));
 temp->field = (*list)->field;
 temp->next = *list;

 for (int i = 0; i < num; ++i) {
  (*list)->field = (*list)->next->field;
  (*list) = &((*list)->next);
 }

 (*list)->field = new_data;
}

void print_list(llist *list) {
 printf("list: \nname, lastname, phone:\n");
 while (list != NULL) {
  printf("%s %s %d\n", list->field.name, list->field.lastname, list->field.phone);
  list = list->next;
 };
}

void delete_list(llist *list) {
 llist *next = list;
 while ( next != NULL) {
  list = list->next;
  free(next);
  next = list;
 }
}

int main()
{
    llist* phoneList = NULL;
    init_list(&phoneList);
    
    int n;
    printf("Введите количество элементов тел.книги: ");
    scanf("%d", &n);
    
    for(int i = 0; i < n; i++)
    {
        enter_element(&phoneList);
    }
    print_list(phoneList);
    
    delete_list(phoneList);
    return 0;
}