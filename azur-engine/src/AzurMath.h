#ifndef _MATH_H
#define _MATH_H

#include "vector2float.h"

namespace AzurMath
{
	vector2float find_point_y(vector2float point0, vector2float point1, float point_x);
	vector2float find_point_x(vector2float point0, vector2float point1, float point_y);
}

#endif // _MATH_H
