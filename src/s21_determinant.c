#include "s21_matrix.h"

int s21_determinant(matrix_t *A, double *result) {
  if (common_check(A)) return INCOR_MATR;
  if ((A->columns) != A->rows) return CALC_ER;
  matrix_t buf = {0};
  int error = s21_create_matrix(A->columns, A->rows, &buf);
  if (error == CORRECT) {
    if (buf.rows != 1) {
      for (int i = 0; i < buf.rows; ++i)
        for (int j = 0; j < buf.columns; ++j)
          buf.matrix[i][j] = A->matrix[i][j];
      Bareiss_algorith(buf, result);
    } else {
      *result = A->matrix[0][0];
    }
  }
  s21_remove_matrix(&buf);
  return error;
}

void Bareiss_algorith(matrix_t buf, double *result) {
  /* Bareiss algorithm */
  double det = 1;
  for (int j = 0; j < buf.columns; ++j) {
    int nonZero = j;
    /* Ищем строку с ненулевым элементом */
    for (int i = j; i < buf.rows; ++i) {
      if (buf.matrix[i][j] != 0) {
        nonZero = i;
        break;
      }
    }
    /* Поменяли строки местами */
    if (nonZero != j) {
      for (int k = 0; k < buf.columns; ++k) {
        swap(&(buf.matrix[j][k]), &(buf.matrix[nonZero][k]));
      }
      det = -det;
    }
    /* Проверка деления на ноль, если не прошли, то матрица вырожденная*/
    if (buf.matrix[j][j] == 0) {
      det = 0;
      break;
    }
    /* Сведение к ступенчатому виду с помощью преобразования строк*/
    for (int i = j + 1; i < buf.rows; ++i) {
      double corr = buf.matrix[i][j] / buf.matrix[j][j];
      for (int k = j; k < buf.rows; ++k) {
        buf.matrix[i][k] -= corr * buf.matrix[j][k];
      }
    }
    det *= buf.matrix[j][j];
  }
  if (fabs(det) < 1e-7) {
    det = 0;
  }
  *result = det;
}