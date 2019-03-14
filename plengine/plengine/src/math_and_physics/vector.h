#pragma once
#ifndef __VECTOR_H__
#define __VECTOR_H__
#include "point.h"

struct Vector
{
public:
	Point Position;
	Vector(Point);
	Vector(Point, Point);
	Vector(double length, double angle);
	Vector();
	
	Vector operator+(Vector);
	Vector operator*(Vector);
	Vector operator*(double);

	double Length();
	double Angle();
};

#define NULL_VECTOR Vector()
struct Camera
{
public:
	Point Position;
	double Distance;

	Camera(Point, double);
	Camera(Point);
	Camera();
};

Point GetCameraView(Point, Camera *);

#define CAMERA_HOMOTHETY(e, point) GetDistance(NULL, Point(e, GetDistance(point, 0)))
#define CAMERA_DISTANCE(e, point) GetCoordinate(e, GetDistance(point, 0))
#endif
