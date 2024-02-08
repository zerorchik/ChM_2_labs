#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <windows.h>
#include <cmath>
using namespace std;

#define ICHAR 80  // ������� ����� ����� �������

// ����� ����������
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

// �������� ���������� ��������
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
		cout << "��������� ���� \"Zeydel.TXT\" �� ��������!\n";
		return(-1);
	}
	// ³���������� ������ ����� ����� �� 80 �����
	fgets(desc, ICHAR, finput);
	// ���������� ������� ������ �������
	fscanf(finput, "%d", &n);
	cout << "ʳ������ ������ �������: " << n << endl;
	// ���������� ������� � 
	cout << "\n������� A:\n\n";
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
	// ���������� ������� �
	cout << "\n������ B:\n\n";
	for (i = 0; i < n; i++) 
	{
		fscanf(finput, "%f ", &read);
		b[i] = read;
		printf("%9.2f  ", b[i]);
		cout << endl;
	}
	// ���������� ������� �m - ����'���� � mathcad
	cout << "\n������-����'���� � Mathcad Xm:\n\n";
	for (i = 0; i < n; i++) 
	{
		fscanf(finput, "%f ", &read);
		xm[i] = read;
		printf("%9.3f  ", xm[i]);
		cout << endl;
	}
	fclose(finput);

	cout << "\n�������: ";
	cin >> eps;
	cout << endl;

	for (int i = 0; i < n; i++)
		x[i] = 1;

	// ���������� �������� ��������, ���� ����� ���������� �� ���������
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
			// ���� ���������� ����� ��������
			cout << "�������� " << m << ":\t������ ���'����: " << endl;
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

		cout << "����'���� �������:" << endl << endl;
		for (i = 0; i < n; i++) 
			cout << "x" << i << " = " << okr(x[i], eps) << "" << endl;
		cout << "\n��������: " << m << endl;
		// ���������� ������������������� �������
		double err = 0;
		for (i = 1; i <= n; i++) {
			err += pow(x[i] - xm[i], 2);
		}
		err = sqrt(err / n);

		cout << "\n������������������� ������� = " << err << endl << endl;
	}
	else 
		cout << "ĳ��������� �������� �������!" << endl;
	cout << "\n\n";
}