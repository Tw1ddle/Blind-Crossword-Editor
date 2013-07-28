#ifndef VECTORMATH_H
#define VECTORMATH_H

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
    inline void operator*=(const T);
    inline void operator/=(const T);

    inline Vector3 operator+() const;
    inline Vector3 operator-() const;
    inline Vector3 operator*(T) const;
    inline Vector3 operator/(T) const;

    inline T x() const;
    inline T y() const;
    inline T z() const;

    inline void x(T x);
    inline void y(T y);
    inline void z(T z);

private:
    T m_Vec[3];
};

template<class T> Vector3<T>::Vector3() {}

template<class T> Vector3<T>::Vector3(T x, T y, T z)
{
    v[0] = x;
    v[1] = y;
    v[2] = z;
}

template<class T> Vector3<T>::Vector3(T x)
{
    v[0] = x;
    v[1] = x;
    v[2] = x;
}

template<class T> Vector3<T>& Vector3<T>::operator=(const T* u)
{
    v[0] = u[0];
    v[1] = u[1];
    v[2] = u[2];
}

template<class T> void Vector3<T>::set(T x, T y, T z)
{
    v[0] = x;
    v[1] = y;
    v[2] = z;
}

template<class T> bool Vector3<T>::operator==(const Vector3<T>& u) const
{
    return (v[0] == u.v[0] && v[1] == u.v[1] && v[2] == u.v[2]);
}

template<class T> bool Vector3<T>::operator!=(const Vector3<T>& u) const
{
    return (v[0] != u.v[0] || v[1] != u.v[1] || v[2] != u.v[2]);
}

template<class T> void Vector3<T>::operator+=(const Vector3<T>& u)
{
    v = v + u;
}

template<class T> void Vector3<T>::operator-=(const Vector3<T>& u)
{
    v = v - u;
}

template<class T> void Vector3<T>::operator*=(T s)
{
    v = v * s;
}

template<class T> void Vector3<T>::operator/=(T s)
{
    v = v / s;
}

template<class T> Vector3<T> Vector3<T>::operator+() const
{
    return *this;
}

template<class T> Vector3<T> Vector3<T>::operator-() const
{
    return Vector3<T>(-v[0], -v[1], -v[2]);
}

template<class T> Vector3<T> Vector3<T>::operator*(T s) const
{
    return Vector3<T>(v[0]*s, v[1]*s, v[2]*s);
}

template<class T> Vector3<T> Vector3<T>::operator/(T s) const
{
    return Vector3<T>(v[0]/s, v[1]/s, v[2]/s);
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

typedef Vector3<float> Vec3f;
typedef Vector3<int> Vec3i;

}

#endif // VECTORMATH_H
