#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <windows.h>
using namespace std;

#define ICHAR 80  // Довжина рядку опису системи

void matrixPrint(double a[10][10], int n) 
{
	int i, j;

	for (i = 1; i <= n; i++)
	{
		for (j = 1; j <= n; j++)
			printf("%9.5f  ", a[i][j]);
		cout << endl;
	}
}

void forbenius(double a[10][10], int n) 
{
	int i, j, k;
	double m[10][10], m1[10][10], m1a[10][10];

	for (i = 1; i <= n - 1; i++)
	{
		// m
		for (j = 1; j <= n; j++)
			for (k = 1; k <= n; k++)
			{
				if (j == n - i)
				{
					if (k == j)
						m[j][k] = 1 / (a[j + 1][j]);
					else
						m[j][k] = a[j + 1][k] / (-a[j + 1][j]);
				}
				else if (k == j)
					m[j][k] = 1;
				else
					m[j][k] = 0;
			}
		cout << "\nКРОК " << i << " -------------------------------------";
		cout << "\nM" << n - i << ":" << endl << endl;
		matrixPrint(m, n);
		cout << "\nM" << n - i << "^(-1):" << endl << endl;
		// m^-1
		for (j = 1; j <= n; j++)
			for (k = 1; k <= n; k++)
			{
				if (j == n - i)
					m1[j][k] = a[j + 1][k];
				else if (j == k)
					m1[j][k] = 1;
				else
					m1[j][k] = 0;
			}
		matrixPrint(m1, n);
		// m^-1*a
		for (j = 1; j <= n; j++)
			for (k = 1; k <= n; k++)
			{
				m1a[j][k] = 0;
				for (int p = 1; p <= n; p++)
					m1a[j][k] += m1[j][p] * a[p][k];
			}
		// a= m^-1*a*m
		for (j = 1; j <= n; j++)
			for (k = 1; k <= n; k++)
			{
				a[j][k] = 0;
				for (int p = 1; p <= n; p++)
					a[j][k] += m1a[j][p] * m[p][k];
			}
		cout << "\nA" << i << ":" << endl << endl;
		matrixPrint(a, n);
	}
}

int main() 
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	double a[10][10];
	float read;
	int n, i, j = 0;
	char   desc[ICHAR];
	FILE* finput;

	finput = fopen("Forbenius.TXT", "r");
	if (finput == NULL)
	{
		cout << "Текстовий файл \"Forbenius.TXT\" НЕ знайдено!\n";
		return(-1);
	}
	// Відсканувати перший рядок файлу до 80 знаків
	fgets(desc, ICHAR, finput);

	// Зчитування кількості рівнянь системи
	fscanf(finput, "%d", &n);
	cout << "Кількість рівнянь системи: " << n << endl;

	// Зчитування матриці А 
	cout << "\nМатриця A:\n\n";
	for (i = 1; i <= n; i++)
		for (j = 1; j <= n; j++)
		{
			fscanf(finput, "%f ", &read);
			a[i][j] = read;
		}
	matrixPrint(a, n);

	fclose(finput);

	forbenius(a, n);
}