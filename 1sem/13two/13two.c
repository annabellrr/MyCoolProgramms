#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

const char path[] = "contacts.txt";

typedef struct date {
    int day;
    int month;
    int year;
}date;

typedef struct data {
    char phone[12];
    char name[255];
    char surname[255];
    date date;
}data;

typedef struct Contact {
    data data;
    struct Contact* next;
}Contact;

void addContact(Contact** head, data data) {
    Contact* new = malloc(sizeof(Contact));
    new->data = data;
    new->next = *head;
    *head = new;
}

int deleteById(Contact** head, int id) {
    Contact* tmp = *head;
    if (id <= 0)
        return -1;
    if (id == 1) {
        *head = (*head)->next;
        free(tmp);
        return 0;
    }
    for (int i = 1; i < (id - 1); i++) {
        if (tmp->next == NULL)
            return -1;
        tmp = tmp->next;
    }
    Contact* record_to_delete = tmp->next;
    tmp->next = tmp->next->next;
    free(record_to_delete);
    return 0;
}

void deleteList(Contact** head) {
    Contact* tmp_p;
    while (*head != NULL) {
        tmp_p = *head;
        *head = (*head)->next;
        free(tmp_p);
    }
    *head = NULL;
}

void swap(Contact* p1, Contact* p2) {
    data tmp = p1->data;
    p1->data = p2->data;
    p2->data = tmp;
}

int compareByName(char* name1, char* name2) {
    int i = 0;
    while (name1[i] != '\0') {
        if (name1[i] < name2[i]) {
            return 0;
        }
        if (name1[i] > name2[i]) {
            return 1;
        }
        i++;
    }
    return 0;
}

int compareByDate(date date1, date date2) {
    int res = 0;
    if (date1.year > date2.year)
        res = 1;
    else if (date1.year < date2.year)
        res = 0;
    else if (date1.month > date2.month)
        res = 1;
    else if (date1.month < date2.month)
        res = 0;
    else if (date1.day > date2.day)
        res = 1;
    else if (date1.day < date2.day)
        res = 0;
    return res;
}

int compare(data data1, data data2, int type) {
    if (type == 0)
        return compareByName(data1.name, data2.name);
    if (type == 1)
        return compareByName(data1.surname, data2.surname);
    if (type == 2)
        return compareByDate(data1.date, data2.date);
}

void sort(Contact* head, int type) {
    Contact* pointer_i = head;
    Contact* pointer_j;
    while (pointer_i->next != NULL) {
        pointer_j = head;
        while (pointer_j->next != NULL) {
            if (compare(pointer_j->data, pointer_j->next->data, type)) {
                swap(pointer_j, pointer_j->next);
            }
            pointer_j = pointer_j->next;
        }
        pointer_i = pointer_i->next;
    }
}

void loadFromFile(Contact** head) {
    data record;
    FILE* file = fopen("contacts.txt", "r");
    while (fscanf(file, "%s %s %s %d %d %d", \
        record.phone, record.name, record.surname, \
        & record.date.day, &record.date.month, &record.date.year) != EOF)
        addContact(head, record);

}

void printContacts(Contact** head)
{
    Contact* temp = *head;
    int i = 0;
    printf("%12s %12s %12s %2s %2s %4s %3s\n", "Phone", "Name", "Surname", \
        "D", "M", "Y", "Id");
    while (temp)
    {
        printf("%12s %12s %12s %2d %2d %4d %2d\n", temp->data.phone, temp->data.name, temp->data.surname, \
            temp->data.date.day, temp->data.date.month, temp->data.date.year, i + 1);
        temp = temp->next;
        i++;
    }
}

int saveToFile(Contact* head) {
    Contact* pointer = head;
    FILE* file = fopen("saved.txt", "w");
    while (pointer != NULL) {
        fprintf(file, "%s %s %s %d %d %d\n", pointer->data.phone, pointer->data.name, \
            pointer->data.surname, pointer->data.date.day, pointer->data.date.month, \
            pointer->data.date.year);
        pointer = pointer->next;
    }
    fclose(file);
}

void menu(Contact** head)
{
    int choice = 0;
    while (1) {
        printf("\nВыберите действие:\n");
        printf("1. Добавить контакт\n");
        printf("2. Удалить контакт\n");
        printf("3. Сортировать по имени\n");
        printf("4. Сортировать по фамилии\n");
        printf("5. Сортировать по дате рождения\n");
        printf("6. Вывести список на экран\n");
        printf("7. Сохранить в файл\n");
        printf("8. Загрузить из файла\n");
        printf("0. Выход\n");
        scanf("%d", &choice);
        switch (choice) {
        case 0:
            printf("good job, Mikhael Sergeevich ^_^\n");
            exit(0);
        case 1:
        {
            data data;
            printf("\t\tP.S. Вводите имя и фамилию на английском языке\n");
            printf("\nВведите имя: ");
            scanf("%s", data.name);
            printf("Введите фамилию: ");
            scanf("%s", data.surname);
            printf("Введите телефон: ");
            scanf("%s", data.phone);
            printf("Введите день DD: ");
            scanf("%d", &data.date.day);
            printf("Введите день MM: ");
            scanf("%d", &data.date.month);
            printf("Введите день YYYY: ");
            scanf("%d", &data.date.year);
            addContact(head, data);
            break;
        }
        case 2:
        {
            int id;
            printf("Введите ID: ");
            scanf("%d", &id);
            deleteById(head, id - 1);
            break;
        }
        case 3:
            sort(*head, 0);
            printContacts(head);
            break;
        case 4:
            sort(*head, 1);
            printContacts(head);
            break;
        case 5:
            sort(*head, 2);
            printContacts(head);
            break;
        case 6:
            printContacts(head);
            break;
        case 7:
            saveToFile(*head);
            break;
        case 8:
            loadFromFile(head);
            break;
        default:
            printf("Ошибка! Неправильный выбор.\n");
            exit(1);
        }
    }
}

int main()
{
    setlocale(LC_ALL, "Russian");
    Contact* list = NULL;
    menu(&list);
    deleteList(&list);
    return 0;
}
