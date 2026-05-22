#pragma once
#include <random>

template <typename T>
inline T RandomMt19937(T min, T max)
{
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<T> dist(min, max);
	return dist(mt);
}