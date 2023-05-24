#include "AzurMath.h"

#include <cmath>

namespace AzurMath {
	// It takes two points of a linear function and find a point of that linear function given a x value. 
	vector2float find_point_y(vector2float point0, vector2float point1, float point_x)
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

	// It takes two points of a linear function and find a point of that linear function given a x value. 
	vector2float find_point_x(vector2float point0, vector2float point1, float point_y)
	{
		// Slope: m = (y1 - y0) / (x1 - x0)
		// Linear Function: f(x) = m * x + b
		// Find linear function that crosses the two colliders
		float m = (point1.y - point0.y) / (point1.x - point0.x); // Find Slope
		float b = (point0.y) / (m * point0.x);					 // Find y-intercept
		float y = point_y;
		float x = (y - b) / m;
		return { x, y };
	}

	// NOT IMPLEMENTEDED
	vector2float find_point_distance(vector2float point0, vector2float point1, float distance)
	{
		return vector2float();
	}

	// Returns the distance between two points
	float find_distance_between_points(vector2float point0, vector2float point1)
	{
		return (float)sqrt(pow(point1.x - point0.x, 2) + pow(point1.y - point0.y, 2));
	}
}
