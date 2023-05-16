#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

char* GetText(FILE* stream, char terminator)
{
    int size = 0;
    int capacity = 1024; // начальный размер буфера
    char* buffer = malloc(capacity);
    if (buffer == NULL) {
        perror("Ошибка выделения памяти");
        exit(EXIT_FAILURE);
    }
    int c;
    while ((c = getc(stream)) != EOF && c != terminator) {
        buffer[size++] = c;
        if (size == capacity) { // перевыделение памяти при необходимости
            capacity *= 2;
            char* tmp = realloc(buffer, capacity);
            if (tmp == NULL) {
                perror("Ошибка перевыделения памяти");
                exit(EXIT_FAILURE);
            }
            buffer = tmp;
        }
    }
    buffer = realloc(buffer, size + 1); // перевыделение памяти под нуль-терминатор
    if (buffer == NULL) {
        perror("Ошибка перевыделения памяти");
        exit(EXIT_FAILURE);
    }
    buffer[size] = '\0'; // добавление нуль-терминатора
    return buffer;
}

int main()
{
    setlocale(LC_ALL, "Russian");
    char terminator = '#';
    char* text;

    printf("Введите 'c' для ввода текста из консоли, 'f' для ввода из файла: ");
    int input_type = getchar();

    if (input_type == 'c') {
        printf("Введите текст (введите символ '#' для окончания ввода):\n");
        text = GetText(stdin, terminator);
    }
    else if (input_type == 'f') {
        printf("Введите имя файла: ");
        char filename[256];
        scanf_s("%255s", filename);
        FILE* file = fopen_s(filename, "r");
        if (file == NULL) {
            perror("Ошибка открытия файла");
            exit(EXIT_FAILURE);
        }
        text = GetText(file, terminator);
        fclose(file);
    }
    else {
        printf("Неверный ввод\n");
        exit(EXIT_FAILURE);
    }

    printf("Введенный текст: \n%s\n", text);
    free(text);
    return 0;
}