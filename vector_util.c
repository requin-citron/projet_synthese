#include "vector_util.h"



float Q_rsqrt( float number ){
	long i;
	float x2, y;
	const float threehalfs = 1.5F;

	x2 = number * 0.5F;
	y  = number;
	i  = * ( long * ) &y;                       // evil floating point bit level hacking
	i  = 0x5f3759df - ( i >> 1 );               // what the fuck?
	y  = * ( float * ) &i;
	y  = y * ( threehalfs - ( x2 * y * y ) );   // 1st iteration
//	y  = y * ( threehalfs - ( x2 * y * y ) );   // 2nd iteration, this can be removed
	return (float)y;
}

void normalize(vector* v){
  float norme = pow(v->x, 2) + pow(v->y, 2) + pow(v->z, 2);
  float magie = Q_rsqrt(norme);
  v->x *= magie;
  v->y *= magie;
  v->z *= magie;
}

vector produit_vectoriel(vector *v1, vector *v2){
  vector ret;
    ret.x = (v1->y*v2->z) - (v1->z*v2->y);
    ret.y = (v1->z*v2->x) - (v2->z*v1->x);
    ret.z = (v1->x*v2->y) - (v1->y*v2->x);
  return ret;
}

vector scale(vector *v1, float s){
  vector ret;
    ret.x = v1->x*s;
    ret.y = v1->y*s;
    ret.z = v1->z*s;
  return ret;
}

float produit_scalaire(vector *v1, vector *v2){
  return v1->x*v2->x + v1->y*v2->y + v1->z*v2->z;
}

//on crée une matisse de changement de base
// pour faire avoir une base orthogonal en p1

matrix create_base(point p1, point p2){
  p2.x-=p1.x;
  p2.y-=p1.y;
  p2.z-=p1.z;
  p1.x=0;
  p1.y=0;
  p1.z=0;
  vector vector_normal;
    vector_normal.x = p2.x - p1.x;
    vector_normal.y = p2.y - p1.y;
    vector_normal.z = p2.z - p1.z;

  vector vector_plan1;
    vector_plan1.x = (1./vector_normal.x);
    vector_plan1.y = (-1./vector_normal.y);
    vector_plan1.z = 0;
  //produit vectoriel
  vector vector_plan2 = produit_vectoriel(&vector_normal, &vector_plan1);
  // printf("DEBUG1: vector_plan1.vector_normal = %f\n", produit_scalaire(vector_normal,vector_plan1));
  // printf("DEBUG2: vector_plan1.vector_plan2 = %f\n", produit_scalaire(vector_plan2,vector_plan1));
  // printf("DEBUG3: vector_normal.vector_plan2 = %f\n", produit_scalaire(vector_plan2,vector_normal));
  matrix ret;
    ret.v[0] = vector_normal;
    ret.v[1] = vector_plan1;
    ret.v[2] = vector_plan2;
  normalize(&ret.v[0]);
  normalize(&ret.v[1]);
  normalize(&ret.v[2]);
  return ret;
}

vector add_vect(vector *v1, vector *v2){
  vector ret;
    ret.x = v1->x+v2->x;
    ret.y = v1->y + v2->y;
    ret.z = v1->z + v2->z;
  return ret;
}

point change_base(float x, float y, float z, matrix *math){
  point ret;
    ret.x = math->v[0].x * x + math->v[1].x * y + math->v[2].x * z;
    ret.y = math->v[0].y * x + math->v[1].y * y + math->v[2].y * z;
    ret.z = math->v[0].z * x + math->v[1].z * y + math->v[2].z * z;
  return ret;
}
