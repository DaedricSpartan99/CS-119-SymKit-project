#ifndef __VECTOR_H__
#define __VECTOR_H__ 

#include <initializer_list>
#include <vector>
#include <iosfwd>

#define DEFAULT_VECTOR_SIZE 1

class Vector {

public:

    Vector();

    Vector(const std::initializer_list<double> &init);

    /* Constructeur par liste de valeurs 
     * Par exemple: Vector v = {0, 3, 2};
     */
    

	//Constructeur
	Vector(const std::vector<double>&);

    /* Deuxieme constructeur */
    Vector(const Vector&);

	//Destructeur
	~Vector();

    /* Assignment operator */
	//Vector& operator=(const Vector&);
    //Vector& operator=(const Vector& v);

	/*Iterator for Vector class*/
    typedef std::vector<double>::iterator iterator;
    typedef std::vector<double>::const_iterator const_iterator;

    /* For auto implementation */
    /* it allows to loop through components
     *
     * for (auto comp : v)
     * {
     *      // loop content
     * }
     */

    iterator begin();
    iterator end();

    const_iterator begin() const;
    const_iterator end() const;

    /* Retourne le vecteur unitaire du vecteur d'intérêt */
    Vector unit() const;
		
	//Manipulateurs
/* La fonction qui suit est superflue grace à l'operateur [] pour la classe Vector
 * Voir commentaire réspectif dans le fichier "vector.cpp"
 		void set_coord(size_t i, double x);
*/	
	/* Augmente d'une dimension en l'affectant */
    void augmente(double x = 0);
    /* Diminue d'une dimension*/ 
    void decale();
    /* Vide le le vecteur */
	void clear();
		
	//Accesseurs
	
	/* Accède à la dimension du vecteur */
    typedef std::size_t size_t;

	size_t size() const;

	/* Accède à la i-ème valeur */
	double& operator[](size_t i);
	const double& operator[](size_t i) const;

	/* Return the module */
    double module() const;
    double sq_module() const; // squared module
    
    //Operateurs
    
	/* Operateurs de comparaison */
	bool operator==(const Vector&) const;
    bool operator!=(const Vector&) const;

    bool operator>=(const Vector&) const;
    bool operator<=(const Vector&) const;

    bool operator>=(double) const;
    bool operator<=(double) const;

    bool operator>(const Vector&) const;
    bool operator<(const Vector&) const;

    bool operator>(double) const;
    bool operator<(double) const;

    /* Plus / minus */
    Vector& operator+=(const Vector&);
    Vector& operator-=(const Vector&);

    /* Scalar multiplication / division */
    Vector& operator*=(double k);
    Vector& operator/=(double k);

    Vector operator-() const;
    Vector& operator~();

    /* Cross product */
    Vector operator^(const Vector&) const;

    /* Dot product */
    double operator*(const Vector&) const;

    /* For printing a Vector on a ostream */
    void affiche(std::ostream&) const;

    /* get vector raw data */

    double * rawdata();
    const double * rawdata() const;
		
private:

	//Composantes du vecteur
	std::vector<double> components;
};

const Vector null2v = {0, 0};
const Vector null3v = {0, 0 ,0};
const Vector null4v = {0, 0 ,0 ,0};
const Vector operator+(Vector , const Vector& );
const Vector operator-(Vector , const Vector& );

const Vector operator*(Vector , double const& );
const Vector operator/(Vector , double const& );

// forward declaration of ostream
#include <iosfwd>

std::ostream& operator<<(std::ostream&, const Vector&);

#endif
