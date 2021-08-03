#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <iostream>
#include <math.h>
#include <vector>
#include <loadpng.h>
#include <process_image.h>
#include <gl\gl_texture.h>

using namespace std;

#define WIDTH  1280
#define HEIGHT  720
#define INTERVAL 15

Rect Rct_Background = {0, 1280,0, 720};
Image Img_Background;

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);// Xóa những thứ trước đó và vẽ lại
	glLoadIdentity();// load hệ tọa độ


	Map_Texture(&Img_Background);
	Draw_Rect(&Rct_Background);

	glutSwapBuffers(); // Dùng cho GL_DOUBLE 
} 
void init_Game(){
	//Load Hình
	Load_Texture_Swap(&Img_Background,"Images/bg-1280x720.png");
}
void init()
{
	// Thiết lập màu nền : Trắng
	glClearColor(0.0, 0.0, 0.0, 0.0);	

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0,0,WIDTH,HEIGHT);
	gluOrtho2D(0, WIDTH, 0, HEIGHT);
	glMatrixMode(GL_MODELVIEW);
	
	//Bật chế độ vẽ ảnh 2D
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_LINE_SMOOTH);
	glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glEnable(GL_TEXTURE_2D);
	init_Game();
}

void Timer(int value){
	//Post lại display
	glutPostRedisplay();
	glutTimerFunc(INTERVAL,Timer,0);
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
	glutCreateWindow("My window");
	init();
	init_Game();
	glutDisplayFunc(display);

	glutTimerFunc(0,Timer,0);
	glutMainLoop();
	return 0;
}