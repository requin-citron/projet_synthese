#ifndef VECTOR_UTIL_H
#define VECTOR_UTIL_H
#include <stdio.h>
#include <math.h>


//structure de point
typedef struct{
  float x;
  float y;
  float z;
} point;

//structure vector
typedef struct{
  float x;
  float y;
  float z;
} vecteur;

//structure matrice
typedef struct{
  vecteur v[3];
} matrix_base;

//hack 1/sqrt(x)
float Q_rsqrt( float  );
void normalize(vecteur* );
vecteur produit_vectoriel(vecteur , vecteur );
vecteur scale(vecteur , float );
float produit_scalaire(vecteur , vecteur );
matrix_base create_base(point , point );
vecteur add_vect(vecteur , vecteur );
point change_base(float , float , float , matrix_base );
#endif
