#include "s21_matrix.h"

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  if (common_check(A) || result == NULL) return INCOR_MATR;
  if (A->columns != A->rows) return CALC_ER;
  double det = 0;
  int error = s21_determinant(A, &det);
  if (error == CORRECT) {
    if ((det != 0)) {
      if (A->rows > 1) {
        matrix_t compl = {0};
        matrix_t mult = {0};
        s21_calc_complements(A, &compl );
        s21_transpose(&compl, &mult);
        s21_mult_number(&mult, (double)1 / det, result);
        s21_remove_matrix(&compl );
        s21_remove_matrix(&mult);
      } else {
        s21_create_matrix(1, 1, result);
        result->matrix[0][0] = (double)1 / A->matrix[0][0];
      }
    } else {
      error = CALC_ER;
    }
  }
  return error;
}