class Point3
{
public:
	Point3();
	~Point3();
	Point3(double, double, double);
	Point3(const Point3& p);
	friend Point3 operator +(const Point3 &p0, const Point3 &p1);//�է����姩?�اڧէ�
	friend Point3 operator -(const Point3 &p0, const Point3 &p1);
	friend Point3 operator *(const Point3 &p, double scalar);
	friend Point3 operator *(double scalar, const Point3 &p);
	friend Point3 operator /(const Point3 &p, double scalar);
public:
	double x, y, z;
};