#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <locale.h>
#include <time.h>
#include <string.h>
#include <conio.h>
#include <stddef.h>
#include <stdlib.h>

int new_zapisi(zapis, chislo_zapis);
int pechat(zapis, chislo_zapis);
int vivod_poisk(zapis, chislo_zapis);
int poisk(zapis, chislo_zapis);
void poisk_sec(zapis, chislo_zapis);
void sohr(zapis, chislo_zapis);
int sortirovka(zapis, chislo_zapis);
void sohr(zapis, chislo_zapis);
int read(zapis, chislo_zapis);
void ShellSort(zapis, chislo_zapis);
void red(zapis, number, chislo_zapis);

struct database {
	int number;
	char tema[50];
	char FIO[50];
	int poradok;
	int min;
	int data[3];
};
typedef struct database kp;

int main() {
	setlocale(LC_ALL, "rus");
	system("chcp 1251");
	int g = 1, z;
	FILE* out;
	int chislo_zapis = 0;
	kp* zapis = NULL;


	printf("Выберите пункт\n");
	while (g != 0) {
		printf("1)Добавить новую строку\n2)Вывод записей\n3)Поиск по критериям\n4)сортировка\n5)изменить запись\n0)выход\n");
		scanf("%d", &z);
		switch (z) {
		case 1:
			zapis = realloc(zapis, (chislo_zapis + 1) * sizeof(kp));

			chislo_zapis = new_zapisi(zapis, chislo_zapis);

			int o_f = 2;   /*Нужна для того, чтобы понять, для чего открыть файл(Для записи с начала или для дозаписования)*/
			sohr(zapis, chislo_zapis - 1, o_f);
			break;
		case 2:
			out = fopen("kp.txt", "r");

			int str = 0;
			while (!feof(out))
			{
				if (fgetc(out) == '\n')
					str++;
			}
			str = str / 4;
			zapis = (kp*)malloc(str * sizeof(kp));

			chislo_zapis = read(zapis, chislo_zapis);
			pechat(zapis, chislo_zapis);
			break;
		case 3:
		{
			int p;
			printf("Выберите поиск:\n1-по имени\n2-по номеру секции\n");
			scanf("%d", &p);
		
			if (p == 1)poisk(zapis, chislo_zapis);
			else if (p == 2); poisk_sec(zapis, chislo_zapis);

		break; 
		}
		case 4:
			chislo_zapis = read(zapis, chislo_zapis);
			ShellSort(zapis, chislo_zapis);
			break;
		case 5:
		{
			int number;

			printf("Введите номер записи, которую хотите изменить\n");
			scanf("%d", &number);
			getchar();
			number--;

			chislo_zapis = read(zapis, chislo_zapis);
			red(zapis, number, chislo_zapis);

			for (int i = 0; i < chislo_zapis; i++)
			{
				if (i == 0) sohr(zapis, i, 1);
				else sohr(zapis, i, 2);
			}
			break;
		}
		case 0:
			g = 0;
			break;
		}
	}
}
int new_zapisi(kp* zapis, int chislo_zapis) {
	printf("Дата научного доклада\n");
	scanf("%d.%d.%d", &zapis[chislo_zapis].data[0], &zapis[chislo_zapis].data[1], &zapis[chislo_zapis].data[2]);
	getchar();

	printf("# Секции\n");
	scanf("%d", &zapis[chislo_zapis].number);
	getchar();

	printf("тема доклада\n");
	fgets(zapis[chislo_zapis].tema, 50, stdin);

	printf("Фамилия Имя Отчество\n");
	fgets(zapis[chislo_zapis].FIO, 50, stdin);

	printf("Регламент в минутах\n");
	scanf("%d", &zapis[chislo_zapis].min);

	chislo_zapis++;
	return chislo_zapis;
}
int pechat(kp* zapis, int chislo_zapis) {
	for (int i = 0; i < chislo_zapis; i++) {
		printf("Дата научного доклада-%d.%d.%d\n# Секции %d\nтема доклада-%sФ.И.О-%sРегламент в минутах-%dmin\n\n", zapis[i].data[0], zapis[i].data[1], zapis[i].data[2], zapis[i].number, zapis[i].tema, zapis[i].FIO, zapis[i].min);
	}
}
int vivod_poisk(kp* zapis, int chislo_zapis) {
	printf("Дата научного доклада-%d.%d.%d\n#Секции %d\nтема доклада-%sФ.И.О-%sРегламент в минутах-%dmin\n\n", zapis[chislo_zapis].data[0], zapis[chislo_zapis].data[1], zapis[chislo_zapis].data[2], zapis[chislo_zapis].number, zapis[chislo_zapis].tema, zapis[chislo_zapis].FIO, zapis[chislo_zapis].min);
}

int poisk(kp* zapis, int chislo_zapis) {
	char name_poisk[50];
	printf("Введите Ф.И.О\n");
	getchar();
	fgets(name_poisk, 50, stdin);
	
	for (int i = 0; i <= chislo_zapis; i++) {
		if (strcmp(name_poisk, zapis[i].FIO) == 0) vivod_poisk(zapis, i);
	}
}

void poisk_sec(kp* zapis, int chislo_zapis) {

	int number_poisk;
	printf("Введите # секции\n");
	scanf("%d", &number_poisk);

	for (int i = 0; i <= chislo_zapis; i++)
		if (number_poisk == zapis[i].number) vivod_poisk(zapis, i);
}

void sohr(kp* zapis, int chislo_zapis, int o_f)
{
	FILE* out;
	if (o_f == 1) out = fopen("kp.txt", "w");
	else out = fopen("kp.txt", "a");

	fprintf(out, "\n%d ", zapis[chislo_zapis].data[0]);
	fprintf(out, "%d ", zapis[chislo_zapis].data[1]);
	fprintf(out, "%d\n", zapis[chislo_zapis].data[2]);
	fprintf(out, "%d\n", zapis[chislo_zapis].number);
	fprintf(out, "%s", zapis[chislo_zapis].tema);
	fprintf(out, "%s", zapis[chislo_zapis].FIO);
	fprintf(out, "%d", zapis[chislo_zapis].min);

	fclose(out);
}

int read(kp* zapis, int chislo_zapis) {
	int i = 0;
	FILE* out;
	char b[50];

	out = fopen("kp.txt", "r");
	while (!feof(out)) {
		fscanf(out, "%d", &zapis[i].data[0]);
		fscanf(out, "%d", &zapis[i].data[1]);
		fscanf(out, "%d\n", &zapis[i].data[2]);
		fscanf(out, "%d\n", &zapis[i].number);
		fgets(zapis[i].tema, 50, out);
		fgets(zapis[i].FIO, 50, out);
		fscanf(out, "%d\n", &zapis[i].min);
		i++;
	}
	fclose(out);
	return i;
}

void ShellSort(kp* zapis, int chislo_zapis)
{
	int i, j, step;
	int tmp;
	for (step = chislo_zapis / 2; step > 0; step /= 2)
		for (i = step; i < chislo_zapis; i++)
		{
			tmp = zapis[i].number;
			for (j = i; j >= step; j -= step)
			{
				if (tmp < zapis[j - step].number)
					zapis[j] = zapis[j - step];
				else
					break;
			}
			zapis[j].number = tmp;
		}
	for (int i = 0; i < chislo_zapis; i++) {
		printf("# Секции %d\n\n", zapis[i].number);
	}
}

void red(kp* zapis, int number, int chislo_zapis)
{
	if (number >= chislo_zapis) {
		printf("Запись не найдена\n");
		return NULL;
	}

	new_zapisi(zapis, number);
}
