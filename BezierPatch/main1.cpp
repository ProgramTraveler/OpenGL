/////////////////////////////////////
//绘制一个Bezier曲面片
//操作：使用鼠标确定一个曲面的16个控制点
//键c：绘制曲面；键e：清屏；键w、a、z、s控制曲面旋转；键q：结束运行
/////////////////////////////////////////
#include <GL/glut.h>
#include <iostream>
#include <cstdlib>
#include "BicubicBezierPatch.h"

#define MAX_NUM_POINTS 16 

static GLint width = 800, height = 800;
GLfloat oldx, oldy;
double alpha_x = 0.0;
double alpha_y = 0.0;

static int n = 0;

Point3 P0[4][4];
Point3 *P;
BicubicBezierPatch patch0;

void init_controlpoint();
bool mouseFlag = 0;
void init()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-10.0, 10.0, -10.0, 10.0, -10.0, 10);
	glMatrixMode(GL_MODELVIEW);
	// Set the clear color to black
	glClearColor(0.0, 0.0, 0.0, 0.0); //black
	//init_controlpoint();
	P = new Point3[MAX_NUM_POINTS];
}

void  display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	if (mouseFlag)
	{
		init_controlpoint();
		patch0.ReadControlPoint(P0);
		glRotatef(alpha_x, 1, 0, 0);
		glRotatef(alpha_y, 0, 1, 0);
		
		patch0.DrawControlGrid();
		patch0.DrawCurvedPatch();
		patch0.DrawControlPoint();
	}
	glFlush();
}

void init_controlpoint()
{
	double l = 3, m = 1;
	int n = 0;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			P0[i][j].x = P[n + j].x;
			P0[i][j].y = P[n + j].y;
			P0[i][j].z = -(l * m + rand() % 3);
		}
		n += 4;
	}
	
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
			std::cout << P0[i][j].x << " / " << P0[i][j].y << " / " << P0[i][j].z << std::endl;
		std::cout << "---------\n";
	}
}
void mouse(int button, int state, int x, int y)
{
	float wx, wy;
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		mouseFlag = true;
		/* Translate screen coordinate system to view coordinate system */
		//wx = (20.0 * (x - 250)) / (float)(width);
		//wy = (20.0 * (height / 2 - y)) / (float)(height);
		wx = -10 + (20.0 * x ) / (float)(width);
		wy = (20.0 * (height / 2.0 - y)) / (float)(height);
		/* See if we have room for any more control points */
		if (n == MAX_NUM_POINTS) return;
		/* Save the point */
		P[n].x = wx;
		P[n].y = wy;
		std::cout << "x-y:" << x << " " << y << std::endl;

		std::cout << P[n].x << " ";
		std::cout << P[n].y << std::endl;
		n++;
		/* Draw the point */
		glColor3f(1.0, 0.0, 0.0);
		glPointSize(5.0);
		glBegin(GL_POINTS);
		glVertex3f(wx, wy, 0.0);
		glEnd();
		glFlush();
	}
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'q':
	case 'Q':
		exit(0);
		break;
	case 'c':
	case 'C':   //redraw
		n = 0;
		glutPostRedisplay();
		break;
	case 'e':
	case 'E':  //erase 
		mouseFlag = false;
		glutPostRedisplay();
		break;
	case 'd':
	case 'D':
		glutPostRedisplay();
		break;
	case 'w':
	case 'W':
		alpha_x += 360 * 1.0f / width;
		glutPostRedisplay();
		break;
	case 'z':
	case 'Z':
		alpha_x -= 360 * 1.0f /width ;
		glutPostRedisplay();
		break;
	case 's':
	case 'S':
		alpha_y += 360 * 1.0f / height;
		glutPostRedisplay();
		break;
	case 'a':
	case 'A':
		alpha_y -= 360 * 1.0f / height;
		glutPostRedisplay();
		break;
	}
}

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h)
		glOrtho(-10.0, 10.0, -10.0*(GLfloat)h / (GLfloat)w,
		10.0*(GLfloat)h / (GLfloat)w, -10.0, 10.0);
	else
		glOrtho(-10.0*(GLfloat)w / (GLfloat)h,
		10.0*(GLfloat)w / (GLfloat)h, -10.0, 10.0, -10.0, 10.0);
	glMatrixMode(GL_MODELVIEW);
}
int  main(int  argc, char  **argv)
{
	glutInit(&argc, argv);    // Initialize GLUT function callings
	//sets the initial display mode
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	// Set window position, from the left and top corner of the screen, in numbers of pixels 
	glutInitWindowPosition(200, 100);

	// Set window size (width, height) in number of pixels     
	glutInitWindowSize(800, 800);

	// Specify a window creation event 
	glutCreateWindow("Bezier Surface");
	init();	    // Invoke this function for initialization	
	//A window is reshaped
	glutReshapeFunc(reshape);

	// Specify the drawing function that is called when the window 
	glutDisplayFunc(display);         // is created or re-drew

	
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	
	glutMainLoop();    // Enter the event processing loop

	return 0;          // Indicate normal termination 		
}
