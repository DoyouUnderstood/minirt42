#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct {
    int rows;
    int cols;
    double** data;
} Matrix;

double calculateDeterminant2x2(double matrix[2][2]) {
    return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
}

double minor(double matrix[3][3], int row, int column) {
    double submatrix[2][2];
    int subi = 0;
    for (int i = 0; i < 3; i++) {
        if (i == row) continue;
        int subj = 0;
        for (int j = 0; j < 3; j++) {
            if (j == column) continue;
            submatrix[subi][subj] = matrix[i][j];
            subj++;
        }
        subi++;
    }
    return calculateDeterminant2x2(submatrix);
}

//fonction pour faire des submatrix

Matrix createSubmatrix(Matrix original, int excludeRow, int excludeCol) 
{
    Matrix sub;
    sub.rows = original.rows - 1;
    sub.cols = original.cols - 1;
    sub.data = malloc(sub.rows * sizeof(double*));

    for (int i = 0; i < sub.rows; ++i) {
        sub.data[i] = malloc(sub.cols * sizeof(double));
    }
    for (int i = 0, row = 0; i < original.rows; ++i) {
        if (i == excludeRow) 
            continue;

        for (int j = 0, col = 0; j < original.cols; ++j) {
            if (j == excludeCol) 
                continue;
            sub.data[row][col] = original.data[i][j];
            ++col;
        }
        ++row;
    }
    return (sub);
}

//calcul le cofacteur d'une matrix 3x3
double cofactor(double matrix[3][3], int row, int column) 
{
    double minorValue = minor(matrix, row, column);
    double cofactorValue;
    if ((row + column) % 2 == 0)
        cofactorValue = minorValue;
    else
        cofactorValue = -minorValue;
    return (cofactorValue);
}

// calcul le determinant d'une matrix 3x3
double determinant3x3(double matrix[3][3]) {
    double det = 0.0;
    for (int col = 0; col < 3; col++) {
        det += matrix[0][col] * cofactor(matrix, 0, col);
    }
    return det;
}

void getSubMatrix(double original[4][4], double subMatrix[3][3], int excludeRow, int excludeCol) {
    int row = 0;
    for (int i = 0; i < 4; i++) {
        if (i == excludeRow) 
            continue;
        int col = 0;
        for (int j = 0; j < 4; j++) {
            if (j == excludeCol) 
                continue;
            subMatrix[row][col] = original[i][j];
            col++;
        }
        row++;
    }
}

double determinant4x4(double matrix[4][4]) 
{
    double det = 0.0;
    for (int col = 0; col < 4; col++) 
    {
        double subMatrix[3][3];
        // Exclure la ligne 0 et la colonne `col` pour créer la sous-matrice 3x3
        getSubMatrix(matrix, subMatrix, 0, col);
        // Calculer le mineur de l'élément
        double minor = determinant3x3(subMatrix);
        // Calculer le cofacteur
        double cofactor = ((0 + col) % 2 == 0 ? 1 : -1) * minor;
        // Ajouter au déterminant total
        det += matrix[0][col] * cofactor;
    }
    return det;
}

// int main() {
//     double matrix4x4[4][4] = {
//         {-2, -8, 3, 5},
//         {-3, 1, 7, 3},
//         {1, 2, -9, 6},
//         {-6, 7, 7, -9}
//     };
//     double subMatrix[3][3];
//     getSubMatrix(matrix4x4, subMatrix, 1, 1); // Exemple d'extraction de sous-matrice
//     double det = determinant3x3(subMatrix); // Calcul du déterminant de la sous-matrice
//     printf("Le déterminant de la sous-matrice est: %f\n", det);
//     return 0;
// }


