#include "s21_matrix.h"

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  if (common_check(A)) return INCOR_MATR;
  int error = s21_create_matrix(A->rows, A->columns, result);
  if (error == CORRECT) {
    for (int i = 0; i < A->rows; ++i) {
      for (int j = 0; j < A->columns; ++j) {
        result->matrix[i][j] = A->matrix[i][j] * number;
      }
    }
  }
  return error;
}