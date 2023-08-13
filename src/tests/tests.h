#ifndef SRC_TESTS_TEST_H_
#define SRC_TESTS_TEST_H_

#include <check.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../s21_matrix.h"

#define S21_PI 3.1415926535
#define S21_EX 2.7182818284

#define SUCCESS 1
#define FAILURE 0

Suite *suite_complements(void);
Suite *suite_create_matrix(void);
Suite *suite_transpose_matrix(void);
Suite *suite_eq_matrix(void);
Suite *suite_sum_matrix(void);
Suite *suite_sub_matrix(void);
Suite *suite_mult_matrix(void);
Suite *suite_mult_number_matrix(void);
Suite *suite_determinant(void);
Suite *suite_inverse_matrix(void);

void run_testcase(Suite *testcase);
double get_rand(double min, double max);

#endif  // SRC_TEST_H_
          