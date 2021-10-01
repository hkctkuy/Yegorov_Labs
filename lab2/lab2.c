#include <stdio.h>
#include "matrixlib.h"
// Made by hkctkuy (Ilya Yegorov)

int main() {

    float **matrix1, **matrix2, **matrix3, scalar; int n1, m1, n2, m2; char charcacter;

    printf("%s", "Input size of your matrix (num_of_col num_of_str): ");

    scanf("%d%d%c", &n1, &m1, &charcacter);

    matrix1 = get_matrix(n1, m1);

    if (matrix1 != 0) {

        print_matrix(matrix1, n1, m1);
    }

    printf("%s", "Input scalar: ");

    scanf("%f", &scalar);

    matrix_scalar_multiplication(matrix1, n1, m1, scalar);

    if (matrix1 != 0) {

        print_matrix(matrix1, n1, m1);
    }
    printf("%s", "Input size of your matrix (num_of_col num_of_str): ");

    scanf("%d%d%c", &n2, &m2, &charcacter);

    matrix2 = get_matrix(n2, m2);

    matrix3 = matrix_multiplication(matrix1, n1, m1, matrix2, n2, m2);

    if (matrix3 != 0) {

        print_matrix(matrix3, n1, m2);
    }

    printf("%f\n", det(matrix1, n1, m1));

    print_matrix(matrix1, n1, m1);

    return 0;
}
