#include "s21_matrix.h"

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  if (common_check(A) || result == NULL) return INCOR_MATR;
  if (A->columns != A->rows) return CALC_ER;
  int error = s21_create_matrix(A->columns, A->rows, result);
  if (error == CORRECT) {
    if (result->rows != 1) {
      matrix_t buf;
      error = s21_create_matrix(A->rows - 1, A->columns - 1, &buf);
      if (error == CORRECT) {
        for (int i = 0; i < A->rows; ++i) {
          for (int j = 0; j < A->columns; ++j) {
            find_minor(i, j, *A, &buf);
            s21_determinant(&buf, &(result->matrix[i][j]));
            if (((i + j) % 2 != 0) && (i + j != 0)) result->matrix[i][j] *= -1;
          }
        }
      }
      s21_remove_matrix(&buf);
    } else
      result->matrix[0][0] = A->matrix[0][0];
  }
  return error;
}