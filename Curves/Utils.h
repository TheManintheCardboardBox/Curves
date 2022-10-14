#pragma once

#include <algorithm>
#include <future>
#include <memory>
#include <numeric>
#include <random>
#include <thread>
#include <vector>
#include "../Library/Library.h"

template <typename Iterator, typename T, typename Lambda>
struct Accumulator
{
    T operator()(Iterator first, Iterator last, T init, Lambda lambda)
    {
        return std::accumulate(first, last, init, lambda);
    }
};

template <typename Iterator, typename T, typename Lambda>
T ParallelAccumulate(Iterator first, Iterator last, T init, Lambda lambda)
{
    const int length = std::distance(first, last);
    if (!length)
    {
        return init;
    }

    const int minPerThread = 25;
    const int maxThreads = (length + minPerThread - 1) / minPerThread;
    const int hardwareThreads = std::thread::hardware_concurrency();
    const int numThreads = std::min(hardwareThreads, maxThreads);
    const int blockSize = length / numThreads;

    std::vector<std::future<T>> futures(numThreads - 1);
    std::vector<std::thread> threads(numThreads - 1);

    Iterator blockStart = first;
    for (int i = 0; i < numThreads - 1; ++i)
    {
        Iterator blockEnd = blockStart;
        std::advance(blockEnd, blockSize);

        std::packaged_task<T(Iterator, Iterator, T, Lambda)> task(Accumulator<Iterator, T, Lambda>{});
        futures[i] = task.get_future();
        threads[i] = std::thread(std::move(task), blockStart, blockEnd, T(), lambda);

        blockStart = blockEnd;
    }

    T lastResult = Accumulator<Iterator, T, Lambda>{}(blockStart, last, T(), lambda);
    std::for_each(threads.begin(),threads.end(), std::mem_fn(&std::thread::join));

    T result = init;
    for(int i = 0; i < numThreads - 1; ++i)
    {
        result += futures[i].get();
    }
    result += lastResult;

    return result;
}

std::unique_ptr<ParametricCurve> CreateRandomObject()
{
    enum class ObjectType
    {
        Circle,
        Ellipse,
        Helix,
        Count
    };

    std::random_device rd;
    std::uniform_int_distribution<int> distribI(0, static_cast<int>(ObjectType::Count) - 1);
    std::uniform_real_distribution<float> distribF(1.0f, 10.0f);

    const ObjectType type = static_cast<ObjectType>(distribI(rd));
    switch (type)
    {
        case ObjectType::Circle:
        {
            const float radius = distribF(rd);
            return CreateCircle(radius);
        }

        case ObjectType::Ellipse:
        {
            const float a = distribF(rd);
            const float b = distribF(rd);
            return CreateEllipse(a, b);
        }

        case ObjectType::Helix:
        {
            const float radius = distribF(rd);
            const float step = distribF(rd);
            return CreateHelix(radius, step);
        }
    }

    return CreateCircle(1.0f);
}
