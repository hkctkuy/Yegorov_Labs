#include <stdio.h>
#include <stdlib.h>
// Made by hkctkuy (Ilya Yegorov)
float **allocate_matrix(int n, int m) {  // Allocate memory for matrix

    float **matrix; int i;

    matrix = malloc(n * sizeof(float *));  // Memory allocation for matrix

    for (i = 0; i < n; i++) {

        matrix[i] = malloc(m * sizeof(float));
    }
    return matrix;
}

float **get_matrix(int n, int m) {  // Creat matrix with size n * m and return adress

    float **matrix; int i, j, NaN = 0;

    printf("%s%d%s%d%s\n", "Input your matrix (", n, "*", m, "): ");

    matrix = allocate_matrix(n, m);

    for (i = 0; i < n; i++) {

        for (j = 0; j < m; j++) {

            char ch, input_stream[256] = {'\0'}; int size = 0;  // Сhecking for correctness of input ("Проверка на дурака/full checking")

            while ((ch = getchar()) != ' ' && ch != '\n') {

                input_stream[size++] = ch;
            }
            NaN = sscanf(input_stream, "%f", &matrix[i][j]) != 1;

            if (NaN) {

                break;
            }
        }
        if(NaN) {

            break;
        }
    }
    if(NaN) {  // Clean memory if input isn't correct

      for (i = 0; i < n; i++) {

          free(matrix[i]);
      }
      free(matrix);

      printf("%s\n", "Error: Not a number");

      matrix = 0;
    }

    return matrix;
}

void matrix_scalar_multiplication (float **matrix, int n, int m, float scalar) {  // Multiply matrix with size n * m by scalar

    int i, j;

    for (i = 0; i < n; i++) {

        for (j = 0; j < m; j++) {

            matrix[i][j] *= scalar;
        }
    }
    return;
}

float **matrix_multiplication(float **matrix1, int n1, int m1, float **matrix2, int n2, int m2) {

    float **result_matrix; int i, j, k;

    if (m1 != n2) {

        printf("%s\n", "Error: Can't multiply matrices with such sizes");

        return 0;
    }

    result_matrix = allocate_matrix(n1, m2);

    for (i = 0; i < n1; i++) {

        for (j = 0; j < m2; j++) {

            for (k = 0; k < m1; k++) {

                result_matrix[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }
    return result_matrix;
}

void swap_matrix_string(float **string1, float **string2) {  //Swap strings in matrix

    float *tmp;

    tmp = *string1; *string1 = *string2; *string2 = tmp;

    return;
}
void gaussian_elemntion(float **matrix, int n) {  // Confirm Gaussian elimination for square matrix and remember all transformations

    int i, j, k;

    for (j = 0; j < n; j++) {

        for (i = j; i < n; i++) {  // Putting a nonzero element on the diagonal (if possible)

            if (matrix[i][j] != 0) {

                swap_matrix_string(&matrix[i], &matrix[j]);

                break;
            }
        }
        if (matrix[j][j] != 0) {  // Zeroing the rest of the lines

            for (i = j + 1; i < n; i++) {

                float coefficient = matrix[i][j];

                for(k = j; k < n; k++) {

                    matrix[i][k] -= coefficient / matrix[j][j] * matrix[j][k];
                }
            }
        }
    }
    return;
}

float det(float **matrix, int n, int m) {  // Calculate the determinant of a matrix (Gaussian elimination)

    if (n != m) {

        printf("%s\n", "Error: Matrix is not square");

        return 0;
    }
    float determinant = 1; int i;

    gaussian_elemntion(matrix, n);

    for (i = 0; i < n; i++) {

        determinant *= matrix[i][i];
    }

    return determinant;
}
void print_matrix(float **matrix, int n, int m) {  // Print matrix with size n * m

    int i, j;

    for (i = 0; i < n; i++) {

      for (j = 0; j < m; j++) {

          printf("%f%c", matrix[i][j], ' ');
      }
      printf("\n");
    }
    return;
}
