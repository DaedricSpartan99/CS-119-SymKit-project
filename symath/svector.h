#ifndef __STATIC_VECTOR_H__
#define __STATIC_VECTOR_H__

#include <array>

template<std::size_t N> 
class SVector
{

public:

    typedef std::size_t size_t;

    /* Constructors */

    SVector(const double &value = 0);

    SVector(const std::initializer_list<double> &init);

    SVector(const SVector& init);

    /* For auto implementation */
    /* it allows to loop through components
     *
     * for (auto comp : v)
     * {
     *      // loop content
     * }
     */

    typedef typename std::array<double, N>::iterator iterator;
    typedef typename std::array<double, N>::const_iterator const_iterator;

    iterator begin();

    iterator end();

    const_iterator begin() const;

    const_iterator end() const;

    /* 
     * Reduce to module = 1 
     */
    SVector& unit();

    /* Set the module to a specific value keeping the direction */
    SVector& normalize(const double &value);

    /* Same as unit, be it returns another vector */
    SVector directional() const;

    /* Returns the dimension, in this case it is fixed */
	size_t size() const;

    /* Access operators */
	double& operator[](size_t i);

	const double& operator[](size_t i) const;

    /* Comparison operators */
    bool operator==(const SVector& v) const;

    bool operator!=(const SVector& v) const;

    /* Implicit module comparison operators */

    bool operator<=(const SVector& v) const;

    bool operator>=(const SVector& v) const;

    bool operator<=(double) const;

    bool operator>=(double) const;

    bool operator<(const SVector& v) const;

    bool operator>(const SVector& v) const;

    bool operator<(double) const;

    bool operator>(double) const;

    /* Plus / minus operators */
    SVector& operator+=(const SVector& v);

    SVector& operator-=(const SVector& v);

    /* Scalar multiplication / division */
    SVector& operator*=(double k);

    SVector& operator/=(double k);

    /* Dot product */
    double operator*(const SVector& v) const;

    SVector& operator~();    // inversion without copy

    /* Return the module */
    double module() const;

    /* Squared module */
    double sq_module() const;

    /* reset the vector to null vector */
    SVector& null();

    /* obtain array raw data */

    double * rawdata();
    const double * rawdata() const;

    /* null vector constant */
    static const SVector nullv;

private:

    std::array<double, N> components;
};

/*
 * External operators overloading
 */

/*
 * Sum or subtraction
 */

template<std::size_t N>
const SVector<N> operator+(SVector<N> v, const SVector<N>& w);

template<std::size_t N>
const SVector<N> operator-(SVector<N> v, const SVector<N>& w);

/*
 * Scalar multiplication
 */

template<std::size_t N>
const SVector<N> operator*(SVector<N> v, double k);

template<std::size_t N>
const SVector<N> operator/(SVector<N> v, double k);

template<std::size_t N>
const SVector<N> operator*(double k, SVector<N> v);

template<std::size_t N>
const SVector<N> operator/(double k, SVector<N> v);

/* 
 * Inversion operator
 */
template<std::size_t N>
const SVector<N> operator-(SVector<N> v);

/*
 * Prototipe for cross product
 * Implementation in "vector.cpp"
 */
const SVector<3> operator^(const SVector<3>& v, const SVector<3>& w);


/*
 * Macro of use of vectors
 * Useful in some qt functions for the opengl
 */
#define ARRAY_3D_FLOAT_ARGS(v) (float)v[0], (float)v[1], (float)v[2]

/*
 * Output stream << operator overloading
 * Define this macro before including svector.h if you want
 * to use this function.
 *
 * For example:
 *
 * #define _USE_SVECTOR_OSTREAM
 * #include "svector.h"
 *
 */
#ifdef _USE_SVECTOR_OSTREAM

#include <ostream>

template <std::size_t N>    
std::ostream& operator<<(std::ostream& os, const SVector<N> &v);

#endif

/*
 * Include definitions file
 */
#define __SVECTOR_CPP__
#include "svector.tpp"
#undef __SVECTOR_CPP__

#endif // __SVECTOR_H__
