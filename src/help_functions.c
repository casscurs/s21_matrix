#include "s21_matrix.h"

/* Вернет 0, если числа равны, 1 - не равны */
int float_compare(double a, double b) {
  return round(a * pow(10, 6)) == round(b * pow(10, 6)) ? 0 : 1;
}

/* Вернет 1, если размеры совпали */
int size_check(matrix_t *A, matrix_t *B) {
  int result = 0;
  if (((A->columns) == (B->columns)) && ((A->rows) == (B->rows))) {
    result = 1;
  }
  return result;
}

/* Вернет 1, если указатель NULL или row ||col <= 0 */
int common_check(matrix_t *A) {
  int result = 0;
  if (A == NULL || (A->matrix == NULL) || (A->rows <= 0 || A->columns <= 0)) {
    result = 1;
  }
  return result;
}

/* Замена элементов */
void swap(double *A, double *B) {
  double temp = 0;
  temp = *A;
  *A = *B;
  *B = temp;
}

/* Составление минора элемента матрицы*/
void find_minor(int i, int j, matrix_t A, matrix_t *buf) {
  int minRow = -1;
  for (int l = 0; l < A.rows; ++l) {
    int minCol = 0;
    if (l != i) minRow++;
    for (int n = 0; n < A.columns; ++n) {
      if (l == i || n == j) {
        continue;
      } else {
        buf->matrix[minRow][minCol] = A.matrix[l][n];
        minCol++;
      }
    }
  }
}