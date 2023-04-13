#include "vector.h"
#include <cmath> // pour sqrt()
#include "svector.h"

using namespace std;

Vector::Vector() : components(DEFAULT_VECTOR_SIZE) {}

// Costructeur sur la base d'une liste de valuers

Vector::Vector(const initializer_list<double> &init) : components(init.begin(), init.end()) {}

// Constructeur sur la base d'un std::vector

Vector::Vector(const vector<double>& init) : components(init) {}

Vector::Vector(const Vector& init)
{
    *this = init;
}

//Destructeur
Vector::~Vector(){}


//Permet, par un simple operator =, d'affecter un Vector à un autre
/*Vector& Vector::operator=(const Vector& v) {

    // clear current memory
    this->clear();

    // assure allocation size
    this->components.reserve(v.size());

    // copy all components
    for (auto comp : v)
        this->components.push_back(comp);

    return *this;
}*/
	
/* for auto loop */

Vector::iterator Vector::begin()
{
    return components.begin();
}

Vector::iterator Vector::end()
{
    return components.end();
}

Vector::const_iterator Vector::begin() const
{
    return components.begin();
}

Vector::const_iterator Vector::end() const
{
    return components.end();
}



Vector Vector::unit() const
{
    return (*this) / this->module();
}


/*
 * cette fonctions était démandée en exercice, mais l'operator "[]" permet de faire la même chose
 * et en plus elle foction de operateur [] comme pour les "vector" (ex. v[i] cordonnée i de v) 
 * mais pour notre classe "Vector"
 *
void Vector::set_coord(size_t i, double x){
	
	if (i<components->size())
		*components[i]=val;
	//On vérifie si l'entrée i est plausible pour ensuite affecter la valeur à la coordonnée choisie
	else
		throw string("Vector: Out of bound error");
	//Autrement on lance une erreur d'Out of bound
}
*/

void Vector::augmente(double x) {

	components.push_back(x);
	//On rajoute simplement la valeur à un nouveau paramètre, correspondant à une dimension de plus
}

void Vector::decale()
{
    components.pop_back();
}
		
void Vector::clear(){
	
    components.clear();
}


//Permet d'utiliser la fonction size pour une variale Vector, comme si celle si était un vector
size_t Vector::size() const {

	return components.size();
}

/*Ici de suite on retrouve deux foctions "identiques" 
 * mais qui opèrent sur des objets constants ou non
*/
const double& Vector::operator[](size_t i) const {

	return components[i];
	//Retourne la valeur du vecteur à l'indice i(i commence à 0)
}

double& Vector::operator[](size_t i) {

	return components[i];
	//Retourne la valeur du vecteur à l'indice i(i commence à 0)
}


/*void Vector::affiche() const{
	
	cout << "(";
	
	for(auto a : *components){
			cout << a << ", ";
	}
	//Par cette boucle on peut afficher un après l'autre tous les coordonnées du Vecteur
	cout << ")"<< endl;
}
*
* 
* Celle si à été substituée par un ostream implementé plus loins
*/


//Operateurs comparaisons

bool Vector::operator==(const Vector& v) const {
	
	if(components.size() != v.size())
		return false;
	
	//Retourne déjà faux si les deux vecteurs n'ont pas la même dimension
	for(size_t i(0); i < v.size(); ++i){
		
		if (components[i] != v[i])
			return false;
			//Lors que le programme rencontre deux coordonnées différenentes respectivement pour la même dimension des deux vecteurs
			//la fonction retourne false
	}
	return true;
}

bool Vector::operator>=(const Vector& v) const
{
    return sq_module() >= v.sq_module();
}

bool Vector::operator<=(const Vector& v) const
{
    return sq_module() <= v.sq_module();
}

bool Vector::operator>=(double m) const
{
    return sq_module() >= m * m;
}

bool Vector::operator<=(double m) const
{
    return sq_module() <= m * m;
}

bool Vector::operator>(const Vector& v) const
{
    return sq_module() > v.sq_module();
}

bool Vector::operator<(const Vector& v) const
{
    return sq_module() < v.sq_module();
}

bool Vector::operator>(double m) const
{
    return sq_module() > m * m;
}

bool Vector::operator<(double m) const
{
    return sq_module() < m * m;
}

bool Vector::operator!=(const Vector& w) const
{
    return !(*this == w);
}

//Operateurs somme et produit

Vector& Vector::operator+=(const Vector& w)
{
    size_t n = (this->size() <= w.size()) ? this->size() : w.size();

    for (size_t i= 0; i < n; ++i)
        (*this)[i] += w[i]; 

    return *this;
}


Vector& Vector::operator-=(const Vector& w)
{
    size_t n = (this->size() <= w.size()) ? this->size() : w.size();

    for (size_t i = 0; i < n; ++i)
        (*this)[i] -= w[i]; 

    return *this;
}

Vector& Vector::operator*=(double k)
{
    for (size_t i = 0; i < this->size(); ++i)
        (*this)[i] *= k; 

    return *this;
}

Vector& Vector::operator/=(double k)
{
    for (size_t i = 0; i < this->size(); ++i)
        (*this)[i] /= k; 

    return *this;
}

const Vector operator+(Vector v, const Vector& w)
{
    return v += w;
}

const Vector operator-(Vector v, const Vector& w)
{
    return v -= w;
}

const Vector operator*(Vector v, double const& k)
{
    return v *= k;
}

const Vector operator/(Vector v, double const& k)
{
    return v /= k;
}

#include "skerror.h"

using namespace symkit;

/* Cross product */
Vector Vector::operator^(const Vector& w) const
{
    Vector u = {0, 0, 0};

    if (this->size() != 3 || w.size() != 3)
        throw SKError(ERR_NUMERICAL, "operator^", "Vector", "Cross product of non-3D vectors", 0);

    u[0] = (*this)[1] * w[2] - (*this)[2] * w[1];
    u[1] = (*this)[2] * w[0] - (*this)[0] * w[2];
    u[2] = (*this)[0] * w[1] - (*this)[1] * w[0];

    return u;
}

/* Dot product */
double Vector::operator*(const Vector& w) const
{
    double x = 0;

    if (this->size() != w.size())
        throw SKError(ERR_NUMERICAL, "operator*", "Vector", "Scalar producat of vector with different dimension", 0);

    for (size_t i = 0; i < this->size(); ++i)
        x += (*this)[i] * w[i];

    return x;
}

Vector Vector::operator-() const
{
    return (*this) * (-1);
}

Vector& Vector::operator~()
{
    return (*this)*=-1.0;
}

double Vector::sq_module() const 
{
    double x = 0;
    
    for (size_t i = 0; i < this->size(); ++i)
        x += (*this)[i] * (*this)[i];

    return x;
}

double Vector::module() const
{
    return sqrt(this->sq_module());
}


/* Implementation of ostream operator overloading */

/* Le prototype je le mets dans un header séparé parce que
 * il ne fait pas partie de l'implementation d'un vecteur
 * Une classe l'utilisant n'as pas besoin de l'imprimer
 */

//#include "iosymkit.h" // pour implementer ostream<<
#include <ostream>

void Vector::affiche(std::ostream& os) const
{
    os << "(";

    for (size_t i(0); i < (components.size() - 1); ++i)
    {
        os << components[i] << ", ";
    }

    os << components[components.size()-1] << ")";
}


// Flux de sortie permettant d'afficher les coordonnées du vecteur
ostream& operator<<(ostream& os, const Vector& v)
{
    v.affiche(os);
    return os;
}

#include "svector.h"

/*
 * Cross product implementation for SVector
 */

const SVector<3> operator^(const SVector<3>& v, const SVector<3>& w)
{
    SVector<3> u = {0, 0, 0};

    if (v.size() != 3 || w.size() != 3)
        throw SKError(ERR_NUMERICAL, "operator^", "SVector", "Cross product of non-3D vectors", 0);


    u[0] = v[1] * w[2] - v[2] * w[1];
    u[1] = v[2] * w[0] - v[0] * w[2];
    u[2] = v[0] * w[1] - v[1] * w[0];

    return u;
}

double * Vector::rawdata()
{
    return &components[0];
}

const double * Vector::rawdata() const
{
    return &components[0];
}
