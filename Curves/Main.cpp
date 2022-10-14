#include "Utils.h"

static constexpr int numObjects = 1000;

int main()
{
    std::vector<std::unique_ptr<ParametricCurve>> v0;
    v0.reserve(numObjects);
    for (int i = 0; i < numObjects; ++i)
    {
        v0.push_back(CreateRandomObject());
    }

    std::cout << "Coordinates of points and derivatives at t = PI/4:" << std::endl;
    for (auto& c : v0)
    {
        std::cout << c->Evaluate(PI_DIV_4) << "\t" << c->Derivative(PI_DIV_4) << std::endl;
    }

    std::vector<Circle*> v1;
    for (auto& c : v0)
    {
        auto cp = dynamic_cast<Circle*>(c.get());
        if (cp)
        {
            v1.push_back(cp);
        }
    }

    std::sort(
        v1.begin(),
        v1.end(),
        [](auto c0, auto c1)
        {
            return c0->Radius() < c1->Radius();
        });

    auto totalSum = ParallelAccumulate(
        v1.begin(),
        v1.end(),
        0.0f,
        [](float total, Circle* c)
        {
            return total + c->Radius();
        });
}
