#pragma once
#ifndef __PHYSICS_H__
#define __PHYSICS_H__
#include "plmath.h"
#include "collision.h"

#define G 9.80665

#define ACCELERATION(m, A, drag, vector) (vector * m * A * (1 - drag))
#define GRAVITY_ACCELERATION(m, drag) ACCELERATION(m, G, drag, Vector(Point(0, -1)))
#define FORCE_FRICTION(N, k) (N * k)

typedef Vector Speed;
typedef int Time;  //milliseconds

#define MOVE(point, speed) point += speed.Position;

struct Ground
{
public:
	double Strong;
	Line Colider;
	Ground(Line, double);
	Ground(Line);
	Ground();
};

struct Rigidbody
{
public:
	double Mass, Drag, Strong;
	bool UseGravity, Brakeable;
	Speed Acceleration;

	Rigidbody(double m, double d, double s, bool u, bool b, Speed);
	Rigidbody();
};
struct Object
{
public:
	Objectm Colider;
	Objectm Visible;
	Point Center;
	Rigidbody Params;

	inline Object(Point, Objectm * colider, Objectm * visible, Rigidbody);
	inline Object(Objectm * colider, Objectm * visible, Rigidbody);
	inline Object(Objectm *, Rigidbody);
	inline Object(Objectm * colider, Objectm * visible);
	inline Object(Objectm *);
	Object();
};

struct Space
{
	Ground Plane;
	std::vector<Object> Objects;
};

Space GetCameraView(Space *, Camera *);
void SetSpaceCenter(Space *, Point);
std::vector<Object> DestroyObject(Object *, int /*max parts count*/);

//Time = 1F
Speed ApplyGravity(Object * q, Ground * l, Speed s);
#endif
