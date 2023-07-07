# matrix.h

Реализация библиотеки matrix.h.


### Структура матрицы на языке C:

```c
typedef struct matrix_struct {
    double** matrix;
    int rows;
    int columns;
} matrix_t;
```

## Операции над матрицами

Все операции (кроме сравнения матриц) должны возвращать результирующий код:  
- 0 - OK
- 1 - Ошибка, некорректная матрица   
- 2 - Ошибка вычисления (несовпадающие размеры матриц; матрица, для которой нельзя провести вычисления и т.д.)

### Создание матриц (create_matrix)

```c
int  create_matrix(int rows, int columns, matrix_t *result);
```

### Очистка матриц (remove_matrix)

```c
void  remove_matrix(matrix_t *A);
```

### Сравнение матриц (eq_matrix)

```c
#define SUCCESS 1
#define FAILURE 0

int  eq_matrix(matrix_t *A, matrix_t *B);
```

### Сложение (sum_matrix) и вычитание матриц (sub_matrix)

```c
int  sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int  sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
```

### Умножение матрицы на число (mult_number). Умножение двух матриц (mult_matrix)

```c
int  mult_number(matrix_t *A, double number, matrix_t *result);
int  mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
```

### Транспонирование матрицы (transpose)

```c
int  transpose(matrix_t *A, matrix_t *result);
```

### Минор матрицы и матрица алгебраических дополнений (calc_complements)

```c
int  calc_complements(matrix_t *A, matrix_t *result);
```

### Определитель матрицы (determinant)

```c
int  determinant(matrix_t *A, double *result);
```

### Обратная матрица (inverse_matrix)

```c
int  inverse_matrix(matrix_t *A, matrix_t *result);
```

