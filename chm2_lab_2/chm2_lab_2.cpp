#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <math.h>
#include <iostream>
using namespace std;

#define ICHAR 80  // ������� ����� ����� �������
#define IDEBUG 1  // �� ��������� ����� �������� ������� �� ���������� �������

int matrix_print_off(int nr, int nc, double** A) {
	int i, j;
	if (nr <= 0) return (-1);
	if (nc <= 0) return (-2);
	for (i = 1; i <= nr; i++) {
		for (j = 1; j <= nc; j++) {
			printf("%9.2f  ", A[i][j]);
		}
		printf("\n");
	}
	return (0);
}

int vector_print_off(int nr, double* x) {
	int i;

	if (nr <= 0) return (-1);

	for (i = 1; i <= nr; i++) {
		cout << "     "<< x[i] << "\n";
	}
	printf("\n");
	return (0);
}

double* matrix_on_vector_mult(int nr, int nc, double** A, double* x) {
	if (nr <= 0) return NULL;
	if (nc <= 0) return NULL;
	double* b = (double*)calloc(nr, sizeof(double)); b--;
	for (int i = 1; i <= nr; i++) {
		b[i] = 0;
		for (int j = 1; j <= nc; j++) b[i] += A[i][j] * x[j];
	}
	return b;
}

void gauss(double** a, double* b, double* x, int n) {
	int   i, j, k, m, rowx;
	double xfac, temp, temp1, amax;

	rowx = 0;
	for (k = 1; k <= n - 1; ++k) {
		amax = (double)fabs(a[k][k]);
		m = k;
		for (i = k + 1; i <= n; i++) {
			xfac = (double)fabs(a[i][k]);
			if (xfac > amax) { amax = xfac; m = i; }
		}
		if (m != k) {
			rowx = rowx + 1;
			temp1 = b[k];
			b[k] = b[m];
			b[m] = temp1;
			for (j = k; j <= n; j++) {
				temp = a[k][j];
				a[k][j] = a[m][j];
				a[m][j] = temp;
			}
		}
		for (i = k + 1; i <= n; ++i) {
			xfac = a[i][k] / a[k][k];

			for (j = k + 1; j <= n; ++j) {
				a[i][j] = a[i][j] - xfac * a[k][j];
			}
			b[i] = b[i] - xfac * b[k];
		}
		if (IDEBUG == 1) {
			printf("���� % d:\n\n", k);
			matrix_print_off(n, n, a);
			cout << "\n";
		}
	}

	for (j = 1; j <= n; ++j) {
		k = n - j + 1;
		x[k] = b[k];
		for (i = k + 1; i <= n; ++i) {
			x[k] = x[k] - a[k][i] * x[i];
		}
		x[k] = x[k] / a[k][k];
	}
}

int main(void) {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	double** a, ** a0, * b, * b0, * x, * xm, * r;
	float  aij, bi, xmi;
	char   desc[ICHAR];
	int    i, j, n;
	FILE* finput;

	finput = fopen("Gaus.TXT", "r");
	if (finput == NULL) {
		printf("��������� ���� \"Gaus.TXT\" �� ��������!\n");
		return(-1);
	}

	fgets(desc, ICHAR, finput);
	// ³���������� ������ ����� ����� �� 80 �����
	fscanf(finput, "%d", &n);
	printf("����� ������� (N*N) = %d\n\n", n);

	// �������� ���'�� ��� ������� (������ ������)
	a = (double**)calloc(n, sizeof(double*)); --a;		// �-- ��� ����������� �������� ������ � �������
	a0 = (double**)calloc(n, sizeof(double*)); --a0;	// ���� ������� ��� �������� ����'����
	
	for (i = 1; i <= n; ++i) {
		a[i] = (double*)calloc(n, sizeof(double)); --a[i];
		a0[i] = (double*)calloc(n, sizeof(double)); --a0[i];
	}

	// �������� ���'�� ��� ������� (������� ������)
	b = (double*)calloc(n, sizeof(double)); --b;
	b0 = (double*)calloc(n, sizeof(double)); --b0;		// ���� ������� ��� �������� ����'����
	x = (double*)calloc(n, sizeof(double)); --x;
	xm = (double*)calloc(n, sizeof(double)); --xm;
	r = (double*)calloc(n, sizeof(double)); --r;

	// ���������� ������� � 
	for (i = 1; i <= n; i++) {
		for (j = 1; j <= n; j++) {
			fscanf(finput, "%f ", &aij);
			a[i][j] = (double)aij;
			a0[i][j] = (double)aij;
		}
	}
	// ���������� ������� �
	for (i = 1; i <= n; i++) {
		fscanf(finput, "%f ", &bi);
		b[i] = (double)bi;
		b0[i] = (double)bi;
	}
	// ���������� ������� �M - ����'���� � mathcad
	for (i = 1; i <= n; i++) {
		fscanf(finput, "%f ", &xmi);
		xm[i] = (double)xmi;
	}

	fclose(finput);

	printf("---------------------�ղ�Ͳ ��Ͳ---------------------\n");

	printf("\n������� A:\n\n");
	matrix_print_off(n, n, a);

	printf("\n������ �:\n\n");
	vector_print_off(n, b);

	cout << "-------------------------ղ�-------------------------\n\n";
	gauss(a, b, x, n);

	printf("\n----------------------����'����----------------------\n\n������ �:\n\n");
	vector_print_off(n, x);

	if (IDEBUG == 1) {
		// ��������� ���������� ������� �*�
		double* a0x = matrix_on_vector_mult(n, n, a0, x);
		printf("----------------------����²���----------------------\n\n������-������� A*X:\n\n");
		vector_print_off(n, a0x);

		// ��������� ������� ���'���� R
		cout << "\n������ ���'���� R=B-A*X:\n\n";
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				r[i] = b0[i] - a0x[i];
			}
		}
		vector_print_off(n, r);

		// ���������� ������������������� �������
		double err = 0;
		for (i = 1; i <= n; i++) {
			err += pow(x[i] - xm[i], 2);
		}
		err = sqrt(err / n);

		cout << "\n-------------������������������� �������--------------\n\nQ  = " << err << "\n\n";
	}

	getchar();
	return(0);
}