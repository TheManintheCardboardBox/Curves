#pragma once

#include <memory>
#include "Vec3.h"

using Point = Vec3;

static constexpr float PI = 3.14159265359f;
static constexpr float PI_2 = 2.0f * PI;
static constexpr float PI_2_INV = 1.0f / PI_2;
static constexpr float PI_DIV_4 = 0.25f * PI;

class ParametricCurve
{
public:
    virtual Point __stdcall Evaluate(float t) const = 0;
    virtual Vec3 __stdcall Derivative(float t) const = 0;

protected:
    ParametricCurve(float lowerBound, float upperBound);

protected:
    float lowerBound;
    float upperBound;
};

class Circle : public ParametricCurve
{
public:
    Circle(float radius);

    virtual Point __stdcall Evaluate(float t) const override;
    virtual Vec3 __stdcall Derivative(float t) const override;

    float __stdcall Radius() const { return radius; }

private:
    float radius;
};

class Ellipse : public ParametricCurve
{
public:
    Ellipse(float a, float b);

    virtual Point __stdcall Evaluate(float t) const override;
    virtual Vec3 __stdcall Derivative(float t) const override;

private:
    float a;
    float b;
};

class Helix : public ParametricCurve
{
public:
    Helix(float radius, float step);

    virtual Point __stdcall Evaluate(float t) const override;
    virtual Vec3 __stdcall Derivative(float t) const override;

private:
    float radius;
    float step;
};

#if defined(LIBRARY_EXPORTS)
#define LIBSPEC __declspec(dllexport)
#else
#define LIBSPEC __declspec(dllimport)
#endif

LIBSPEC std::unique_ptr<ParametricCurve> __stdcall CreateCircle(float radius);
LIBSPEC std::unique_ptr<ParametricCurve> __stdcall CreateEllipse(float a, float b);
LIBSPEC std::unique_ptr<ParametricCurve> __stdcall CreateHelix(float radius, float step);
