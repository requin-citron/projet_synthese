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

void normalize(vecteur* v){
  float norme = pow(v->x, 2) + pow(v->y, 2) + pow(v->z, 2);
  float magie = Q_rsqrt(norme);
  v->x *= magie;
  v->y *= magie;
  v->z *= magie;
}

vecteur produit_vectoriel(vecteur v1, vecteur v2){
  vecteur ret{
    (v1.y*v2.z) - (v1.z*v2.y),
    (v1.z*v2.x) - (v2.z*v1.x),
    (v1.x*v2.y) - (v1.y*v2.x),
  };
  return ret;
}

vecteur scale(vecteur v1, float s){
  vecteur ret{
    v1.x*s,
    v1.y*s,
    v1.z*s,
  };
  return ret;
}

float produit_scalaire(vecteur v1, vecteur v2){
  return v1.x*v2.x + v1.y*v2.y + v1.z*v2.z;
}

//on crée une matisse de changement de base
// pour faire avoir une base orthogonal en p1
matrix_base create_base(point p1, point p2){
  p2.x-=p1.x;
  p2.y-=p1.y;
  p2.z-=p1.z;
  p1.x=0;
  p1.y=0;
  p1.z=0;
  vecteur vecteur_normal = {
    p2.x-p1.x,
    p2.y-p1.y,
    p2.z-p1.z,
  };
  vecteur vecteur_plan1 = {
    (1./vecteur_normal.x),
    (-1./vecteur_normal.y),
    0,
  };
  //produit vectoriel
  vecteur vecteur_plan2 = produit_vectoriel(vecteur_normal, vecteur_plan1);
  // printf("DEBUG1: vecteur_plan1.vecteur_normal = %f\n", produit_scalaire(vecteur_normal,vecteur_plan1));
  // printf("DEBUG2: vecteur_plan1.vecteur_plan2 = %f\n", produit_scalaire(vecteur_plan2,vecteur_plan1));
  // printf("DEBUG3: vecteur_normal.vecteur_plan2 = %f\n", produit_scalaire(vecteur_plan2,vecteur_normal));
  matrix_base ret{
    vecteur_normal,vecteur_plan1,vecteur_plan2,
  };
  normalize(&ret.v[0]);
  normalize(&ret.v[1]);
  normalize(&ret.v[2]);
  return ret;
}

vecteur add_vect(vecteur v1, vecteur v2){
  vecteur ret{
    v1.x+v2.x,
    v1.y + v2.y,
    v1.z + v2.z,
  };
  return ret;
}

point change_base(float x, float y, float z, matrix_base math){
  point ret{
    math.v[0].x * x + math.v[1].x * y + math.v[2].x * z,
    math.v[0].y * x + math.v[1].y * y + math.v[2].y * z,
    math.v[0].z * x + math.v[1].z * y + math.v[2].z * z,
  };
  return ret;
}
