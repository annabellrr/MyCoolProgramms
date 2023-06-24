#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define BUFF_SIZE 255

void insert_symb(char text[], int pos, char symb[])
{
    char buffer[BUFF_SIZE] = {};
    
    strncpy(buffer, text, pos);
    int len = strlen(buffer);
    
    strcpy(buffer + len, symb);
    len += strlen(symb);
    
    strcpy(buffer+len, text+pos);

    strcpy(text, buffer); 
}

void delete_symb(char text[], int idx)
{
    memcpy(&text[idx], &text[idx + 1], strlen(text) - idx);
}

void replace_symb(char text[], int idx, char symb[])
{
    delete_symb(text, idx);
    insert_symb(text, idx, symb);
}

void correct_string(char text[])
{
    // удаляем лишние пробемы
    int i, x;
    for(i = x = 0; text[i] != '\0'; ++i)
        if(!isspace(text[i])  (i > 0 && !isspace(text[i-1])))
            text[x++] = text[i];
    text[x] = '\0';
    
    // правим первую букву в предложении
    if(islower(text[0]))
    {
        text[0] = toupper(text[0]);
    }
    
    // Начало предложений с большой буквы
    for(int j = 0; j < strlen(text) - 1; j++)
    {
        if(text[j] == '.'  text[j] == '!'  text[j] == '?')
        {
            if(text[j] == '\0')
            {
                break;
            }
            if(islower(text[j + 1]))
            {
                text[j+1] = toupper(text[j+1]);
            }
            if(isspace(text[j + 1]) && islower(text[j + 2]))
            {
                text[j+2] = toupper(text[j+2]);
            }
        }
    }
    
    // Вставляем упущенные пробелы
    for(int j = 0; j < strlen(text) - 1; j++)
    {
        if(text[j] == '.'  text[j] == '!'  text[j] == '?'  text[j] == ',')
        {
            if(text[j] == '\0')
            {
                break;
            }
            if(!isspace(text[j + 1]))
            {
                insert_symb(text, j+1, " ");
            }
        }
    }
}

int main()
{
    
    printf("This program can correct the text according to the canon.");
    printf("\nPlease enter invalid text:\n");

    char text[BUFF_SIZE];
    
    fgets(text, sizeof(text), stdin);
    
    // test:
    //     hello.My name is Anna.what is you name? Great,how are you!
    correct_string(text);
    
    
    printf("%s", text);
    return 0;
}