#include "physics.h"

Ground::Ground(Line l, double d) : Colider(l), Strong(d) { }
Ground::Ground(Line l) : Ground(l, 0) { }
Ground::Ground() : Ground(Line(), 0) { }

inline Object::Object(Point cn, Objectm * c, Objectm * v, Rigidbody p) : Center(cn), Colider(*c), Visible(*v), Params(p) { }
inline Object::Object(Objectm * c, Objectm * v, Rigidbody p) : Object(0, c, v, p) { }
inline Object::Object(Objectm * v, Rigidbody p) : Object(v, v, p) { }
inline Object::Object(Objectm * c, Objectm * v) : Object(c, v, Rigidbody()) { }
inline Object::Object(Objectm * v) : Object(v, v) { }
Object::Object() : Object(&Objectm()) { }

Rigidbody::Rigidbody(double m, double d, double s, bool u, bool b, Speed sp) : Mass(m), Drag(d), Strong(s), UseGravity(u), Brakeable(b), Acceleration(sp) { }
Rigidbody::Rigidbody() : Rigidbody(1, 0, 0, true, false, Vector(0)) { }

Line GetCameraView(Line l, Camera * c)
{
	Point p = Point(0, l.b);
	p = GetCameraView(p, c);
	return Line(l.k, p.y - l.k * p.x);
}
Line MoveLine(Line l, Point p)
{
	p = Point(0, l.b) - p;
	return Line(l.k, p.y - l.k * p.x);
}

Space GetCameraView(Space * s, Camera * c)
{
	Space q = *s;
	q.Plane.Colider = GetCameraView(q.Plane.Colider, c);
	for (int i = 0; i < (int)q.Objects.size(); i++)
	{
		q.Objects[i].Visible = GetCameraView(&q.Objects[i].Visible, c);
		q.Objects[i].Colider = GetCameraView(&q.Objects[i].Colider, c);
	}
	return q;
}

void SetSpaceCenter(Space * s, Point center)
{
	s->Plane.Colider = MoveLine(s->Plane.Colider, center);
	for (int i = 0; i < (int)s->Objects.size(); i++)
	{
		Objectm * c = &s->Objects.operator[](i).Colider;
		Objectm * v = &s->Objects.operator[](i).Visible;
		for (int j = 0; j < (int)c->Points.size(); j++)
			c->Points[j] -= center;
		for (int j = 0; j < (int)v->Points.size(); j++)
			v->Points[j] -= center;
	}
}

Speed ApplyGravity(Object * q, Ground * l, Speed s)
{
	if (!q->Params.UseGravity) return;
	s = s + GRAVITY_ACCELERATION(q->Params.Mass, q->Params.Drag);
	Point check1 = q->Colider.Points[0];
	q->Center += s.Position;
	Point check2 = q->Colider.Points[0];
	LineSegment check = { check1, check1 };
	if (COLLISION_WITH_LINE(l->Colider, q->Colider) || LINES_COLLISION(l->Colider, check))
	{
		Speed Fu = Vector(Point((l->Colider.b - 1 ) / l->Colider.k, 1));
		Fu = Vector(s.Length() * l->Strong, Fu.Angle());
		q->Center += Fu.Position;
		s = s + Fu;
	}
	return s;
}

std::vector<Object> DestroyObject(Object * obj, int max)
{
	int parts = rand() % max;
	if (parts < 2) parts = 2;
	std::vector<Object> l;
	for (int i = 0; i < obj->Visible.Points.size(); i++)
	{
		Objectm p = Objectm(&std::vector<Point>({ obj->Visible.Points[i % obj->Visible.Points.size()],
			obj->Visible.Points[(i + 1) % obj->Visible.Points.size()],
			obj->Visible.Points[(i + 2) % obj->Visible.Points.size()] }));
		Rigidbody pp = obj->Params;
		pp.Acceleration = pp.Acceleration + Vector(obj->Center, obj->Visible.Points[i % obj->Visible.Points.size()]);
		l.push_back(Object(obj->Center, &p, &p, pp));
		if (l.size() <= parts) break;
	}
	return l;
}
