#pragma once
#include<vector>
typedef struct _SnakeNode {
	float mposx;//�ؽ�λ��
	float mposz;//
	float mDriection[2];//����
	float mAngle;//
}SnakeNode;


class Snake {
public:
	Snake();
	~Snake();
	void  ChangeDirection(int diretion, int mode = 0);//�ı�m_MoveDriection���򣬺������巽�����ж�
	void  MoveForWard(float t);//�ƶ� -->���㷽�� -->�ı�λ��
	void  Draw();//���� ע��ͷ��β��������
	bool  CollisonFood(float foodx, float foody);//����Ƿ�Ե�ʳ��
	std::vector<SnakeNode> m_snake;//�ؽ�
	float m_MoveAng;//��ͷ�ƶ�����
	float m_MoveSpeed;//��ͷ�ƶ��ٶ�
private:



	float m_MoveMap[2];//���Χ
	void  Init();//��ʼ��
	void  CollisonSelf();//�Լ��Ƿ���ײ
};

