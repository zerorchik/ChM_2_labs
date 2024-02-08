#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <windows.h>
#include <cmath>
using namespace std;

#define ICHAR 80  // Довжина рядку опису системи

// Умова завершення
bool converge(double xk[10], double xkp[10], int n, double eps)
{
	double norm = 0;

	for (int i = 0; i < n; i++)
		norm += (xk[i] - xkp[i]) * (xk[i] - xkp[i]);
	return (sqrt(norm) < eps);
}

double okr(double x, double eps)
{
	int i = 0;
	double neweps = eps;

	while (neweps < 1)
	{
		i++;
		neweps *= 10;
	}
	int okr = pow(double(10), i);
	x = int(x * okr + 0.5) / double(okr);
	return x;
}

// Перевірка діагональної переваги
bool diagonal(double a[10][10], int n)
{
	int i, j, k = 1;
	double sum;

	for (i = 0; i < n; i++) 
	{
		sum = 0;
		for (j = 0; j < n; j++) 
			sum += abs(a[i][j]);
		sum -= abs(a[i][i]);
		if (sum > a[i][i]) k = 0;
	}
	return (k == 1);
}

double matrix_on_vector_mult(int n, double a[10], double x[10]) {
	double ax = 0;
	for (int i = 0; i < n; i++) 
	{
		ax += a[i] * x[i];
	}
	return ax;
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	double eps, a[10][10], b[10], x[10], p[10], a0[10], ax[10], r[10], xm[10];
	float read;
	int n, i, j, m = 0;
	int method;
	char   desc[ICHAR];
	FILE* finput;

	finput = fopen("Zeydel.TXT", "r");
	if (finput == NULL)
	{
		cout << "Текстовий файл \"Zeydel.TXT\" НЕ знайдено!\n";
		return(-1);
	}
	// Відсканувати перший рядок файлу до 80 знаків
	fgets(desc, ICHAR, finput);
	// Зчитування кількості рівнянь системи
	fscanf(finput, "%d", &n);
	cout << "Кількість рівнянь системи: " << n << endl;
	// Зчитування матриці А 
	cout << "\nМатриця A:\n\n";
	for (i = 0; i < n; i++) 
	{
		for (j = 0; j < n; j++) 
		{
			fscanf(finput, "%f ", &read);
			a[i][j] = read;
			printf("%9.2f  ", a[i][j]);
		}
		cout << endl;
	}
	// Зчитування вектора В
	cout << "\nВектор B:\n\n";
	for (i = 0; i < n; i++) 
	{
		fscanf(finput, "%f ", &read);
		b[i] = read;
		printf("%9.2f  ", b[i]);
		cout << endl;
	}
	// Зчитування вектора Хm - розв'язку з mathcad
	cout << "\nВектор-розв'язок з Mathcad Xm:\n\n";
	for (i = 0; i < n; i++) 
	{
		fscanf(finput, "%f ", &read);
		xm[i] = read;
		printf("%9.3f  ", xm[i]);
		cout << endl;
	}
	fclose(finput);

	cout << "\nТочність: ";
	cin >> eps;
	cout << endl;

	for (int i = 0; i < n; i++)
		x[i] = 1;

	// Виконувати наступну ітерацію, поки умова завершення не досягнута
	if (diagonal(a, n)) 
	{
		do
		{
			for (int i = 0; i < n; i++)
				p[i] = x[i];
			for (int i = 0; i < n; i++)
			{
				double var = 0;
				for (int j = 0; j < n; j++)
					if (j != i) var += (a[i][j] * x[j]);

				x[i] = (b[i] - var) / a[i][i];
			}
			m++;
			// Вивід результатів кожної ітерації
			cout << "Ітерація " << m << ":\tВектор нев'язки: " << endl;
			for (i = 0; i < n; i++)
			{
				for (j = 0; j < n; j++)
					a0[j] = a[i][j];
				ax[i] = matrix_on_vector_mult(n, a0, x);
				r[i] = b[i] - ax[i];
				cout << "x" << i << " = " << okr(x[i], eps) << "\t";
				cout << "r" << i << " = " << r[i] << endl;
			}
			cout << "\n\n";
		} while (!converge(x, p, n, eps));

		cout << "Розв'язок системи:" << endl << endl;
		for (i = 0; i < n; i++) 
			cout << "x" << i << " = " << okr(x[i], eps) << "" << endl;
		cout << "\nІтерацій: " << m << endl;
		// Розрахунок середньоквадратичної похибки
		double err = 0;
		for (i = 1; i <= n; i++) {
			err += pow(x[i] - xm[i], 2);
		}
		err = sqrt(err / n);

		cout << "\nСередньоквадратична похибка = " << err << endl << endl;
	}
	else 
		cout << "Діагональна перевага відсутня!" << endl;
	cout << "\n\n";
}