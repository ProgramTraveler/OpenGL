#include <iostream>
#include "glut.h"//openglͷ�ļ�
#pragma comment(lib,"glut32.lib")//opengl��
#include"Snake.h"
#include<vector>
#include"Food.h"
#include"LoadTexbmp.h"
#include<string>
#include <sstream>

GLfloat m_tranlate[3] = { 0,0,-10 };//����ƽ�ƣ���ӦX Y Z ƽ����������W:��    S:��    A:��  D:��
GLfloat m_rorate[2] = { 0,0 };//������ת���ֱ���X���Y����ת�ĽǶȣ�������������
GLfloat m_scale = 1.0;//�������ţ�������м���ֿ���
GLint   m_MouseDownPT[2] = { 0,0 };//��¼�������㣬���ڿ�����ת�Ƕ�
bool    m_bMouseDown = false;//��¼�������Ƿ��£�����ΪTRUE,��ʼֵΪfalse
float map_witdh = 100;//��ͼ�Ŀ��
float map_depth = 100;//��ͼ�����
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
GLuint TextureImage[6];//�����Ӧ�ı�� ���������ӳ����� 

void  LoadTextMap(void) {//����ͼ
	TextureImage[0] = LoadTexBMP("food.bmp");//���صڶ���ͼ
	TextureImage[1] = LoadTexBMP("table.bmp");//���صڶ���ͼ
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

//���»���
void display() {
	char string[25];
	_itoa_s(score, string, 10);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	//��������ɫ����Ȼ���

	DoRasterString(0, 0.3, -1, "score:");
	DoRasterString(0.15, 0.3, -1, string);
	glPushMatrix();//ѹջ
	glColor3f(1.0, 0, 0);//������ɫΪ��ɫ
	glTranslatef(m_tranlate[0], m_tranlate[1], m_tranlate[2]);//ƽ��(X,Y,Z)
	glRotatef(m_rorate[0], 1, 0, 0);//��ת ��X��
	glRotatef(m_rorate[1], 0, 1, 0);//��ת ��Y��
	glScalef(m_scale, m_scale, m_scale);//���ţ�X,Y,Z��


	
	gluLookAt(eye[0], eye[1], eye[2], lookat[0], lookat[1], lookat[2], 0, 1, 0);
	DrawMap();//���Ƶ�ͼ
	m_snake.Draw();		//������
	m_food.Draw(TextureImage[0]);//����ʳ��
	
	glPopMatrix();//��ջ
	glutSwapBuffers();//����ǰ�󻺳���

}

//���ڴ�С�ı��¼�  
void ReshapeEvent(int width, int height) {

	glViewport(0, 0, width, height);//�ӿ�����Ļ�Ĵ�Сλ�� 
	glMatrixMode(GL_PROJECTION);// ͶӰ����
	glLoadIdentity();           // ����λ
	gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 10000.0f);// ����ͶӰ����
	glMatrixMode(GL_MODELVIEW);	// ģ�;���
	glLoadIdentity();//��λ����
	glEnable(GL_DEPTH_TEST);//������ȼ��

}
//�����¼������¼�
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
	//������
	
	lookat[0] = (*m_snake.m_snake.begin()).mposx;// -a * map_witdh;
	lookat[1] = 2;
	lookat[2] = (*m_snake.m_snake.begin()).mposz;// -b * map_depth;
	float ang = m_snake.m_MoveAng;
	float dis = 10;
	eye[0] = lookat[0] - dis * cos(ang / 180 * 3.1415926);
	eye[1] = lookat[1] + 3;
	eye[2] = lookat[2] + dis * sin(ang / 180 * 3.1415926);


	m_snake.MoveForWard(0.1);
	glutPostRedisplay(); //ˢ�º���

}

//�����¼� Ĭ����Ӣ�����뷨�µĴ�д��ĸ
void KeyboardEvent(unsigned char key, int x, int y) {
	switch (key) {
	case 'W'://���ƶ�
		m_snake.MoveForWard(0.1);
		//m_tranlate[1] += 0.1;
		break;
	case 'S'://���ƶ�
		m_tranlate[1] -= 0.1;
		break;
	case 'A'://���ƶ�
		m_snake.ChangeDirection(-1, 1);
		//m_tranlate[0] -= 0.1;
		break;
	case 'D'://���ƶ�
		m_snake.ChangeDirection(1, 1);
		//m_tranlate[0] += 0.1;
		break;
	}
}
//����¼�
void MouseEvent(int button, int state, int x, int y) {

	//1��������ţ����Ϲ����Ŵ����¹�����С
	if (state == GLUT_UP && button == GLUT_WHEEL_UP) {//�������Ϲ���
		m_scale += 0.1;
	}

	else if (state == GLUT_UP && button == GLUT_WHEEL_DOWN) {//�������¹���
		m_scale -= 0.1;
		if (m_scale < 0.1) m_scale = 0.1;
	}


	//��2 �������Ƿ��¡�
	if (state == GLUT_DOWN && button == GLUT_LEFT_BUTTON) {
		m_bMouseDown = true;//����������
		m_MouseDownPT[0] = x;//��¼��ǰX����
		m_MouseDownPT[1] = y;////��¼��ǰY����
	}
	else {
		m_bMouseDown = false;//���������𣬽�����ת
	}


	/*��һ�����������ĸ����������»��ɿ�������������������������ֵ�е�һ����
	GLUT_LEFT_BUTTON
	GLUT_MIDDLE_BUTTON
	GLUT_RIGHT_BUTTON
	�ڶ����������������������÷���ʱ������״̬��Ҳ�����Ǳ����£����ɿ�������ȡֵ���£�
	GLUT_DOWN
	GLUT_UP
	�����ĸ����� XY �����Ͻ�λԭ��
	*/



}
void init() {
	LoadTextMap();
}

//������갴ť�ƶ�����¼�
void MotionEvent(int x, int y) {
	if (m_bMouseDown) {//���������������
		m_rorate[0] += y - m_MouseDownPT[1];//ͨ���������ı���ת�ĽǶ�
		m_rorate[1] += x - m_MouseDownPT[0];//ͨ���������ı���ת�ĽǶ�

		m_MouseDownPT[0] = x;//��¼��ǰX����
		m_MouseDownPT[1] = y;//��¼��ǰY����
	}
}

//�����������뿪����
void MouseEntry(int state) {
	/*state������ֵ�������뿪���ǽ��봰��:
	GLUT_LEFT
	GLUT_ENTERED*/
}

//����˵���Ӧ�¼�
void MenuEvent(int choose) {
	switch (choose) {
	case 1://��λ������תƽ�����ŵ�ֵ��λ
		//����ƽ�ƣ���ӦX Y Z ƽ����������W:��  S:��   A:��  D����
		m_tranlate[0] = 0;
		m_tranlate[1] = 0;
		m_tranlate[2] = -10;

		//������ת���ֱ�����X�� ��Y����ת�ĽǶȣ�������������
		m_rorate[0] = 0;
		m_rorate[1] = 0;

		//�������ţ�������м���ֿ���
		m_scale = 1.0;

		//��¼�������㣬���ڿ�����ת�Ƕȣ�
		m_MouseDownPT[0] = 0;
		m_MouseDownPT[1] = 0;

		//��¼�������Ƿ��£�����Ϊtrue,��ʼֵΪfalse
		m_bMouseDown = false;
		break;
	case 2://���ܴ�������ʱ��������
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

	glutTimerFunc(10, timerProc, 1);//��Ҫ�ں������ٵ���һ�Σ����ܱ�֤ѭ��

}

int main(int argc, char** argv) {
	glutInit(&argc, (char**)argv); //��GLUT���г�ʼ�� 
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); //����ģʽΪ��˫���壬��Ȼ�����
	glutInitWindowPosition(110, 120);//����λ��
	glutInitWindowSize(440, 400);//���ڴ�С
	glutCreateWindow("project");  //��������
	glutDisplayFunc(display);    // ���»����¼� 
	//-------------ע��ص�����---------------------//
	glutKeyboardFunc(KeyboardEvent); // �����¼�
	glutMouseFunc(MouseEvent);       //����¼�
	glutReshapeFunc(ReshapeEvent);   //���ڴ�С�����仯�¼�
	glutMotionFunc(MotionEvent);     //����ƶ��¼�
	glutIdleFunc(IdleEvent);         //���д����¼�
	glutSpecialFunc(&SpecialKey);
	init();
	glutEntryFunc(MouseEntry);       //�����������뿪����
	{
		glutCreateMenu(MenuEvent);       //�����˵�
		glutAddMenuEntry("��λ", 1);     //�˵���1
		glutAddMenuEntry("����", 2);     //�˵���2
		glutAttachMenu(GLUT_RIGHT_BUTTON);//����Ҽ����µ����˵�
	}
	//glutTimerFunc(33, timerProc, 1);//��Ҫ�ں������ٵ���һ�Σ����ܱ�֤ѭ��
	glutMainLoop();                  //������ע��Ļص����� 

	return 0;
}


// ���г���: Ctrl + F5 ����� >����ʼִ��(������)���˵�
// ���Գ���: F5 ����� >����ʼ���ԡ��˵�

// ������ʾ: 
//   1. ʹ�ý��������Դ�������������/�����ļ�
//   2. ʹ���Ŷ���Դ�������������ӵ�Դ�������
//   3. ʹ��������ڲ鿴���������������Ϣ
//   4. ʹ�ô����б��ڲ鿴����
//   5. ת������Ŀ��>���������Դ����µĴ����ļ�����ת������Ŀ��>�����������Խ����д����ļ���ӵ���Ŀ
//   6. ��������Ҫ�ٴδ򿪴���Ŀ����ת�����ļ���>���򿪡�>����Ŀ����ѡ�� .sln �ļ�
