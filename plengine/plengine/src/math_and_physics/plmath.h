#pragma once
#ifndef __OBJECT_H__
#define __OBJECT_H__
#include "vector.h"

#ifndef __VECTOR_LIB__
#define __VECTOR_LIB__
#include <vector>
#endif

struct Objectm
{
public:
	std::vector<Point> Points;

	Objectm(std::vector<Point> *);
	Objectm();

	void Homothety(Point, double);
	void Move(Vector);
	void Rotate(Point, double);
};

Objectm GetCameraView(Objectm *, Camera *);

typedef Coords<int> MapCoords;
 struct Map
{
public:
	Objectm * Objects;
	MapCoords Size;
};

#define CreateNewMap(map, size_x, size_y) Objectm map##___simpleobjname___; Objectm map##___arrname___[size_x][size_y]; Map map; map.Objects = *map##___arrname___; map.Size = MapCoords(size_x, size_y)
#define ClearMap(map) map##___arrname___[map.Size.x][map.Size.y]; map.Objects = *map##___arrname___
#define GetObject(map, coords) *(map.Objects + coords.x * (coords.y + 1))
#define SetObject(object, map, coords) map.Objects += coords.x * (coords.y + 1); *map.Objects = object; map.Objects -= coords.x * (coords.y + 1)
#define DeleteObject(map, coords) SetObject(Objectm(), map, coords)
#define MoveObject(map, from, to) SetObject(GetObject(map, from), map, to); SetObject(Objectm(), map, from)
#define ChangeObjects(map, first, second) map##___simpleobjname___ = GetObject(map, first); SetObject(GetObject(map, second), map, first); SetObject(map##___simpleobjname___, map, second); map##___simpleobjname___ = Objectm()

struct Line
{
public:
	double k, b;
	//y = k * x + b
	Line(double k, double b);
	Line();
};
Line GetCameraView(Line, Camera *);
Line MoveLine(Line, Point);

typedef Point LineSegment[2];

#endif
