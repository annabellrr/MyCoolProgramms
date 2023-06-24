#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>

//в этой игрушке должна стоять англ раскладка
//для передвижения используйте "WASD", для выхода - "e or q"

int main()
{
	char mas[12][26];
	int i;
	int x = 10, y = 5;
	char key;
	int ox, oy;
	int ax = 6, ay = 4;
	srand(time(NULL));

	do
	{
		sprintf_s(mas[0], "####################");
		for (i = 1; i < 11; i++)
			sprintf_s(mas[i], "#                  #");
		sprintf_s(mas[11], "####################");

		mas[y][x] = '@';
		mas[ay][ax] = '*';

		system("cls");
		for (i = 0; i < 12; i++)
			printf("%s\n", mas[i]);

		key = _getch();

		ox = x;
		oy = y;
		if (key == 'q')
			break;
		if (key == 'w') y--;
		if (key == 's') y++;
		if (key == 'a') x--;
		if (key == 'd') x++;
		if (mas[y][x] == '#')
		{
			printf("\n\n\t\t\t\tGAME OVER, Mikhael Sergeevich! \the-he ^_^\n\n");
			break;
		}

		if ((x == ax) && (y == ay))
		{
			ax = rand() * 1.0 / RAND_MAX * 22 + 1;
			ay = rand() * 1.0 / RAND_MAX * 8 + 1;
		}

	} while (key != 'e');

	return 0;

}