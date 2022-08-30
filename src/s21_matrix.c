#include "s21_matrix.h"

/* void print(matrix_t s_matrix) {
  for (int x = 0; x < s_matrix.rows; x++) {
    for (int y = 0; y < s_matrix.columns; y++) {
      printf("% 10lf ", s_matrix.matrix[x][y]);
    }
    printf("\n");
  }
  printf("\n");
} */

/*
  Проверка матрицы
  0 - Корректная матрица
  1 - Некорректная матрица
*/
int s21_check_matrix(matrix_t A) {
  int type;
  if (A.rows < 1 || A.columns < 1 || !A.matrix) {
    type = 1;
  } else {
    type = 0;
  }
  return type;
}

/*
    Создание матриц
    0 - OK
    1 - Ошибка, некорректная матрица
    2 - Ошибка вычисления (несовпадающие размеры матриц;
    матрица, для которой нельзя провести вычисления и т.д.)
*/
int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int res = 1;
  result->matrix = NULL;
  result->rows = 0;
  result->columns = 0;

  if (rows > 0 && columns > 0) {
    result->matrix = (double **)calloc(rows, sizeof(double *));
    if (result->matrix != NULL) {
      for (int i = 0; i < rows; i++) {
        result->matrix[i] = (double *)calloc(columns, sizeof(double));
      }
      result->rows = rows;
      result->columns = columns;
      res = 0;
    }
  }

  return res;
}

/* Очистка матриц */
void s21_remove_matrix(matrix_t *A) {
  if (A->matrix) {
    if (A->rows > 0) {
      for (int i = 0; i < A->rows; i++) {
        if (A->matrix[i]) free(A->matrix[i]);
      }
      free(A->matrix);
    }
  }
  A->rows = 0;
  A->columns = 0;
  A->matrix = NULL;
}

/*
    Сравнение матриц
    SUCCESS 1
    FAILURE 0
*/
int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int type_A = s21_check_matrix(*A);
  int type_B = s21_check_matrix(*B);
  int res = SUCCESS;
  if (type_A == 1 || type_B == 1) {
    res = FAILURE;
  } else if (A->rows != B->rows || A->columns != B->columns) {
    res = FAILURE;
  } else {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        if (A->matrix[i][j] * B->matrix[i][j] < 0) {
          res = FAILURE;
          break;
        }
        if (fabs(A->matrix[i][j] - B->matrix[i][j]) > EPS) {
          res = FAILURE;
          break;
        }
      }
      if (!res) break;
    }
  }
  return res;
}

/*
    Сложение матриц
    0 - OK
    1 - Ошибка, некорректная матрица
    2 - Ошибка вычисления (несовпадающие размеры матриц;
    матрица, для которой нельзя провести вычисления и т.д.)
*/
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int type_A = s21_check_matrix(*A);
  int type_B = s21_check_matrix(*B);

  int res = 1;
  if (type_A == 1 || type_B == 1) {
    res = 1;
  } else if (A->rows != B->rows || A->columns != B->columns) {
    res = 2;
  } else {
    if (s21_create_matrix(A->rows, A->columns, result) == 0) {
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
        }
      }
      res = 0;
    }
  }
  return res;
}

/*
    Вычитание матриц
    0 - OK
    1 - Ошибка, некорректная матрица
    2 - Ошибка вычисления (несовпадающие размеры матриц;
    матрица, для которой нельзя провести вычисления и т.д.)
*/
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int type_A = s21_check_matrix(*A);
  int type_B = s21_check_matrix(*B);

  int res = 1;
  if (type_A == 1 || type_B == 1) {
    res = 1;
  } else if (A->rows != B->rows || A->columns != B->columns) {
    res = 2;
  } else {
    if (s21_create_matrix(A->rows, A->columns, result) == 0) {
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
        }
      }
      res = 0;
    }
  }
  return res;
}

/*
    Умножение матрицы на число
    0 - OK
    1 - Ошибка, некорректная матрица
    2 - Ошибка вычисления (несовпадающие размеры матриц;
    матрица, для которой нельзя провести вычисления и т.д.)
*/
int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  int type_A = s21_check_matrix(*A);
  int res = 1;
  if (type_A == 0 && s21_create_matrix(A->rows, A->columns, result) == 0) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[i][j] = A->matrix[i][j] * number;
      }
    }
    res = 0;
  }
  return res;
}

/*
    Умножение матриц
    0 - OK
    1 - Ошибка, некорректная матрица
    2 - Ошибка вычисления (несовпадающие размеры матриц;
    матрица, для которой нельзя провести вычисления и т.д.)
*/
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int type_A = s21_check_matrix(*A);
  int type_B = s21_check_matrix(*B);
  int res = 1;
  if (type_A || type_B) {
    res = 1;
  } else if (A->columns != B->rows) {
    res = 2;
  } else {
    if (s21_create_matrix(A->rows, B->columns, result) == 0) {
      for (int i = 0; i < A->rows; i++) {
        for (int k = 0; k < A->columns; k++) {
          for (int j = 0; j < B->columns; j++) {
            result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
          }
        }
      }
      res = 0;
    }
  }
  return res;
}

/*
    Транспонирование матрицы
    0 - OK
    1 - Ошибка, некорректная матрица
    2 - Ошибка вычисления (несовпадающие размеры матриц;
    матрица, для которой нельзя провести вычисления и т.д.)
*/
int s21_transpose(matrix_t *A, matrix_t *result) {
  int type_A = s21_check_matrix(*A);
  int res = 1;
  if (type_A == 0 && s21_create_matrix(A->columns, A->rows, result) == 0) {
    for (int j = 0; j < A->columns; j++) {
      for (int i = 0; i < A->rows; i++) {
        result->matrix[j][i] = A->matrix[i][j];
      }
    }
    res = 0;
  }
  return res;
}

/*
    Меняем строки матрицы местами
*/
int s21_change_rows(matrix_t *tri, int k) {
  int flag = 0;
  int i = k + 1;
  double temp;
  while (!tri->matrix[k][k] && i < tri->rows) {
    for (int j = k; j < tri->columns; j++) {
      temp = tri->matrix[k][j];
      tri->matrix[k][j] = tri->matrix[i][j];
      tri->matrix[i][j] = -temp;
      if (tri->matrix[k][k]) flag = 1;
    }
    if (flag) break;
    i++;
  }
  return flag;
}

/*
    Приведение матрицы
    к верхнетреугольному виду
    и вычисление определителя
*/
double s21_triangle(matrix_t *temp) {
  int size = temp->rows;
  int flag = 1;
  double res = 1;

  for (int k = 0; k < size - 1; k++) {
    if (!temp->matrix[k][k]) {
      flag = s21_change_rows(temp, k);
    }
    if (!flag) {
      res = 0;
      break;
    } else {
      for (int i = k + 1; i < size; i++) {
        double kkk = temp->matrix[i][k];
        if (kkk) {
          for (int j = k; j < size; j++) {
            temp->matrix[i][j] = temp->matrix[i][j] -
                                 temp->matrix[k][j] * kkk / temp->matrix[k][k];
          }
        }
      }
    }
  }
  if (res) {
    for (int i = 0; i < size; i++) {
      res *= temp->matrix[i][i];
    }
  }

  return res;
}

/*
  Нахождение значения минора матрицы
*/
double s21_minor(matrix_t *A, int x, int y) {
  double res = 0;
  int size = A->rows;
  matrix_t temp;

  s21_create_matrix(size - 1, size - 1, &temp);
  int a = 0, b = 0;
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      if (i != x && j != y) {
        temp.matrix[a][b++] = A->matrix[i][j];
        if (b == (size - 1)) {
          a++;
          b = 0;
        }
      }
    }
  }
  if (temp.rows == 2) {
    res = temp.matrix[0][0] * temp.matrix[1][1] -
          temp.matrix[0][1] * temp.matrix[1][0];
  } else {
    res = s21_triangle(&temp);
  }
  s21_remove_matrix(&temp);
  return res;
}

/*
    Создание матрицы алгебраических дополнений
    0 - OK
    1 - Ошибка, некорректная матрица
    2 - Ошибка вычисления (несовпадающие размеры матриц;
    матрица, для которой нельзя провести вычисления и т.д.)
*/
int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int res = 1;
  int type_A = s21_check_matrix(*A);
  if (type_A) {
    res = 1;
  } else if (type_A == 0 && A->rows != A->columns) {
    res = 2;
  } else if (s21_create_matrix(A->rows, A->columns, result) == 0) {
    int size = A->rows;
    if (size == 1) {
      result->matrix[0][0] = 1;
    } else if (size == 2) {
      result->matrix[0][0] = A->matrix[1][1];
      result->matrix[0][1] = -A->matrix[1][0];
      result->matrix[1][0] = -A->matrix[0][1];
      result->matrix[1][1] = A->matrix[0][0];
    } else {
      for (int i = 0; i < result->rows; i++) {
        for (int j = 0; j < result->columns; j++) {
          result->matrix[i][j] = s21_minor(A, i, j) * pow(-1, (i + j));
        }
      }
    }
    res = 0;
  }
  return res;
}

/*
    Нахождение детерминанта матрицы
    0 - OK
    1 - Ошибка, некорректная матрица
    2 - Ошибка вычисления (несовпадающие размеры матриц;
    матрица, для которой нельзя провести вычисления и т.д.)
*/
int s21_determinant(matrix_t *A, double *result) {
  int res = 1;
  int type_A = s21_check_matrix(*A);
  if (type_A) {
    res = 1;
  } else if (type_A == 0 && A->rows != A->columns) {
    res = 2;
  } else {
    matrix_t temp;

    *result = 0;
    s21_calc_complements(A, &temp);
    for (int i = 0; i < A->rows; i++) {
      *result += A->matrix[0][i] * temp.matrix[0][i];
    }
    s21_remove_matrix(&temp);
    res = 0;
  }

  return res;
}

/*
    Создание обратной матрицы
    0 - OK
    1 - Ошибка, некорректная матрица
    2 - Ошибка вычисления (несовпадающие размеры матриц;
    матрица, для которой нельзя провести вычисления и т.д.)
*/
int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  int res = 1;
  int type_A = s21_check_matrix(*A);
  if (type_A) {
    res = 1;
  } else if (type_A == 0 && A->rows != A->columns) {
    res = 2;
  } else {
    matrix_t temp;
    double det = 0;
    s21_determinant(A, &det);
    if (fabs(det) < EPS) {
      res = 2;
    } else {
      s21_calc_complements(A, &temp);
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          temp.matrix[i][j] /= det;
        }
      }
      s21_transpose(&temp, result);
      s21_remove_matrix(&temp);
      res = 0;
    }
  }
  return res;
}
