#include <stdio.h>
#include <stdlib.h>
#include <gl\glut.h>
#include <gl\GL.h>
#include <gl\GLU.h>
#include <vector>
#include <iostream>
#include <math.h>
#include <windows.h>
#include <string.h>
#include "loadpng.h"
#include "process_image.h"
#include "gl_texture.h"

using namespace std;
// khai báo toàn cục
#include "Rain_Cloud.h"
Image c_Rain :: Img_Save;
c_Rain Rain[2];
Image c_Cloud :: Img_Save;
c_Cloud Cloud[4];
Rect	Rct_ShopScreen = {0, 1280, 720,0}, //Màn hình shop
		//Cửa sổ exit
		Rct_btn_Buy={990,205+990,75+605,605};
		//Rct_Score;

Image Img_ShopScreen;
#define WIDTH 1280
#define HEIGHT 720
#define INTERVAL 10
void init()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, WIDTH, HEIGHT);
	// góc trái trên có tọa độ  là 0,0, góc dưới phải là w,h
	gluOrtho2D(0, WIDTH, HEIGHT,0);
    glMatrixMode(GL_MODELVIEW);
		// vẽ background shop
	Load_Texture_Swap(&Img_ShopScreen, "Images/bg2.png");

	c_Cloud :: Load_Image("Images/Cloud4.png"); // khai báo init 
	Cloud[0].Init(370.0f, 0.0f);
	Cloud[1].Init(930.0f, 200.0f);
	Cloud[2].Init(240.0f, 355.0f);

	c_Rain :: Load_Image("Images/rain.png");
	Rain[0].Init(370.0f, 0.0f);
	Rain[1].Init(530.0f, 0.0f);



	// Bật chế độ vẽ hình ảnh 2D
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_LINE_SMOOTH);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glutIgnoreKeyRepeat(GL_TRUE);
    glEnable(GL_TEXTURE_2D);


}


void display()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glLoadIdentity();

	// vẽ background shop
	Map_Texture(&Img_ShopScreen);
	Draw_Rect(&Rct_ShopScreen);

		// mây // khai báo display va cai nao ve truoc thi o duoi
	Cloud[0].Draw();
	Cloud[1].Draw();
	Cloud[2].Draw();
	//mua
	Rain[0].Draw();
	Rain[1].Draw();


	glutSwapBuffers();
}
// Cho phép gọi đi gọi lại nhiều lần

void Timer(int value)
{

	Rain[0].Update();
	Rain[1].Update();
	for(int i =0; i < 3; i++)
		Cloud[i].Update();
	glutPostRedisplay();
	glutTimerFunc(INTERVAL,Timer, 0);
}
void mouseClick(int button , int state, int x, int y)
{

	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		Rain[0].Key_Down();
		Rain[1].Key_Down();
	}

	glutPostRedisplay();
}
int main(int argc, char** argv)
{
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	// lay kich thuoc man hinh tru cho cua so
	int POS_X = (glutGet(GLUT_SCREEN_WIDTH)- WIDTH) >> 1;
	int POS_Y = (glutGet(GLUT_SCREEN_HEIGHT)- HEIGHT) >> 1;
	// Tao cua so ngay giua man hinh
	glutInitWindowSize(WIDTH, HEIGHT);
	glutInitWindowPosition(POS_X,POS_Y);
	glutCreateWindow("SKY GARDEN");

	
	init();
	glutDisplayFunc(display);
	glutMouseFunc(mouseClick);

	glutTimerFunc(0,Timer,0);


	glutMainLoop();
	return 0;
}
