#include "tests.h"

START_TEST(normal) {
  matrix_t m = {0};
  matrix_t expected = {0};
  int code1 = s21_create_matrix(3, 3, &m);
  int code2 = s21_create_matrix(3, 3, &expected);

  if (!code1 && !code2) {
    m.matrix[0][0] = 2;
    m.matrix[0][1] = 5;
    m.matrix[0][2] = 7;

    m.matrix[1][0] = 6;
    m.matrix[1][1] = 3;
    m.matrix[1][2] = 4;

    m.matrix[2][0] = 5;
    m.matrix[2][1] = -2;
    m.matrix[2][2] = -3;

    expected.matrix[0][0] = 1;
    expected.matrix[0][1] = -1;
    expected.matrix[0][2] = 1;

    expected.matrix[1][0] = -38;
    expected.matrix[1][1] = 41;
    expected.matrix[1][2] = -34;

    expected.matrix[2][0] = 27;
    expected.matrix[2][1] = -29;
    expected.matrix[2][2] = 24;

    matrix_t result = {0};
    int code = s21_inverse_matrix(&m, &result);
    ck_assert_int_eq(s21_eq_matrix(&result, &expected), 1);
    ck_assert_int_eq(code, 0);
    s21_remove_matrix(&result);
  }
  s21_remove_matrix(&m);
  s21_remove_matrix(&expected);
}
END_TEST

START_TEST(calc_inverse) {
  matrix_t a = {0};
  matrix_t exp = {0};
  matrix_t res = {0};

  ck_assert_int_eq(s21_create_matrix(3, 3, &a), CORRECT);
  ck_assert_ptr_ne(a.matrix, NULL);

  a.matrix[0][0] = 1;
  a.matrix[0][1] = 2;
  a.matrix[0][2] = 3;
  a.matrix[1][0] = 0;
  a.matrix[1][1] = 4;
  a.matrix[1][2] = 2;
  a.matrix[2][0] = 5;
  a.matrix[2][1] = 2;
  a.matrix[2][2] = 1;

  ck_assert_int_eq(s21_inverse_matrix(&a, &res), CORRECT);
  ck_assert_int_eq(s21_create_matrix(3, 3, &exp), CORRECT);
  exp.matrix[0][0] = 0;
  exp.matrix[0][1] = -0.1;
  exp.matrix[0][2] = 0.2;
  exp.matrix[1][0] = -0.25;
  exp.matrix[1][1] = 0.35;
  exp.matrix[1][2] = 0.05;
  exp.matrix[2][0] = 0.5;
  exp.matrix[2][1] = -0.2;
  exp.matrix[2][2] = -0.1;

  ck_assert_int_eq(s21_eq_matrix(&res, &exp), SUCCESS);

  s21_remove_matrix(&a);
  s21_remove_matrix(&exp);
  s21_remove_matrix(&res);
}
END_TEST

START_TEST(calc_inverse_hard) {
  matrix_t a = {0};
  matrix_t res = {0};
  matrix_t exp = {0};

  ck_assert_int_eq(s21_create_matrix(3, 3, &a), CORRECT);
  ck_assert_ptr_ne(a.matrix, NULL);
  for (int i = 0; i < 3; i++) {
    ck_assert_ptr_ne(a.matrix[i], NULL);
  }

  a.matrix[0][0] = 72;
  a.matrix[0][1] = 41;
  a.matrix[0][2] = 3.16;
  a.matrix[1][0] = 13.02;
  a.matrix[1][1] = 15;
  a.matrix[1][2] = 900;
  a.matrix[2][0] = 6;
  a.matrix[2][1] = 7;
  a.matrix[2][2] = 14.009;

  ck_assert_int_eq(s21_inverse_matrix(&a, &res), CORRECT);
  ck_assert_int_eq(s21_create_matrix(3, 3, &exp), CORRECT);

  exp.matrix[0][0] = -6089.8650000000 / -224544.961980;
  exp.matrix[1][0] = 5217.6028200000 / -224544.961980;
  exp.matrix[2][0] = 1.1400000000 / -224544.961980;
  exp.matrix[0][1] = -552.2490000000 / -224544.961980;
  exp.matrix[1][1] = 989.6880000000 / -224544.961980;
  exp.matrix[2][1] = -258.0000000000 / -224544.961980;
  exp.matrix[0][2] = 36852.6000000000 / -224544.961980;
  exp.matrix[1][2] = -64758.8568000000 / -224544.961980;
  exp.matrix[2][2] = 546.1800000000 / -224544.961980;

  ck_assert_int_eq(s21_eq_matrix(&exp, &res), SUCCESS);

  s21_remove_matrix(&a);
  s21_remove_matrix(&exp);
  s21_remove_matrix(&res);
}
END_TEST

START_TEST(calc_inverse_edge) {
  matrix_t a = {0};
  matrix_t res = {0};
  ck_assert_int_eq(s21_create_matrix(3, 4, &a), CORRECT);
  ck_assert_ptr_ne(a.matrix, NULL);
  for (int i = 0; i < 3; i++) {
    ck_assert_ptr_ne(a.matrix[i], NULL);
  }
  ck_assert_int_eq(s21_inverse_matrix(&a, &res), CALC_ER);
  ck_assert_int_eq(s21_inverse_matrix(NULL, &res), INCOR_MATR);
  s21_remove_matrix(&a);
  s21_remove_matrix(&res);
}
END_TEST

START_TEST(zero_det) {
  matrix_t m = {0};
  matrix_t result = {0};
  int codec = s21_create_matrix(1, 1, &m);
  if (!codec) {
    int code = s21_inverse_matrix(&m, &result);
    s21_remove_matrix(&m);
    ck_assert_int_eq(code, 2);
    s21_remove_matrix(&result);
  }
}
END_TEST

START_TEST(incorrect) {
  matrix_t m = {0};
  matrix_t result = {0};
  int code = s21_inverse_matrix(&m, &result);
  ck_assert_int_eq(code, 1);
  s21_remove_matrix(&m);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(not_sqare) {
  matrix_t m = {0};
  matrix_t result = {0};
  int codec = s21_create_matrix(1, 4, &m);
  if (!codec) {
    int code = s21_inverse_matrix(&m, &result);
    ck_assert_int_eq(code, 2);
    s21_remove_matrix(&m);
    s21_remove_matrix(&result);
  }
}
END_TEST

START_TEST(inverse_all) {
  matrix_t matrix_1, result, correct_res;
  s21_create_matrix(3, 2, &matrix_1);
  s21_create_matrix(3, 3, &correct_res);
  int err = 0;

  err = s21_inverse_matrix(NULL, &result);
  ck_assert_int_eq(INCOR_MATR, err);
  err = s21_inverse_matrix(&matrix_1, NULL);
  ck_assert_int_eq(INCOR_MATR, err);
  err = s21_inverse_matrix(&matrix_1, &result);
  ck_assert_int_eq(CALC_ER, err);

  s21_create_matrix(3, 3, &matrix_1);

  matrix_1.matrix[0][0] = 2;
  matrix_1.matrix[1][0] = 5;
  matrix_1.matrix[2][0] = 3;
  matrix_1.matrix[0][1] = 1;
  matrix_1.matrix[1][1] = -5;
  matrix_1.matrix[2][1] = 3.3;
  matrix_1.matrix[0][2] = -1;
  matrix_1.matrix[1][2] = 0;
  matrix_1.matrix[2][2] = 0.3;
  correct_res.matrix[0][0] = -1.5 / -36;
  correct_res.matrix[1][0] = -1.5 / -36;
  correct_res.matrix[2][0] = 31.5 / -36;
  correct_res.matrix[0][1] = -3.6 / -36;
  correct_res.matrix[1][1] = 3.6 / -36;
  correct_res.matrix[2][1] = -3.6 / -36;
  correct_res.matrix[0][2] = -5. / -36;
  correct_res.matrix[1][2] = -5. / -36;
  correct_res.matrix[2][2] = -15. / -36;

  err = s21_inverse_matrix(&matrix_1, &result);
  ck_assert_int_eq(CORRECT, err);
  err = s21_eq_matrix(&result, &correct_res);
  ck_assert_int_eq(SUCCESS, err);

  correct_res.matrix[2][2] = -14. / -36;
  err = s21_inverse_matrix(&matrix_1, &result);
  ck_assert_int_eq(CORRECT, err);
  err = s21_eq_matrix(&result, &correct_res);
  ck_assert_int_eq(FAILURE, err);

  matrix_1.matrix[0][2] = 0;
  matrix_1.matrix[1][2] = 0;
  matrix_1.matrix[2][2] = 0;
  err = s21_inverse_matrix(&matrix_1, &result);
  ck_assert_int_eq(CALC_ER, err);

  matrix_1.rows = -2;
  err = s21_inverse_matrix(&matrix_1, &result);
  ck_assert_int_eq(INCOR_MATR, err);

  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&result);
  s21_remove_matrix(&correct_res);
}
END_TEST

START_TEST(test_inverse_identity_matrix) {
  matrix_t m = {0};
  matrix_t expected = {0};
  int code1 = s21_create_matrix(3, 3, &m);
  int code2 = s21_create_matrix(3, 3, &expected);

  if (!code1 && !code2) {
    m.matrix[0][0] = 1;
    m.matrix[1][1] = 1;
    m.matrix[2][2] = 1;

    expected.matrix[0][0] = 1;
    expected.matrix[1][1] = 1;
    expected.matrix[2][2] = 1;

    matrix_t result = {0};
    int code = s21_inverse_matrix(&m, &result);
    ck_assert_int_eq(s21_eq_matrix(&result, &expected), 1);
    ck_assert_int_eq(code, 0);
    s21_remove_matrix(&result);
  }
  s21_remove_matrix(&m);
  s21_remove_matrix(&expected);
}
END_TEST

START_TEST(test_inverse_random_matrix) {
  matrix_t m = {0};
  matrix_t expected = {0};
  int code1 = s21_create_matrix(2, 2, &m);
  int code2 = s21_create_matrix(2, 2, &expected);

  if (!code1 && !code2) {
    m.matrix[0][0] = 1.5;
    m.matrix[0][1] = 0.2;

    m.matrix[1][0] = 0.8;
    m.matrix[1][1] = 2.0;

    expected.matrix[0][0] = 0.704225;
    expected.matrix[0][1] = -0.070423;

    expected.matrix[1][0] = -0.281690;
    expected.matrix[1][1] = 0.528169;

    matrix_t result = {0};
    int code = s21_inverse_matrix(&m, &result);
    ck_assert_int_eq(s21_eq_matrix(&result, &expected), SUCCESS);

    ck_assert_int_eq(code, CORRECT);
    s21_remove_matrix(&result);
  }
  s21_remove_matrix(&m);
  s21_remove_matrix(&expected);
}
END_TEST

START_TEST(test_inverse_singular_matrix) {
  matrix_t m = {0};
  matrix_t result = {0};
  int code1 = s21_create_matrix(3, 3, &m);

  if (!code1) {
    m.matrix[0][0] = 1.0;
    m.matrix[0][1] = 2.0;
    m.matrix[0][2] = 3.0;

    m.matrix[1][0] = 2.0;
    m.matrix[1][1] = 4.0;
    m.matrix[1][2] = 6.0;

    m.matrix[2][0] = 3.0;
    m.matrix[2][1] = 6.0;
    m.matrix[2][2] = 9.0;

    int code = s21_inverse_matrix(&m, &result);
    ck_assert_int_eq(code, CALC_ER);
    s21_remove_matrix(&result);
  }
  s21_remove_matrix(&m);
}
END_TEST

START_TEST(test_inverse_zero_column_matrix) {
  matrix_t m = {0};
  matrix_t result = {0};
  int code1 = s21_create_matrix(2, 2, &m);

  if (!code1) {
    m.matrix[0][0] = 1;
    m.matrix[0][1] = 0;

    m.matrix[1][0] = 2;
    m.matrix[1][1] = 0;

    int code = s21_inverse_matrix(&m, &result);
    ck_assert_int_eq(code, CALC_ER);
    s21_remove_matrix(&result);
  }
  s21_remove_matrix(&m);
}
END_TEST

START_TEST(test_inverse_one) {
  matrix_t m = {0};
  matrix_t result = {0};
  matrix_t exp = {0};
  int code1 = s21_create_matrix(1, 1, &m);
  int code2 = s21_create_matrix(1, 1, &exp);

  if (!code1 && !code2) {
    m.matrix[0][0] = 3;
    exp.matrix[0][0] = 1.0 / 3.0;
    int code = s21_inverse_matrix(&m, &result);
    ck_assert_int_eq(s21_eq_matrix(&result, &exp), SUCCESS);
    ck_assert_int_eq(code, CORRECT);
    s21_remove_matrix(&result);
  }
  s21_remove_matrix(&exp);
  s21_remove_matrix(&m);
}
END_TEST

Suite *suite_inverse_matrix(void) {
  Suite *s = suite_create("suite_inverse_matrix");
  TCase *tc = tcase_create("case_inverse_matrix");
  tcase_add_test(tc, normal);
  tcase_add_test(tc, not_sqare);
  tcase_add_test(tc, zero_det);
  tcase_add_test(tc, incorrect);
  tcase_add_test(tc, calc_inverse);
  tcase_add_test(tc, calc_inverse_edge);
  tcase_add_test(tc, calc_inverse_hard);

  tcase_add_test(tc, inverse_all);
  tcase_add_test(tc, test_inverse_identity_matrix);
  tcase_add_test(tc, test_inverse_random_matrix);
  tcase_add_test(tc, test_inverse_singular_matrix);
  tcase_add_test(tc, test_inverse_zero_column_matrix);
  tcase_add_test(tc, test_inverse_one);

  suite_add_tcase(s, tc);
  return s;
}
