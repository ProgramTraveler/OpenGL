#include <GL/glut.h> 
#include<math.h>
#include<iostream>
#include<vector>
#include<queue>
#include<stack>

using namespace std;

class Point {
public:
	Point(int  _x, int _y) {
		x = _x;
		y = _y;
	}
	int x, y;
};

double x00, y00, x11, y11;


int flag[2021][2021] = { 0 };

vector<Point> line; //记录原始名字点的坐标
vector<Point> traslation; //记录平移后的点的坐标
vector<Point> scale; //记录比列变换后的点的坐标

void MakeName() {
	//第一部分连接点
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

	line.push_back(Point(400, 100));
	line.push_back(Point(520, 150));

	line.push_back(Point(400, 100));
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
}


void Traslation(int row, int col) {
	//对原坐标进行平移变换，设置x和y的移动距离
	for (int i = 0; i < line.size(); i++) {
		traslation.push_back(Point(line[i].x + row, line[i].y + col));
	}
}

void Scale(double k) {
	for (int i = 0; i < line.size(); i++) {
		scale.push_back(Point(line[i].x * k - 950, line[i].y * k - 450));
	}
}

void Flood(int a, int b) {
	int dx[4] = { -1, 0, 1, 0 };
	int dy[4] = { 0, -1, 0, 1 };

	//stack<Point> q;
	queue<Point> q;
	q.push(Point(a, b));

	flag[a + 1000][b + 1000] = 1;

	while (q.size()) {
		//auto t = q.top();
		auto t = q.front();
		q.pop();

		for (int i = 0; i < 4; i++) {

			int n = t.x + dx[i];
			int m = t.y + dy[i];
			//cout << m << n << endl;

			if (n < -1000 || n > 1000 || m < -1000 || m >= 1000) continue;

			if (flag[n + 1000][m + 1000]) continue;

			flag[n + 1000][m + 1000] = 1;
			glBegin(GL_POINTS);
			glColor3f(0, 1, 1);
			glVertex2f((double)n / 1000, (double)m / 1000);
			glEnd();
			q.push(Point(n, m));
			//glFlush();
		}
	}

}

void DrawLine(vector<Point>& Line) {
	for (int i = 0; i < Line.size() - 1; i += 2) {
		x00 = Line[i].x;
		y00 = Line[i].y;
		x11 = Line[i + 1].x;
		y11 = Line[i + 1].y;



		double A = y00 - y11;
		double B = x11 - x00;
		double k = -1 * (A / B);


		double  x, y, t;

		double d;

		//保留之前画的线条，所以把这行代码注释掉
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
			d = (2 * A + B);
			x = x00;
			y = y00;
			while (x != x11) {
				glBegin(GL_POINTS);
				glColor3f(0, 1, 1);
				glVertex2f(x / 1000, y / 1000);
				flag[(int)(x + 1000)][(int)(y + 1000)] = 1;
				glEnd();
				if (d <= 0) {
					x += 1;
					y += 1;
					d += (2 * (A + B));
				}
				else {
					x++;
					d += (2 * A);
				}
				glFlush();
			}
		}
		if (k > 1) {
			d = (A + 2 * B);
			x = x00;
			y = y00;
			while (y != y11) {
				glBegin(GL_POINTS);
				glColor3f(0, 1, 1);
				glVertex2f(x / 1000, y / 1000);
				flag[(int)(x + 1000)][(int)(y + 1000)] = 1;
				glEnd();
				if (d < 0) {
					y += 1;
					d += (2 * B);
				}
				else {
					y += 1;
					x += 1;
					d += (2 * (A + B));
				}
				glFlush();
			}

		}
		if (k >= -1 && k < 0) {
			d = (2 * A - B);
			x = x00;
			y = y00;
			while (x != x11) {
				glBegin(GL_POINTS);
				glColor3f(0, 1, 1);
				glVertex2f(x / 1000, y / 1000);
				flag[(int)(x + 1000)][(int)(y + 1000)] = 1;
				glEnd();
				if (d < 0) {
					x += 1;
					d += (2 * A);
				}
				else {
					x += 1;
					y -= 1;
					d += (2 * (A - B));
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
				glColor3f(0, 1, 1);
				glVertex2f(x / 1000, y / 1000);
				flag[(int)(x + 1000)][(int)(y + 1000)] = 1;
				glEnd();
				if (d < 0) {
					y -= 1;
					x += 1;
					d += (2 * (A - B));
				}
				else {
					y -= 1;
					d -= (2 * B);
				}
				glFlush();
			}
		}
	}
}

void DrawName() {
	MakeName(); //生成文字所需要点的信息
	DrawLine(line); //绘制原文字
	//对原文字进行填充
	Flood(25, 102);
	Flood(141, 90);
	Flood(521, 151);
	glFlush();

	Traslation(-950, 450); //对原文字进行平移变换
	DrawLine(traslation);
	Flood(25 - 950, 102 + 450);
	Flood(141 - 950, 90 + 450);
	Flood(521 - 950, 151 + 450);
	glFlush();

	Scale(0.5);

	DrawLine(scale);
	Flood(25 * 0.5 - 950, 102 * 0.5 - 450);
	Flood(141 * 0.5 - 950, 90 * 0.5 - 450);
	Flood(521 * 0.5 - 950, 151 * 0.5 - 450);
	glFlush();


}

void display() {
	DrawName();
}

int main(int argc, char** argv) {

	glutInit(&argc, argv); //初始化glut
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);//设置窗口的模式－深度缓存，单缓存，颜色模型
	glutInitWindowPosition(200, 200); //设置窗口的位置

	glutInitWindowSize(600, 600); //设置窗口的大小
	glutCreateWindow("对名字进行填充"); //创建窗口并赋予title

	glutDisplayFunc(display);

	glutMainLoop(); //进入循环等待

	return 0;
}

