#include <cmath>
#include <stdexcept>
#include "Library.h"

ParametricCurve::ParametricCurve(float lowerBound, float upperBound) :
    lowerBound(lowerBound),
    upperBound(upperBound)
{
    if (lowerBound > upperBound)
    {
        throw std::invalid_argument("Lower bound cannot be greater than upper bound");
    }
}

Circle::Circle(float radius) :
    ParametricCurve(0, PI_2),
    radius(radius)
{
    if (radius <= 0.0f)
    {
        throw std::invalid_argument("Radius must be positive");
    }
}

Point __stdcall Circle::Evaluate(float t) const
{
    if (t < lowerBound || t >= upperBound)
    {
        throw std::invalid_argument("Parameter is out of bounds");
    }

    return Point(radius * std::cos(t), radius * std::sin(t), 0.0f);
}

Vec3 __stdcall Circle::Derivative(float t) const
{
    if (t < lowerBound || t >= upperBound)
    {
        throw std::invalid_argument("Parameter is out of bounds");
    }

    return Vec3(-radius * std::sin(t), radius * std::cos(t), 0.0f);
}

Ellipse::Ellipse(float a, float b) :
    ParametricCurve(0, PI_2),
    a(a),
    b(b)
{
    if (a <= 0.0f || b <= 0.0f)
    {
        throw std::invalid_argument("Radii must be positive");
    }
}

Point __stdcall Ellipse::Evaluate(float t) const
{
    if (t < lowerBound || t >= upperBound)
    {
        throw std::invalid_argument("Parameter is out of bounds");
    }

    return Point(a * std::cos(t), b * std::sin(t), 0.0f);
}

Vec3 __stdcall Ellipse::Derivative(float t) const
{
    if (t < lowerBound || t >= upperBound)
    {
        throw std::invalid_argument("Parameter is out of bounds");
    }

    return Vec3(-a * std::sin(t), b * std::cos(t), 0.0f);
}

Helix::Helix(float radius, float step) :
    ParametricCurve(0, FLT_MAX),
    radius(radius),
    step(step)
{
    if (radius <= 0.0f)
    {
        throw std::invalid_argument("Radius must be positive");
    }

    if (step <= 0.0f)
    {
        throw std::invalid_argument("Step must be positive");
    }
}

Point __stdcall Helix::Evaluate(float t) const
{
    if (t < lowerBound || t >= upperBound)
    {
        throw std::invalid_argument("Parameter is out of bounds");
    }

    return Point(radius * std::cos(t), radius * std::sin(t), step * t * PI_2_INV);
}

Vec3 __stdcall Helix::Derivative(float t) const
{
    if (t < lowerBound || t >= upperBound)
    {
        throw std::invalid_argument("Parameter is out of bounds");
    }

    return Vec3(-radius * std::sin(t), radius * std::cos(t), step * PI_2_INV);
}

std::unique_ptr<ParametricCurve> __stdcall CreateCircle(float radius)
{
    return std::make_unique<Circle>(radius);
}

std::unique_ptr<ParametricCurve> __stdcall CreateEllipse(float a, float b)
{
    return std::make_unique<Ellipse>(a, b);
}

std::unique_ptr<ParametricCurve> __stdcall CreateHelix(float radius, float step)
{
    return std::make_unique<Helix>(radius, step);
}
