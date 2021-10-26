#include "vector_util.h"


//what the fuck fucking fuck
//! 1/sqrt(x)
/*!
	\param[in] number x

	on utilise une astuce pour augmenter le traitement de 1/sqrt(x)
	qui est trés long a calculer normalement ce **hack** viens de quake
	qui utilisé ca pour normaliser ses vecteur ce que nous allons faire ici
	aussi. L'algo utilise une astuce provenant de la norme des floatant IEE754
	et de la facilité a calculer les log en binaire
*/
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
//!fonction de normalisation des vecteur
/*!
	\param[out] v pointeur sur un vecteur
	on multiplie chaque composantes par 1/|v|
	on utilise donc Q_rsqrt pour amiliorer la vitesse car
	cette fonction est appeller **énormement**
*/
void normalize(vector* v){
  float norme = pow(v->x, 2) + pow(v->y, 2) + pow(v->z, 2);
  float magie = Q_rsqrt(norme);
  v->x *= magie;
  v->y *= magie;
  v->z *= magie;
}

//! fonction qui calcule le produit vectoriel
/*!
	\return vecteur normal aux deux vecteur en parametre
	\param[in] v1 premier pointeur de vecteur
	\param[in] v2 deuxieme pointeur de vecteur
	la fonction calcule le produit vectoriel qui est trés utile
	car si v1 et v2 sont perpendiculaire le resulta du produit scalaire
	est un vecteur orthogonal aux deux vecteur ce qui est **watibien**
*/
vector produit_vectoriel(vector *v1, vector *v2){
  vector ret;
    ret.x = (v1->y*v2->z) - (v1->z*v2->y);
    ret.y = (v1->z*v2->x) - (v2->z*v1->x);
    ret.z = (v1->x*v2->y) - (v1->y*v2->x);
  return ret;
}

//!fonction de mise a l'echelle d'un vecteur
/*!
	\return vecteur mis a l'echelle
	\param[in] v1 pointeur sur un vecteur
	\param s coefficient multiplicateur
	on multiplie chaque composantes du vecteur par
	le coefficient.
*/
vector scale(vector *v1, float s){
  vector ret;
    ret.x = v1->x*s;
    ret.y = v1->y*s;
    ret.z = v1->z*s;
  return ret;
}
//!produit scalaire de deux vecteur
/*!
	\return resultat du produit scalaire
	\param v1 pointeur sur le premier vecteur
	\param v2 pointeur sur le deuxieme vecteur
	renvois le produit sclaire quand il est égale a 0 les deux vecteur
	sont perpendiculaire ce qui est **tres utile**
*/
float produit_scalaire(vector *v1, vector *v2){
  return v1->x*v2->x + v1->y*v2->y + v1->z*v2->z;
}

//on crée une matisse de changement de base
// pour faire avoir une base orthogonal en p1
//!crée une base a partir de deux points
/*!
	\return matrice représentant la base
	\param p1 premier point
	\param p2 deuxième point
	a partir des deux points il est possible d'obtenir un vecteur
	v1 = p2-p1
	ensuite nous crée  un vecteur qui est perpendiculaire a ce premier
	v2.x = 1/v1.x
	v2.y = -1/v1.y
	v2.z = 0
	le produit scalaire de v1 et v2 produit un vecteur null
	on prend les valeurs absolue de v2. Qui régle un problème d'inversion
	de base dans le cas d'une courbe de bezier
	pour avoir le troisème vecteur on utilise le produit vectoriel
	on utilise ensuite Q_rsqrt pour normaliser les trois vecteur de la base
*/
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
		//aproxymation
		//matematiquement fausse mais assez proche pour
		//etre utiliser et optimiser notre programme
    vector_plan1.x = fabsf(1./vector_normal.x);
    vector_plan1.y = fabsf(-1./vector_normal.y);
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
//! somme deux vecteur
/*!
	\return somme des deux vecteur
	\param[in] v1 premier vecteur
	\param[in] v2 deuxieme vecteur
	renvois un nouveau vecteur qui est la resultante de
	la somme deux deux vecteur en parametre
*/
vector add_vect(vector *v1, vector *v2){
  vector ret;
    ret.x = v1->x+v2->x;
    ret.y = v1->y + v2->y;
    ret.z = v1->z + v2->z;
  return ret;
}

//! renvois un point aprés un changement de base
/*!
	\return point
	\param x composante x
	\param y composante y
	\param z composante z
	\param[in] math matrice de la base
	on renvois un point aprés changement de base pour x y z
*/
point change_base(float x, float y, float z, matrix *math){
  point ret;
    ret.x = math->v[0].x * x + math->v[1].x * y + math->v[2].x * z;
    ret.y = math->v[0].y * x + math->v[1].y * y + math->v[2].y * z;
    ret.z = math->v[0].z * x + math->v[1].z * y + math->v[2].z * z;
  return ret;
}
//!initialisation d'une matrice a 0
/*!
	\param[out] m matrice qui doit etre mis  a zero
	chaqu vecteur est mis a 0 ce qui donne une
	matrice 3x3 a 0
*/
void matrix_zero(matrix *m){
	for(size_t i=0; i < 3; i++){
		m->v[i].x= 0;
		m->v[i].y = 0;
		m->v[i].z = 0;
	}
}
//!fonction de debug
/*!
	\param[in] m matrice qui doit etre afficher
	affiche chaque veteur de la matrice dans la sortie standard
*/
void matrix_debug(matrix *m){
    for (size_t i = 0; i < 3; i++) {
      printf("v[%lu] = (%f,%f,%f)\n", i, m->v[i].x, m->v[i].y, m->v[i].z);
    }
}

//! fais une rotation de Pi sur la matrice de changement de base
/*!
	\param[out] m matrice qui doit etre modifier
	on inverse toutes les composantes du vecteur z
	puis on recrée le vecteur y a partir du produit vectoriel
	le vecteur x ne bouge pas
*/
void inverse_z(matrix *m){
  vector z = m->v[2];
  z.x *= -1;
  z.y *= -1;
  z.z *= -1;
  m->v[2] = z;
  vector  y = produit_vectoriel(&m->v[0],&m->v[2]);
  m->v[1] = y;
}
