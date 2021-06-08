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
	void GenerateFood(Snake snake);//生成新的food
	void Init();
	void Deal(float x, float z);
	void Draw(unsigned int texid);
	std::vector<SinglFood> m_food;//食物
private:
	float m_MoveMap[2];//活动范围

	int m_count;//数量
};

