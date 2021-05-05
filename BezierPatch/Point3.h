class Point3
{
public:
	Point3();
	~Point3();
	Point3(double, double, double);
	Point3(const Point3& p);
	friend Point3 operator +(const Point3 &p0, const Point3 &p1);//忱局局批妝?忪我忱我
	friend Point3 operator -(const Point3 &p0, const Point3 &p1);
	friend Point3 operator *(const Point3 &p, double scalar);
	friend Point3 operator *(double scalar, const Point3 &p);
	friend Point3 operator /(const Point3 &p, double scalar);
public:
	double x, y, z;
};