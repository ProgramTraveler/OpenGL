#include <iostream>
#include "glut.h"//opengl头文件
#pragma comment(lib,"glut32.lib")//opengl库
#include"Snake.h"
#include<vector>
#include"Food.h"
#include"LoadTexbmp.h"
#include<string>
#include <sstream>

GLfloat m_tranlate[3] = { 0,0,-10 };//用于平移，对应X Y Z 平移量。按键W:上    S:下    A:左  D:右
GLfloat m_rorate[2] = { 0,0 };//用于旋转，分别绕X轴和Y轴旋转的角度，用鼠标左键控制
GLfloat m_scale = 1.0;//用于缩放，用鼠标中间滚轮控制
GLint   m_MouseDownPT[2] = { 0,0 };//记录鼠标坐标点，用于控制旋转角度
bool    m_bMouseDown = false;//记录鼠标左键是否按下，按下为TRUE,初始值为false
float map_witdh = 100;//地图的宽度
float map_depth = 100;//地图的深度
Snake m_snake;
Food m_food;
float eye[3];
float lookat[3];
int score = 0;


void DoRasterString(float x, float y, float z, const char* s) {
	glRasterPos3f((GLfloat)x, (GLfloat)y, (GLfloat)z);

	char c; // one character to print
	for (; (c = *s) != '\0'; s++) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);
	}
}
GLuint TextureImage[6];//纹理对应的编号 定义纹理的映射个数 

void  LoadTextMap(void) {//加载图
	TextureImage[0] = LoadTexBMP("food.bmp");//加载第二个图
	TextureImage[1] = LoadTexBMP("table.bmp");//加载第二个图
}
void DrawMap() {
	glPushMatrix();
	
	glColor3f(1, 1, 1);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, TextureImage[1]);
	glBegin(GL_QUADS);

	glTexCoord2f(-map_depth / 2.0, -map_depth / 2.0); glVertex3f(-map_depth / 2.0, 0, -map_depth / 2.0);
	glTexCoord2f(map_depth / 2.0, -map_depth / 2.0); glVertex3f(map_depth / 2.0, 0, -map_depth / 2.0);
	glTexCoord2f(map_depth / 2.0, map_depth / 2.0); glVertex3f(map_depth / 2.0, 0, map_depth / 2.0);
	glTexCoord2f(-map_depth / 2.0, map_depth / 2.0); glVertex3f(-map_depth / 2.0, 0, map_depth / 2.0);

	glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}

//重新绘制
void display() {
	char string[25];
	_itoa_s(score, string, 10);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	//擦除背景色和深度缓存

	DoRasterString(0, 0.3, -1, "score:");
	DoRasterString(0.15, 0.3, -1, string);
	glPushMatrix();//压栈
	glColor3f(1.0, 0, 0);//设置颜色为红色
	glTranslatef(m_tranlate[0], m_tranlate[1], m_tranlate[2]);//平移(X,Y,Z)
	glRotatef(m_rorate[0], 1, 0, 0);//旋转 绕X轴
	glRotatef(m_rorate[1], 0, 1, 0);//旋转 绕Y轴
	glScalef(m_scale, m_scale, m_scale);//缩放（X,Y,Z）


	
	gluLookAt(eye[0], eye[1], eye[2], lookat[0], lookat[1], lookat[2], 0, 1, 0);
	DrawMap();//绘制地图
	m_snake.Draw();		//绘制蛇
	m_food.Draw(TextureImage[0]);//绘制食物
	
	glPopMatrix();//出栈
	glutSwapBuffers();//交互前后缓冲区

}

//窗口大小改变事件  
void ReshapeEvent(int width, int height) {

	glViewport(0, 0, width, height);//视口在屏幕的大小位置 
	glMatrixMode(GL_PROJECTION);// 投影矩阵
	glLoadIdentity();           // 矩阵单位
	gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 10000.0f);// 设置投影矩阵
	glMatrixMode(GL_MODELVIEW);	// 模型矩阵
	glLoadIdentity();//单位矩阵化
	glEnable(GL_DEPTH_TEST);//启动深度检测

}
//空闲事件处理事件
void IdleEvent() {
	for (std::vector<SinglFood>::iterator ptr = m_food.m_food.begin(); ptr != m_food.m_food.end(); ptr++) {
		if (m_snake.CollisonFood((*ptr).mposx, (*ptr).mposz)) {
			if ((*ptr).mode == 1) {
				m_snake.m_MoveSpeed *= 1.4;
			}
			else {
				m_snake.m_MoveSpeed *= 0.8;
			}
			score += 1;
			m_food.Deal((*ptr).mposx, (*ptr).mposz);
			m_food.GenerateFood(m_snake);
			break;
		}
	}
	//超界限
	
	lookat[0] = (*m_snake.m_snake.begin()).mposx;// -a * map_witdh;
	lookat[1] = 2;
	lookat[2] = (*m_snake.m_snake.begin()).mposz;// -b * map_depth;
	float ang = m_snake.m_MoveAng;
	float dis = 10;
	eye[0] = lookat[0] - dis * cos(ang / 180 * 3.1415926);
	eye[1] = lookat[1] + 3;
	eye[2] = lookat[2] + dis * sin(ang / 180 * 3.1415926);


	m_snake.MoveForWard(0.1);
	glutPostRedisplay(); //刷新函数

}

//键盘事件 默认是英文输入法下的大写字母
void KeyboardEvent(unsigned char key, int x, int y) {
	switch (key) {
	case 'W'://上移动
		m_snake.MoveForWard(0.1);
		//m_tranlate[1] += 0.1;
		break;
	case 'S'://下移动
		m_tranlate[1] -= 0.1;
		break;
	case 'A'://左移动
		m_snake.ChangeDirection(-1, 1);
		//m_tranlate[0] -= 0.1;
		break;
	case 'D'://右移动
		m_snake.ChangeDirection(1, 1);
		//m_tranlate[0] += 0.1;
		break;
	}
}
//鼠标事件
void MouseEvent(int button, int state, int x, int y) {

	//1、鼠标缩放：往上滚动放大；往下滚动缩小
	if (state == GLUT_UP && button == GLUT_WHEEL_UP) {//滚轮往上滚动
		m_scale += 0.1;
	}

	else if (state == GLUT_UP && button == GLUT_WHEEL_DOWN) {//滚轮往下滚动
		m_scale -= 0.1;
		if (m_scale < 0.1) m_scale = 0.1;
	}


	//【2 鼠标左键是否按下】
	if (state == GLUT_DOWN && button == GLUT_LEFT_BUTTON) {
		m_bMouseDown = true;//鼠标左键按下
		m_MouseDownPT[0] = x;//记录当前X坐标
		m_MouseDownPT[1] = y;////记录当前Y坐标
	}
	else {
		m_bMouseDown = false;//鼠标左键弹起，结束旋转
	}


	/*第一个参数表明哪个鼠标键被按下或松开，这个变量可以是下面的三个值中的一个：
	GLUT_LEFT_BUTTON
	GLUT_MIDDLE_BUTTON
	GLUT_RIGHT_BUTTON
	第二个参数表明，函数被调用发生时，鼠标的状态，也就是是被按下，或松开，可能取值如下：
	GLUT_DOWN
	GLUT_UP
	第三四个参数 XY 以左上角位原点
	*/



}
void init() {
	LoadTextMap();
}

//按下鼠标按钮移动鼠标事件
void MotionEvent(int x, int y) {
	if (m_bMouseDown) {//如果鼠标左键被按下
		m_rorate[0] += y - m_MouseDownPT[1];//通过滑动鼠标改变旋转的角度
		m_rorate[1] += x - m_MouseDownPT[0];//通过滑动鼠标改变旋转的角度

		m_MouseDownPT[0] = x;//记录当前X坐标
		m_MouseDownPT[1] = y;//记录当前Y坐标
	}
}

//检测鼠标进入或离开窗口
void MouseEntry(int state) {
	/*state有两个值表明是离开还是进入窗口:
	GLUT_LEFT
	GLUT_ENTERED*/
}

//点击菜单响应事件
void MenuEvent(int choose) {
	switch (choose) {
	case 1://复位：把旋转平移缩放的值复位
		//用于平移，对应X Y Z 平移量。按键W:上  S:下   A:左  D：右
		m_tranlate[0] = 0;
		m_tranlate[1] = 0;
		m_tranlate[2] = -10;

		//用于旋转，分别是绕X轴 和Y轴旋转的角度，用鼠标左键控制
		m_rorate[0] = 0;
		m_rorate[1] = 0;

		//用于缩放，用鼠标中间滚轮控制
		m_scale = 1.0;

		//记录鼠标坐标点，用于控制旋转角度；
		m_MouseDownPT[0] = 0;
		m_MouseDownPT[1] = 0;

		//记录鼠标左键是否按下，按下为true,初始值为false
		m_bMouseDown = false;
		break;
	case 2://功能待定：暂时不做处理
		break;

	}
}

void SpecialKey(GLint key, GLint x, GLint y) {

	if (key == GLUT_KEY_UP) {
		m_snake.m_MoveSpeed += 0.01;
		if (m_snake.m_MoveSpeed > 1.0)m_snake.m_MoveSpeed = 1.0;
	}
	if (key == GLUT_KEY_LEFT) {
		m_snake.ChangeDirection(-1);
	}
	if (key == GLUT_KEY_DOWN) {
		m_snake.m_MoveSpeed -= 0.01;
		if (m_snake.m_MoveSpeed < 0.05)m_snake.m_MoveSpeed = 0.05;
	}
	if (key == GLUT_KEY_RIGHT) {
		m_snake.ChangeDirection(1);
	}

}

void timerProc(int id) {

	glutTimerFunc(10, timerProc, 1);//需要在函数中再调用一次，才能保证循环

}

int main(int argc, char** argv) {
	glutInit(&argc, (char**)argv); //对GLUT进行初始化 
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); //设置模式为：双缓冲，深度缓存区
	glutInitWindowPosition(110, 120);//窗口位置
	glutInitWindowSize(440, 400);//窗口大小
	glutCreateWindow("project");  //创建窗口
	glutDisplayFunc(display);    // 重新绘制事件 
	//-------------注册回调函数---------------------//
	glutKeyboardFunc(KeyboardEvent); // 键盘事件
	glutMouseFunc(MouseEvent);       //鼠标事件
	glutReshapeFunc(ReshapeEvent);   //窗口大小发生变化事件
	glutMotionFunc(MotionEvent);     //鼠标移动事件
	glutIdleFunc(IdleEvent);         //空闲处理事件
	glutSpecialFunc(&SpecialKey);
	init();
	glutEntryFunc(MouseEntry);       //检测鼠标进入或离开窗口
	{
		glutCreateMenu(MenuEvent);       //创建菜单
		glutAddMenuEntry("复位", 1);     //菜单项1
		glutAddMenuEntry("待定", 2);     //菜单项2
		glutAttachMenu(GLUT_RIGHT_BUTTON);//鼠标右键按下弹出菜单
	}
	//glutTimerFunc(33, timerProc, 1);//需要在函数中再调用一次，才能保证循环
	glutMainLoop();                  //调用已注册的回调函数 

	return 0;
}


// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
