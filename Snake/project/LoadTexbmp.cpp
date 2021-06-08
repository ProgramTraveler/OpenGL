#include"LoadTexbmp.h"

/*
 *  从BMP文件中加载纹理
 */

int LoadTexBMP(const char* file) {
	unsigned int   texture; //纹理名称  
	FILE* f; //文件指针          
	short magic; //Image magic
	int   dx, dy, size; //图片尺寸
	short nbp, bpp;   
	char* image;      
	int   off; //图像偏移
	int   k;   // Counter
	int   max; //最大纹理尺寸    

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

	//生成二维纹理
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	//复制图片
	glTexImage2D(GL_TEXTURE_2D, 0, 3, dx, dy, 0, GL_RGB, GL_UNSIGNED_BYTE, image);

	//当图像大小不匹配时线性缩放
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	free(image);
	//返回纹理名称
	return texture;
}
