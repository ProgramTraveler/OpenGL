#include<gl/glut.h>
#include<string>
#include<math.h>
#include<time.h>
#include<stdio.h>
#include<iostream>
using namespace std;

#define DISTANCE 99999 //最大视距

#define random(x) (rand()%x)//产生0~x-1之间的随机数

float WinLong = 1980 / 2 - 100;//视窗长宽z

float WinWide = 1080 / 2 + 200;

float camera_x, camera_y, camera_z;//相机移动位置

int level;//迭代次数

float univer_r;//空间旋转

GLint WindW = 800;
GLint WindH = 600;
GLfloat oldx, oldy;//鼠标移动因子
GLfloat xangle = 15.0f;
GLfloat yangle = -15.0f;//旋转因子  


//文法生成元
//F绘制树干，X绘制叶子，AB更改树干参数，+-/*%&坐标变换，[]进出栈

string grammar1 = "FA[+*&X][-/X][+%X]B";
string grammar2 = "FA[%-X][&*X][+/X][-*X]B";
string grammar3 = "FA[-*X][/&X][*%X][+&X]B";
string treegra;

//根据元生成文法字符串
string grammarIteration(string grammar, int level) {
	string tempRule = grammar;
	string rule = {};
	for (int i = 1; i <= level; i++) {
		int curlen = tempRule.length();
		int j = 0;
		srand((int)time(0));//随机种子
		while (j < curlen) {
			if (tempRule[j] == 'X') { // X迭代，替换成文法模型		
				int n = random(3);
				if (n == 0) {
					rule += grammar3;
				}
				else if (n == 1){
					rule += grammar2;
				}
				else if (n == 2) {
					rule += grammar1;
				}
				j++;
			}
			else { // 保留	
				rule += tempRule[j];
				j++;
			}
		}
		tempRule = rule;
		rule.clear();
	}
	rule = tempRule;
	return rule;
}

// 绘制树干
void drawTree(float baseRadius, float topRadius, float height) {
	GLUquadricObj* tree_obj;
	tree_obj = gluNewQuadric();//创建二次曲面对象
	glColor3ub(155, 181, 133);
	gluCylinder(tree_obj, baseRadius, topRadius, height, 30, 30);//绘制
	glTranslatef(0.0f, 0.0f, height);
}

// 绘制叶子
void drawLeaf() {
	glBegin(GL_QUADS); //绘制四边形
	//设置四边形顶点坐标
	glVertex3f(0, 0, 0);
	glVertex3f(10, 10, 0);
	glVertex3f(0, 20, 0);
	glVertex3f(-10, 10, 0);
	glEnd();
}

// 根据文法绘制分形树
void grammarDraw(string grammar) {
	float baseRadius = 10, topRadius = 6, height = 200;
	int i = 0;
	while (i < grammar.length()) {
		switch (grammar[i]) {
			//F绘制树干，X绘制叶子，AB更改树干参数，+-/*%&坐标变换，[]进出栈
			case'F':drawTree(baseRadius, topRadius, height); break;
			case'X':drawLeaf(); break;
			case'A':height *= 0.6; baseRadius *= 0.5; topRadius *= 0.5; break;
			case'B':height /= 0.6; baseRadius /= 0.5; topRadius /= 0.5; break;
			case'+':glRotatef(35, 1, 0, 0); break;
			case'-':glRotatef(-35, 1, 0, 0); break;
			case'*':glRotatef(35, 0, 1, 0); break;
			case'/':glRotatef(-35, 0, 1, 0); break;
			case'%':glRotatef(35, 0, 0, 1); break;
			case'&':glRotatef(-35, 0, 0, 1); break;
			case'[':glPushMatrix(); break;
			case']':glPopMatrix(); break;
		}
		i++;
	}
}

// 键盘回调函数
void keyBoard(unsigned char key, int x, int y) {
	univer_r += 1;
	glutPostRedisplay();  //重画，重新调用myDisplay()
}

// 绘制空间
void DrawRoom() {

	glMatrixMode(GL_PROJECTION);//投影矩阵应用
	glLoadIdentity();
	
	//正投影空间
	glOrtho(-WinLong / 2, WinLong / 2, -WinWide / 2, WinWide / 2, -DISTANCE, DISTANCE);
	
	glMatrixMode(GL_MODELVIEW);	//模型视图矩阵应用
	glLoadIdentity();
	
	//设定相机位置
	glTranslatef(camera_x, camera_y, camera_z);//移动位置
	
	gluLookAt(WinWide / 2, WinWide / 2, WinWide / 4, 0, 0, 0, 0, 0, 1);//设定机位
	
	glRotatef(univer_r, 0, 0, 1);//设定机位后旋转为旋转空间

	// 绘制分形树
	grammarDraw(treegra);

	glLoadIdentity();
}

// 显示函数
void myDisplay(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//颜色和深度缓存清空

	DrawRoom();

	glutSwapBuffers();   //双缓冲刷新
}

// 初始化函数 
void Initial(void) {
	//参数初始化
	int starGrammar = random(3);
	if (starGrammar == 0) {
		treegra = grammarIteration(grammar1, level);
	}
	else if (starGrammar == 1) {
		treegra = grammarIteration(grammar2, level);
	}
	else if (starGrammar == 2) {
		treegra = grammarIteration(grammar3, level);
	}
	glClearColor(0.8f, 0.8f, 0.8f, 0.1f);//背景，前3个是RGB，最后是Alpha值，控制透明，0.0表示完全透明
}



// 使用glut库函数进行窗口管理
int main(int argc, char* argv[]) {
	//参数初始化
	camera_x = 0;
	camera_y = -200;
	camera_z = 0;
	
	level = 4;

	//窗口初始化
	glutInit(&argc, argv);//glut初始化
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);//RGBA颜色模型|双缓冲
	glutInitWindowPosition(0, 100);//初始位置
	glutInitWindowSize(WinLong, WinWide);//窗口大小

	glutCreateWindow("L分形树");//创建窗口

	Initial();//初始化
	glutDisplayFunc(&myDisplay);//myDisplay指定为当前窗口的显示内容函数

	glutKeyboardFunc(&keyBoard);

	glutMainLoop();//使窗口框架运行

	return 0;
}
