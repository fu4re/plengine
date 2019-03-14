#ifndef ___BASE_H___
#define ___BASE_H___
#include "point.h"

const double PI = 3.1415926535;
#define RADIANS(e) ( e * PI / 180 )
#define DEGREES(e) ( e * 180 / PI )
#define SQUARE(X) ( X*X )
#define MIDDLE(P1, P2) ((P1 + P2) / 2)
#define XOR(a, b) (a && !b) || (!a && b)

double Abs(double);

double Sin(double);
double Cos(double);
double Atan(double);
double Asin(double);

double GetAngle(Point);
double GetDistance(Point, Point);
double GetDistance(double, double);
double GetCoordinate(double, double coordinate);

Point RotateVector(Point target, Point center, double);
#endif
