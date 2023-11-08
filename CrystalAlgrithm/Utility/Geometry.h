/*
    Copyright (C) <2023>  <Dezeming>  <feimos@mail.ustc.edu.cn>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or any
    later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.

    Github site: <https://github.com/dezeming/Crystal>
*/

#ifndef __Geometry_h__
#define __Geometry_h__

#include "CrystalAlgrithm/Utility/cuda_Common.cuh"

#include <algorithm>
#include <cmath>
#include <iterator>
#include <string>

namespace CrystalAlgrithm {

template <typename T>
class Vector2;
template <typename T>
class Vector3;
template <typename T>
class Point3;
template <typename T>
class Point2;
template <typename T>
class Normal3;

template <typename T>
HOST_AND_DEVICE inline bool isNaN(const T x) {
    return std::isnan(x);
}
template <>
HOST_AND_DEVICE inline bool isNaN(const int x) {
    return false;
}

// Vector Declarations
template <typename T>
class Vector2 {
public:
    // Vector2 Public Methods
    HOST_AND_DEVICE Vector2() { x = y = 0; }
    HOST_AND_DEVICE Vector2(T xx, T yy) : x(xx), y(yy) { DCHECK(!HasNaNs()); }
    HOST_AND_DEVICE bool HasNaNs() const { return isNaN(x) || isNaN(y); }
    HOST_AND_DEVICE explicit Vector2(const Point2<T>& p);
    HOST_AND_DEVICE explicit Vector2(const Point3<T>& p);

    HOST_AND_DEVICE Vector2<T> operator+(const Vector2<T>& v) const {
        DCHECK(!v.HasNaNs());
        return Vector2(x + v.x, y + v.y);
    }

    HOST_AND_DEVICE Vector2<T>& operator+=(const Vector2<T>& v) {
        DCHECK(!v.HasNaNs());
        x += v.x;
        y += v.y;
        return *this;
    }
    HOST_AND_DEVICE Vector2<T> operator-(const Vector2<T>& v) const {
        DCHECK(!v.HasNaNs());
        return Vector2(x - v.x, y - v.y);
    }

    HOST_AND_DEVICE Vector2<T>& operator-=(const Vector2<T>& v) {
        DCHECK(!v.HasNaNs());
        x -= v.x;
        y -= v.y;
        return *this;
    }
    HOST_AND_DEVICE bool operator==(const Vector2<T>& v) const { return x == v.x && y == v.y; }
    HOST_AND_DEVICE bool operator!=(const Vector2<T>& v) const { return x != v.x || y != v.y; }
    template <typename U>
    HOST_AND_DEVICE Vector2<T> operator*(U f) const {
        return Vector2<T>(f * x, f * y);
    }

    template <typename U>
    HOST_AND_DEVICE Vector2<T>& operator*=(U f) {
        DCHECK(!isNaN(f));
        x *= f;
        y *= f;
        return *this;
    }
    template <typename U>
    HOST_AND_DEVICE Vector2<T> operator/(U f) const {
        DCHECK_NE(f, 0);
        float inv = (float)1 / f;
        return Vector2<T>(x * inv, y * inv);
    }

    template <typename U>
    HOST_AND_DEVICE Vector2<T>& operator/=(U f) {
        DCHECK_NE(f, 0);
        float inv = (float)1 / f;
        x *= inv;
        y *= inv;
        return *this;
    }
    HOST_AND_DEVICE Vector2<T> operator-() const { return Vector2<T>(-x, -y); }
    HOST_AND_DEVICE T operator[](int i) const {
        DCHECK(i >= 0 && i <= 1);
        if (i == 0) return x;
        return y;
    }

    HOST_AND_DEVICE T& operator[](int i) {
        DCHECK(i >= 0 && i <= 1);
        if (i == 0) return x;
        return y;
    }
    HOST_AND_DEVICE float LengthSquared() const { return x * x + y * y; }
    HOST_AND_DEVICE float Length() const { return std::sqrt(LengthSquared()); }

    // Vector2 Public Data
    T x, y;
};

template <typename T>
class Vector3 {
public:
    // Vector3 Public Methods
    HOST_AND_DEVICE T operator[](int i) const {
        DCHECK(i >= 0 && i <= 2);
        if (i == 0) return x;
        if (i == 1) return y;
        return z;
    }
    HOST_AND_DEVICE T& operator[](int i) {
        DCHECK(i >= 0 && i <= 2);
        if (i == 0) return x;
        if (i == 1) return y;
        return z;
    }
    HOST_AND_DEVICE Vector3() { x = y = z = 0; }
    HOST_AND_DEVICE Vector3(T x, T y, T z) : x(x), y(y), z(z) { DCHECK(!HasNaNs()); }
    HOST_AND_DEVICE bool HasNaNs() const { return isNaN(x) || isNaN(y) || isNaN(z); }
    HOST_AND_DEVICE explicit Vector3(const Point3<T>& p);
    HOST_AND_DEVICE Vector3<T> operator+(const Vector3<T>& v) const {
        DCHECK(!v.HasNaNs());
        return Vector3(x + v.x, y + v.y, z + v.z);
    }
    HOST_AND_DEVICE Vector3<T>& operator+=(const Vector3<T>& v) {
        DCHECK(!v.HasNaNs());
        x += v.x;
        y += v.y;
        z += v.z;
        return *this;
    }
    HOST_AND_DEVICE Vector3<T> operator-(const Vector3<T>& v) const {
        DCHECK(!v.HasNaNs());
        return Vector3(x - v.x, y - v.y, z - v.z);
    }
    HOST_AND_DEVICE Vector3<T>& operator-=(const Vector3<T>& v) {
        DCHECK(!v.HasNaNs());
        x -= v.x;
        y -= v.y;
        z -= v.z;
        return *this;
    }
    HOST_AND_DEVICE bool operator==(const Vector3<T>& v) const {
        return x == v.x && y == v.y && z == v.z;
    }
    HOST_AND_DEVICE bool operator!=(const Vector3<T>& v) const {
        return x != v.x || y != v.y || z != v.z;
    }
    template <typename U>
    HOST_AND_DEVICE Vector3<T> operator*(U s) const {
        return Vector3<T>(s * x, s * y, s * z);
    }
    template <typename U>
    HOST_AND_DEVICE Vector3<T>& operator*=(U s) {
        DCHECK(!isNaN(s));
        x *= s;
        y *= s;
        z *= s;
        return *this;
    }
    template <typename U>
    HOST_AND_DEVICE Vector3<T> operator/(U f) const {
        DCHECK_NE(f, 0);
        float inv = (float)1 / f;
        return Vector3<T>(x * inv, y * inv, z * inv);
    }

    template <typename U>
    HOST_AND_DEVICE Vector3<T>& operator/=(U f) {
        DCHECK_NE(f, 0);
        float inv = (float)1 / f;
        x *= inv;
        y *= inv;
        z *= inv;
        return *this;
    }
    HOST_AND_DEVICE Vector3<T> operator-() const { return Vector3<T>(-x, -y, -z); }
    HOST_AND_DEVICE float LengthSquared() const { return x * x + y * y + z * z; }
    HOST_AND_DEVICE float Length() const { return std::sqrt(LengthSquared()); }
    HOST_AND_DEVICE explicit Vector3(const Normal3<T>& n);

    // Vector3 Public Data
    T x, y, z;
};


typedef Vector2<float> Vector2f;
typedef Vector2<int> Vector2i;
typedef Vector2<unsigned int> Vector2ui;

typedef Vector3<float> Vector3f;
typedef Vector3<int> Vector3i;
typedef Vector3<unsigned int> Vector3ui;

// Point Declarations
template <typename T>
class Point2 {
public:
    // Point2 Public Methods
    HOST_AND_DEVICE explicit Point2(const Point3<T>& p) : x(p.x), y(p.y) { DCHECK(!HasNaNs()); }
    HOST_AND_DEVICE Point2() { x = y = 0; }
    HOST_AND_DEVICE Point2(T xx, T yy) : x(xx), y(yy) { DCHECK(!HasNaNs()); }

    template <typename U>
    HOST_AND_DEVICE explicit Point2(const Point2<U>& p) {
        x = (T)p.x;
        y = (T)p.y;
        DCHECK(!HasNaNs());
    }

    template <typename U>
    HOST_AND_DEVICE explicit Point2(const Vector2<U>& p) {
        x = (T)p.x;
        y = (T)p.y;
        DCHECK(!HasNaNs());
    }

    template <typename U>
    HOST_AND_DEVICE explicit operator Vector2<U>() const {
        return Vector2<U>(x, y);
    }

    HOST_AND_DEVICE Point2<T> operator+(const Vector2<T>& v) const {
        DCHECK(!v.HasNaNs());
        return Point2<T>(x + v.x, y + v.y);
    }

    HOST_AND_DEVICE Point2<T>& operator+=(const Vector2<T>& v) {
        DCHECK(!v.HasNaNs());
        x += v.x;
        y += v.y;
        return *this;
    }
    HOST_AND_DEVICE Vector2<T> operator-(const Point2<T>& p) const {
        DCHECK(!p.HasNaNs());
        return Vector2<T>(x - p.x, y - p.y);
    }

    HOST_AND_DEVICE Point2<T> operator-(const Vector2<T>& v) const {
        DCHECK(!v.HasNaNs());
        return Point2<T>(x - v.x, y - v.y);
    }
    HOST_AND_DEVICE Point2<T> operator-() const { return Point2<T>(-x, -y); }
    HOST_AND_DEVICE Point2<T>& operator-=(const Vector2<T>& v) {
        DCHECK(!v.HasNaNs());
        x -= v.x;
        y -= v.y;
        return *this;
    }
    HOST_AND_DEVICE Point2<T>& operator+=(const Point2<T>& p) {
        DCHECK(!p.HasNaNs());
        x += p.x;
        y += p.y;
        return *this;
    }
    HOST_AND_DEVICE Point2<T> operator+(const Point2<T>& p) const {
        DCHECK(!p.HasNaNs());
        return Point2<T>(x + p.x, y + p.y);
    }
    template <typename U>
    HOST_AND_DEVICE Point2<T> operator*(U f) const {
        return Point2<T>(f * x, f * y);
    }
    template <typename U>
    HOST_AND_DEVICE Point2<T>& operator*=(U f) {
        x *= f;
        y *= f;
        return *this;
    }
    template <typename U>
    HOST_AND_DEVICE Point2<T> operator/(U f) const {
        CHECK_NE(f, 0);
        float inv = (float)1 / f;
        return Point2<T>(inv * x, inv * y);
    }
    template <typename U>
    HOST_AND_DEVICE Point2<T>& operator/=(U f) {
        CHECK_NE(f, 0);
        float inv = (float)1 / f;
        x *= inv;
        y *= inv;
        return *this;
    }
    HOST_AND_DEVICE T operator[](int i) const {
        DCHECK(i >= 0 && i <= 1);
        if (i == 0) return x;
        return y;
    }

    HOST_AND_DEVICE T& operator[](int i) {
        DCHECK(i >= 0 && i <= 1);
        if (i == 0) return x;
        return y;
    }
    HOST_AND_DEVICE bool operator==(const Point2<T>& p) const { return x == p.x && y == p.y; }
    HOST_AND_DEVICE bool operator!=(const Point2<T>& p) const { return x != p.x || y != p.y; }
    HOST_AND_DEVICE bool HasNaNs() const { return isNaN(x) || isNaN(y); }

    // Point2 Public Data
    T x, y;
};


template <typename T>
class Point3 {
public:
    // Point3 Public Methods
    HOST_AND_DEVICE Point3() { x = y = z = 0; }
    HOST_AND_DEVICE Point3(T x, T y, T z) : x(x), y(y), z(z) { DCHECK(!HasNaNs()); }
    template <typename U>
    HOST_AND_DEVICE explicit Point3(const Point3<U>& p)
        : x((T)p.x), y((T)p.y), z((T)p.z) {
        DCHECK(!HasNaNs());
    }
    template <typename U>
    HOST_AND_DEVICE explicit operator Vector3<U>() const {
        return Vector3<U>(x, y, z);
    }
    HOST_AND_DEVICE Point3<T> operator+(const Vector3<T>& v) const {
        DCHECK(!v.HasNaNs());
        return Point3<T>(x + v.x, y + v.y, z + v.z);
    }
    HOST_AND_DEVICE Point3<T>& operator+=(const Vector3<T>& v) {
        DCHECK(!v.HasNaNs());
        x += v.x;
        y += v.y;
        z += v.z;
        return *this;
    }
    HOST_AND_DEVICE Vector3<T> operator-(const Point3<T>& p) const {
        DCHECK(!p.HasNaNs());
        return Vector3<T>(x - p.x, y - p.y, z - p.z);
    }
    HOST_AND_DEVICE Point3<T> operator-(const Vector3<T>& v) const {
        DCHECK(!v.HasNaNs());
        return Point3<T>(x - v.x, y - v.y, z - v.z);
    }
    HOST_AND_DEVICE Point3<T>& operator-=(const Vector3<T>& v) {
        DCHECK(!v.HasNaNs());
        x -= v.x;
        y -= v.y;
        z -= v.z;
        return *this;
    }
    HOST_AND_DEVICE Point3<T>& operator+=(const Point3<T>& p) {
        DCHECK(!p.HasNaNs());
        x += p.x;
        y += p.y;
        z += p.z;
        return *this;
    }
    HOST_AND_DEVICE Point3<T> operator+(const Point3<T>& p) const {
        DCHECK(!p.HasNaNs());
        return Point3<T>(x + p.x, y + p.y, z + p.z);
    }
    template <typename U>
    HOST_AND_DEVICE Point3<T> operator*(U f) const {
        return Point3<T>(f * x, f * y, f * z);
    }
    template <typename U>
    HOST_AND_DEVICE Point3<T>& operator*=(U f) {
        x *= f;
        y *= f;
        z *= f;
        return *this;
    }
    template <typename U>
    HOST_AND_DEVICE Point3<T> operator/(U f) const {
        DCHECK_NE(f, 0);
        float inv = (float)1 / f;
        return Point3<T>(inv * x, inv * y, inv * z);
    }
    template <typename U>
    HOST_AND_DEVICE Point3<T>& operator/=(U f) {
        DCHECK_NE(f, 0);
        float inv = (float)1 / f;
        x *= inv;
        y *= inv;
        z *= inv;
        return *this;
    }
    HOST_AND_DEVICE T operator[](int i) const {
        DCHECK(i >= 0 && i <= 2);
        if (i == 0) return x;
        if (i == 1) return y;
        return z;
    }

    HOST_AND_DEVICE T& operator[](int i) {
        DCHECK(i >= 0 && i <= 2);
        if (i == 0) return x;
        if (i == 1) return y;
        return z;
    }
    HOST_AND_DEVICE bool operator==(const Point3<T>& p) const {
        return x == p.x && y == p.y && z == p.z;
    }
    HOST_AND_DEVICE bool operator!=(const Point3<T>& p) const {
        return x != p.x || y != p.y || z != p.z;
    }
    HOST_AND_DEVICE bool HasNaNs() const { return isNaN(x) || isNaN(y) || isNaN(z); }
    HOST_AND_DEVICE Point3<T> operator-() const { return Point3<T>(-x, -y, -z); }

    // Point3 Public Data
    T x, y, z;
};

typedef Point2<float> Point2f;
typedef Point2<int> Point2i;
typedef Point3<float> Point3f;
typedef Point3<int> Point3i;

// Normal Declarations
template <typename T>
class Normal3 {
public:
    // Normal3 Public Methods
    HOST_AND_DEVICE Normal3() { x = y = z = 0; }
    HOST_AND_DEVICE Normal3(T xx, T yy, T zz) : x(xx), y(yy), z(zz) { DCHECK(!HasNaNs()); }
    HOST_AND_DEVICE Normal3<T> operator-() const { return Normal3(-x, -y, -z); }
    HOST_AND_DEVICE Normal3<T> operator+(const Normal3<T>& n) const {
        DCHECK(!n.HasNaNs());
        return Normal3<T>(x + n.x, y + n.y, z + n.z);
    }

    HOST_AND_DEVICE Normal3<T>& operator+=(const Normal3<T>& n) {
        DCHECK(!n.HasNaNs());
        x += n.x;
        y += n.y;
        z += n.z;
        return *this;
    }
    HOST_AND_DEVICE Normal3<T> operator-(const Normal3<T>& n) const {
        DCHECK(!n.HasNaNs());
        return Normal3<T>(x - n.x, y - n.y, z - n.z);
    }

    HOST_AND_DEVICE Normal3<T>& operator-=(const Normal3<T>& n) {
        DCHECK(!n.HasNaNs());
        x -= n.x;
        y -= n.y;
        z -= n.z;
        return *this;
    }
    HOST_AND_DEVICE bool HasNaNs() const { return isNaN(x) || isNaN(y) || isNaN(z); }
    template <typename U>
    HOST_AND_DEVICE Normal3<T> operator*(U f) const {
        return Normal3<T>(f * x, f * y, f * z);
    }

    template <typename U>
    HOST_AND_DEVICE Normal3<T>& operator*=(U f) {
        x *= f;
        y *= f;
        z *= f;
        return *this;
    }
    template <typename U>
    HOST_AND_DEVICE Normal3<T> operator/(U f) const {
        DCHECK_NE(f, 0);
        float inv = (float)1 / f;
        return Normal3<T>(x * inv, y * inv, z * inv);
    }

    template <typename U>
    HOST_AND_DEVICE Normal3<T>& operator/=(U f) {
        DCHECK_NE(f, 0);
        float inv = (float)1 / f;
        x *= inv;
        y *= inv;
        z *= inv;
        return *this;
    }
    HOST_AND_DEVICE float LengthSquared() const { return x * x + y * y + z * z; }
    HOST_AND_DEVICE float Length() const { return std::sqrt(LengthSquared()); }

    HOST_AND_DEVICE explicit Normal3<T>(const Vector3<T>& v) : x(v.x), y(v.y), z(v.z) {
        DCHECK(!v.HasNaNs());
    }
    HOST_AND_DEVICE bool operator==(const Normal3<T>& n) const {
        return x == n.x && y == n.y && z == n.z;
    }
    HOST_AND_DEVICE bool operator!=(const Normal3<T>& n) const {
        return x != n.x || y != n.y || z != n.z;
    }

    HOST_AND_DEVICE T operator[](int i) const {
        DCHECK(i >= 0 && i <= 2);
        if (i == 0) return x;
        if (i == 1) return y;
        return z;
    }

    HOST_AND_DEVICE T& operator[](int i) {
        DCHECK(i >= 0 && i <= 2);
        if (i == 0) return x;
        if (i == 1) return y;
        return z;
    }

    // Normal3 Public Data
    T x, y, z;
};

typedef Normal3<float> Normal3f;

// Geometry Inline Functions
template <typename T>
HOST_AND_DEVICE inline Vector3<T>::Vector3(const Point3<T>& p)
    : x(p.x), y(p.y), z(p.z) {
    DCHECK(!HasNaNs());
}

template <typename T, typename U>
HOST_AND_DEVICE inline Vector3<T> operator*(U s, const Vector3<T>& v) {
    return v * s;
}
template <typename T>
HOST_AND_DEVICE Vector3<T> Abs(const Vector3<T>& v) {
    return Vector3<T>(std::abs(v.x), std::abs(v.y), std::abs(v.z));
}

template <typename T>
HOST_AND_DEVICE inline T Dot(const Vector3<T>& v1, const Vector3<T>& v2) {
    DCHECK(!v1.HasNaNs() && !v2.HasNaNs());
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

template <typename T>
HOST_AND_DEVICE inline T AbsDot(const Vector3<T>& v1, const Vector3<T>& v2) {
    DCHECK(!v1.HasNaNs() && !v2.HasNaNs());
    return std::abs(Dot(v1, v2));
}

template <typename T>
HOST_AND_DEVICE inline Vector3<T> Cross(const Vector3<T>& v1, const Vector3<T>& v2) {
    DCHECK(!v1.HasNaNs() && !v2.HasNaNs());
    double v1x = v1.x, v1y = v1.y, v1z = v1.z;
    double v2x = v2.x, v2y = v2.y, v2z = v2.z;
    return Vector3<T>((v1y * v2z) - (v1z * v2y), (v1z * v2x) - (v1x * v2z),
        (v1x * v2y) - (v1y * v2x));
}

template <typename T>
HOST_AND_DEVICE inline Vector3<T> Cross(const Vector3<T>& v1, const Normal3<T>& v2) {
    DCHECK(!v1.HasNaNs() && !v2.HasNaNs());
    double v1x = v1.x, v1y = v1.y, v1z = v1.z;
    double v2x = v2.x, v2y = v2.y, v2z = v2.z;
    return Vector3<T>((v1y * v2z) - (v1z * v2y), (v1z * v2x) - (v1x * v2z),
        (v1x * v2y) - (v1y * v2x));
}

template <typename T>
HOST_AND_DEVICE inline Vector3<T> Cross(const Normal3<T>& v1, const Vector3<T>& v2) {
    DCHECK(!v1.HasNaNs() && !v2.HasNaNs());
    double v1x = v1.x, v1y = v1.y, v1z = v1.z;
    double v2x = v2.x, v2y = v2.y, v2z = v2.z;
    return Vector3<T>((v1y * v2z) - (v1z * v2y), (v1z * v2x) - (v1x * v2z),
        (v1x * v2y) - (v1y * v2x));
}

template <typename T>
HOST_AND_DEVICE inline Vector3<T> Normalize(const Vector3<T>& v) {
    return v / v.Length();
}
template <typename T>
HOST_AND_DEVICE T MinComponent(const Vector3<T>& v) {
    return std::min(v.x, std::min(v.y, v.z));
}

template <typename T>
HOST_AND_DEVICE T MaxComponent(const Vector3<T>& v) {
    return std::max(v.x, std::max(v.y, v.z));
}

template <typename T>
HOST_AND_DEVICE int MaxDimension(const Vector3<T>& v) {
    return (v.x > v.y) ? ((v.x > v.z) ? 0 : 2) : ((v.y > v.z) ? 1 : 2);
}

template <typename T>
HOST_AND_DEVICE Vector3<T> Min(const Vector3<T>& p1, const Vector3<T>& p2) {
    return Vector3<T>(std::min(p1.x, p2.x), std::min(p1.y, p2.y),
        std::min(p1.z, p2.z));
}

template <typename T>
HOST_AND_DEVICE Vector3<T> Max(const Vector3<T>& p1, const Vector3<T>& p2) {
    return Vector3<T>(std::max(p1.x, p2.x), std::max(p1.y, p2.y),
        std::max(p1.z, p2.z));
}

template <typename T>
HOST_AND_DEVICE Vector3<T> Permute(const Vector3<T>& v, int x, int y, int z) {
    return Vector3<T>(v[x], v[y], v[z]);
}

template <typename T>
HOST_AND_DEVICE inline void CoordinateSystem(const Vector3<T>& v1, Vector3<T>* v2,
    Vector3<T>* v3) {
    if (std::abs(v1.x) > std::abs(v1.y))
        *v2 = Vector3<T>(-v1.z, 0, v1.x) / std::sqrt(v1.x * v1.x + v1.z * v1.z);
    else
        *v2 = Vector3<T>(0, v1.z, -v1.y) / std::sqrt(v1.y * v1.y + v1.z * v1.z);
    *v3 = Cross(v1, *v2);
}

template <typename T>
HOST_AND_DEVICE Vector2<T>::Vector2(const Point2<T>& p)
    : x(p.x), y(p.y) {
    DCHECK(!HasNaNs());
}

template <typename T>
HOST_AND_DEVICE Vector2<T>::Vector2(const Point3<T>& p)
    : x(p.x), y(p.y) {
    DCHECK(!HasNaNs());
}

template <typename T, typename U>
HOST_AND_DEVICE inline Vector2<T> operator*(U f, const Vector2<T>& v) {
    return v * f;
}
template <typename T>
HOST_AND_DEVICE inline float Dot(const Vector2<T>& v1, const Vector2<T>& v2) {
    DCHECK(!v1.HasNaNs() && !v2.HasNaNs());
    return v1.x * v2.x + v1.y * v2.y;
}

template <typename T>
HOST_AND_DEVICE inline float AbsDot(const Vector2<T>& v1, const Vector2<T>& v2) {
    DCHECK(!v1.HasNaNs() && !v2.HasNaNs());
    return std::abs(Dot(v1, v2));
}

template <typename T>
HOST_AND_DEVICE inline Vector2<T> Normalize(const Vector2<T>& v) {
    return v / v.Length();
}
template <typename T>
HOST_AND_DEVICE Vector2<T> Abs(const Vector2<T>& v) {
    return Vector2<T>(std::abs(v.x), std::abs(v.y));
}

template <typename T>
HOST_AND_DEVICE inline float Distance(const Point3<T>& p1, const Point3<T>& p2) {
    return (p1 - p2).Length();
}

template <typename T>
HOST_AND_DEVICE inline float DistanceSquared(const Point3<T>& p1, const Point3<T>& p2) {
    return (p1 - p2).LengthSquared();
}

template <typename T, typename U>
HOST_AND_DEVICE inline Point3<T> operator*(U f, const Point3<T>& p) {
    DCHECK(!p.HasNaNs());
    return p * f;
}

template <typename T>
HOST_AND_DEVICE Point3<T> Lerp(float t, const Point3<T>& p0, const Point3<T>& p1) {
    return (1 - t) * p0 + t * p1;
}

template <typename T>
HOST_AND_DEVICE Point3<T> Min(const Point3<T>& p1, const Point3<T>& p2) {
    return Point3<T>(std::min(p1.x, p2.x), std::min(p1.y, p2.y),
        std::min(p1.z, p2.z));
}

template <typename T>
HOST_AND_DEVICE Point3<T> Max(const Point3<T>& p1, const Point3<T>& p2) {
    return Point3<T>(std::max(p1.x, p2.x), std::max(p1.y, p2.y),
        std::max(p1.z, p2.z));
}

template <typename T>
HOST_AND_DEVICE Point3<T> Floor(const Point3<T>& p) {
    return Point3<T>(std::floor(p.x), std::floor(p.y), std::floor(p.z));
}

template <typename T>
HOST_AND_DEVICE Point3<T> Ceil(const Point3<T>& p) {
    return Point3<T>(std::ceil(p.x), std::ceil(p.y), std::ceil(p.z));
}

template <typename T>
HOST_AND_DEVICE Point3<T> Abs(const Point3<T>& p) {
    return Point3<T>(std::abs(p.x), std::abs(p.y), std::abs(p.z));
}

template <typename T>
HOST_AND_DEVICE inline float Distance(const Point2<T>& p1, const Point2<T>& p2) {
    return (p1 - p2).Length();
}

template <typename T>
HOST_AND_DEVICE inline float DistanceSquared(const Point2<T>& p1, const Point2<T>& p2) {
    return (p1 - p2).LengthSquared();
}

template <typename T, typename U>
HOST_AND_DEVICE inline Point2<T> operator*(U f, const Point2<T>& p) {
    DCHECK(!p.HasNaNs());
    return p * f;
}

template <typename T>
HOST_AND_DEVICE Point2<T> Floor(const Point2<T>& p) {
    return Point2<T>(std::floor(p.x), std::floor(p.y));
}

template <typename T>
HOST_AND_DEVICE Point2<T> Ceil(const Point2<T>& p) {
    return Point2<T>(std::ceil(p.x), std::ceil(p.y));
}

template <typename T>
HOST_AND_DEVICE Point2<T> Lerp(float t, const Point2<T>& v0, const Point2<T>& v1) {
    return (1 - t) * v0 + t * v1;
}

template <typename T>
HOST_AND_DEVICE Point2<T> Min(const Point2<T>& pa, const Point2<T>& pb) {
    return Point2<T>(std::min(pa.x, pb.x), std::min(pa.y, pb.y));
}

template <typename T>
HOST_AND_DEVICE Point2<T> Max(const Point2<T>& pa, const Point2<T>& pb) {
    return Point2<T>(std::max(pa.x, pb.x), std::max(pa.y, pb.y));
}

template <typename T>
HOST_AND_DEVICE Point3<T> Permute(const Point3<T>& p, int x, int y, int z) {
    return Point3<T>(p[x], p[y], p[z]);
}

template <typename T, typename U>
HOST_AND_DEVICE inline Normal3<T> operator*(U f, const Normal3<T>& n) {
    return Normal3<T>(f * n.x, f * n.y, f * n.z);
}

template <typename T>
HOST_AND_DEVICE inline Normal3<T> Normalize(const Normal3<T>& n) {
    return n / n.Length();
}

template <typename T>
HOST_AND_DEVICE inline Vector3<T>::Vector3(const Normal3<T>& n)
    : x(n.x), y(n.y), z(n.z) {
    DCHECK(!n.HasNaNs());
}

template <typename T>
HOST_AND_DEVICE inline T Dot(const Normal3<T>& n1, const Vector3<T>& v2) {
    DCHECK(!n1.HasNaNs() && !v2.HasNaNs());
    return n1.x * v2.x + n1.y * v2.y + n1.z * v2.z;
}

template <typename T>
HOST_AND_DEVICE inline T Dot(const Vector3<T>& v1, const Normal3<T>& n2) {
    DCHECK(!v1.HasNaNs() && !n2.HasNaNs());
    return v1.x * n2.x + v1.y * n2.y + v1.z * n2.z;
}

template <typename T>
HOST_AND_DEVICE inline T Dot(const Normal3<T>& n1, const Normal3<T>& n2) {
    DCHECK(!n1.HasNaNs() && !n2.HasNaNs());
    return n1.x * n2.x + n1.y * n2.y + n1.z * n2.z;
}

template <typename T>
HOST_AND_DEVICE inline T AbsDot(const Normal3<T>& n1, const Vector3<T>& v2) {
    DCHECK(!n1.HasNaNs() && !v2.HasNaNs());
    return std::abs(n1.x * v2.x + n1.y * v2.y + n1.z * v2.z);
}

template <typename T>
HOST_AND_DEVICE inline T AbsDot(const Vector3<T>& v1, const Normal3<T>& n2) {
    DCHECK(!v1.HasNaNs() && !n2.HasNaNs());
    return std::abs(v1.x * n2.x + v1.y * n2.y + v1.z * n2.z);
}

template <typename T>
HOST_AND_DEVICE inline T AbsDot(const Normal3<T>& n1, const Normal3<T>& n2) {
    DCHECK(!n1.HasNaNs() && !n2.HasNaNs());
    return std::abs(n1.x * n2.x + n1.y * n2.y + n1.z * n2.z);
}

template <typename T>
HOST_AND_DEVICE inline Normal3<T> Faceforward(const Normal3<T>& n, const Vector3<T>& v) {
    return (Dot(n, v) < 0.f) ? -n : n;
}

template <typename T>
HOST_AND_DEVICE inline Normal3<T> Faceforward(const Normal3<T>& n, const Normal3<T>& n2) {
    return (Dot(n, n2) < 0.f) ? -n : n;
}

template <typename T>
HOST_AND_DEVICE inline Vector3<T> Faceforward(const Vector3<T>& v, const Vector3<T>& v2) {
    return (Dot(v, v2) < 0.f) ? -v : v;
}

template <typename T>
HOST_AND_DEVICE inline Vector3<T> Faceforward(const Vector3<T>& v, const Normal3<T>& n2) {
    return (Dot(v, n2) < 0.f) ? -v : v;
}

template <typename T>
HOST_AND_DEVICE Normal3<T> Abs(const Normal3<T>& v) {
    return Normal3<T>(std::abs(v.x), std::abs(v.y), std::abs(v.z));
}






}


#endif



