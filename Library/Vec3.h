#pragma once

#include <iostream>

struct Vec3
{
    float v[3];

    static constexpr int dim = 3;

    Vec3() { v[0] = v[1] = v[2] = 0; }
    Vec3(float x) { v[0] = v[1] = v[2] = x; }
    Vec3(float x, float y, float z) { v[0] = x; v[1] = y; v[2] = z; }

    float& operator[](int i) { return v[i]; }
    const float& operator[](int i) const { return v[i]; }

    Vec3 operator-() const { return Vec3(-v[0], -v[1], -v[2]); }

    Vec3& operator+=(const Vec3& rhs)
    {
        for (int i = 0; i < 3; ++i)
        {
            v[i] += rhs[i];
        }

        return *this;
    }

    Vec3& operator*=(const Vec3& rhs)
    {
        for (int i = 0; i < 3; ++i)
        {
            v[i] *= rhs[i];
        }

        return *this;
    }

    Vec3& operator/=(const Vec3& rhs)
    {
        for (int i = 0; i < 3; ++i)
        {
            v[i] /= rhs[i];
        }

        return *this;
    }
};

inline Vec3 operator+(const Vec3& lhs, const Vec3& rhs)
{
    return Vec3(lhs[0] + rhs[0], lhs[1] + rhs[1], lhs[2] + rhs[2]);
}

inline Vec3 operator+(const Vec3& v, float k)
{
    return Vec3(v[0] + k, v[1] + k, v[2] + k);
}

inline Vec3 operator+(float k, const Vec3& v)
{
    return v + k;
}

inline Vec3 operator-(const Vec3& lhs, const Vec3& rhs)
{
    return Vec3(lhs[0] - rhs[0], lhs[1] - rhs[1], lhs[2] - rhs[2]);
}

inline Vec3 operator-(const Vec3& v, float k)
{
    return Vec3(v[0] - k, v[1] - k, v[2] - k);
}

inline Vec3 operator-(float k, const Vec3& v)
{
    return Vec3(k - v[0], k - v[1], k - v[2]);
}

inline Vec3 operator*(const Vec3& lhs, const Vec3& rhs)
{
    return Vec3(lhs[0] * rhs[0], lhs[1] * rhs[1], lhs[2] * rhs[2]);
}

inline Vec3 operator*(const Vec3& v, float k)
{
    return Vec3(v[0] * k, v[1] * k, v[2] * k);
}

inline Vec3 operator*(float k, const Vec3& v)
{
    return v * k;
}

inline Vec3 operator/(const Vec3& lhs, const Vec3& rhs)
{
    return Vec3(lhs[0] / rhs[0], lhs[1] / rhs[1], lhs[2] / rhs[2]);
}

inline Vec3 operator/(const Vec3& v, float k)
{
    return Vec3(v[0] / k, v[1] / k, v[2] / k);
}

inline Vec3 operator/(float k, const Vec3& v)
{
    return Vec3(k / v[0], k / v[1], k / v[2]);
}

inline float Dot(const Vec3& lhs, const Vec3& rhs)
{
    return lhs[0] * rhs[0] + lhs[1] * rhs[1] + lhs[2] * rhs[2];
}

inline Vec3 Cross(const Vec3& lhs, const Vec3& rhs)
{
    return Vec3(lhs[1] * rhs[2] - lhs[2] * rhs[1], lhs[2] * rhs[0] - lhs[0] * rhs[2], lhs[0] * rhs[1] - lhs[1] * rhs[0]);
}

std::ostream& operator<<(std::ostream& os, const Vec3& v)
{
    os << "(" << v[0] << ", " << v[1] << ", " << v[2] << ")";
    return os;
}
