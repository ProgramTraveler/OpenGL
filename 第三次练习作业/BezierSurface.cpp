#include "BezierSurface.h"
#include <GL/glut.h>
//#include <cmath>
#include <iostream>

BezierSurface::BezierSurface()
{
}
void BezierSurface::ReadControlPoint(Point3D P[4][4])
{
	for (int i = 0; i<4; i++)
		for (int j = 0; j < 4; j++)
		{
			P3[i][j] = P[i][j];
			//std::cout << P3[i][j].x << "  " << P3[i][j].y << " ";
		}
}
void BezierSurface::DrawCurvedSurface()
{
	double M[4][4];//ÏµÊý¾ØÕóMbe
	M[0][0] = -1; M[0][1] = 3; M[0][2] = -3; M[0][3] = 1;
	M[1][0] = 3; M[1][1] = -6; M[1][2] = 3; M[1][3] = 0;
	M[2][0] = -3; M[2][1] = 3; M[2][2] = 0; M[2][3] = 0;
	M[3][0] = 1; M[3][1] = 0; M[3][2] = 0; M[3][3] = 0;
	Point3D P[4][4];//ÇúÏß¼ÆËãÓÃ¿ØÖÆµãÊý×é
	for (int i = 0; i<4; i++)
		for (int j = 0; j<4; j++)
			P[i][j] = P3[i][j];
	LeftMultiplyMatrix(M, P);//Êý×Ö¾ØÕó×ó³ËÈýÎ¬µã¾ØÕó
	TransposeMatrix(M);//¼ÆËã×ªÖÃ¾ØÕó
	RightMultiplyMatrix(P, M);//Êý×Ö¾ØÕóÓÒ³ËÈýÎ¬µã¾ØÕó
	double tStep = 0.1;//tµÄ²½³¤
	double u0, u1, u2, u3, v0, v1, v2, v3;//u£¬v²ÎÊýµÄÃÝ

	glColor3f(0, 1, 0);
	//glColor3f(0.537, 0.325, 0.129);
	glLineWidth(1);
	//glPushMatrix();
	
	for (double u = 0; u <= 1; u += tStep)
	{
		glBegin(GL_LINE_STRIP);  //lines between two points
		for (double v = 0; v <= 1; v += tStep)
		{
			u3 = u*u*u; u2 = u*u; u1 = u; u0 = 1; v3 = v*v*v; v2 = v*v; v1 = v; v0 = 1;
			Point3D pt = (u3*P[0][0] + u2*P[1][0] + u1*P[2][0] + u0*P[3][0])*v3
				+ (u3*P[0][1] + u2*P[1][1] + u1*P[2][1] + u0*P[3][1])*v2
				+ (u3*P[0][2] + u2*P[1][2] + u1*P[2][2] + u0*P[3][2])*v1
				+ (u3*P[0][3] + u2*P[1][3] + u1*P[2][3] + u0*P[3][3])*v0;
			glVertex3f(pt.x, pt.y, pt.z);
		}
		glEnd();
	}
	
	for (double v = 0; v <= 1; v += tStep)
	{
		glBegin(GL_LINE_STRIP);
		for (double u = 0; u <= 1; u += tStep)
		{
			u3 = u*u*u; u2 = u*u; u1 = u; u0 = 1; v3 = v*v*v; v2 = v*v; v1 = v; v0 = 1;
			Point3D pt = (u3*P[0][0] + u2*P[1][0] + u1*P[2][0] + u0*P[3][0])*v3
				+ (u3*P[0][1] + u2*P[1][1] + u1*P[2][1] + u0*P[3][1])*v2
				+ (u3*P[0][2] + u2*P[1][2] + u1*P[2][2] + u0*P[3][2])*v1
				+ (u3*P[0][3] + u2*P[1][3] + u1*P[2][3] + u0*P[3][3])*v0;
			glVertex3d(pt.x, pt.y, pt.z);
		}
		glEnd();
	}
	//glPopMatrix();
}
void BezierSurface::DrawControlGrid()
{
	Point3D pt[4][4];//ÈýÎ¬¿ØÖÆµã
	for (int i = 0; i<4; i++)
		for (int j = 0; j < 4; j++)
		{
			pt[i][j].x = P3[i][j].x;
			pt[i][j].y = P3[i][j].y;
			pt[i][j].z = P3[i][j].z;
		}
	glColor3f(1, 1, 0);
	glLineWidth(2);

	for (int i = 0; i < 4; i++)
	{
		glBegin(GL_LINE_STRIP);
		for (int j = 0; j < 4; j++)
			glVertex3d(pt[i][j].x, pt[i][j].y, pt[i][j].z);
		glEnd();
	}

	for (int j = 0; j<4; j++)
	{
		glBegin(GL_LINE_STRIP);
		for (int i = 0; i<4; i++)
			glVertex3d(pt[i][j].x, pt[i][j].y, pt[i][j].z);
		glEnd();
	}
	glFlush();
}
void BezierSurface::DrawControlPoint()
{
	glColor3f(1, 1, 0);
	glPointSize(6);
	glBegin(GL_POINTS);
	for (int i = 0; i<4; i++)
		for (int j = 0; j<4; j++)
			glVertex3d(P3[i][j].x, P3[i][j].y, P3[i][j].z);
	glEnd();
}
void BezierSurface::LeftMultiplyMatrix(double M[][4], Point3D P[][4])//×ó³Ë¾ØÕóM*P
{
	Point3D T[4][4];//ÁÙÊ±¾ØÕó
	for (int i = 0; i<4; i++)
		for (int j = 0; j<4; j++)
			T[i][j] = M[i][0] * P[0][j] + M[i][1] * P[1][j] + M[i][2] * P[2][j] + M[i][3] * P[3][j];
	for (int i = 0; i<4; i++)
		for (int j = 0; j<4; j++)
			P[i][j] = T[i][j];
}

void BezierSurface::RightMultiplyMatrix(Point3D P[][4], double M[][4])//ÓÒ³Ë¾ØÕóP*M
{
	Point3D T[4][4];//ÁÙÊ±¾ØÕó
	for (int i = 0; i<4; i++)
		for (int j = 0; j<4; j++)
			T[i][j] = P[i][0] * M[0][j] + P[i][1] * M[1][j] + P[i][2] * M[2][j] + P[i][3] * M[3][j];
	for (int i = 0; i<4; i++)
		for (int j = 0; j<4; j++)
			P[i][j] = T[i][j];
}

void BezierSurface::TransposeMatrix(double M[][4])//×ªÖÃ¾ØÕó
{
	double T[4][4];//ÁÙÊ±¾ØÕó
	for (int i = 0; i<4; i++)
		for (int j = 0; j<4; j++)
			T[j][i] = M[i][j];
	for (int i = 0; i<4; i++)
		for (int j = 0; j<4; j++)
			M[i][j] = T[i][j];
}
