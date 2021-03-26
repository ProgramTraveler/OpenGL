#include <GL/glut.h> 
#include<math.h>
#include<iostream>
#include<vector>

using namespace std;


double x00, y00, x11, y11;

class Point {
public :
	Point(int  _x, int _y) {
		x = _x;
		y = _y;
	}
	int x, y;
};

void MidPoint() {

	vector<Point> line;

	//第一部分连结点
	line.push_back(Point(100, 500));
	line.push_back(Point(150, 500));

	line.push_back(Point(0, 100));
	line.push_back(Point(100, 500));

	line.push_back(Point(0, 100));
	line.push_back(Point(50, 100));

	line.push_back(Point(130, 420));
	line.push_back(Point(150, 500));

	line.push_back(Point(50, 100));
	line.push_back(Point(100, 300));

	line.push_back(Point(130, 420));
	line.push_back(Point(240, 420));

	line.push_back(Point(100, 300));
	line.push_back(Point(240, 300));

	line.push_back(Point(240, 420));
	line.push_back(Point(240, 300));

	//第二部分连接点
	line.push_back(Point(100, 200));
	line.push_back(Point(100, 250));

	line.push_back(Point(100, 150));
	line.push_back(Point(100, 100));

	line.push_back(Point(100, 250));
	line.push_back(Point(240, 250));

	line.push_back(Point(240, 250));
	line.push_back(Point(240, 200));

	line.push_back(Point(100, 200));
	line.push_back(Point(140, 200));

	line.push_back(Point(200, 200));
	line.push_back(Point(240, 200));

	line.push_back(Point(140, 200));
	line.push_back(Point(140, 150));

	line.push_back(Point(100, 150));
	line.push_back(Point(140, 150));

	line.push_back(Point(200, 200));
	line.push_back(Point(200, 150));

	line.push_back(Point(200, 150));
	line.push_back(Point(240, 150));

	line.push_back(Point(240, 150));
	line.push_back(Point(240, 100));

	line.push_back(Point(100, 100));
	line.push_back(Point(140, 100));

	line.push_back(Point(200, 100));
	line.push_back(Point(240, 100));

	line.push_back(Point(140, 100));
	line.push_back(Point(140, -100));

	line.push_back(Point(200, 100));
	line.push_back(Point(200, -10));

	line.push_back(Point(200, -10));
	line.push_back(Point(240, 10));

	line.push_back(Point(140, -100));
	line.push_back(Point(300, -20));

	line.push_back(Point(240, 10));
	line.push_back(Point(300, -20));
	
	//第三部分连接点
	line.push_back(Point(400, 500));
	line.push_back(Point(450, 500));

	line.push_back(Point(300, 250));
	line.push_back(Point(400, 500));

	line.push_back(Point(300, 250));
	line.push_back(Point(350, 250));

	line.push_back(Point(350, 250));
	line.push_back(Point(370, 300));

	line.push_back(Point(430, 450));
	line.push_back(Point(450, 500));

	line.push_back(Point(430, 450));
	line.push_back(Point(700, 450));

	line.push_back(Point(390, 350));
	line.push_back(Point(410, 400));

	line.push_back(Point(410, 400));
	line.push_back(Point(600, 350));

	line.push_back(Point(560, 250));
	line.push_back(Point(600, 350));

	line.push_back(Point(390, 350));
	line.push_back(Point(560, 250));

	line.push_back(Point(370, 300));
	line.push_back(Point(520, 150));

	line.push_back(Point(440, -50));
	line.push_back(Point(520, 150));

	line.push_back(Point(440, -50));
	line.push_back(Point(500, -50));

	line.push_back(Point(500, -50));
	line.push_back(Point(580, 150));

	line.push_back(Point(620, 250));
	line.push_back(Point(700, 450));

	line.push_back(Point(580, 150));
	line.push_back(Point(580, -100));

	line.push_back(Point(620, 250));
	line.push_back(Point(770, 250));

	line.push_back(Point(770, 250));
	line.push_back(Point(770, -100));

	line.push_back(Point(580, -100));
	line.push_back(Point(770, -100));

	line.push_back(Point(620, 200));
	line.push_back(Point(740, 200));

	line.push_back(Point(740, 200));
	line.push_back(Point(740, -50));

	line.push_back(Point(620, -50));
	line.push_back(Point(740, -50));
	
	line.push_back(Point(620, -50));
	line.push_back(Point(620, 200));


	cout << line.size() << endl;
	for (int i = 0; i < line.size() - 1; i += 2) {
		x00 = line[i].x;
		y00 = line[i].y;
		x11 = line[i + 1].x;
		y11 = line[i + 1].y;
		//cout << x00 << " " << y00 << " " << x11 << " " << y11 << endl;
		glutDisplayFunc(MidPoint);

		double A = y00 - y11;
		double B = x11 - x00;
		double k = -1 * (A / B);
		//cout << k << endl;
		double  x, y, t;
		int d;

		//glClear(GL_COLOR_BUFFER_BIT);

		if (x11 < x00) {
			t = x11;
			x11 = x00;
			x00 = t;
			t = y11;
			y11 = y00;
			y00 = t;
		}

		if (k >= 0 && k <= 1) {
			d = (int)(2 * A + B);
			x = x00;
			y = y00;
			while (x != x11) {
				glBegin(GL_POINTS);
				glColor3f(2, 1, 1);
				glVertex2f(x / 1000, y / 1000);
				glEnd();
				if (d <= 0) {
					x++;
					y++;
					d += (int)(2 * (A + B));
				}
				else {
					x++;
					d += (int)(2 * A);
				}
				glFlush();
			}
		}
		if (k > 1) {
			d = (int)(A + 2 * B);
			x = x00;
			y = y00;
			//cout << "B" << endl;
			while (y != y11) {
				glBegin(GL_POINTS);
				glColor3f(2, 2, 2);
				glVertex2f(x / 1000, y / 1000);
				glEnd();
				if (d < 0) {
					y += 1;
					d += (int)(2 * B);
				}
				else {
					y += 1;
					x += 1;
					d += (int)(2 * (A + B));
				}
				glFlush();
			}

		}
		if (k >= -1 && k < 0) {
			d = (int)(2 * A - B);
			x = x00;
			y = y00;
			while (x != x11) {
				glBegin(GL_POINTS);
				glColor3f(2, 2, 2);
				glVertex2f(x / 1000, y / 1000);
				glEnd();
				if (d < 0) {
					x += 1;
					d += (int)(2 * A);
				}
				else {
					x += 1;
					y -= 1;
					d += (int)(2 * (A - B));
				}
				glFlush();
			}

		}
		if (k < -1) {
			d = (int)(A - 2 * B);
			x = x00;
			y = y00;
			while (y != y11) {
				glBegin(GL_POINTS);
				glColor3f(2, 2, 2);
				glVertex2f(x / 1000, y / 1000);
				glEnd();
				if (d < 0) {
					y -= 1;
					x += 1;
					d += (int)(2 * (A - B));
				}
				else {
					y -= 1;
					d -= (int)(2 * B);
				}
				glFlush();
			}
		}
	}
}

void main(int argc, char** argv) {

	glutInit(&argc, argv); //初始化glut
	glutInitDisplayMode(GLUT_DEPTH | GLUT_SINGLE | GLUT_RGBA);//设置窗口的模式－深度缓存，单缓存，颜色模型
	glutInitWindowPosition(200, 200); //设置窗口的位置
	glutInitWindowSize(1000, 500); //设置窗口的大小
	glutCreateWindow("对名字进行填充"); //创建窗口并赋予title

	/*vector<Point> line;
	line.push_back(Point(500, 500));
	line.push_back(Point(600, 600));
	
	line.push_back(Point(500, 500));
	line.push_back(Point(100,100));
	cout << line.size() << endl;
	/*for (int i = 0; i < line.size() - 1; i += 2) {
		x00 = line[i].x;
		y00 = line[i].y;
		x11 = line[i + 1].x;
		y11 = line[i + 1].y;
		cout << x00 << " " << y00 << " " << x11 << " " << y11 << endl;
		glutDisplayFunc(MidPoint);
	}*/
	
	/*x00 = line[0].x;
	y00 = line[0].y;
	x11 = line[1].x;
	y11 = line[1].y;*/
	glutDisplayFunc(MidPoint);

	glutMainLoop(); //进入循环等待
}

