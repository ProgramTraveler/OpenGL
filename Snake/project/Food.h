#pragma once
#include<vector>
#include"Snake.h"
typedef struct _SinglFood {
	float mposx;
	float mposz;
	int mode;
}SinglFood;

class Food {
public:
	Food();
	~Food();
	void GenerateFood(Snake snake);//�����µ�food
	void Init();
	void Deal(float x, float z);
	void Draw(unsigned int texid);
	std::vector<SinglFood> m_food;//ʳ��
private:
	float m_MoveMap[2];//���Χ

	int m_count;//����
};

