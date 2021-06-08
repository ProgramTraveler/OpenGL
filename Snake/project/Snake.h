#pragma once
#include<vector>
typedef struct _SnakeNode {
	float mposx;//关节位置
	float mposz;//
	float mDriection[2];//方向
	float mAngle;//
}SnakeNode;


class Snake {
public:
	Snake();
	~Snake();
	void  ChangeDirection(int diretion, int mode = 0);//改变m_MoveDriection方向，和蛇身体方向做判断
	void  MoveForWard(float t);//移动 -->计算方向 -->改变位置
	void  Draw();//绘制 注意头和尾部的区别
	bool  CollisonFood(float foodx, float foody);//检测是否吃到食物
	std::vector<SnakeNode> m_snake;//关节
	float m_MoveAng;//蛇头移动方向
	float m_MoveSpeed;//蛇头移动速度
private:



	float m_MoveMap[2];//活动范围
	void  Init();//初始化
	void  CollisonSelf();//自己是否碰撞
};

