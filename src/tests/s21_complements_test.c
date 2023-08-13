#include "tests.h"

START_TEST(test_normal) {
  matrix_t m = {0};
  matrix_t expected = {0};
  int code1 = s21_create_matrix(3, 3, &m);
  int code2 = s21_create_matrix(3, 3, &expected);

  if (!code1 && !code2) {
    m.matrix[0][0] = 1;
    m.matrix[0][1] = 2;
    m.matrix[0][2] = 3;

    m.matrix[1][0] = 0;
    m.matrix[1][1] = 4;
    m.matrix[1][2] = 2;

    m.matrix[2][0] = 5;
    m.matrix[2][1] = 2;
    m.matrix[2][2] = 1;

    expected.matrix[0][0] = 0;
    expected.matrix[0][1] = 10;
    expected.matrix[0][2] = -20;

    expected.matrix[1][0] = 4;
    expected.matrix[1][1] = -14;
    expected.matrix[1][2] = 8;

    expected.matrix[2][0] = -8;
    expected.matrix[2][1] = -2;
    expected.matrix[2][2] = 4;

    matrix_t result = {0};
    int code = s21_calc_complements(&m, &result);
    ck_assert_int_eq(s21_eq_matrix(&result, &expected), 1);
    ck_assert_int_eq(code, 0);
    s21_remove_matrix(&result);
  }
  s21_remove_matrix(&m);
  s21_remove_matrix(&expected);
}
END_TEST

START_TEST(test_all) {
  matrix_t matrix_1 = {0}, result = {0}, correct_res = {0}, matrix_2 = {0};
  s21_create_matrix(3, 2, &matrix_1);
  s21_create_matrix(3, 3, &correct_res);
  int err = 0;

  err = s21_calc_complements(NULL, &result);
  ck_assert_int_eq(INCOR_MATR, err);

  err = s21_calc_complements(&matrix_1, NULL);
  ck_assert_int_eq(INCOR_MATR, err);

  err = s21_calc_complements(&matrix_1, &result);
  ck_assert_int_eq(CALC_ER, err);

  s21_create_matrix(3, 3, &matrix_2);

  matrix_2.matrix[0][0] = 2;
  matrix_2.matrix[1][0] = 5;
  matrix_2.matrix[2][0] = 3;
  matrix_2.matrix[0][1] = 1;
  matrix_2.matrix[1][1] = -5;
  matrix_2.matrix[2][1] = 3.3;
  matrix_2.matrix[0][2] = -1;
  matrix_2.matrix[1][2] = 0;
  matrix_2.matrix[2][2] = 0.3;
  correct_res.matrix[0][0] = -1.5;
  correct_res.matrix[0][1] = -1.5;
  correct_res.matrix[0][2] = 31.5;
  correct_res.matrix[1][0] = -3.6;
  correct_res.matrix[1][1] = 3.6;
  correct_res.matrix[1][2] = -3.6;
  correct_res.matrix[2][0] = -5;
  correct_res.matrix[2][1] = -5;
  correct_res.matrix[2][2] = -15;

  err = s21_calc_complements(&matrix_2, &result);
  ck_assert_int_eq(CORRECT, err);
  err = s21_eq_matrix(&result, &correct_res);
  ck_assert_int_eq(SUCCESS, err);

  matrix_1.rows = -3;
  err = s21_calc_complements(&matrix_1, &result);
  ck_assert_int_eq(INCOR_MATR, err);

  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&result);
  s21_remove_matrix(&correct_res);
}
END_TEST

START_TEST(test_incorrect) {
  matrix_t m = {0};
  matrix_t result = {0};
  int code = s21_calc_complements(&m, &result);
  ck_assert_int_eq(code, 1);
  s21_remove_matrix(&m);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_not_sqare) {
  matrix_t m = {0};
  matrix_t result = {0};
  int codec = s21_create_matrix(3, 4, &m);
  if (codec == 0) {
    int code = s21_calc_complements(&m, &result);
    ck_assert_int_eq(code, 2);
    s21_remove_matrix(&m);
    s21_remove_matrix(&result);
  }
}
END_TEST

START_TEST(test_zero_matrix) {
  matrix_t m = {0};
  matrix_t expected = {0};
  int code1 = s21_create_matrix(3, 3, &m);
  int code2 = s21_create_matrix(3, 3, &expected);

  if (!code1 && !code2) {
    expected.matrix[0][0] = 0;
    expected.matrix[0][1] = 0;
    expected.matrix[0][2] = 0;

    expected.matrix[1][0] = 0;
    expected.matrix[1][1] = 0;
    expected.matrix[1][2] = 0;

    expected.matrix[2][0] = 0;
    expected.matrix[2][1] = 0;
    expected.matrix[2][2] = 0;

    matrix_t result = {0};
    int code = s21_calc_complements(&m, &result);
    ck_assert_int_eq(s21_eq_matrix(&result, &expected), 1);
    ck_assert_int_eq(code, 0);
    s21_remove_matrix(&result);
  }
  s21_remove_matrix(&m);
  s21_remove_matrix(&expected);
}
END_TEST
START_TEST(test_identity_matrix) {
  matrix_t m = {0};
  matrix_t expected = {0};
  int code1 = s21_create_matrix(3, 3, &m);
  int code2 = s21_create_matrix(3, 3, &expected);

  if (!code1 && !code2) {
    m.matrix[0][0] = 1;
    m.matrix[1][1] = 1;
    m.matrix[2][2] = 1;

    expected.matrix[0][0] = 1;
    expected.matrix[0][1] = 0;
    expected.matrix[0][2] = 0;

    expected.matrix[1][0] = 0;
    expected.matrix[1][1] = 1;
    expected.matrix[1][2] = 0;

    expected.matrix[2][0] = 0;
    expected.matrix[2][1] = 0;
    expected.matrix[2][2] = 1;

    matrix_t result = {0};
    int code = s21_calc_complements(&m, &result);
    ck_assert_int_eq(s21_eq_matrix(&result, &expected), 1);
    ck_assert_int_eq(code, 0);
    s21_remove_matrix(&result);
  }
  s21_remove_matrix(&m);
  s21_remove_matrix(&expected);
}
END_TEST

START_TEST(test_symmetric_matrix) {
  matrix_t m = {0};
  matrix_t expected = {0};
  int code1 = s21_create_matrix(3, 3, &m);
  int code2 = s21_create_matrix(3, 3, &expected);

  if (!code1 && !code2) {
    m.matrix[0][0] = 1;
    m.matrix[0][1] = 2;
    m.matrix[0][2] = 3;

    m.matrix[1][0] = 2;
    m.matrix[1][1] = 4;
    m.matrix[1][2] = 5;

    m.matrix[2][0] = 3;
    m.matrix[2][1] = 5;
    m.matrix[2][2] = 6;

    expected.matrix[0][0] = -1;
    expected.matrix[0][1] = 3;
    expected.matrix[0][2] = -2;

    expected.matrix[1][0] = 3;
    expected.matrix[1][1] = -3;
    expected.matrix[1][2] = 1;

    expected.matrix[2][0] = -2;
    expected.matrix[2][1] = 1;
    expected.matrix[2][2] = 0;

    matrix_t result = {0};
    int code = s21_calc_complements(&m, &result);
    ck_assert_int_eq(s21_eq_matrix(&result, &expected), 1);
    ck_assert_int_eq(code, 0);
    s21_remove_matrix(&result);
  }
  s21_remove_matrix(&m);
  s21_remove_matrix(&expected);
}
END_TEST
START_TEST(test_large_matrix) {
  matrix_t m = {0};
  matrix_t expected = {0};
  int code1 = s21_create_matrix(4, 4, &m);
  int code2 = s21_create_matrix(4, 4, &expected);

  if (!code1 && !code2) {
    m.matrix[0][0] = 4;
    m.matrix[0][1] = 2;
    m.matrix[0][2] = 8;
    m.matrix[0][3] = 6;

    m.matrix[1][0] = 1;
    m.matrix[1][1] = 5;
    m.matrix[1][2] = 3;
    m.matrix[1][3] = 9;

    m.matrix[2][0] = 7;
    m.matrix[2][1] = 0;
    m.matrix[2][2] = 2;
    m.matrix[2][3] = 4;

    m.matrix[3][0] = 6;
    m.matrix[3][1] = 8;
    m.matrix[3][2] = 1;
    m.matrix[3][3] = 3;

    expected.matrix[0][0] = -38;
    expected.matrix[0][1] = 34;
    expected.matrix[0][2] = 487;
    expected.matrix[0][3] = -177;

    expected.matrix[1][0] = -164;
    expected.matrix[1][1] = 2;
    expected.matrix[1][2] = -214;
    expected.matrix[1][3] = 394;

    expected.matrix[2][0] = 342;
    expected.matrix[2][1] = -306;
    expected.matrix[2][2] = -258;
    expected.matrix[2][3] = 218;

    expected.matrix[3][0] = 112;
    expected.matrix[3][1] = 334;
    expected.matrix[3][2] = 12;
    expected.matrix[3][3] = -202;

    matrix_t result = {0};
    int code = s21_calc_complements(&m, &result);
    ck_assert_int_eq(s21_eq_matrix(&result, &expected), 1);
    ck_assert_int_eq(code, 0);
    s21_remove_matrix(&result);
  }
  s21_remove_matrix(&m);
  s21_remove_matrix(&expected);
}
END_TEST

START_TEST(test_mixed_values) {
  matrix_t m = {0};
  matrix_t expected = {0};
  int code1 = s21_create_matrix(3, 3, &m);
  int code2 = s21_create_matrix(3, 3, &expected);

  if (!code1 && !code2) {
    m.matrix[0][0] = -25.53;
    m.matrix[0][1] = 28.29;
    m.matrix[0][2] = -18.96;

    m.matrix[1][0] = 17.10;
    m.matrix[1][1] = 17.15;
    m.matrix[1][2] = 16.13;

    m.matrix[2][0] = 7.57;
    m.matrix[2][1] = -14.21;
    m.matrix[2][2] = 16.00;

    expected.matrix[0][0] = 503.6073;
    expected.matrix[0][1] = -151.4959;
    expected.matrix[0][2] = -372.8165;

    expected.matrix[1][0] = -183.2184;
    expected.matrix[1][1] = -264.9528;
    expected.matrix[1][2] = -148.626;

    expected.matrix[2][0] = 781.4817;
    expected.matrix[2][1] = 87.5829;
    expected.matrix[2][2] = -921.5985;

    matrix_t result = {0};
    int code = s21_calc_complements(&m, &result);
    ck_assert_int_eq(s21_eq_matrix(&result, &expected), 1);
    ck_assert_int_eq(code, 0);
    s21_remove_matrix(&result);
  }
  s21_remove_matrix(&m);
  s21_remove_matrix(&expected);
}
END_TEST

START_TEST(test_floating_point_values) {
  matrix_t m = {0};
  matrix_t expected = {0};
  int code1 = s21_create_matrix(2, 2, &m);
  int code2 = s21_create_matrix(2, 2, &expected);

  if (!code1 && !code2) {
    m.matrix[0][0] = 1.5;
    m.matrix[0][1] = 0.2;

    m.matrix[1][0] = 0.8;
    m.matrix[1][1] = 2.0;

    expected.matrix[0][0] = 2.0;
    expected.matrix[0][1] = -0.8;

    expected.matrix[1][0] = -0.2;
    expected.matrix[1][1] = 1.5;

    matrix_t result = {0};
    int code = s21_calc_complements(&m, &result);
    ck_assert_int_eq(s21_eq_matrix(&result, &expected), 1);
    ck_assert_int_eq(code, 0);
    s21_remove_matrix(&result);
  }
  s21_remove_matrix(&m);
  s21_remove_matrix(&expected);
}
END_TEST

START_TEST(test_singular_matrix) {
  matrix_t m = {0};
  matrix_t expected = {0};
  int code1 = s21_create_matrix(3, 3, &m);
  int code2 = s21_create_matrix(3, 3, &expected);

  if (!code1 && !code2) {
    /* Вырожденная матрица (все строки пропорциональны) */
    m.matrix[0][0] = 1.0;
    m.matrix[0][1] = 2.0;
    m.matrix[0][2] = 3.0;

    m.matrix[1][0] = 2.0;
    m.matrix[1][1] = 4.0;
    m.matrix[1][2] = 6.0;

    m.matrix[2][0] = 3.0;
    m.matrix[2][1] = 6.0;
    m.matrix[2][2] = 9.0;

    /* Ожидаемые алгебраические дополнения (все нули, так как матрица
     * вырожденная) */
    for (int i = 0; i < 3; ++i) {
      for (int j = 0; j < 3; ++j) {
        expected.matrix[i][j] = 0.0;
      }
    }

    matrix_t result = {0};
    int code = s21_calc_complements(&m, &result);
    ck_assert_int_eq(s21_eq_matrix(&result, &expected), 1);
    ck_assert_int_eq(code, 0);
    s21_remove_matrix(&result);
  }
  s21_remove_matrix(&m);
  s21_remove_matrix(&expected);
}
END_TEST

Suite *suite_complements(void) {
  Suite *s = suite_create("suite_complements");
  TCase *tc = tcase_create("case_complements");
  tcase_add_test(tc, test_normal);
  tcase_add_test(tc, test_all);
  tcase_add_test(tc, test_not_sqare);
  tcase_add_test(tc, test_incorrect);
  tcase_add_test(tc, test_zero_matrix);
  tcase_add_test(tc, test_identity_matrix);
  tcase_add_test(tc, test_symmetric_matrix);
  tcase_add_test(tc, test_large_matrix);
  tcase_add_test(tc, test_mixed_values);
  tcase_add_test(tc, test_floating_point_values);
  tcase_add_test(tc, test_singular_matrix);
  suite_add_tcase(s, tc);
  return s;
}
