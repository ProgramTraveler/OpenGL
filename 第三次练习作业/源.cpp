#include <GL/glut.h>
#include <iostream>
#include <cstdlib>
#include <string>
#include <cstdlib>
#include <fstream>
#include "BezierSurface.h"
#include "Patch.h"
using namespace std;
#define MAX_NUM_POINTS 302 

static GLint width = 800, height = 800;

GLfloat alpha_x = 0.0;
GLfloat alpha_y = 0.0;
GLfloat oldx, oldy;

Point3D P3[4][4]; //3D point
Point3D P[306];   //总控制点
Patch patch[32]; //总面片
BezierSurface surface;
BezierSurface surfaceControlGrid[32];

void ReadVertex();//读入控制多边形顶点
void ReadPatch();//读入双三次曲面片

void DrawBody();//物体

void init_controlpoint();
bool gridFlag = 0;
bool ctrlPointFlag = 0;
GLfloat wSize = 600.0;  //window's size
void init()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-wSize, wSize, -wSize, wSize, -wSize, wSize);
	glMatrixMode(GL_MODELVIEW);
	// Set the clear color to black
	glClearColor(0.0, 0.0, 0.0, 0.0); //black
	//init_controlpoint();
	ReadVertex();
	ReadPatch();
}
void ReadVertex()
{
	string file = "Vertices.txt";
	ifstream infile;
	infile.open(file.data());   //将文件流对象与文件连接起来 
	if (!infile)
		cout << "error " << file << endl;
	string s; //each line
	int index = 0;//用于区分数字
	string data1, data2, data3;//存放坐标
	int i = 0;
	while (getline(infile, s))
	{
		//cout << s << endl;
		for (int j = 0; j < s.length(); j++)
		{
			if (' ' == s[j])
				index++;
			switch (index)
			{
			case 0:
				data1 += s[j];
				break;
			case 1:
				data2 += s[j];
				break;
			case 2:
				data3 += s[j];
				break;
			}
		}
		P[i].x = atof(data1.c_str()) * 100;//浮点数表示的x值
		P[i].y = atof(data3.c_str()) * 100;//浮点数表示的z值
		P[i].z = atof(data2.c_str()) * 100;//浮点数表示的y值
		data1 = "", data2 = "", data3 = "", index = 0;
		i++;
		//cout << i << " ";
	}
	infile.close();             //关闭文件输入流 
}

void ReadPatch()
{
	string file = "Patches.txt";
	ifstream infile;
	infile.open(file.data());   //将文件流对象与文件连接起来 
	if (!infile)
		cout << "error " << file << endl;
	string s; //each line
	int index = 0;//用于区分数字
	string str[16];//存放控制点索引号
	int surfNum = 0;
	while (getline(infile, s))
	{
		//cout << s << endl;
		for (int i = 0; i < s.length(); i++)
		{
			if (' ' == s[i])
				index++;
			switch (index)
			{
			case 0:
				str[0] += s[i];
				break;
			case 1:
				str[1] += s[i];
				break;
			case 2:
				str[2] += s[i];
				break;
			case 3:
				str[3] += s[i];
				break;
			case 4:
				str[4] += s[i];
				break;
			case 5:
				str[5] += s[i];
				break;
			case 6:
				str[6] += s[i];
				break;
			case 7:
				str[7] += s[i];
				break;
			case 8:
				str[8] += s[i];
				break;
			case 9:
				str[9] += s[i];
				break;
			case 10:
				str[10] += s[i];
				break;
			case 11:
				str[11] += s[i];
				break;
			case 12:
				str[12] += s[i];
				break;
			case 13:
				str[13] += s[i];
				break;
			case 14:
				str[14] += s[i];
				break;
			case 15:
				str[15] += s[i];
				break;
			}
		}
		patch[surfNum].pNumber = 16;//双三次Bezier曲面片有16个控制点
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				patch[surfNum].pIndex[i][j] = atoi(str[i * 4 + j].c_str());//整数表示的控制点索引号
		s = "";
		for (int nPoint = 0; nPoint < 16; nPoint++)
		{
			str[nPoint] = "";
		}
		index = 0;
		surfNum++;
		//cout << surfNum << " ";
	}
	infile.close();             //关闭文件输入流 
}

void DrawBody()
{
	for (int nSurface = 0; nSurface < 4; nSurface++)
	{
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++) {
				P3[i][j] = P[patch[nSurface].pIndex[i][j] - 1];
			}
		surface.ReadControlPoint(P3);
		surface.DrawCurvedSurface();
		if (gridFlag)
			surface.DrawControlGrid();
		if (ctrlPointFlag)
			surface.DrawControlPoint();
	}
	for (int nSurface = 4; nSurface < 8; nSurface++)
	{
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++) {
				P3[i][j] = P[patch[nSurface].pIndex[i][j] - 1];
			}
		surface.ReadControlPoint(P3);
		surface.DrawCurvedSurface();
		if (gridFlag)
			surface.DrawControlGrid();
		if (ctrlPointFlag)
			surface.DrawControlPoint();
	}
}

void  display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glRotatef(alpha_x, 1, 0, 0);
	glRotatef(alpha_y, 0, 1, 0);
	glPushMatrix();
	
	DrawBody();;
	glPopMatrix();
	glFlush();
	glutSwapBuffers();
}
void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h)
		glOrtho(-wSize, wSize, -wSize * (GLfloat)h / (GLfloat)w,
			wSize * (GLfloat)h / (GLfloat)w, -wSize, wSize);
	else
		glOrtho(-wSize * (GLfloat)w / (GLfloat)h,
			wSize * (GLfloat)w / (GLfloat)h, -wSize, wSize, -wSize, wSize);
	glMatrixMode(GL_MODELVIEW);
}
void mouse(int btn, int state, int x, int y)
{
	if ((btn == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN))
	{
		oldx = x; oldy = y;
	}
}
void processMenu(int value)
{
	switch (value)
	{
	case 1:
		alpha_x = 0;
		alpha_y = 0;
		glLoadIdentity();
		gridFlag = 0;
		ctrlPointFlag = 0;
		break;
	case 2:
		alpha_x = 0;
		alpha_y = 0;
		glLoadIdentity();
		gridFlag = 1;
		break;
	case 3:
		alpha_x = 0;
		alpha_y = 0;
		glLoadIdentity();
		ctrlPointFlag = 1;
		gridFlag = 1;
		break;
	}
	glutPostRedisplay();
}
void motion(int x, int y)
{
	GLint deltax = oldx - x;
	GLint deltay = oldy - y;
	alpha_y += 360 * (GLfloat)deltax / (GLfloat)height;//根据屏幕上鼠标滑动的距离来设置旋转的角度  
	alpha_x += 360 * (GLfloat)deltay / (GLfloat)width;
	oldx = x;//记录此时的鼠标坐标，更新鼠标坐标  
	oldy = y;//若是没有这两句语句，滑动是旋转会变得不可控  
	glutPostRedisplay();
}
int  main(int  argc, char** argv)
{
	glutInit(&argc, argv);    // Initialize GLUT function callings
	//sets the initial display mode
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	// Set window position, from the left and top corner of the screen, in numbers of pixels 
	glutInitWindowPosition(200, 100);

	// Set window size (width, height) in number of pixels     
	glutInitWindowSize(800, 800);

	// Specify a window creation event 
	glutCreateWindow("Utah Teapot");
	init();	    // Invoke this function for initialization	
	//A window is reshaped
	int nModeMenu = glutCreateMenu(processMenu);
	glutAddMenuEntry("Display Teapot", 1);
	glutAddMenuEntry("Display Teapot with Grids", 2);
	glutAddMenuEntry("Display Teapot with Control Points", 3);
	//将菜单榜定到鼠标右键上  
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutReshapeFunc(reshape);

	// Specify the drawing function that is called when the window 
	glutDisplayFunc(display);         // is created or re-drew
	glutMouseFunc(mouse);
	glutMotionFunc(motion);

	glutMainLoop();    // Enter the event processing loop

	return 0;          // Indicate normal termination 		
}