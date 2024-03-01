#ifndef MATRIX_H
#define MATRIX_H


#include "vecteur.h"

typedef struct 
{
    float m[4][4];
} Matrice4x4;

Matrice4x4 initMatriceIdentite();
void afficherMatrice(Matrice4x4 matrice);
Matrice4x4 multiplierMatrices(Matrice4x4 Ma, Matrice4x4 Mb);
int is_same_matrice(Matrice4x4 Ma, Matrice4x4 Mb);
Matrice4x4 transposeMatrix(Matrice4x4 mat);
t_tuple multiplyMatrixByTuple(Matrice4x4 mat, t_tuple tup);
double determinant2x2(double a, double b, double c, double d);
t_tuple translate(t_tuple p, t_tuple translation);
t_tuple inverseTranslation(t_tuple translation);
t_tuple scale(t_tuple point, double sx, double sy, double sz);
t_tuple reflectPoint(t_tuple point, char axis);

#endif
