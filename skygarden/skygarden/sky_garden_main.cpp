#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <iostream>
#include <math.h>
#include <vector>

#include "../Lib/loadpng.h"
#include "../Lib/process_image.h"
#include "../Lib/gl_texture.h"

using namespace std;

//#define STB_IMAGE_IMPLEMENTATION
#define WIDTH 1280
#define HEIGHT 720
// Dùng để gọi lại
#define INTERVAL 15
// Trái Phải dưới trên
Rect    Rct_Background = {0, 1280, 720,0},
		Rct_Background2 = {0, 1280, 720,0},
		Rct_HelpScreen = {0, 1280, 720,0},
		Rct_Ground = {200 , 300+200, 50+200 ,200},
		bt1 = {200,300+200,50+400,400};


Rect // bt screen 1
	 BT_1={150,250+150,75+475,475}, //250x75
	 BT_2={150,250+150,75+575,575},
	 BT_3={880,250+880,75+475,475},
	 BT_4={880,250+880,75+575,575},
	 // bt back
	 BT_back ={20,50+20,75+20,20},
	 // filter lock
	 filter_lock1={270,810+270,180,0},
	 filter_lock2={270,810+270,180+180,180};

Image Img_Background, Img_Background2, Img_HelpScreen,
	  Img_Ground,
	  Img_filter_lock,
	  Img_Bt1, Img_Bt2, Img_Bt3, Img_Bt4,
	  
	  //bt back
	  Img_Bt_back;


	 

// Mỗi lần thêm hình thì vẽ khung cho nó
void Init_Menu()
{
	Load_Texture_Swap(&Img_Background,"Images/bg1.png");
	Load_Texture_Swap(&Img_Bt1,"Images/bt-NewGame.png");
	Load_Texture_Swap(&Img_Bt2,"Images/bt-Continue.png");
	Load_Texture_Swap(&Img_Bt3,"Images/bt-Help.png");
	Load_Texture_Swap(&Img_Bt4,"Images/bt-Exit.png");
}

//InGame
void Init_InGame(){
	//Load Bt back
	Load_Texture_Swap(&Img_Bt_back,"Images/bt-back.png");
	//load lớp phủ
	Load_Texture_Swap(&Img_filter_lock,"Images/lopphu.png");
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	
	Map_Texture(&Img_Background);
	Draw_Rect(&Rct_Background); 
	// Dùng để load hình
	
	Map_Texture(&Img_Bt1);
	Draw_Rect(&BT_1);
	Map_Texture(&Img_Bt2);
	Draw_Rect(&BT_2);
	Map_Texture(&Img_Bt3);
	Draw_Rect(&BT_3);
	Map_Texture(&Img_Bt4);
	Draw_Rect(&BT_4);

	glutSwapBuffers();
}
//Đổi DisPlayIG thành screenGame
void screenGame()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	//_____________Start_____________
	//Load bg
	Load_Texture_Swap(&Img_Background2,"Images/bg2.png");

	Map_Texture(&Img_Background2);
	Draw_Rect(&Rct_Background2); 
	// load lớp phủ
	Map_Texture(&Img_filter_lock);
	Draw_Rect(&filter_lock1);
	Draw_Rect(&filter_lock2);

	//Load button back
	Map_Texture(&Img_Bt_back);
	Draw_Rect(&BT_back);

	//_____________End_____________
	glutSwapBuffers();
}
void screenHelp()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	//_____________Start_____________
	Map_Texture(&Img_Background2);
	Draw_Rect(&Rct_Background2); 
	Load_Texture_Swap(&Img_HelpScreen,"Images/bg3-help.png");

	Map_Texture(&Img_HelpScreen);
	Draw_Rect(&Rct_HelpScreen);
	//Load button back
	Map_Texture(&Img_Bt_back);
	Draw_Rect(&BT_back);
	//_____________End_____________
	glutSwapBuffers();

}

void init()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, WIDTH, HEIGHT);
	// góc trái trên có tọa độ  là 0,0, góc dưới phải là w,h
	gluOrtho2D(0, WIDTH, HEIGHT,0);
    glMatrixMode(GL_MODELVIEW);

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

	Init_Menu();
	Init_InGame();
}
void mouseClick(int button , int state, int x, int y)
{

	//NEW GAME
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && x >=150 && x <= 400  && y >= 475 && y <=  550)
		glutDisplayFunc(screenGame);

	// Continue
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && x >= 150 && x <= 400 && y >= 575 && y <= 650)
	{
		// hàm continue
	}
	//Help
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && x >= 880 && x <= 1130 &&  y >= 475 && y <= 550)
	{
		glutDisplayFunc(screenHelp);
	}
	// exit
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && x >= 880 && x <= 1130 && y >= 575 && y <= 650)
	{
		exit(true);
	}
	//bt back
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && x >= 20 && x <= 70 && y >= 95 && y <= 20)
	{
		glutDisplayFunc(display);
	}
	//chuột phải
	if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN){
		glutDisplayFunc(display);
	}
	glutPostRedisplay();

	//_____________End_____________
	glutPostRedisplay();
}
// Cho phép gọi đi gọi lại nhiều lần
void Timer(int value)
{
	glutPostRedisplay();
	glutTimerFunc(INTERVAL,Timer, 0);
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