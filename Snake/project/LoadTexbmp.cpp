#include"LoadTexbmp.h"

/*
 *  ��BMP�ļ��м�������
 */

int LoadTexBMP(const char* file) {
	unsigned int   texture; //��������  
	FILE* f; //�ļ�ָ��          
	short magic; //Image magic
	int   dx, dy, size; //ͼƬ�ߴ�
	short nbp, bpp;   
	char* image;      
	int   off; //ͼ��ƫ��
	int   k;   // Counter
	int   max; //�������ߴ�    

	fopen_s(&f, file, "rb");

	if (!f) {}
	
	if (fread(&magic, 2, 1, f) != 1) {}

	if (magic != 0x4D42 && magic != 0x424D) {}

	if (fseek(f, 8, SEEK_CUR) || fread(&off, 4, 1, f) != 1 || fseek(f, 4, SEEK_CUR) || fread(&dx, 4, 1, f) != 1 || fread(&dy, 4, 1, f) != 1 || fread(&nbp, 2, 1, f) != 1 || fread(&bpp, 2, 1, f) != 1 || fread(&k, 4, 1, f) != 1)
	{}

	
	glGetIntegerv(GL_MAX_TEXTURE_SIZE, &max);

	size = 3 * dx * dy;
	image = (char*)malloc(size);
	if (!image) {}
	
	if (fseek(f, off, SEEK_SET) || fread(image, size, 1, f) != 1) {}

	fclose(f);

	for (k = 0; k < size; k += 3) {
		unsigned char temp = image[k];
		image[k] = image[k + 2];
		image[k + 2] = temp;
	}

	//  Sanity check

	//���ɶ�ά����
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	//����ͼƬ
	glTexImage2D(GL_TEXTURE_2D, 0, 3, dx, dy, 0, GL_RGB, GL_UNSIGNED_BYTE, image);

	//��ͼ���С��ƥ��ʱ��������
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	free(image);
	//������������
	return texture;
}
