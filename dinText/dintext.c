#include <stdio.h>
#include <malloc.h>

typedef struct text_type
{
	int size;
	char* p;
	int end;

}text_type;


//чтение из файла, выделение памяти
text_type textReadStep(FILE* stream, text_type text, int buffer_s, char terminator)
{
	text_type newtext;
	newtext.end = 0;
	newtext.size = 0;
	char* pbuffer;
	int stopind = buffer_s - 1;
	pbuffer = malloc(sizeof(char) * (buffer_s + 1));
	if (pbuffer == NULL)
	{
		printf("textReadStep: No memory available!");
		return text;
	}

	fgets(pbuffer, buffer_s + 1, stream);
	for (int i = 0; i < buffer_s; i++)
	{
		if (*(pbuffer + i) == '\n')
		{
			stopind = i;
			break;
		}
		if (*(pbuffer + i) == terminator)
		{
			stopind = i;
			newtext.end = 1;
			break;
		}
	}

	newtext.size = text.size + stopind + 1;
	newtext.p = malloc(sizeof(char) * newtext.size);
	if (newtext.p == NULL)
	{
		printf("textReadStep: No memory available!");
		return text;
	}

	for (int i = 0; i < text.size; i++)
		*(newtext.p + i) = *(text.p + i);
	if (text.size != 0)
		free(text.p);
	for (int i = text.size; i < newtext.size; i++)
		*(newtext.p + i) = *(pbuffer + i - text.size);
	free(pbuffer);
	return newtext;
}


//чтение текста
text_type getText(FILE* stream, char terminator, int buffer_s)
{
	text_type text;
	text.size = 0;

	while (1)
	{
		text = textReadStep(stream, text, buffer_s, terminator);
		if (text.end == 1)
		{
			*(text.p + text.size - 1) = '\0';
			if (stream != stdin)
				fclose(stream);
			return text;
		}
	}

}


//изменение размера текста
int correctSize(text_type text)
{
	int sizeDelta = 0, i0 = 0;
	for (int i = 0; (*(text.p + i) == ' ') || (*(text.p + i) == '\n'); i++)
	{
		sizeDelta--;
		i0 = i;
	}

	for (int i = i0 + 1; i < text.size - 1; i++)
	{
		if (*(text.p + i) == ' ')
		{
			if ((*(text.p + i + 1) == ' ') ||
				(*(text.p + i + 1) == '.') ||
				(*(text.p + i + 1) == ',') ||
				(*(text.p + i + 1) == '!') ||
				(*(text.p + i + 1) == '?') ||
				(*(text.p + i + 1) == '\0'))
				sizeDelta--;
		}
		if ((*(text.p + i) == '.') ||
			(*(text.p + i) == ',') ||
			(*(text.p + i) == '!') ||
			(*(text.p + i) == '?'))
			if ((*(text.p + i + 1) != '.') &&
				(*(text.p + i + 1) != ',') &&
				(*(text.p + i + 1) != '!') &&
				(*(text.p + i + 1) != '?') &&
				(*(text.p + i + 1) != ' ') &&
				(*(text.p + i + 1) != '\0'))
				sizeDelta++;
	}
	return sizeDelta;
}

//первая заглавная буква
int symFirst(text_type text, text_type newtext)
{
	int i0 = 0;
	for (int i = 0; i < text.size - 1; i++)
		if ((*(text.p + i) != ' ') &&
			(*(text.p + i) != '\n'))
		{
			i0 = i;
			if ((*(text.p + i) >= 97) && (*(text.p + i) <= 122))
				*newtext.p = *(text.p + i) - 32;
			else
				*newtext.p = *(text.p + i);
			break;
		}
	return i0;
}


//проверяет пробелы
int symSpace(text_type text, text_type newtext, int i, int pos)
{
	if (*(text.p + i) == ' ')
	{
		if ((*(text.p + i + 1) != '.') &&
			(*(text.p + i + 1) != ',') &&
			(*(text.p + i + 1) != '!') &&
			(*(text.p + i + 1) != '?') &&
			(*(text.p + i + 1) != ' ') &&
			(*(text.p + i + 1) != '\0'))
		{
			*(newtext.p + pos) = ' ';
			return pos + 1;
		}
	}
	return pos;
}


//проверка знаков препинания
int symPunct(text_type text, text_type newtext, int i, int pos)
{
	if ((*(text.p + i) == ',') ||
		(*(text.p + i) == '.') ||
		(*(text.p + i) == '!') ||
		(*(text.p + i) == '?'))
	{
		*(newtext.p + pos) = *(text.p + i);
		if ((*(text.p + i + 1) != '.') &&
			(*(text.p + i + 1) != ',') &&
			(*(text.p + i + 1) != '!') &&
			(*(text.p + i + 1) != '?') &&
			(*(text.p + i + 1) != ' ') &&
			(*(text.p + i + 1) != '\0'))
		{
			*(newtext.p + pos + 1) = ' ';
			return pos + 2;
		}
		return pos + 1;
	}
	return pos;
}


//регистр
int symLetter(text_type text, text_type newtext, int i, int pos)
{
	if ((*(text.p + i) != '.') &&
		(*(text.p + i) != ',') &&
		(*(text.p + i) != '!') &&
		(*(text.p + i) != '?') &&
		(*(text.p + i) != ' '))
	{
		*(newtext.p + pos) = *(text.p + i);
		if ((*(newtext.p + pos) >= 65) && (*(newtext.p + pos) <= 90))
			*(newtext.p + pos) += 32;
		if ((*(newtext.p + pos) >= 97) && (*(newtext.p + pos) <= 122))
		{
			if (*(newtext.p + pos - 1) == ' ')
				if ((*(newtext.p + pos - 2) == '.') ||
					(*(newtext.p + pos - 2) == '!') ||
					(*(newtext.p + pos - 2) == '?'))
					*(newtext.p + pos) -= 32;
			if (*(newtext.p + pos - 1) == '\n')
				*(newtext.p + pos) -= 32;
		}
		return pos + 1;
	}
	return pos;
}

//возвращает коррект текст
text_type textCorrect(text_type text)
{
	int i0, pos;
	text_type newtext;
	newtext.size = text.size + correctSize(text);
	newtext.p = malloc(sizeof(char) * newtext.size);
	if (newtext.p == NULL)
	{
		printf("textCorrect: No memory available! Can't correct text");
		return text;
	}
	*(newtext.p + newtext.size - 1) = '\0';
	i0 = symFirst(text, newtext);
	pos = 1;
	for (int i = i0 + 1; i < text.size - 1; i++)
	{
		pos = symSpace(text, newtext, i, pos);
		pos = symPunct(text, newtext, i, pos);
		pos = symLetter(text, newtext, i, pos);
	}
	return newtext;
}

FILE* streamInit()
{
	int stream_type;
	FILE* stream = stdin;
	char* fname[255];
	char trash;
	printf("Input stream type:\n");
	printf("0 - stdin (default)\n");
	printf("1 - file (input.txt)\n");
	scanf_s("%d", &stream_type);
	trash = getchar();
	if (stream_type == 1)
	{
		if ((fopen_s(&stream, "input.txt", "r")) != 0)
		{
			printf("File open error\n");
			return 0;
		}
	}
	return stream;
}

void textPrint(char* text, FILE* stream)
{
	FILE* output;
	if (stream == stdin)
	{
		printf("Corrected text:\n");
		printf("%s\n", text);
	}
	else
	{
		if ((fopen_s(&output, "output.txt", "w")) != 0)
		{
			printf("File open error\n");
			return 0;
		}
		printf("Text in output.txt\n");
		fprintf(output, "%s\n", text);
		fclose(output);
	}
}

void main()
{
	text_type text, newtext;
	char terminator = '#', trash, * terms[10];
	int buffer_s;
	FILE* stream = stdin, output;
	stream = streamInit();
	printf("Input terminator:\n");
	fgets(terms, 10, stdin);
	for (int i = 0; terms[i] != '\0'; i++)
		if ((terms[i] != ' ') &&
			(terms[i] != '\n'))
		{
			terminator = terms[i];
			break;
		}
	printf("Input buffer size:\n");
	scanf_s("%d", &buffer_s);
	if (stream == stdin)
		printf("Input text:\n");
	trash = getchar();
	text = getText(stream, terminator, buffer_s);
	newtext = textCorrect(text);
	textPrint(newtext.p, stream);
	free(text.p);
	free(newtext.p);
	return 0;
}