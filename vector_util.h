#ifndef VECTOR_UTIL_H
#define VECTOR_UTIL_H
#include <stdio.h>
#include <math.h>


//structure de point
//! structure point
/*!
  structure de point ayant trois composantes x y et z
  les trois composante sont des float
*/
typedef struct{
  float x;
  float y;
  float z;
} point;

//structure vector
//! structure  vecteur
/*!
  structure de vecteur qui prend trois composantes x y et z
  les trois composantes sont des float
*/
typedef struct{
  float x;
  float y;
  float z;
} vector;

//structure matrice
//!structure de matrice
/*!
  la mtrice  a un seule membre qui est un tableau de 3 vecteur
  donc la matrice est représenté avec ses trois vecteur **colonnes**
*/
typedef struct{
  vector v[3];
} matrix;

//hack 1/sqrt(x)
float Q_rsqrt( float  );
void normalize(vector* );
vector produit_vectoriel(vector *, vector *);
vector scale(vector *, float);
float produit_scalaire(vector *, vector *);
matrix create_base(point , point );
vector add_vect(vector *, vector *);
point change_base(float , float , float , matrix *);
void matrix_zero(matrix *);
void matrix_debug(matrix *);
void inverse_z(matrix *);
#endif
