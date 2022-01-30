#include <stdio.h>
#include <stdlib.h>
#include <glut.h>
#include <gl\GL.h>
#include <gl\GLU.h>
#include <vector>
#include <iostream>
#include <math.h>
#include <windows.h>
#include <string.h>
#include <loadpng.h>
#include <process_image.h>
#include <gl_texture.h>

using namespace std;
//Kích thước màn hình
#define WIDTH 1280
#define HEIGHT 720

//Khai báo các biến vẽ màn hình
Rect	rct_bg = {0, 1280, 720, 0}, //Màn hình menu
		rct_bg2 = {0, 1280, 720, 0}, //Màn hình ingame(chính)
		rct_helpScreen = {0, 1280, 720, 0},  //Bg Màn hình help
		rct_shopScreen = {0, 1280, 720, 0},  //Bg Màn hình shop
		rct_exit_YN = {292, 705 + 292, 430 + 135, 135};
//Button
Rect	rct_btn_newGame={150, 250 + 150, 75 + 475, 475}, //250x75
		rct_btn_continue={150, 250 + 150, 75 + 575, 575},
		rct_btn_help={880, 250 + 880, 75 + 475, 475},
		rct_btn_buy={990, 205 + 990, 75 + 605, 605},
		rct_btn_exit={880, 250 + 880, 75 + 575, 575}, 
		rct_btn_back={20, 50 + 20, 75 + 20, 20};
		//btn right
		
		//btn left
//Khai báo hình ảnh
Image	img_bg, img_bg2, img_helpScreen, img_exit_YN, img_shopScreen,//bg
		//buttton
		img_newGame, img_continue, img_help, img_exit, 
		//btn right
		img_shop, img_list, img_bag,
		//btn left
		img_harVest, img_shoVel, img_water, 
		//Mũi tên , btn back
		img_arrow, img_btn_back,
		//Chậu
		img_pot1, img_pot2, img_pot3,
		//Hạt giống
		img_seed1,img_seed2,img_seed3,
		//Hoa(các giai đoạn- hạt, mầm, hoa)
		img_seed, img_germ, img_fl1, img_fl2, img_fl3;
//Khai báo hàm
void init();
void display();
void init_inGame();//Btn khởi động game
void init_menu();
void screenExit();// Hiển thị màn Exit(Yes/No)
void screenHelp();// Hiển thị màn Help
void btnBack();   // Tạo btn back ngay góc trái trên
void clickMenuIntro(int button, int state, int x, int y); // Click các btn ngoài màn newgame
void clickExit(int button, int state, int x, int y);      // Chọn Yes để thoát, No quay về Display
void clickBack_display(int button, int state, int x, int y); // Dùng để quay lại màn hình display từ các màn khác(Newgame, helpScreen)

// Mã nguồn code chính
int main(int argc, char ** argv) {
  glutInit( & argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  // lay kich thuoc man hinh tru cho cua so
  int POS_X = (glutGet(GLUT_SCREEN_WIDTH) - WIDTH) >> 1;
  int POS_Y = (glutGet(GLUT_SCREEN_HEIGHT) - HEIGHT) >> 1;
  // Tao cua so ngay giua man hinh
  glutInitWindowSize(WIDTH, HEIGHT);
  glutInitWindowPosition(POS_X, POS_Y);
  glutCreateWindow("SKY GARDEN");
  //gọi icon
  //glutSetIconTitle("ic_skygarden.ico");
  init();
  glutMouseFunc(clickMenuIntro);
  glutDisplayFunc(display);
  //glutTimerFunc(0, Timer, 0);
  glutMainLoop();
  return 0;
}
void init() {
  glClearColor(0.0, 0.0, 0.0, 1.0);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glViewport(0, 0, WIDTH, HEIGHT);
  // góc trái trên có tọa độ  là 0,0, góc dưới phải là w,h
  gluOrtho2D(0, WIDTH, HEIGHT, 0);
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

  init_menu();
  init_inGame();
}
void init_inGame() {
  //Load bg
  Load_Texture_Swap( & img_bg, "Images/bg1.png");
  Load_Texture_Swap( & img_bg2, "Images/bg2.png");
  Load_Texture_Swap( & img_helpScreen, "Images/bg3-help.png");
  Load_Texture_Swap( & img_exit_YN, "Images/Exit_YN.png");
  //Load Mũi tên
  Load_Texture_Swap( & img_arrow, "Images/Arrow.png");
  Load_Texture_Swap( & img_btn_back, "Images/btn-Back.png");
  //Load Chậu
  Load_Texture_Swap( & img_pot1, "Images/Pot1.png");
  Load_Texture_Swap( & img_pot2, "Images/Pot2.png");
  Load_Texture_Swap( & img_pot3, "Images/Pot3.png");
  //Load hạt giống(Để lựa chọn hạt giống)
  Load_Texture_Swap( & img_seed1, "Images/Seed1.png");
  Load_Texture_Swap( & img_seed2, "Images/Seed2.png");
  Load_Texture_Swap( & img_seed3, "Images/Seed3.png");
  //Load hoa các giai đoạn(hạt, mầm, hoa-3 loại)
  Load_Texture_Swap( & img_seed, "Images/Seed.png");
  Load_Texture_Swap( & img_germ, "Images/Germ.png");
  Load_Texture_Swap( & img_fl1, "Images/fl1.png");
  Load_Texture_Swap( & img_fl2, "Images/fl2.png");
  Load_Texture_Swap( & img_fl3, "Images/fl3.png");
  //Load btn right
  Load_Texture_Swap( & img_bag, "Images/btn-Bag.png");
  Load_Texture_Swap( & img_shop, "Images/btn-Shop.png");
  Load_Texture_Swap( & img_list, "Images/btn-List.png");
  //Load btn left
  Load_Texture_Swap( & img_harVest, "Images/btn-Harvest.png");
  Load_Texture_Swap( & img_shoVel, "Images/btn-Shovel.png");
  Load_Texture_Swap( & img_water, "Images/btn-Water-Bottle.png");

}
//hàm khởi động game
void init_menu() {
  Load_Texture_Swap( & img_continue, "Images/bt-Continue.png");
  Load_Texture_Swap( & img_exit, "Images/bt-Exit.png");
  Load_Texture_Swap( & img_newGame, "Images/bt-NewGame.png");
  Load_Texture_Swap( & img_help, "Images/bt-Help.png");
}
void display() {
  glutSetWindowTitle("SKY GARDEN");
  glClear(GL_COLOR_BUFFER_BIT);
  glLoadIdentity();
  //_____________Start___________
  Map_Texture( & img_bg);
  Draw_Rect( & rct_bg);
  Map_Texture( & img_newGame);
  Draw_Rect( & rct_btn_newGame);
  Map_Texture( & img_continue);
  Draw_Rect( & rct_btn_continue);
  Map_Texture( & img_help);
  Draw_Rect( & rct_btn_help);
  Map_Texture( & img_exit);
  Draw_Rect( & rct_btn_exit);
  //Click gọi lại hàm exit
  glutMouseFunc(clickMenuIntro);
  //_____________End_____________
  glutSwapBuffers();
}
//Vẽ btn back
void btnBack() {
  Map_Texture( & img_btn_back);
  Draw_Rect( & rct_btn_back);
}
//hàm gọi màn help
void screenHelp(){
  glutSetWindowTitle("HELP");
  glClear(GL_COLOR_BUFFER_BIT);
  glLoadIdentity();
  //_____________Start___________
  Map_Texture( & img_helpScreen);
  Draw_Rect( & rct_helpScreen);
  btnBack();
  glutMouseFunc(clickBack_display);
  //_____________End_____________
  glutSwapBuffers();
}
//Khi click exit
void screenExit() {
  glutSetWindowTitle("Exit");
  glClear(GL_COLOR_BUFFER_BIT);
  glLoadIdentity();
  //_____________Start___________
  Map_Texture( & img_bg);
  Draw_Rect( & rct_bg);
  Map_Texture( & img_newGame);
  Draw_Rect( & rct_btn_newGame);
  Map_Texture( & img_continue);
  Draw_Rect( & rct_btn_continue);
  Map_Texture( & img_help);
  Draw_Rect( & rct_btn_help);
  Map_Texture( & img_exit);
  Draw_Rect( & rct_btn_exit);
   //Exit
  Map_Texture( & img_exit_YN);
  Draw_Rect( & rct_exit_YN);
  //Click gọi hàm xác nhận thoát yes/no
  glutMouseFunc(clickExit);
  //_____________End_____________
  glutSwapBuffers();
}
void clickMenuIntro(int button, int state, int x, int y) {
	//btn chuyển sang màn help
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && x >= 880 && x <= 1130 && y >= 475 && y <= 550)
		glutDisplayFunc(screenHelp);

	//btn Exit
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && x >= 880 && x <= 1130 && y >= 575 && y <= 650)
		//exit(true);
		glutDisplayFunc(screenExit);
	glutPostRedisplay();
}
void clickExit(int button, int state, int x, int y) {
  //yes
  if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && x >= 495 && x <= 495 + 110 && y >= 380 && y <= 380 + 110)
    exit(true);
  else if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && x >= 687 && x <= 687 + 110 && y >= 380 && y <= 380 + 110)
    glutDisplayFunc(display);
  glutPostRedisplay();
}
void clickBack_display(int button, int state, int x, int y){
	//back từ màn screen help
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && x >= 20 && x <= 70 && y >= 20 && y <= 95)
		glutDisplayFunc(display);
	glutPostRedisplay();
}