#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Задание 2
// Дана целочисленная квадратная матрица. Определить:
// 1) сумму элементов в тех столбцах, которые не содержат отрицательных элементов;
// 2) минимум среди сумм модулей элементов диагоналей, параллельных побочной диагонали матрицы.


#define M 5


int Laboratornaya__4()
{
	int arr[M][M] = {
		{2,  -3,   3,   4,   5},
		{1,   7,  8,   9,   10},
		{11,   12,  13,  14,  -15},
		{16, 17,  18,   19,   9},
		{21,  22,   23,   1,   25},
	};
	int i, j, k;
	int sum, ok, * sums, sum_index;
	int min_elem = 10000000000;

	for (j = 0; j < M; j++) {
		ok = 1;
		sum = 0;
		for (k = 0; k < M; k++) {
			if (arr[k][j] < 0) {
				ok = 0;
				break;
			}
			sum += arr[k][j];
		}
		if (ok) {
			printf("column: %d, sum: %d\n", j + 1, sum);
		}
	}

	sums = (int*)malloc(sizeof(int) * (M - 1) * 2);
	if (sums == NULL) {
		exit(EXIT_FAILURE);
	}
	sum_index = 0;

	// в верхней треугольной
	for (i = 0; i < M - 1; i++) {
		j = i;
		k = 0;
		sum = 0;
		while (j >= 0 && k < M) {
			sum += abs(arr[j][k]);
			j--;
			k++;
		}
		sums[sum_index] = sum;
		sum_index++;

		if (sum < min_elem) min_elem = sum;
	}

	// в нижней треугольной
	for (i = 1; i < M; i++) {
		j = M - 1;
		k = i;
		sum = 0;
		while (j > 0 && k < M) {
			sum += abs(arr[j][k]);
			j--;
			k++;
		}
		sums[sum_index] = sum;
		sum_index++;

		if (sum < min_elem) min_elem = sum;
	}

	//	min_elem = sums[0];
	for (sum_index -= 1; sum_index >= 0; sum_index--) {
		//		if (min_elem > sums[sum_index]) {
			//		min_elem = sums[sum_index];
		//		}
	}

	printf("min: %d\n", min_elem);

	free(sums);
	exit(EXIT_SUCCESS);
	return 4;
}