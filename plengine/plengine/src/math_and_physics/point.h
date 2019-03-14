#pragma once
#ifndef NULL
#define NULL 0
#endif

#ifndef __POINT_H__
#define __POINT_H__

template<typename T>
struct Coords
{
public:
	T x, y;
	Coords(T X, T Y) : x(X), y(Y) { }
	Coords(T V) : Coords(V, V) { }
	Coords() : Coords(NULL) { }

	bool operator==(Coords<T> c)
	{
		return x == c.x && y == c.y;
	}
	bool operator!=(Coords<T> c)
	{
		return !(*this == c);
	}
	bool operator >(Coords<T> c)
	{
		return x > c.x && y > c.y;
	}
	bool operator <(Coords<T> c)
	{
		return x < c.x && y < c.y;
	}
	bool operator >=(Coords<T> c)
	{
		return operator>(c) && operator==(c);
	}
	bool operator <=(Coords<T> c)
	{
		return operator<(c) && operator==(c);
	}

	Coords<T> operator+(Coords<T> c)
	{
		return Coords(x + c.x, y + c.y);
	}
	Coords<T> operator-(Coords<T> c)
	{
		return Coords(x - c.x, y - c.y);
	}
	Coords<T> operator*(T t)
	{
		return Coords(x * t, y * t);
	}
	Coords<T> operator/(T t)
	{
		return operator*(1 / t);
	}

	void operator+=(Coords<T> c)
	{
		x += c.x;
		y += c.y;
	}
	void operator-=(Coords<T> c)
	{
		x -= c.x;
		y -= c.y;
	}
	void operator*=(T c)
	{
		x = x * c;
		y = y * c;
	}
	void operator/=(T c)
	{
		x = x / c;
		y = y / c;
	}


	void operator++()
	{
		operator+=(1);
	}
	void operator--()
	{
		operator-=(1);
	}
};

typedef Coords<double> Point;
#endif
