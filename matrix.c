#include <stdio.h>

#define MAX_SIZE 10 

typedef int Matrix[MAX_SIZE][MAX_SIZE];


//scalar multiplication function
void scalar_multiply(Matrix result, Matrix m, int rows, int cols, int k) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result[i][j] = k * m[i][j];
        }
    }
}

//transpose of a matrix funtion
void transpose(Matrix result, Matrix m, int rows, int cols) {
    for (int i = 0; i < cols; i++) {
        for (int j = 0; j < rows; j++) {
            result[i][j] = m[j][i];
        }
    }
}

//matrix multiplication function
void multiply(Matrix result, Matrix m1, int m1_rows, int m1_cols, Matrix m2, int m2_rows, int m2_cols) {
    for (int i = 0; i < m1_rows; i++) {
        for (int j = 0; j < m2_cols; j++) {
            result[i][j] = 0;
            for (int k = 0; k < m1_cols; k++) {
                result[i][j] += m1[i][k] * m2[k][j];
            }
        }
    }
}

//matrix addition
void add(Matrix result, Matrix m1, int rows, int cols, Matrix m2) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result[i][j] = m1[i][j] + m2[i][j];
        }
    }
}

//setting the matrix values function
void set_matrix(Matrix matrix, int rows, int cols, int values[]) {
    int k = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = values[k++];
        }
    }
}


//function to print a matrix
void print_matrix(const Matrix matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

int main() {
    Matrix A, B, C, temp1, transposed, temp2, D;
    int aRows = 2, aCols = 2;
    int bRows = 2, bCols = 3;
    int cRows = 2, cCols = 3;

    int a_values[] = {6, 4, 8, 3};
    set_matrix(A, aRows, aCols, a_values);

    int b_values[] = {1, 2, 3, 4, 5, 6};
    set_matrix(B, bRows, bCols, b_values);

    int c_values[] = {2, 4, 6, 1, 3, 5};
    set_matrix(C, cRows, cCols, c_values);

    scalar_multiply(temp1, B, bRows, bCols, 3);
    transpose(transposed, C, cRows, cCols);
    multiply(temp2, temp1, bRows, bCols, transposed, cCols, cRows);
    add(D, A, aRows, aCols, temp2);

    print_matrix(D, aRows, aCols);

    return 0;
}