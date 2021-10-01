#include <stdio.h>
#include <stdlib.h>
// Made by hkctkuy (Ilya Yegorov)
float **allocate_matrix(int row_size, int column_size) {  // Allocate memory for matrix

    float **matrix; int i;

    matrix = malloc(row_size * sizeof(float *));  // Memory allocation for matrix

    for (i = 0; i < row_size; i++) {

        matrix[i] = malloc(column_size * sizeof(float));
    }
    return matrix;
}

float **get_matrix(int row_size, int column_size) {  // Creat matrix with size n * m and return adress

    float **matrix; int i, j, NaN = 0;

    printf("%s%d%s%d%s\n", "Input your matrix (", row_size, "*", column_size, "): ");

    matrix = allocate_matrix(row_size, column_size);

    for (i = 0; i < row_size; i++) {

        for (j = 0; j < column_size; j++) {

            char charcacter, input_stream[256] = {'\0'}; int size = 0;  // Сhecking for correctness of input ("Проверка на дурака/full checking")

            while ((charcacter = getchar()) != ' ' && charcacter != '\n') {

                input_stream[size++] = charcacter;
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

      for (i = 0; i < row_size; i++) {

          free(matrix[i]);
      }
      free(matrix);

      printf("%s\n", "Error: Not a number");

      matrix = 0;
    }

    return matrix;
}

void matrix_scalar_multiplication (float **matrix, int row_size, int column_size, float scalar) {  // Multiply matrix with size n * m by scalar

    int i, j;

    for (i = 0; i < row_size; i++) {

        for (j = 0; j < column_size; j++) {

            matrix[i][j] *= scalar;
        }
    }
    return;
}

float **matrix_multiplication(float **matrix1, int row_size_1, int column_size_1, float **matrix2, int row_size_2, int column_size_2) {

    float **result_matrix; int i, j, k;

    if (column_size_1 != row_size_2) {

        printf("%s\n", "Error: Can't multiply matrices with such sizes");

        return 0;
    }

    result_matrix = allocate_matrix(row_size_1, column_size_2);

    for (i = 0; i < row_size_1; i++) {

        for (j = 0; j < column_size_2; j++) {

            for (k = 0; k < column_size_1; k++) {

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
void gaussian_elemntion(float **matrix, int row_size) {  // Confirm Gaussian elimination for square matrix and remember all transformations

    int i, j, k;

    for (j = 0; j < row_size; j++) {

        for (i = j; i < row_size; i++) {  // Putting a nonzero element on the diagonal (if possible)

            if (matrix[i][j] != 0) {

                swap_matrix_string(&matrix[i], &matrix[j]);

                break;
            }
        }
        if (matrix[j][j] != 0) {  // Zeroing the rest of the lines

            for (i = j + 1; i < row_size; i++) {

                float coefficient = matrix[i][j];

                for(k = j; k < row_size; k++) {

                    matrix[i][k] -= coefficient / matrix[j][j] * matrix[j][k];
                }
            }
        }
    }
    return;
}

float det(float **matrix, int row_size, int column_size) {  // Calculate the determinant of a matrix (Gaussian elimination)

    if (row_size != column_size) {

        printf("%s\n", "Error: Matrix is not square");

        return 0;
    }
    float determinant = 1; int i;

    gaussian_elemntion(matrix, row_size);

    for (i = 0; i < row_size; i++) {

        determinant *= matrix[i][i];
    }

    return determinant;
}
void print_matrix(float **matrix, int row_size, int column_size) {  // Print matrix with size n * m

    int i, j;

    for (i = 0; i < row_size; i++) {

      for (j = 0; j < column_size; j++) {

          printf("%f%c", matrix[i][j], ' ');
      }
      printf("\n");
    }
    return;
}
