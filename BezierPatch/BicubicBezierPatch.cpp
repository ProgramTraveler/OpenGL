#include "GL/glut.h"
#include "BicubicBezierPatch.h"
#include <cmath>

#pragma once

BicubicBezierPatch::BicubicBezierPatch()
{
}


BicubicBezierPatch::~BicubicBezierPatch()
{
}

void BicubicBezierPatch::ReadControlPoint(Point3 CP[4][4])
{
   for(int i=0;i<4;i++)
	   for(int j=0;j<4;j++)
   			this->P[i][j]= CP[i][j];
}

void BicubicBezierPatch::DrawCurvedPatch()
 {
	double M[4][4];//系数矩阵Mbe
	M[0][0]=-1;M[0][1]=3; M[0][2]=-3;M[0][3]=1;
	M[1][0]=3; M[1][1]=-6;M[1][2]=3; M[1][3]=0;
	M[2][0]=-3;M[2][1]=3; M[2][2]=0; M[2][3]=0;
	M[3][0]=1; M[3][1]=0; M[3][2]=0; M[3][3]=0;
	Point3 P3[4][4];//曲线计算用控制点数组
	for(int i=0;i<4;i++)
		for(int j=0;j<4;j++)
			P3[i][j]=P[i][j];
	LeftMultiplyMatrix(M,P3);//数字矩阵左乘三维点矩阵
	TransposeMatrix(M);//计算转置矩阵
	RightMultiplyMatrix(P3,M);//数字矩阵右乘三维点矩阵
	double Step =0.1;//步长
	double u0,u1,u2,u3,v0,v1,v2,v3;//u，v参数的幂
	glColor3f(1, 1, 0);
	glLineWidth(1);
	glPushMatrix();
	for (double u = 0; u <= 1; u += Step)
	{
		glBegin(GL_LINE_STRIP);
		for (double v = 0; v <= 1; v += Step)
		{
			u3 = u*u*u, u2 = u*u, u1 = u, u0 = 1;
			v3 = v*v*v, v2 = v*v, v1 = v, v0 = 1;
			Point3 pt = (u3*P3[0][0] + u2*P3[1][0] + u1*P3[2][0] + u0*P3[3][0])*v3
				+ (u3*P3[0][1] + u2*P3[1][1] + u1*P3[2][1] + u0*P3[3][1])*v2
				+ (u3*P3[0][2] + u2*P3[1][2] + u1*P3[2][2] + u0*P3[3][2])*v1
				+ (u3*P3[0][3] + u2*P3[1][3] + u1*P3[2][3] + u0*P3[3][3])*v0;
			
			glVertex3d(pt.x, pt.y, pt.z);
		}
		glEnd();
	}
	
	for(double v=0;v<=1;v+=Step)
	{
		glBegin(GL_LINE_STRIP);
		for(double u=0;u<=1;u+=Step)
		{
			u3=u*u*u;u2=u*u;u1=u;u0=1;v3=v*v*v;v2=v*v;v1=v;v0=1;
			Point3 pt=(u3*P3[0][0]+u2*P3[1][0]+u1*P3[2][0]+u0*P3[3][0])*v3
			          +(u3*P3[0][1]+u2*P3[1][1]+u1*P3[2][1]+u0*P3[3][1])*v2
			          +(u3*P3[0][2]+u2*P3[1][2]+u1*P3[2][2]+u0*P3[3][2])*v1
			          +(u3*P3[0][3]+u2*P3[1][3]+u1*P3[2][3]+u0*P3[3][3])*v0;			
			glVertex3d(pt.x, pt.y,pt.z);
		}
		glEnd();
   }
	glPopMatrix();
}


void BicubicBezierPatch::LeftMultiplyMatrix(double M[][4],Point3 P[][4])//左乘矩阵M*P
{
	Point3 T[4][4];//临时矩阵
	for(int i=0;i<4;i++)
		for(int j=0;j<4;j++)
			T[i][j]=M[i][0]*P[0][j]+M[i][1]*P[1][j]+M[i][2]*P[2][j]+M[i][3]*P[3][j];
	for(int i=0;i<4;i++)
		for(int j=0;j<4;j++)
			P[i][j]=T[i][j];
}

void BicubicBezierPatch::RightMultiplyMatrix(Point3 P[][4],double M[][4])//右乘矩阵P*M
{
	Point3 T[4][4];//临时矩阵
	for(int i=0;i<4;i++)
		for(int j=0;j<4;j++)
			T[i][j]=P[i][0]*M[0][j]+P[i][1]*M[1][j]+P[i][2]*M[2][j]+P[i][3]*M[3][j];
	for(int i=0;i<4;i++)
		for(int j=0;j<4;j++)
			P[i][j]=T[i][j];
}

void BicubicBezierPatch::TransposeMatrix(double M[][4])//转置矩阵
{
	double T[4][4];//临时矩阵
	for(int i=0;i<4;i++)
		for(int j=0;j<4;j++)
			T[j][i]=M[i][j];
	for(int i=0;i<4;i++)
		for(int j=0;j<4;j++)
			M[i][j]=T[i][j];
}

void BicubicBezierPatch::DrawControlGrid()//绘制控制网格
{
	Point3 P2[4][4];//二维控制点
	for(int i=0;i<4;i++)
		for (int j = 0; j < 4; j++)
		{
			P2[i][j].x = P[i][j].x;
			P2[i][j].y = P[i][j].y;
			P2[i][j].z = P[i][j].z;
		}
	glColor3f(0, 1, 0);
	glLineWidth(3);
	
	for(int i=0;i<4;i++)
	{
		glBegin(GL_LINE_STRIP);
		for(int j=0;j<4;j++)
			glVertex3d(P2[i][j].x, P2[i][j].y, P2[i][j].z);
		glEnd();
	}
	
	
	for(int j=0;j<4;j++)
	{
		glBegin(GL_LINE_STRIP);
		for(int i=0;i<4;i++)
			glVertex3d(P2[i][j].x, P2[i][j].y, P2[i][j].z);
		glEnd();
	}
	
}
void BicubicBezierPatch::DrawControlPoint()//绘制控制
{
	glColor3f(1, 0, 0);
	glPointSize(5);
	glBegin(GL_POINTS);
	for (int i = 0; i<4; i++)
		for (int j = 0; j<4; j++)
			glVertex3d(P[i][j].x, P[i][j].y, P[i][j].z);
	glEnd();
}