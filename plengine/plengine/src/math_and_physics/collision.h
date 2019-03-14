#pragma once
#ifndef __COLLISION_H__
#define __COLLISION_H__
#include "plmath.h"
#include "base.h"

#define LINES_COLLISION(l, s) XOR(s[0].y > s[0].x * l.k + l.b, s[1].y > s[1].x * l.k + l.b)
#define LINES_COLLISION_POINT(l1, l2) Point((l1.b - l2.b) / (l2.k - l1.k), ((l1.b - l2.b) / (l2.k - l1.k) * (l1.k + l2.k) + (b1.k + b2.k)) / 2)
#define CONVERT_LINESEGMENT_TO_LINE(p1, p2) Line((p1.y - p2.y) / (p1.x - p2.x), ((p1.y + p2.y) - (p1.y - p2.y) / (p1.x - p2.x) * (p1.x + p2.x)) / 2)

#define POINT_AND_LINE_COLLISION(p, l) (p.y == l.k * p.x + l.b)
#define POINT_AND_LINESEGMENT_COLLISION(p, s) (POINT_AND_LINE_COLLISION(p, CONVERT_LINESEGMENT_TO_LINE(s[0], s[1])) && XOR((s[0] > p), (s[1] > p)))
bool POINT_AND_OBJECT_COLLISIONREF(Point, Objectm *);
#define POINT_AND_OBJECT_COLLISION(p, obj) POINT_AND_OBJECT_COLLISIONREF(p, &obj);

bool COLLISION_WITH_LINEREF(Line, Objectm *);
#define COLLISION_WITH_LINE(line, obj) COLLISION_WITH_LINEREF(line, &obj)

bool OBJECTS_COLLISION_SHORT(Objectm *, Objectm *);
bool OBJECTS_COLLISION_LONG(Objectm *, Objectm *);

#ifdef USE_LONG_OBJECT_COLLISION
#define OBJECTS_COLLISIONREF OBJECTS_COLLISION_LONG
#else
#define OBJECTS_COLLISIONREF OBJECTS_COLLISION_SHORT
#endif
#define OBJECTS_COLLISION(obj1, obj2) OBJECTS_COLLISIONREF(&obj1, &obj2)

#endif
