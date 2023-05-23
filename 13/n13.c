#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

// Односвязный список
typedef struct contact {
    char firstname[20];
    char lastname[20];
    char phone[15];
    char dob[11];
    struct contact* next;
} Contact;

Contact* head = NULL; // Голова списка

void free_list(Contact** head) {
    Contact* temp;
    while (*head != NULL) {
        temp = *head;
        *head = (*head)->next;
        free(temp);
    }
    *head = NULL;
}

// Функция для добавления элемента в список
void add_contact(char* firstname, char* lastname, char* phone, char* dob) {
    Contact* new_contact = (Contact*)malloc(sizeof(Contact)); // Выделение памяти для нового элемента
    strcpy(new_contact->firstname, firstname);
    strcpy(new_contact->lastname, lastname);
    strcpy(new_contact->phone, phone);
    strcpy(new_contact->dob, dob);
    new_contact->next = head;
    head = new_contact; // Новый элемент становится "головой" списка
}

// Функция для удаления элемента из списка
void remove_contact(char* firstname, char* lastname) {
    Contact* current = head;
    Contact* previous = NULL;
    while (current != NULL) {
        if (strcmp(current->firstname, firstname) == 0 && strcmp(current->lastname, lastname) == 0) {
            if (previous == NULL) { // Если удаляем первый элемент списка
                head = current->next;
            }
            else { // Если удаляем не первый элемент списка
                previous->next = current->next;
            }
            free(current);
            printf("Контакт %s %s успешно удален из записной книжки\n", firstname, lastname);
            return;
        }
        previous = current;
        current = current->next;
    }
    printf("Контакт %s %s не найден в записной книжке\n", firstname, lastname);
}

// Функция для сравнения строк
int compare_strings(char* str1, char* str2) {
    // Для удобства сравнения, переводим строки в верхний регистр
    for (int i = 0; str1[i]; i++) {
        str1[i] = toupper(str1[i]);
    }
    for (int i = 0; str2[i]; i++) {
        str2[i] = toupper(str2[i]);
    }
    return strcmp(str1, str2); // Функция strcmp() используется для сравнения строк
}

/// Функция для сортировки списка
void sort_contacts(int field) {
    Contact* current = head;
    Contact* prev = NULL;
    Contact* next = current->next;
    int swapped = 1;
    int iterations = 0;
    while (swapped && iterations < 100) { //ограничение на максимальное кол-во итераций
        swapped = 0;
        current = head;
        while (current->next != NULL) {
            int comparator;
            switch (field)
            {
            case 1:
                comparator = compare_strings(current->firstname, current->next->firstname);
                break;
            case 2:
                comparator = compare_strings(current->lastname, current->next->lastname);
                break;
            case 3:
                comparator = compare_strings(current->phone, current->next->phone);
                break;
            case 4:
                comparator = compare_strings(current->dob, current->next->dob);
                break;
            }
            if (comparator > 0)
            {
                next = current->next;
                current->next = next->next;
                next->next = current;
                if (prev == NULL) { // Первый элемент списка
                    head = next;
                }
                else {
                    prev->next = next;
                }
                prev = next;
                swapped = 1;
            }
            else
            {
                prev = current;
                current = current->next;
            }
        }
        printf("Записная книжка успешно отсортирована\n");
    }
}

// Функция для вывода списка на экран
void print_contacts() {
    printf("---------------------------------------------------------------------------------\n");
    printf("Имя\t\t|  Фамилия\t\t|  Телефон\t\t|  Дата рождения\n");
    printf("---------------------------------------------------------------------------------\n");
    for (Contact* current = head; current != NULL; current = current->next) {
        printf("%s\t\t|  %s\t\t\t|  %s\t\t|  %s\n", current->firstname, current->lastname, current->phone, current->dob);
    }
    printf("---------------------------------------------------------------------------------\n");
}

// Функция для сохранения списка в файл
void save_contacts() {
    FILE* f = fopen("yourContacts.txt", "w");
    if (f == NULL) {
        printf("Ошибка при открытии файла\n");
        return;
    }
    for (Contact* current = head; current != NULL; current = current->next) {
        fprintf(f, "%s %s %s %s\n", current->firstname, current->lastname, current->phone, current->dob);
    }
    printf("Записная книжка успешно сохранена в файл\n");
    fclose(f);
}

// Функция для загрузки списка из файла
void load_contacts() {
    FILE* f = fopen("contacts.txt", "r");
    if (f == NULL) {
        printf("Ошибка при открытии файла\n");
        return;
    }
    char buf[60];
    while (fgets(buf, 60, f)) {
        char* firstname = strtok(buf, " ");
        char* lastname = strtok(NULL, " ");
        char* phone = strtok(NULL, " ");
        char* dob = strtok(NULL, "\n");
        add_contact(firstname, lastname, phone, dob);
    }
    printf("Записная книжка успешно загружена из файла\n");
    fclose(f);
}

// Функция для работы с пользовательским меню
void menu() {
    int choice = 0;
    while (1) {
        printf("\nВыберите действие:\n");
        printf("1. Добавить контакт\n");
        printf("2. Удалить контакт\n");
        printf("3. Сортировать по имени\n");
        printf("4. Сортировать по фамилии\n");
        printf("5. Сортировать по телефону\n");
        printf("6. Сортировать по дате рождения\n");
        printf("7. Вывести список на экран\n");
        printf("8. Сохранить в файл\n");
        printf("9. Загрузить из файла\n");
        printf("0. Выход\n");
        scanf("%d", &choice);
        char firstname[20], lastname[20], phone[15], dob[11];
        switch (choice) {
        case 0:
            printf("good job, Mikhael Sergeevich ^_^\n");
            exit(0);
        case 1:
            printf("\t\tP.S. Вводите имя и фамилию на английском языке\n");
            printf("\nВведите имя: ");
            scanf("%s", firstname);
            printf("Введите фамилию: ");
            scanf("%s", lastname);
            printf("Введите телефон: ");
            scanf("%s", phone);
            printf("Введите дату рождения (в формате DD.MM.YYYY): ");
            scanf("%s", dob);
            add_contact(firstname, lastname, phone, dob);
            break;
        case 2:
            printf("Введите имя: ");
            scanf("%s", firstname);
            printf("Введите фамилию: ");
            scanf("%s", lastname);
            remove_contact(firstname, lastname);
            break;
        case 3:
            sort_contacts(1);
            break;
        case 4:
            sort_contacts(2);
            break;
        case 5:
            sort_contacts(3);
            break;
        case 6:
            sort_contacts(4);
            break;
        case 7:
            print_contacts();
            break;
        case 8:
            save_contacts();
            break;
        case 9:
            load_contacts();
            break;
        default:
            printf("Ошибка! Неправильный выбор.\n");
            exit(1);
        }
    }
}

int main() {
    system("chcp 1251 > nul");
    setlocale(LC_ALL, "Russian");
    menu();
    return 0;
}
