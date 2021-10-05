#include <stdio.h>
#include "matrixlib.h"
// Made by hkctkuy (Ilya Yegorov)

int main() {

    float **matrix1, **matrix2, **matrix3, scalar; int row_size_1, column_size_1, row_size_2, column_size_2; char charcacter;

    printf("%s", "Input size of your matrix (num_of_col num_of_str): ");

    scanf("%d%d%c", &row_size_1, &column_size_1, &charcacter);

    matrix1 = get_matrix(row_size_1, column_size_1);

    if (matrix1 != 0) {

        print_matrix(matrix1, row_size_1, column_size_1);
    }

    printf("%s", "Input scalar: ");

    scanf("%f", &scalar);

    matrix_scalar_multiplication(matrix1, row_size_1, column_size_1, scalar);

    if (matrix1 != 0) {

        print_matrix(matrix1, row_size_1, column_size_1);
    }
    printf("%s", "Input size of your matrix (num_of_col num_of_str): ");

    scanf("%d%d%c", &row_size_2, &column_size_2, &charcacter);

    matrix2 = get_matrix(row_size_2, column_size_2);

    matrix3 = matrix_multiplication(matrix1, row_size_1, column_size_1, matrix2, row_size_2, column_size_2);

    if (matrix3 != 0) {

        print_matrix(matrix3, row_size_1, column_size_2);
    }

    printf("%f\n", det(matrix1, row_size_1, column_size_1));

    print_matrix(matrix1, row_size_1, column_size_1);

    return 0;
}
