#include "collision.h"

bool COLLISION_WITH_LINEREF(Line line, Objectm * obj)
{
	for (int i = 0; i < obj->Points.size(); i++)
	{
		LineSegment l = { obj->Points[i % obj->Points.size()], obj->Points[(i + 1) % obj->Points.size()] };
		if (LINES_COLLISION(line, l))
			return true;
	}
	return false;
}

bool POINT_AND_OBJECT_COLLISIONREF(Point p, Objectm * obj)
{
	for (int i = 0; i < obj->Points.size(); i++)
		for (int j = 0; j < obj->Points.size(); j++)
		{
			if (i == j) continue;
			LineSegment l = { obj->Points[i % obj->Points.size()], obj->Points[(i + 1) % obj->Points.size()] };
			if (POINT_AND_LINESEGMENT_COLLISION(p, l))
				return true;
		}
	return false;
}

bool OBJECTS_COLLISION_SHORT(Objectm * q1, Objectm * q2)
{
	for (int i = 0; i < q1->Points.size(); i++)
		for (int j = 0; j < q2->Points.size(); j++)
		{
			LineSegment s1 = { q1->Points[i % q1->Points.size()], q1->Points[(i + 1) % q1->Points.size()] };
			LineSegment s2 = { q2->Points[i % q2->Points.size()], q2->Points[(i + 1) % q2->Points.size()] };
			Line l1 = CONVERT_LINESEGMENT_TO_LINE(s1[0], s1[1]);
			Line l2 = CONVERT_LINESEGMENT_TO_LINE(s2[0], s2[1]);
			if (l1.b == l2.b && l1.k == l2.k) return true;
			if (!LINES_COLLISION(l1, s2)) continue;
			if (!LINES_COLLISION(l2, s1)) continue;
			return true;
		}

	return false;
}

bool OBJECTS_COLLISION_LONG(Objectm * q1, Objectm * q2)
{
	for (int i = 0; i < q1->Points.size(); i++)
		if(POINT_AND_OBJECT_COLLISIONREF(q1->Points[i], q2))
			return true;
	return false;
}
