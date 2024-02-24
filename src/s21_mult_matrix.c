#include "s21_matrix.h"

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  if ((common_check(A) || common_check(B))) return INCOR_MATR;
  if ((A->columns != B->rows)) return CALC_ER;
  int error = s21_create_matrix(A->rows, B->columns, result);
  if (error == CORRECT) {
    for (int i = 0; i < result->rows; ++i) {
      for (int j = 0; j < result->columns; ++j) {
        result->matrix[i][j] = 0;
        for (int k = 0; k < A->columns; k++) {
          result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
        }
      }
    }
  }
  return error;
}