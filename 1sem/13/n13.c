#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <windows.h>


// ����������� ������
typedef struct contact {
    char firstname[20];
    char lastname[20];
    char phone[15];
    char dob[11];
    struct contact* next;
} Contact;

Contact* head = NULL; // ������ ������

void free_list(Contact** head) {
    Contact* temp;
    while (*head != NULL) {
        temp = *head;
        *head = (*head)->next;
        free(temp);
    }
    *head = NULL;
}

// ������� ��� ���������� �������� � ������
void add_contact(char* firstname, char* lastname, char* phone, char* dob) {
    Contact* new_contact = (Contact*)malloc(sizeof(Contact)); // ��������� ������ ��� ������ ��������
    if (new_contact != 0)
    {
        strcpy(new_contact->firstname, firstname);
        strcpy(new_contact->lastname, lastname);
        strcpy(new_contact->phone, phone);
        strcpy(new_contact->dob, dob);
        new_contact->next = head;
        head = new_contact; // ����� ������� ���������� "�������" ������
    }
}

// ������� ��� �������� �������� �� ������
void remove_contact(char* firstname, char* lastname) {
    Contact* current = head;
    Contact* previous = NULL;
    while (current != NULL) {
        if (strcmp(current->firstname, firstname) == 0 && strcmp(current->lastname, lastname) == 0) {
            if (previous == NULL) { // ���� ������� ������ ������� ������
                head = current->next;
            }
            else { // ���� ������� �� ������ ������� ������
                previous->next = current->next;
            }
            free(current);
            printf("������� %s %s ������� ������ �� �������� ������\n", firstname, lastname);
            return;
        }
        previous = current;
        current = current->next;
    }
    printf("������� %s %s �� ������ � �������� ������\n", firstname, lastname);
}

// ������� ��� ��������� �����
int compare_strings(const char* str1, const char* str2) {
    return strcoll(str1, str2);
}

void swap(Contact* prev, Contact* current) {
    Contact* next = current->next;
    current->next = next->next;
    next->next = current;
    if (prev == NULL) { // ������ ������� ������
        head = next;
    }
    else {
        prev->next = next;
    }
}

//��� �����
int compare_contacts(const Contact* contact1, const Contact* contact2) {
    return strcmp(contact1->firstname, contact2->firstname);
}

// ������� ��� ���������� ������
void sort_contacts(int field) {
    int comparator = -1;
    int swapped = 1;
    int iterations = 0;
    Contact* prev = NULL;

    while (swapped && iterations < 100) { //����������� �� ������������ ���-�� ��������
        swapped = 0;
        Contact* current = head;
        while (current->next != NULL) {
            switch (field)
            {
            case 1:
                comparator = compare_contacts(current->firstname, current->next->firstname);
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
                if (prev != 0)
                {
                    swap(prev, current);
                    swapped = 1;
                    current = prev->next;
                }
            }
            else
            {
                prev = current;
                current = current->next;
            }
        }
        iterations++;
    }
    printf("�������� ������ ������� �������������\n");
}


// ������� ��� ������ ������ �� �����
void print_contacts() {
    printf("---------------------------------------------------------------------------------\n");
    printf("���\t\t|  �������\t\t\t|  �������\t\t|  ���� ��������\n");
    printf("---------------------------------------------------------------------------------\n");
    for (Contact* current = head; current != NULL; current = current->next) {
        printf("%s\t\t|  %s\t\t\t|  %s\t\t|  %s\n", current->firstname, current->lastname, current->phone, current->dob);
    }
    printf("---------------------------------------------------------------------------------\n");
}

// ������� ��� ���������� ������ � ����
void save_contacts() {
    FILE* f = fopen("yourContacts.txt", "w");
    if (f == NULL) {
        printf("������ ��� �������� �����\n");
        return;
    }
    for (Contact* current = head; current != NULL; current = current->next) {
        fprintf(f, "%s %s %s %s\n", current->firstname, current->lastname, current->phone, current->dob);
    }
    printf("�������� ������ ������� ��������� � ����\n");
    fclose(f);
}

// ������� ��� �������� ������ �� �����
void load_contacts() {
    FILE* f = fopen("contacts.txt", "r");
    if (f == NULL) {
        printf("������ ��� �������� �����\n");
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
    printf("�������� ������ ������� ��������� �� �����\n");
    fclose(f);
}

// ������� ��� ������ � ���������������� ����
void menu() {
    int choice = 0;
    while (1) {
        printf("\n�������� ��������:\n");
        printf("1. �������� �������\n");
        printf("2. ������� �������\n");
        printf("3. ����������� �� �����\n");
        printf("4. ����������� �� �������\n");
        printf("5. ����������� �� ��������\n");
        printf("6. ����������� �� ��� ��������\n");
        printf("7. ������� ������ �� �����\n");
        printf("8. ��������� � ����\n");
        printf("9. ��������� �� �����\n");
        printf("0. �����\n");
        scanf("%d", &choice);
        char firstname[50], lastname[50], phone[15], dob[11];
        switch (choice) {
        case 0:
            printf("good job, Mikhael Sergeevich ^_^\n");
            exit(0);
        case 1:
            printf("\t\tP.S. ������� ��� � ������� �� ���������� �����\n");
            printf("\n������� ���: ");
            scanf("%s", firstname);
            printf("������� �������: ");
            scanf("%s", lastname);
            printf("������� �������: ");
            scanf("%s", phone);
            printf("������� ���� �������� (� ������� DD.MM.YYYY): ");
            scanf("%s", dob);
            add_contact(firstname, lastname, phone, dob);
            break;
        case 2:
            printf("������� ���: ");
            scanf("%s", firstname);
            printf("������� �������: ");
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
            printf("������! ������������ �����.\n");
            exit(1);
        }
    }
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Russian");
    menu();
    return 0;
}
