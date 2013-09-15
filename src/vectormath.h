#ifndef VECTORMATH_H
#define VECTORMATH_H

#include <math.h>

namespace VectorMath
{

// Template for a 3-element vector
template<class T>
class Vector3
{
public:
    inline Vector3();
    inline Vector3(T, T, T);
    inline Vector3(T);

    inline Vector3& operator=(const T*);
    inline void set(T, T, T);

    inline bool operator==(const Vector3<T>&) const;
    inline bool operator!=(const Vector3<T>&) const;

    inline void operator+=(const Vector3<T>&);
    inline void operator-=(const Vector3<T>&);
    inline void operator%=(const Vector3<T>&);
    inline void operator*=(const T);
    inline void operator/=(const T);


    inline Vector3 operator+() const;
    inline Vector3 operator-() const;
    inline Vector3 operator*(T) const;
    inline Vector3 operator/(T) const;

    inline Vector3 operator+(const Vector3<T>&) const;
    inline Vector3 operator-(const Vector3<T>&) const;

    inline Vector3<T> abs() const;
    inline T product() const;

    inline T x() const;
    inline T y() const;
    inline T z() const;

    inline void x(T x);
    inline void y(T y);
    inline void z(T z);

private:
    T m_Vec[3];
};

template<class T> Vector3<T>::Vector3()
{
    m_Vec[0] = 0;
    m_Vec[1] = 0;
    m_Vec[2] = 0;
}

template<class T> Vector3<T>::Vector3(T x, T y, T z)
{
    m_Vec[0] = x;
    m_Vec[1] = y;
    m_Vec[2] = z;
}

template<class T> Vector3<T>::Vector3(T x)
{
    m_Vec[0] = x;
    m_Vec[1] = x;
    m_Vec[2] = x;
}

template<class T> Vector3<T>& Vector3<T>::operator=(const T* u)
{
    m_Vec[0] = u[0];
    m_Vec[1] = u[1];
    m_Vec[2] = u[2];
}

template<class T> void Vector3<T>::set(T x, T y, T z)
{
    m_Vec[0] = x;
    m_Vec[1] = y;
    m_Vec[2] = z;
}

template<class T> bool Vector3<T>::operator==(const Vector3<T>& u) const
{
    return (m_Vec[0] == u.m_Vec[0] && m_Vec[1] == u.m_Vec[1] && m_Vec[2] == u.m_Vec[2]);
}

template<class T> bool Vector3<T>::operator!=(const Vector3<T>& u) const
{
    return (m_Vec[0] != u.m_Vec[0] || m_Vec[1] != u.m_Vec[1] || m_Vec[2] != u.m_Vec[2]);
}

template<class T> void Vector3<T>::operator+=(const Vector3<T>& u)
{
    m_Vec = m_Vec + u;
}

template<class T> void Vector3<T>::operator-=(const Vector3<T>& u)
{
    m_Vec = m_Vec - u;
}

template<class T> void Vector3<T>::operator%=(const Vector3<T>& u)
{
    m_Vec[0] = m_Vec[0] % u.m_Vec[0];
    m_Vec[1] = m_Vec[1] % u.m_Vec[1];
    m_Vec[2] = m_Vec[2] % u.m_Vec[2];
}

template<class T> void Vector3<T>::operator*=(T s)
{
    m_Vec = m_Vec * s;
}

template<class T> void Vector3<T>::operator/=(T s)
{
    m_Vec = m_Vec / s;
}

template<class T> Vector3<T> Vector3<T>::operator+(const Vector3<T>& u) const
{
    return Vector3<T>(m_Vec[0] + u.m_Vec[0], m_Vec[1] + u.m_Vec[1], m_Vec[2] + u.m_Vec[2]);
}

template<class T> Vector3<T> Vector3<T>::operator-(const Vector3<T>& u) const
{
    return Vector3<T>(m_Vec[0] - u.m_Vec[0], m_Vec[1] - u.m_Vec[1], m_Vec[2] - u.m_Vec[2]);
}

template<class T> Vector3<T> Vector3<T>::operator+() const
{
    return *this;
}

template<class T> Vector3<T> Vector3<T>::operator-() const
{
    return Vector3<T>(-m_Vec[0], -m_Vec[1], -m_Vec[2]);
}

template<class T> Vector3<T> Vector3<T>::operator*(T s) const
{
    return Vector3<T>(m_Vec[0]*s, m_Vec[1]*s, m_Vec[2]*s);
}

template<class T> Vector3<T> Vector3<T>::operator/(T s) const
{
    return Vector3<T>(m_Vec[0]/s, m_Vec[1]/s, m_Vec[2]/s);
}

template<class T> T Vector3<T>::x() const
{
    return m_Vec[0];
}

template<class T> T Vector3<T>::y() const
{
    return m_Vec[1];
}

template<class T> T Vector3<T>::z() const
{
    return m_Vec[2];
}

template<class T> void Vector3<T>::x(T x)
{
    m_Vec[0] = x;
}

template<class T> void Vector3<T>::y(T y)
{
    m_Vec[1] = y;
}

template<class T> void Vector3<T>::z(T z)
{
    m_Vec[2] = z;
}

template<class T> Vector3<T> Vector3<T>::abs() const
{
    return Vector3<T>(std::abs(m_Vec[0]), std::abs(m_Vec[1]), std::abs(m_Vec[2]));
}

template<class T> T Vector3<T>::product() const
{
    return T(m_Vec[0] * m_Vec[1] * m_Vec[2]);
}

typedef Vector3<float> Vec3f;
typedef Vector3<int> Vec3i;

}

#endif // VECTORMATH_H
