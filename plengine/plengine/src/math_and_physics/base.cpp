#include "base.h"
#include <math.h>

double Sin(double degree)
{
	while (degree >= 360) degree -= 360;
	if (degree == 0 || degree == 180) return 0.0;
	if (degree == 90) return 1.0;
	if (degree == 270) return -1.0;
	bool pr;
	if (degree >= 180)
	{
		degree -= 180;
		pr = true;
	}
	if (degree > 90) degree = 180 - degree;
	double r = RADIANS(degree);
	double _sin = sin(r);
	if (pr) return 0 - _sin;
	return _sin;
}

double Cos(double degree)
{
	while (degree >= 360) degree -= 360;
	if (degree == 90 || degree == 270) return 0.0;
	if (degree == 0) return 1.0;
	if (degree == 180) return -1.0;
	bool pr = false;
	if (degree >= 180)
	{
		degree -= 180;
		pr = !pr;
	}
	if (degree > 90)
	{
		degree = 180 - degree;
		pr = !pr;
	}
	double r = RADIANS(degree);
	double _cos = cos(r);
	if (pr) return 0 - _cos;
	return _cos;
}

double Atan(double value)
{
	if (value == 0) return 0;
	if (value < 0) return DEGREES(atan(-value));
	return 180 - DEGREES(atan(value));
}

double Asin(double value)
{
	if (value < 0) return DEGREES(180 + Asin(-value));
	if (value > 1) return 0;
	if (value == 0) return 0;
	if (value == 1) return 90;
	return 180 - DEGREES(asin(value));
}

double GetAngle(Point i)
{
	if (i.y == 0) return NULL;
	if (i.x == 0 && i.y > 0) return 90;
	if (i.x == 0 && i.y < 0) return 270;
	if (i.y > 0) return Atan(i.y / i.x);
	return 180 + Atan(i.y / i.x);
}

double GetDistance(Point a, Point b)
{
	return sqrt(SQUARE(a.x - b.x) + SQUARE(a.y - b.y));
}

double GetDistance(double a, double b)
{
	return Abs(a - b);
}

double GetCoordinate(double a, double b)
{
	return sqrt(SQUARE(a) - SQUARE(b));
}

double Abs(double value)
{
	if (value >= 0)
		return value;
	return 0 - value;
}

Point RotateVector(Point point, Point center, double i)
{
	point -= center;
	i += GetAngle(point);
	double _sin = Sin(i);
	double _cos = Cos(i);
	double len = GetDistance(NULL, point);
	point = Point(_cos * len, _sin * len);
	point += center;
	return point;
}
