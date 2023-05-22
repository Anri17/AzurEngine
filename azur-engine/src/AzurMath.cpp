#include "AzurMath.h"

namespace AzurMath {
	// It takes two points of a linear function and find a point of that linear function given a x value. 
	vector2float find_point(vector2float point0, vector2float point1, float point_x)
	{
		// Slope: m = (y1 - y0) / (x1 - x0)
		// Linear Function: f(x) = m * x + b
		// Find linear function that crosses the two colliders
		float m = (point1.y - point0.y) / (point1.x - point0.x); // Find Slope
		float b = (point0.y) / (m * point0.x);					 // Find y-intercept
		float x = point_x;
		float y = m * x + b;
		return { x, y };
	}
}
