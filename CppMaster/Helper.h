#pragma once
#include <utility>
#include <vector>

#ifndef HELPER_H
#define HELPER_H

static int Min(int x, int y, int z) 
{ 
	using namespace std;
	return min(min(x, y), z); 
}

template<typename T>
void Free(std::vector<T*>& list)
{
	for (auto& ele : list)
	{
		delete ele;
		ele = nullptr;
	}
	list.clear();
}

#endif