#pragma once
#include "point3D.h"

class BezierSurface {
public:
	BezierSurface();

	void ReadControlPoint(Point3D P[4][4]);//读入16个控制点
	void DrawCurvedSurface();   //绘制双三次Bezier曲面片
	void DrawControlGrid();    //绘制控制网格
	void DrawControlPoint(); //绘制控制点
private:
	void LeftMultiplyMatrix(double M[][4], Point3D P[][4]);//左乘顶点矩阵
	void RightMultiplyMatrix(Point3D P[][4], double M[][4]);//右乘顶点矩阵
	void TransposeMatrix(double M[][4]);//转置矩阵
public:
	Point3D P3[4][4]; //三维控制点
};