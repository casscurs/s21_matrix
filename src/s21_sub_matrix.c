#include "s21_matrix.h"

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  if (common_check(A) || common_check(B)) return INCOR_MATR;
  if (!size_check(A, B)) return CALC_ER;
  int error = s21_create_matrix(A->rows, A->columns, result);
  if (error == CORRECT) {
    for (int i = 0; i < A->rows; ++i) {
      for (int j = 0; j < A->columns; ++j) {
        result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
      }
    }
  }
  return error;
}