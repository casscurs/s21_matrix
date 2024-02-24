#include "s21_matrix.h"

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  if (common_check(A) || common_check(B)) return FAILURE;
  int result = SUCCESS;
  if (size_check(A, B)) {
    for (int i = 0; i < (A->rows) && (result == SUCCESS); i++) {
      for (int j = 0; j < (A->columns) && (result == SUCCESS); j++) {
        if (float_compare(A->matrix[i][j], B->matrix[i][j])) {
          result = FAILURE;
        }
      }
    }
  } else {
    result = FAILURE;
  }
  return result;
}