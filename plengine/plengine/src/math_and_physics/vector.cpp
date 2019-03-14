#include "vector.h"
#include "base.h"

Vector::Vector(Point p1, Point p2) : Position(p2 - p1) { }
Vector::Vector(Point p) : Position(p) { }
Vector::Vector(double length, double angle) : Vector(Point(Cos(angle) * length, Sin(angle) * length)) { }
Vector::Vector() : Vector(NULL) { }

Vector Vector::operator+(Vector v)
{
	return Vector(Point(Position.x + v.Position.x, Position.y + v.Position.y));
}
Vector Vector::operator*(Vector v)
{
	return Vector();
}
Vector Vector::operator*(double v)
{
	return Vector(Position * v);
}

double Vector::Length()
{
	return GetDistance(NULL, Position);
}
double Vector::Angle()
{
	return GetAngle(Position);
}

Camera::Camera(Point p, double d) : Position(p), Distance(d) { }
Camera::Camera(Point p) : Camera(p, 1) { }
Camera::Camera() : Camera(NULL, 1) { }

Point GetCameraView(Point p, Camera * camera)
{
	p -= camera->Position;
	Vector v = p;
	v = v * CAMERA_HOMOTHETY(camera->Distance, p);
	return v.Position;
}
