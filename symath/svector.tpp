#ifdef __SVECTOR_CPP__
// note ifdef instead of ifndef

#include <initializer_list>
#include <cmath> // needed for sqrt

/*
 * This is a very special .cpp which must NOT 
 * be compiled.
 *
 * Function definitions of a template class 
 * like SVector must be visible to the linker,
 * so it is not possible to put them in a 
 * "conventional .cpp file".
 *
 * The purpose of this file is to be
 * included into the svector.h after
 * all declarations.
 */

template<std::size_t N>
SVector<N>::SVector(const double &value)
{
    components.fill(value);
}

template<std::size_t N>
SVector<N>::SVector(const std::initializer_list<double> &init)
{
    size_t n = (init.size() < N) ? init.size() : N;

    /* copy init list without include <algorithm> */
    size_t index = 0;

    /* copy the initializer list until its size */
    for (auto c : init)
    {
        if (index >= n)
            break;

        components[index++] = c;
    }

    /* fill the remaining components with zero */
    while(index < N)
        components[index++] = 0;
}

template<std::size_t N>
SVector<N>::SVector(const SVector<N>& init)
{
    *this = init;
}

template<std::size_t N>
typename SVector<N>::iterator SVector<N>::begin()    
{ 
    return components.begin(); 
}

template<std::size_t N>
typename SVector<N>::iterator SVector<N>::end()      
{ 
    return components.end(); 
}

template<std::size_t N>
typename SVector<N>::const_iterator SVector<N>::begin() const 
{ 
    return components.begin(); 
}

template<std::size_t N>
typename SVector<N>::const_iterator SVector<N>::end() const 
{ 
    return components.end(); 
}

template<std::size_t N>
SVector<N>& SVector<N>::unit()
{
    return *this /= module();
}

template<std::size_t N>
SVector<N>& SVector<N>::normalize(const double &value)
{
    return *this *= value / module();
}

template<std::size_t N>
SVector<N> SVector<N>::directional() const
{
    return *this / module();
}

template<std::size_t N>
size_t SVector<N>::size() const
{
    return N;
}

/* Access operators */
template<std::size_t N>
double& SVector<N>::operator[](size_t i)    
{ 
    return components[i]; 
}

template<std::size_t N>
const double& SVector<N>::operator[](size_t i) const 
{ 
    return components[i]; 
}

template<std::size_t N>
bool SVector<N>::operator==(const SVector<N>& v) const
{
    return components == v.components;
}

template<std::size_t N>
bool SVector<N>::operator!=(const SVector<N>& v) const
{
    return !(*this == v);
}

template<std::size_t N>
bool SVector<N>::operator<=(const SVector<N>& v) const
{
    return sq_module() <= v.sq_module();
}

template<std::size_t N>
bool SVector<N>::operator>=(const SVector<N>& v) const
{
    return sq_module() >= v.sq_module();
}

template<std::size_t N>
bool SVector<N>::operator<=(double m) const
{
    return sq_module() <= m * m;
}

template<std::size_t N>
bool SVector<N>::operator>=(double m) const
{
    return sq_module() >= m * m;
}

template<std::size_t N>
bool SVector<N>::operator<(const SVector<N>& v) const
{
    return sq_module() < v.sq_module();
}

template<std::size_t N>
bool SVector<N>::operator>(const SVector<N>& v) const
{
    return sq_module() > v.sq_module();
}

template<std::size_t N>
bool SVector<N>::operator<(double m) const
{
    return sq_module() < m * m;
}

template<std::size_t N>
bool SVector<N>::operator>(double m) const
{
    return sq_module() > m * m;
}

template<std::size_t N>
SVector<N>& SVector<N>::operator+=(const SVector<N>& v)
{
    for (size_t i = 0; i < N; ++i)
        components[i] += v[i];

    return *this;
}

template<std::size_t N>
SVector<N>& SVector<N>::operator-=(const SVector<N>& v)
{
    for (size_t i = 0; i < N; ++i)
        components[i] -= v[i];

    return *this;
}

template<std::size_t N>
SVector<N>& SVector<N>::operator*=(double k)
{
    for (size_t i = 0; i < N; ++i)
        components[i] *= k;

    return *this;
}

template<std::size_t N>
SVector<N>& SVector<N>::operator/=(double k)
{
    for (size_t i = 0; i < N; ++i)
        components[i] /= k;

    return *this;
}

template<std::size_t N>
double SVector<N>::operator*(const SVector<N>& v) const
{
    double x = 0;

    for (size_t i = 0; i < N; ++i)
        x += components[i] * v[i];

    return x;
}


template<std::size_t N>
SVector<N>& SVector<N>::operator~()
{
    return (*this)*=-1;
}

template<std::size_t N>
double SVector<N>::module() const
{
    return sqrt( sq_module() );
}

template<std::size_t N>
double SVector<N>::sq_module() const
{
    return (*this) * (*this);
}

template<std::size_t N>
SVector<N>& SVector<N>::null()
{
    components.fill(0);

    return *this;
}

// define the null vector constant
template <std::size_t N>
const SVector<N> SVector<N>::nullv = SVector<N>(0);


/*
 * Sum and subtraction operators
 */

template<std::size_t N>
const SVector<N> operator+(SVector<N> v, const SVector<N>& w)
{
    return v += w;
}

template<std::size_t N>
const SVector<N> operator-(SVector<N> v, const SVector<N>& w)
{
    return v -= w;
}

/*
 * Scalar multiplication
 */

template<std::size_t N>
const SVector<N> operator*(SVector<N> v, double k)
{
    return v *= k;
}

template<std::size_t N>
const SVector<N> operator/(SVector<N> v, double k)
{
    return v /= k;
}

template<std::size_t N>
const SVector<N> operator*(double k, SVector<N> v)
{
    return v *= k;
}

template<std::size_t N>
const SVector<N> operator/(double k, SVector<N> v)
{
    return v /= k;
}

/* Inversion operators */
template<std::size_t N>
const SVector<N> operator-(SVector<N> v)
{
    return ~v;
}

template<std::size_t N>
double * SVector<N>::rawdata()
{
    return &components[0];
}

template<std::size_t N>
const double * SVector<N>::rawdata() const
{
    return &components[0];
}


#ifdef _USE_SVECTOR_OSTREAM

template <std::size_t N>    
std::ostream& operator<<(std::ostream& os, const SVector<N> &v)
{
    os << "(";

    for (size_t i(0); i < (N - 1); ++i)
    {
        os << v[i] << ", ";
    }

    os << v[N-1] << ")";

    return os;
}

#endif

#endif // __SVECTOR_CPP__
