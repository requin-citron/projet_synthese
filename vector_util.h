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
} vector;

//structure matrice
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
