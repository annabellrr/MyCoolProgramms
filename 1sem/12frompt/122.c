#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

char* GetText(FILE* stream, char terminator)
{
    int size = 0;
    int capacity = 1024; // ��������� ������ ������
    char* buffer = malloc(capacity);
    if (buffer == NULL) {
        perror("������ ��������� ������");
        exit(EXIT_FAILURE);
    }
    int c;
    while ((c = getc(stream)) != EOF && c != terminator) {
        buffer[size++] = c;
        if (size == capacity) { // ������������� ������ ��� �������������
            capacity *= 2;
            char* tmp = realloc(buffer, capacity);
            if (tmp == NULL) {
                perror("������ ������������� ������");
                exit(EXIT_FAILURE);
            }
            buffer = tmp;
        }
    }
    buffer = realloc(buffer, size + 1); // ������������� ������ ��� ����-����������
    if (buffer == NULL) {
        perror("������ ������������� ������");
        exit(EXIT_FAILURE);
    }
    buffer[size] = '\0'; // ���������� ����-�����������
    return buffer;
}

int main()
{
    setlocale(LC_ALL, "Russian");
    char terminator = '#';
    char* text;

    printf("������� 'c' ��� ����� ������ �� �������, 'f' ��� ����� �� �����: ");
    int input_type = getchar();

    if (input_type == 'c') {
        printf("������� ����� (������� ������ '#' ��� ��������� �����):\n");
        text = GetText(stdin, terminator);
    }
    else if (input_type == 'f') {
        printf("������� ��� �����: ");
        char filename[256];
        scanf_s("%255s", filename);
        FILE* file = fopen_s(filename, "r");
        if (file == NULL) {
            perror("������ �������� �����");
            exit(EXIT_FAILURE);
        }
        text = GetText(file, terminator);
        fclose(file);
    }
    else {
        printf("�������� ����\n");
        exit(EXIT_FAILURE);
    }

    printf("��������� �����: \n%s\n", text);
    free(text);
    return 0;
}