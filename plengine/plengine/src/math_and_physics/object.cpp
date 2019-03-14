#include "plmath.h"
#include "base.h"
using std::vector;

Objectm::Objectm(vector<Point> * p) : Points(*p) { }
Objectm::Objectm() : Points(vector<Point>()) { }

void Objectm::Homothety(Point p, double d)
{
	for (int i = 0; i < (int)Points.size(); i++)
		Points[i] = (Points[i] - p) * d + p;
}
void Objectm::Move(Vector v)
{
	for (int i = 0; i < (int)Points.size(); i++)
		Points[i] += v.Position;
}
void Objectm::Rotate(Point p, double d)
{
	for (int i = 0; i < (int)Points.size(); i++)
		Points[i] = RotateVector(Points[i], p, d);
}

Objectm GetCameraView(Objectm * target, Camera * c)
{
	Objectm q = *target;
	for (int i = 0; i < (int)q.Points.size(); i++)
		q.Points[i] = GetCameraView(q.Points[i], c);
	return q;
}

Line::Line(double K, double B) : k(K), b(B) { }
Line::Line() : Line(0, 0) { }
