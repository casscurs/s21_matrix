#include "s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  if (result == NULL) return INCOR_MATR;
  if ((rows <= 0) || (columns <= 0)) return INCOR_MATR;
  int error = CORRECT;
  result->matrix =
      malloc(rows * columns * sizeof(double) + rows * sizeof(double *));
  memset(result->matrix, 0,
         rows * columns * sizeof(double) + rows * sizeof(double *));
  if (result->matrix == NULL)
    error = INCOR_MATR;
  else {
    result->columns = columns;
    result->rows = rows;
    double *ptr = NULL;
    ptr = (double *)((result->matrix) + rows);
    for (int i = 0; i < rows; ++i) {
      result->matrix[i] = ptr + columns * i;
    }
  }
  return (error);
}