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
#include "pot.h"
using namespace std;
//Kích thước màn hình
#define WIDTH 1280
#define HEIGHT 720
//Size của 3 chậu
int xPot1 = 56, yPot1 = 60;
int xPot2 = 58, yPot2 = 57;
int xPot3 = 65, yPot3 = 62;
pot pots[12]; // khai báo 12 chậu
// Khai báo tạo độ cho 4 chậu đầu tiên
//Khai báo các biến vẽ màn hình
Rect	rct_bg = {0, 1280, 720, 0}, //Màn hình menu
		rct_bg2 = {0, 1280, 720, 0}, //Màn hình ingame(chính)
		rct_helpScreen = {0, 1280, 720, 0},  //Bg Màn hình help
		rct_shopScreen = {0, 1280, 720, 0},  //Bg Màn hình shop
		rct_bagScreen = {0, 1280, 720, 0},  //Bg Màn hình bag	
		rct_exit_YN = {292, 705 + 292, 430 + 135, 135};
//Button
Rect	rct_btn_newGame={150, 250 + 150, 75 + 475, 475}, //250x75
		rct_btn_continue={150, 250 + 150, 75 + 575, 575},
		rct_btn_help={880, 250 + 880, 75 + 475, 475},
		rct_btn_buy={990, 205 + 990, 75 + 605, 605},
		rct_btn_exit={880, 250 + 880, 75 + 575, 575}, 
		rct_btn_back={20, 50 + 20, 75 + 20, 20},
		 //cloud filter
		filter_lock1 = {270, 810 + 270, 180, 0},         //Mây lock
		filter_lock2 = {270, 810 + 270, 180 + 180, 180}, // Mây lock
		//btn right
		rct_shop={1170, 81 + 1170, 76 + 100, 100},
		rct_bag= {1170, 85 + 1170, 73 + 280, 280}, 
		rct_mission={1170, 76 + 1170, 79 + 190, 190},
		//btn left
		rct_water= {30, 77 + 30, 71 + 100, 100},
		rct_harVest={45, 64 + 45, 67 + 195, 195},    
		rct_shoVel= {45, 62 + 45, 63 + 290, 290};
Rect    //icon
		//icon_avt={400,54+400,35+640,640},
		//icon_star={400,30+400,29+608,608},
		//btn mũi tên (Nơi đặt chậu hoa)
		// Gán vị trí cho 4 mũi tên(Place to plant pots)
	    Rct_btn_Arrow ={400 ,xPot1+400,yPot1 + 450,450},
	    Rct_btn_Arrow1={600 ,xPot1+600,yPot1 + 450,450},
	    Rct_btn_Arrow2={800 ,xPot1+800,yPot1 + 450,450},
	    Rct_btn_Arrow3={1000,xPot1+1000,yPot1 + 450,450},
		//btn mũi tên (Nơi đặt hoa)
		Rct_btn_Fl,
		Rct_btn_Fl1,
		Rct_btn_Fl2,
		Rct_btn_Fl3,
		// chau hoa trong container
		Rct_pot_Type1 = {600,xPot1+600,yPot1 + 612,612}, // chậu bạc
		Rct_pot_Type2 = {700,xPot2+700,yPot2 + 615,615}, // chậu vàng
		Rct_pot_Type3 = {800,xPot3+800,yPot3 + 612,612}; // chậu đỏ
//Khai báo hình ảnh
Image	img_bg, img_bg2, img_helpScreen, img_exit_YN, img_shopScreen,//bg
		//buttton
		img_newGame, img_continue, img_help, img_exit, 
		//btn right
		img_shop, img_mission, img_bag,
		//btn left
		img_harVest, img_shoVel, img_water, 
		//cloud
		img_cloud,
		//Mũi tên 
		img_arrow,
		//btn back
		img_btn_back,
		//Chậu
		img_pot1, img_pot2, img_pot3,
		//Hạt giống
		img_seed1,img_seed2,img_seed3,
		// thanh gỗ chứa chậu và hoa
		img_container,
		//Hoa(các giai đoạn- hạt, mầm, hoa)
		img_seed, img_germ, img_fl1, img_fl2, img_fl3;

//Khai báo biến màn hình
int screen;

//Khai báo hàm
void init();
void display();
void init_inGame();//hàm load img
void init_menu();
void screenNewGame(); // Hàm startGame
void screenContinue(); // Hàm startGame
void screenExit();// Hiển thị màn Exit(Yes/No)
void screenHelp();// Hiển thị màn Help
void screenShop();// Hiển thị màn Shop
void btnBack();   // Tạo btn back ngay góc trái trên
void btn_screenNewGame(); // chứa các button tại màn new game cũng như continue
void clickMenuIntro(int button, int state, int x, int y); // Click các btn ngoài màn newgame
void clickExit(int button, int state, int x, int y);      // Chọn Yes để thoát, No quay về Display
void clickBack(int button, int state, int x, int y); // Dùng để quay lại màn hình display từ các màn khác(Newgame, helpScreen)
void click_btn_right(int button, int state, int x, int y); // Click chuyển sang Shop
void clickList(int button, int state, int x, int y); // Dùng để chuyển sang màn List
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
  Load_Texture_Swap( & img_shopScreen, "Images/bg4-Shop.png");
  Load_Texture_Swap( & img_mission, "Images/Mission.png");
  //Load mây
  Load_Texture_Swap( & img_cloud, "Images/filter-lock.png");
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
  Load_Texture_Swap( & img_mission, "Images/btn-List.png");
  //Load btn left
  Load_Texture_Swap( & img_harVest, "Images/btn-Harvest.png");
  Load_Texture_Swap( & img_shoVel, "Images/btn-Shovel.png");
  Load_Texture_Swap( & img_water, "Images/btn-Water-Bottle.png");
  // Load ô chứa (thanh gỗ dưới cùng) - container
  Load_Texture_Swap(&img_container,"Images/Container.png");
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
  //__Start__
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
  //__End__
  glutSwapBuffers();
}
//Vẽ btn back
void btnBack() {
  Map_Texture( & img_btn_back);
  Draw_Rect( & rct_btn_back);
}
void btn_screenNewGame() {
  //Load btn left
  Map_Texture( & img_harVest);
  Draw_Rect( & rct_harVest);
  Map_Texture( & img_shoVel);
  Draw_Rect( & rct_shoVel);
  Map_Texture( & img_water);
  Draw_Rect( & rct_water);
  //Load btn right
  Map_Texture( & img_shop);
  Draw_Rect( & rct_shop);
  Map_Texture( & img_bag);
  Draw_Rect( & rct_bag);
  Map_Texture( & img_mission);
  Draw_Rect( & rct_mission);
}
//màn hình newgame
void screenNewGame() {
  glutSetWindowTitle("SKY GRADEN");
  glClear(GL_COLOR_BUFFER_BIT);
  glLoadIdentity();
  //__Start__
  screen = 0;  
  //load bg
  Map_Texture( & img_bg2);  
  Draw_Rect( & rct_bg2);	
  // Load mây lock
  Map_Texture( & img_cloud);
  Draw_Rect( & filter_lock1);
  Draw_Rect( & filter_lock2);
  // mũi tên
  Map_Texture(&img_arrow);
  Draw_Rect(&Rct_btn_Arrow);
  Draw_Rect(&Rct_btn_Arrow1);
  Draw_Rect(&Rct_btn_Arrow2);
  Draw_Rect(&Rct_btn_Arrow3);
  //back
  btnBack();
  //load btn
  btn_screenNewGame();
  //back to display
  glutMouseFunc(clickBack);
  //__End__
  glutSwapBuffers();
}
//hàm gọi màn help
void screenHelp(){
  glutSetWindowTitle("HELP");
  glClear(GL_COLOR_BUFFER_BIT);
  glLoadIdentity();
  //__Start__
  Map_Texture( & img_helpScreen);
  Draw_Rect( & rct_helpScreen);
  btnBack();
  glutMouseFunc(clickBack);
  //__End__
  glutSwapBuffers();
}
//Khi click exit
void screenExit() {
  glutSetWindowTitle("EXIT");
  glClear(GL_COLOR_BUFFER_BIT);
  glLoadIdentity();
  //__Start__
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
  //__End__
  glutSwapBuffers();
}
void screenShop(){
  glutSetWindowTitle("SHOP");
  glClear(GL_COLOR_BUFFER_BIT);
  glLoadIdentity();
  //__Start__
  screen = 1;
  Map_Texture( & img_shopScreen);
  Draw_Rect( & rct_shopScreen);
  //back
  glutMouseFunc(clickBack);
  //__End__
  glutSwapBuffers();
}
void clickMenuIntro(int button, int state, int x, int y) {
  //btn chuyển sang màn help
  if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && x >= 880 && x <= 1130 && y >= 475 && y <= 550)
  {
	  cout << "Qua Help thanh cong\n";
	  glutDisplayFunc(screenHelp);
  }
  //btn Exit
  if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && x >= 880 && x <= 1130 && y >= 575 && y <= 650)
    //exit(true);
    glutDisplayFunc(screenExit);
  //btn newGame screenNewGame
  if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && x >= 150 && x <= 400 && y >= 475 && y <= 550)
  {
	  cout <<"Qua NewGame thanh cong\n";
	  glutDisplayFunc(screenNewGame);
  }
	  
  //btn continues
  glutPostRedisplay();
}
void clickExit(int button, int state, int x, int y) {
  //yes
  if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && x >= 495 && x <= 495 + 110 && y >= 380 && y <= 380 + 110) {
    cout << "Thoat thanh cong\n";
    exit(true);
  } else if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && x >= 687 && x <= 687 + 110 && y >= 380 && y <= 380 + 110) {
    cout << "Khong thoat dau nha\n";
    glutDisplayFunc(display);
  }
  glutPostRedisplay();
}
void clickBack(int button, int state, int x, int y) {
  //back về display
  if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && x >= 20 && x <= 70 && y >= 20 && y <= 95 && screen == 0) {
    cout << "Back to display\n";
    glutDisplayFunc(display);
  }
  //back về screen Newgame
  if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && x >= 20 && x <= 70 && y >= 20 && y <= 95 && screen == 1) {
    cout << "Back to NewGame\n";
    glutDisplayFunc(screenNewGame);
  }
  //go to shop
  if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && x >= 1170 && x <= 81 + 1170 && y >= 100 && y <= 76 + 100 && screen == 0) {
    cout << "Qua Shop thanh cong\n";
    glutDisplayFunc(screenShop);
  }

  glutPostRedisplay();
}