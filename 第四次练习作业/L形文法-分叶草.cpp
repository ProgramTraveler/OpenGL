#include <GL/glut.h>
#include <math.h>
#include <iostream>
#include <string>
#include <stack>

GLint WindW = 800;
GLint WindH = 600;
GLfloat oldx, oldy;//鼠标移动因子
GLfloat xangle = 15.0f;
GLfloat yangle = -15.0f;//旋转因子  

class Point3
{
public:
	GLfloat x, y, z;
	Point3(GLfloat x1, GLfloat y1, GLfloat z1) :x(x1), y(y1), z(z1) {};
	Point3() {};
};

using namespace std;

class Node
{
public:
	Point3 point;
	float dir;
	Node() {}
};

string rule = "F+F-F";
Point3 pStart(0, -15, 0); //start point
float length = 1.0;
float PI = 3.1415;
float Alpha = 20;
float Alphaz = 30;

void LSystemRule()
{
	string way[3];
	//way[0] = "F[+F]F[-F]F";
	way[0] = "FF[++F - F - F][--F + F + F]"; //"F[+F]F[-F]F";"FF - F[+F[+F][-F]F][-F[+F][-F]F]";
	way[1] = "F[+F]F[-F[+F]]";
	way[2] = "FF+[+F+F]-[+F]";
	//rule = way[rand() % 3];
	rule = way[0];
	//cout << "rule " << rule << endl;
	int n = 4;
	string temprule;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < rule.length(); j++)
		{
			if (rule[j] == 'F')
			{
				temprule += way[rand() % 3];
			}
			else
			{
				temprule += rule[j];
			}
		}
		rule = temprule;
		temprule.clear();
		cout << rule << endl;
	}
	cout << endl << rule << endl;
}


void draw_leaf()
{
	int i = 0;
	Node  nextNode, currentNode;
	currentNode.point = pStart;
	currentNode.dir = 85;
	stack<Node> s;
	//glColor3f(170.0 / 255.0, 164.0 / 255.0, 111.0 / 255.0);
	glColor3f(0, 255.0 / 255.0, 0);
	//cout << rule << endl;
	glColor3f(170.0 / 255.0, 164.0 / 255.0, 111.0 / 255.0);
	//cout << rule << endl;
	glScalef(0.7, 0.7, 1);
	glLineWidth(1.5);
	glPushMatrix();
	cout << rule << endl;
	while (i < rule.length())
	{
		switch (rule[i])
		{
		case'F':
			nextNode.point.x = currentNode.point.x + length * cos(currentNode.dir * PI / 180);
			nextNode.point.y = currentNode.point.y + length * sin(currentNode.dir * PI / 180);
			nextNode.point.z = currentNode.point.z + length * sin(currentNode.dir * PI / 180) * cos(currentNode.dir * PI / 180);
			nextNode.dir = currentNode.dir;
			glBegin(GL_LINES);
			glVertex3f(currentNode.point.x, currentNode.point.y, currentNode.point.z);
			glVertex3f(nextNode.point.x, nextNode.point.y, nextNode.point.z);
			glEnd();
			currentNode = nextNode;
			break;
		case'[':
			s.push(currentNode);
			break;
		case']':
			currentNode = s.top();
			s.pop();
			break;
		case'+':
			currentNode.dir += Alpha;
			break;
		case'-':
			currentNode.dir -= Alpha;
			break;
		default:
			;
		}
		i++;
	}
	glPopMatrix();
}
void  display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glLoadIdentity();
	glColor4f(1.0, 1.0, 1.0, 1.0);

	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	//glPushMatrix();
	glRotatef(xangle, 1.0, 0.0, 0.0);
	glRotatef(yangle, 0.0, 1.0, 0.0);//旋转
	draw_leaf();
	//glPopMatrix();
	glFlush();
	glutSwapBuffers();
}

void init()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	//gluOrtho2D(-100, 500, -100, 500); //四个坐标分别是左下角x坐标，右上角x坐标，左下角y坐标，右上角y坐标
	LSystemRule();
	glMatrixMode(GL_MODELVIEW);
}

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	GLfloat f = 25.0f;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h)
		glOrtho(-f, f, -f * (GLfloat)h / (GLfloat)w,
			f * (GLfloat)h / (GLfloat)w, -f, f);
	else
		glOrtho(-f * (GLfloat)w / (GLfloat)h,
			f * (GLfloat)w / (GLfloat)h, -f, f, -f, f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}



void mouse(int btn, int state, int x, int y)
{
	if ((btn == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN)) 
	{
		oldx = x; oldy = y;
	}
}

void motion(int x, int y)
{
	GLint deltax = oldx - x;
	GLint deltay = oldy - y;
	yangle += 360 * (GLfloat)deltax / (GLfloat)WindW;//根据屏幕上鼠标滑动的距离来设置旋转的角度  
	xangle += 360 * (GLfloat)deltay / (GLfloat)WindH;
	oldx = x;//记录此时的鼠标坐标，更新鼠标坐标,否则旋转将不可控 
	oldy = y;
	glutPostRedisplay();
}


int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(100, 200);
	glutInitWindowSize(600, 600);
	glutCreateWindow("Fenyecao");
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);
	init();	    
	glutMainLoop(); 
	return 0; 
}