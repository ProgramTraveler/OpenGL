#include "Point3.h"
Point3::Point3()
{
	x = y = z = 0;
}
Point3::~Point3()
{}
Point3::Point3(double xx, double yy, double zz)
{
	x = xx; y = yy; z = zz;
}
Point3::Point3(const Point3& p)
{
	x = p.x; y = p.y; z = p.z;
}
Point3 operator +(const Point3 &p0, const Point3 &p1)
{
	return(Point3(p0.x + p1.x, p0.y + p1.y, p0.z + p1.z));
}
Point3 operator -(const Point3 &p0, const Point3 &p1)
{
	return(Point3(p0.x - p1.x, p0.y - p1.y, p0.z - p1.z));
}
Point3 operator *(const Point3 &p, double scalar)
{
	return(Point3(p.x * scalar, p.y * scalar, p.z * scalar));
}
Point3 operator *(double scalar, const Point3 &p)
{
	return(Point3(p.x * scalar, p.y * scalar, p.z * scalar));
}
Point3 operator /(const Point3 &p, double scalar)
{
	return(Point3(p.x / scalar, p.y / scalar, p.z / scalar));
}