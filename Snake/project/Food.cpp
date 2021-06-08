
#include "Food.h"
#include<random>
#include"glut.h"

float ang = 0;
Food::Food() {
	Init();
}


Food::~Food() {}
void Food::Deal(float x, float z) {
	int num = 0;
	std::vector<SinglFood>::iterator ptr;
	for (ptr = m_food.begin(); ptr != m_food.end(); ptr++) {
		float dis = sqrt(((*ptr).mposx - x) * ((*ptr).mposx - x) + ((*ptr).mposz - z) * ((*ptr).mposz - z));
		if (dis < 0.1) {
			m_food.erase(ptr);
			break;
		}
	}

}
void  Food::Draw(unsigned int texid) {
	ang += 0.1;
	if (ang > 360) ang = 0;
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texid);
	glEnable(GL_LIGHTING);
	for (std::vector<SinglFood>::iterator ptr = m_food.begin(); ptr != m_food.end(); ptr++)
	{
		glPushMatrix();
		glTranslatef((*ptr).mposx, 0.5, (*ptr).mposz);
		glRotatef(ang, 0, 1, 0);
		//glutSolidTorus(0.3,0.5,40,40);
		if ((*ptr).mode == 0)
			glutSolidTeapot(0.5);
		if ((*ptr).mode == 1)
			glutSolidTorus(0.3, 0.5, 40, 40);
		if ((*ptr).mode == 2)
			glutSolidSphere(0.4, 40, 40);
		glPopMatrix();
	}
	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
}
void Food::GenerateFood(Snake snake)//生成新的food
{
	SinglFood m_SinglFood;
	m_SinglFood.mposx = rand() / (float)RAND_MAX * m_MoveMap[0] - m_MoveMap[0] / 2;
	m_SinglFood.mposz = rand() / (float)RAND_MAX * m_MoveMap[1] - m_MoveMap[1] / 2;
	m_SinglFood.mode = rand() / (float)RAND_MAX * 2.9;
	//for (std::vector<SnakeNode>::iterator ptr = snake.m_snake.begin(); ptr != snake.m_snake.end(); ptr++)
	//{
	//	float dis = sqrt( ((*ptr).mposx - m_SinglFood.mposx)*  ((*ptr).mposx - m_SinglFood.mposx) + ((*ptr).mposz - m_SinglFood.mposz) * ((*ptr).mposz - m_SinglFood.mposz) );
	//	if (dis < 2)
	//	{
	//		m_SinglFood.mposx = (*snake.m_snake.begin()).mposx + 10;
	//		m_SinglFood.mposz = (*snake.m_snake.begin()).mposz + 10;
	//	}
//	}
	m_food.push_back(m_SinglFood);
}
void Food::Init() {
	m_food.clear();
	m_count = 10;
	m_MoveMap[0] = 70;
	m_MoveMap[1] = 70;
	for (int i = 0; i < m_count; i++) {
		SinglFood m_SinglFood;
		m_SinglFood.mposx = rand() / (float)RAND_MAX * m_MoveMap[0] - m_MoveMap[0] / 2;
		m_SinglFood.mposz = rand() / (float)RAND_MAX * m_MoveMap[1] - m_MoveMap[1] / 2;
		m_SinglFood.mode = rand() / (float)RAND_MAX * 2.9;
		m_food.push_back(m_SinglFood);
	}
}
//float m_MoveMap[2];//活动范围