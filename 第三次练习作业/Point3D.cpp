#include "point3D.h"

Point3D operator + (const Point3D &p0, const Point3D &p1)
{
	return Point3D(p0.x + p1.x, p0.y + p1.y, p0.z + p1.z);
}
Point3D operator *(const Point3D &p, double scalar)
{
	return Point3D(p.x * scalar, p.y * scalar, p.z * scalar);
}
Point3D operator *(double scalar, const Point3D &p)
{
	return Point3D(p.x * scalar, p.y * scalar, p.z * scalar);
}