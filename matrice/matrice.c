#include <stdio.h>
#include <stdlib.h>
#include "../include/vecteur.h"
typedef struct 
{
    float m[4][4];
} Matrice4x4;

// Fonction pour initialiser une matrice 4x4 d'identite avec des 1 lors que i et j sont pareil. 0 sinon 
Matrice4x4 initMatriceIdentite() {
    Matrice4x4 matrice;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            matrice.m[i][j] = (i == j) ? 1.0f : 0.0f;
        }
    }
    return (matrice);
}

// Fonction d'affichage de matrice
void afficherMatrice(Matrice4x4 matrice) 
{
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            printf("%0.2f ", matrice.m[i][j]);
        }
        printf("\n");
    }
}

// Fonction pour multiplier deux matrices 4x4
Matrice4x4 multiplierMatrices(Matrice4x4 Ma, Matrice4x4 Mb) 
{
    Matrice4x4 resultat;
    int i;
    int j;
    int k;

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            resultat.m[i][j] = 0;
            for (k = 0; k < 4; k++) {
                resultat.m[i][j] += Ma.m[i][k] * Mb.m[k][j];
            }
        }
    }
    return resultat;
}

// Fonction qui determine si ce sont les memes matrices
int is_same_matrice(Matrice4x4 Ma, Matrice4x4 Mb)
{
    int i = 0;
    int j = 0;

    while (i < 4)
    {
        j = 0;
        while (j < 4)
        {
            if (Ma.m[i][j] != Mb.m[i][j])
                return (0);
            j++;
        }
        i++;
    }
    return (1);
}

// Fonction pour transposez une matrice, cad transformez ses lignes en colonnes et ses colonnes en lignes. (Utile pour l'ombrage)
Matrice4x4 transposeMatrix(Matrice4x4 mat) 
{
    Matrice4x4 transposed;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            transposed.m[j][i] = mat.m[i][j];
        }
    }
    return transposed;
}

//fonction pour multiplier les matrices
t_tuple multiplyMatrixByTuple(Matrice4x4 mat, t_tuple tup) {
    t_tuple result;

    result.x = mat.m[0][0] * tup.x + mat.m[0][1] * tup.y + mat.m[0][2] * tup.z + mat.m[0][3] * tup.w;
    result.y = mat.m[1][0] * tup.x + mat.m[1][1] * tup.y + mat.m[1][2] * tup.z + mat.m[1][3] * tup.w;
    result.z = mat.m[2][0] * tup.x + mat.m[2][1] * tup.y + mat.m[2][2] * tup.z + mat.m[2][3] * tup.w;
    result.w = mat.m[3][0] * tup.x + mat.m[3][1] * tup.y + mat.m[3][2] * tup.z + mat.m[3][3] * tup.w;

    return (result);
}

double determinant2x2(double a, double b, double c, double d) 
{
    return a * d - b * c;
}

// cet fonction prend deux t_tuple : un point p et un vecteur de translation transformation. 
// Elle retourne un nouveau t_tuple qui est le résultat de l'application de la translation au point.
t_tuple translate(t_tuple p, t_tuple translation) {
    t_tuple result = {
        p.x + translation.x,
        p.y + translation.y,
        p.z + translation.z,
        1.0 // Le résultat est toujours un point
    };
    return result;
}

// Fonction pour inverser une matrice de traduction
t_tuple inverseTranslation(t_tuple translation) {
    t_tuple inverse = {
        -translation.x,
        -translation.y,
        -translation.z,
        1.0
    };
    return inverse;
}

// Fonction pour appliquer une mise à l'échelle à un point ou un vecteur
t_tuple scale(t_tuple point, double sx, double sy, double sz) {
    // Appliquer les facteurs d'échelle sur chaque composante
    point.x *= sx;
    point.y *= sy;
    point.z *= sz;
    // La composante w reste inchangée car elle détermine si c'est un point ou un vecteur
    return point;
}

// Fonction pour refléter un point par rapport à un axe spécifié ('x', 'y' ou 'z')
t_tuple reflectPoint(t_tuple point, char axis) {
    switch (axis) {
        case 'x':
            point.x = -point.x;
            break;
        case 'y':
            point.y = -point.y;
            break;
        case 'z':
            point.z = -point.z;
            break;
        default:
            printf("Axe invalide. Choisissez 'x', 'y', ou 'z'.\n");
    }
    return point;
}

// int main() {
//     Matrice4x4 maMatrice = initMatriceIdentite();
//     // printf("%f\n", maMatrice.m[1][1]);
//     afficherMatrice(maMatrice);
//     return 0;
// }