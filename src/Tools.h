#pragma once

#include <iostream>
#include "Object.h"
using namespace std;
class Tools
{
public:

	static void delete1DArray(Object **array)
	{
		delete[] array;
	}

	static void delete2DArray(Object ***array, int size)
	{
		delete2DArrayItems(*array, size);
		delete1DArray(*array);
	}

	static void delete2DArrayItems(Object **array, int size)
	{
		for (int i = 0; i < size; ++i)
		{
			delete array[i];
		}
	}
};
