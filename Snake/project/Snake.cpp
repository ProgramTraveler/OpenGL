
#include "Snake.h"
#include"glut.h"
#include<math.h>
float beginAng = 90;
float distance(float x, float y) {
	return sqrt(x * x + y * y);
}

Snake::Snake() {
	Init();
}


Snake::~Snake() {}


void  Snake::ChangeDirection(int diretion, int mode) {//改变m_MoveDriection方向，和蛇身体方向做判断
	float delteAng = 1;

	m_MoveAng -= diretion * delteAng;

	//限制原地旋转的角度
	if (fabs(m_MoveAng - beginAng) > 30)
		m_MoveAng += diretion * delteAng;

	(*m_snake.begin()).mAngle = m_MoveAng;

	if (mode == 1)
		MoveForWard(0.1);
}
void  Snake::MoveForWard(float t) {//移动 -->计算方向 -->改变位置
	std::vector<SnakeNode>::iterator prePtr;
	//计算方向
	for (std::vector<SnakeNode>::iterator ptr = m_snake.begin(); ptr != m_snake.end(); ptr++) {

		if (ptr == m_snake.begin()) {
			beginAng = m_MoveAng;
			float a = sin(m_MoveAng / 180.0 * 3.1415926);
			//进行移动
			(*ptr).mposx += cos(m_MoveAng / 180.0 * 3.1415926) * m_MoveSpeed * t;
			(*ptr).mposz += -sin(m_MoveAng / 180.0 * 3.1415926) * m_MoveSpeed * t;
		}
		else {
			//计算方向
			float directonX = (*prePtr).mposx - (*ptr).mposx;
			float directonZ = (*prePtr).mposz - (*ptr).mposz;
			directonX = directonX / distance(directonX, directonZ);
			directonZ = directonZ / distance(directonX, directonZ);

			//进行移动
			(*ptr).mposx += directonX * m_MoveSpeed * t;
			(*ptr).mposz += directonZ * m_MoveSpeed * t;
			(*ptr).mDriection[0] = directonX;
			(*ptr).mDriection[1] = directonZ;
			(*ptr).mAngle = atan(directonZ / directonX);
			if (directonZ < 0)
				(*ptr).mAngle = -(*ptr).mAngle;
		}
		prePtr = ptr;
	}
}
void  Snake::Draw() {//绘制 注意头和尾部的区别

	float x = 0; float y = 0;
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	for (std::vector<SnakeNode>::iterator ptr = m_snake.begin(); ptr != m_snake.end(); ptr++) {
		glPushMatrix();
		if (ptr == m_snake.begin()) {
			if ((*ptr).mposx * 2.0 > m_MoveMap[0])x = -m_MoveMap[0];
			if ((*ptr).mposx * 2.0 < -m_MoveMap[0])x = m_MoveMap[0];

			if ((*ptr).mposz * 2.0 > m_MoveMap[1]) y = -m_MoveMap[0];
			if ((*ptr).mposz * 2.0 < -m_MoveMap[1])y = m_MoveMap[0];
		}
		(*ptr).mposx += x;
		(*ptr).mposz += y;
		/*int a = ((*ptr).mposx*2.0) / (m_MoveMap[0]);
		int b = ((*ptr).mposz*2.0) / (m_MoveMap[1]);
		glTranslatef( (*ptr).mposx - a * m_MoveMap[0], 0, (*ptr).mposz - b * m_MoveMap[1]);*/
		glTranslatef((*ptr).mposx, 0, (*ptr).mposz);
		glRotatef((*ptr).mAngle, 0, 1, 0);
		if (ptr == m_snake.begin())
			glutSolidCube(1.0);
		else if (ptr == m_snake.end())
			glutSolidSphere(0.5, 20, 20);
		else
			glutSolidSphere(0.5, 20, 20);
		glPopMatrix();
	}
	glDisable(GL_LIGHTING);

}

bool  Snake::CollisonFood(float foodx, float foody) {//检测是否吃到食物

	//检测头部和食物的位置
	float dis = sqrt((foodx - (*m_snake.begin()).mposx) * (foodx - (*m_snake.begin()).mposx) + (foody - (*m_snake.begin()).mposz) * (foody - (*m_snake.begin()).mposz));
	if (dis < 0.9) {
		//尾部添加
		SnakeNode snake;

		snake.mAngle = m_snake.at(m_snake.size() - 1).mAngle;
		snake.mDriection[0] = m_snake.at(m_snake.size() - 1).mDriection[0];
		snake.mDriection[1] = m_snake.at(m_snake.size() - 1).mDriection[1];
		snake.mposx = m_snake.at(m_snake.size() - 1).mposx - snake.mDriection[0];
		snake.mposz = m_snake.at(m_snake.size() - 1).mposz - snake.mDriection[1];
		m_snake.push_back(snake);
		return true;

	}


	return false;
}

void  Snake::Init() {//初始化
	m_snake.clear();
	//hhstd::vector<SnakeNode> m_snake;
	m_MoveSpeed = 1;// 蛇头移动速度
	m_MoveAng = 90;
	m_MoveMap[0] = 100;//活动范围
	m_MoveMap[1] = 100;

	int xpos = 0;
	int zpos = 0;

	//初始化关节
	for (int i = 0; i < 4; i++) {
		SnakeNode snake;
		snake.mDriection[0] = 0;
		snake.mDriection[1] = -1;
		snake.mAngle = 90.0;
		snake.mposx = xpos + 0.5;
		snake.mposz = zpos + 0.5 + i;

		m_snake.push_back(snake);
	}
}
void  Snake::CollisonSelf() {//自己是否碰撞

	for (std::vector<SnakeNode>::iterator ptr = m_snake.begin(); ptr != m_snake.end(); ptr++) {
		if (ptr != m_snake.begin()) {
			//判断 头部和关节的距离
			float dis = (sqrt((*ptr).mposx - (*m_snake.begin()).mposx) * ((*ptr).mposx - (*m_snake.begin()).mposx) + ((*ptr).mposz - (*m_snake.begin()).mposz) * ((*ptr).mposz - (*m_snake.begin()).mposz));
			if (dis < 0.8)
				Init();
		}

	}

}