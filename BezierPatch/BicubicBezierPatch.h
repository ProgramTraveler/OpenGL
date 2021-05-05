#include "Point3.h"

class BicubicBezierPatch
{
public:
	BicubicBezierPatch();
	~BicubicBezierPatch();
	void ReadControlPoint(Point3 P[4][4]);//����16�����Ƶ�
	void DrawCurvedPatch();//����˫����Bezier����Ƭ
	void DrawControlGrid();//���ƿ�������
	void DrawControlPoint(); //���ƿ��Ƶ�
private:
	void LeftMultiplyMatrix(double M[][4], Point3 CP[][4]);//��˶������
	void RightMultiplyMatrix(Point3 P[][4], double M[][4]);//�ҳ˶������
	void TransposeMatrix(double M[][4]);//ת�þ���
	
public:
	Point3 P[4][4];//��ά���Ƶ�
};


