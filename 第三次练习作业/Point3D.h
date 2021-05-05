class Point3D {
public:
	Point3D() :x(0), y(0), z(0), w(1) {}
	Point3D(double _x, double _y, double _z) :x(_x), y(_y), z(_z), w(1) {}
	Point3D(const Point3D& point)
	{
		x = point.x; y = point.y; z = point.z; w = 1;
	}
	friend Point3D operator +(const Point3D& p0, const Point3D& p1);//‘ÀÀ„∑˚÷ÿ‘ÿ
	friend Point3D operator *(const Point3D& p, double scalar);
	friend Point3D operator *(double scalar, const Point3D& p);

	double x, y, z, w;
};