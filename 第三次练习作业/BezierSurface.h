#pragma once
#include "point3D.h"

class BezierSurface {
public:
	BezierSurface();

	void ReadControlPoint(Point3D P[4][4]);//����16�����Ƶ�
	void DrawCurvedSurface();   //����˫����Bezier����Ƭ
	void DrawControlGrid();    //���ƿ�������
	void DrawControlPoint(); //���ƿ��Ƶ�
private:
	void LeftMultiplyMatrix(double M[][4], Point3D P[][4]);//��˶������
	void RightMultiplyMatrix(Point3D P[][4], double M[][4]);//�ҳ˶������
	void TransposeMatrix(double M[][4]);//ת�þ���
public:
	Point3D P3[4][4]; //��ά���Ƶ�
};