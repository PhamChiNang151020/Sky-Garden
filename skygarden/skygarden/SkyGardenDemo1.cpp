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
int shown = 4; // Số chậu được phép show
//Size của 3 chậu
int xPot1 = 56, yPot1 = 60;
int xPot2 = 58, yPot2 = 57;
int xPot3 = 65, yPot3 = 62;
pot pots[12]; // khai báo 12 chậu
// Khai báo struct chứa vị trí thứ tự của 4 đối tượng
struct location{int x,y,z,c;};
// vị trí của chậu 1 ở 4 arrow // Trái Phải dưới trên 
location locationPot[4] = {locationPot[0].x = 400                   , locationPot[0].y = xPot1+400, locationPot[0].z = yPot1 + 450,locationPot[0].c = 450,
						   locationPot[1].x = locationPot[0].x + 200, locationPot[1].y = xPot1+600, locationPot[1].z = yPot1 + 450,locationPot[1].c = 450,
						   locationPot[2].x = locationPot[0].x + 400, locationPot[2].y = xPot1+800, locationPot[2].z = yPot1 + 450,locationPot[2].c = 450, 
						   locationPot[3].x = locationPot[0].x + 600, locationPot[3].y = xPot1+1000, locationPot[3].z = yPot1 + 450,locationPot[3].c = 450,};
location locationfl[4] = {
				locationfl[0].x = 400				   , locationfl[0].y = xPot1+400,  locationfl[0].z =  450 + 15,locationfl[0].c = 450 - yPot1 + 15, 
				locationfl[1].x = locationfl[0].x + 200, locationfl[1].y = xPot1+600,  locationfl[1].z =  450 + 15,locationfl[1].c = 450 - yPot1 + 15, 
				locationfl[2].x = locationfl[0].x + 400, locationfl[2].y = xPot1+800,  locationfl[2].z =  450 + 15,locationfl[2].c = 450 - yPot1 + 15, 
				locationfl[3].x = locationfl[0].x + 600, locationfl[3].y = xPot1+1000, locationfl[3].z =  450 + 15,locationfl[3].c = 450 - yPot1 + 15, 
			};
//location locationPick[3] = {locationPick[0].x = 600, locationPick[0].y = xPot1+600, locationPick[0].z = yPot1 + 612, locationPick[0].c = 612,
//							locationPick[0].x = 700, locationPick[0].y = xPot1+700, locationPick[0].z = yPot1 + 615, locationPick[0].c = 615,
//							locationPick[0].x = 700, locationPick[0].y = xPot1+800, locationPick[0].z = yPot1 + 612, locationPick[0].c = 612,
//			};
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
		rct_missionScreen={1170, 76 + 1170, 79 + 190, 190},
		//btn left
		rct_water= {30, 77 + 30, 71 + 100, 100},
		rct_harVest={45, 64 + 45, 67 + 195, 195},    
		rct_shoVel= {45, 62 + 45, 63 + 290, 290};
Rect    //icon
		//icon_avt={400,54+400,35+640,640},
		//icon_star={400,30+400,29+608,608},
		//btn mũi tên (Nơi đặt chậu hoa)
		// Gán vị trí cho 4 mũi tên(Place to plant pots)
	    Rct_btn_Arrow0 ={400 ,xPot1+400,yPot1 + 450,450},
	    Rct_btn_Arrow1={600 ,xPot1+600,yPot1 + 450,450},
	    Rct_btn_Arrow2={800 ,xPot1+800,yPot1 + 450,450},
	    Rct_btn_Arrow3={1000,xPot1+1000,yPot1 + 450,450},
		//btn mũi tên (Nơi đặt hoa)
		Rct_btn_Fl,
		Rct_btn_Fl1,
		Rct_btn_Fl2,
		Rct_btn_Fl3,
		// container(thanh gỗ) chứa các chậu và hoa
		rct_container={360,675+360,85+600,600},
		// chau hoa trong container
		Rct_pot_Type1 = {600,xPot1+600,yPot1 + 612,612}, // chậu bạc
		Rct_pot_Type2 = {700,xPot2+700,yPot2 + 615,615}, // chậu vàng
		Rct_pot_Type3 = {800,xPot3+800,yPot3 + 612,612}; // chậu đỏ
//Khai báo hình ảnh
Image	img_bg, img_bg2, img_helpScreen, img_exit_YN, img_shopScreen, img_bagScreen, img_missionScreen,//bg
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
		//container(thanh gỗ) chứa chậu và hoa
		img_container,
		//Chậu
		img_pot1, img_pot2, img_pot3,
		//Hạt giống
		img_seed1,img_seed2,img_seed3,
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
void screenMission(); //
void screenBag(); //
void btnBack();   // Tạo btn back ngay góc trái trên
void btn_screenNewGame(); // chứa các button tại màn new game cũng như continue
void loadFilter();// 2 tang may
void loadContainer(); // thanh go chua chau va hoa
void clickMenuIntro(int button, int state, int x, int y); // Click các btn ngoài màn newgame
void clickExit(int button, int state, int x, int y);      // Chọn Yes để thoát, No quay về Display
void clickBack(int button, int state, int x, int y); // Dùng để quay lại màn hình display từ các màn khác(Newgame, helpScreen)
void click_btn_right(int button, int state, int x, int y); // Click chuyển sang Shop
void clickList(int button, int state, int x, int y); // Dùng để chuyển sang màn List
//
void showElements(); // Hien thi
//void pickPot(int button , int state, int x, int y); // Đặt chậu
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
  Load_Texture_Swap( & img_bagScreen, "Images/screenBag.png");
  Load_Texture_Swap( & img_missionScreen, "Images/Mission.png");
  //Load mây
  Load_Texture_Swap( & img_cloud, "Images/filter-lock.png");
  //Load Mũi tên
  Load_Texture_Swap( & img_arrow, "Images/Arrow.png");
  Load_Texture_Swap( & img_btn_back, "Images/btn-Back.png");
  //Load container
  Load_Texture_Swap( & img_container, "Images/Container.png");
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
  for(int i = 0; i < shown; i++)
  {
	  //khoi tao gia tri ban dau cho class
  pots[i].potType = -1;
  pots[i].location = i;
  pots[i].clickChoosePot = 0;
  }
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
  Draw_Rect( & rct_missionScreen);
}
void loadFilter(){
  Map_Texture( & img_cloud);
  Draw_Rect( & filter_lock1);
  Draw_Rect( & filter_lock2);
}
void loadContainer(){
  Map_Texture( & img_container);
  Draw_Rect( & rct_container);
}
void showElements()
{
	/*Map_Texture(&img_arrow);
	Draw_Rect(&Rct_btn_Arrow0);
	Draw_Rect(&Rct_btn_Arrow1);
	Draw_Rect(&Rct_btn_Arrow2);
	Draw_Rect(&Rct_btn_Arrow3);*/

	for(int i = 0;i < shown;i++){
		if(pots[i].clickChoosePot == 1)
		{
		//Load loại chậu
		Map_Texture(&img_pot1);
		Draw_Rect(&Rct_pot_Type1);
		Map_Texture(&img_pot2);
		Draw_Rect(&Rct_pot_Type2);
		Map_Texture(&img_pot3);
		Draw_Rect(&Rct_pot_Type3);
		}
		if(pots[i].potType == 0) //loại chậu
		{
			Map_Texture(&img_pot1);
			if(pots[i].location == 0 )
				Draw_Rect(&Rct_btn_Arrow0);
			else if (pots[i].location == 1 )
				Draw_Rect(&Rct_btn_Arrow1);
			else if (pots[i].location == 2 )
				Draw_Rect(&Rct_btn_Arrow2);
			else if (pots[i].location == 3 )
				Draw_Rect(&Rct_btn_Arrow3);
		}
		else if (pots[i].potType == 1)
		{
			Map_Texture(&img_pot2);
			if(pots[i].location == 0 )
				Draw_Rect(&Rct_btn_Arrow0);
			else if (pots[i].location == 1 )
				Draw_Rect(&Rct_btn_Arrow1);
			else if (pots[i].location == 2 )
				Draw_Rect(&Rct_btn_Arrow2);
			else if (pots[i].location == 3 )
				Draw_Rect(&Rct_btn_Arrow3);
		}
		else if (pots[i].potType == 2)
		{
			Map_Texture(&img_pot3);
			if(pots[i].location == 0 )
				Draw_Rect(&Rct_btn_Arrow0);
			else if (pots[i].location == 1 )
				Draw_Rect(&Rct_btn_Arrow1);
			else if (pots[i].location == 2 )
				Draw_Rect(&Rct_btn_Arrow2);
			else if (pots[i].location == 3 )
				Draw_Rect(&Rct_btn_Arrow3);
		}
		else if( pots[i].potType == -1)
		{
			// mũi tên
			Map_Texture(&img_arrow);
			if(pots[i].location == 0 )
				Draw_Rect(&Rct_btn_Arrow0);
			else if (pots[i].location == 1 )
				Draw_Rect(&Rct_btn_Arrow1);
			else if (pots[i].location == 2 )
				Draw_Rect(&Rct_btn_Arrow2);
			else if (pots[i].location == 3 )
				Draw_Rect(&Rct_btn_Arrow3);
		}
	}
}
//void pickPot(int button , int state, int x, int y){
//	//Vòng lặp để lưu thứ tự chậu được click // trai phai duoi tren
//	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && x >= locationPot[0].x && x <= locationPot[0].y && y >= locationPot[0].c && y <= locationPot[0].z 
//			&& screen == 0 && pots[0].clickChoosePot == 0)
//		{
//		//load chau trong table
//		cout << "click dat chau\n";
//		cout << "vi tri " << 0 << endl;
//		pots[0].clickChoosePot = 1;
//		glutDisplayFunc(screenNewGame);
//		glutPostRedisplay();
//		}
//		if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && x >= locationPot[1].x && x <= locationPot[1].y && y >= locationPot[1].c && y <= locationPot[1].z 
//			&& screen == 0 && pots[1].clickChoosePot == 0)
//		{
//		//load chau trong table
//		cout << "click dat chau\n";
//		cout << "vi tri " << 1 << endl;
//		pots[1].clickChoosePot = 1;
//		glutDisplayFunc(screenNewGame);
//		glutPostRedisplay();
//		}
//		if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && x >= locationPot[2].x && x <= locationPot[2].y && y >= locationPot[2].c && y <= locationPot[2].z 
//			&& screen == 0 && pots[2].clickChoosePot == 0)
//		{
//		//load chau trong table
//		cout << "click dat chau\n";
//		cout << "vi tri " << 2 << endl;
//		pots[2].clickChoosePot = 1;
//		glutDisplayFunc(screenNewGame);
//		glutPostRedisplay();
//		}
//		if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && x >= locationPot[3].x && x <= locationPot[3].y && y >= locationPot[3].c && y <= locationPot[3].z 
//			&& screen == 0 && pots[3].clickChoosePot == 0)
//		{
//		//load chau trong table
//		cout << "click dat chau\n";
//		cout << "vi tri " << 3 << endl;
//		pots[3].clickChoosePot = 1;
//		glutDisplayFunc(screenNewGame);
//		glutPostRedisplay();
//		}
//	for(int i = 0;i < shown;i++)
//	{
//		//if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && x >= locationPot[i].x && x <= locationPot[i].y && y >= locationPot[i].c && y <= locationPot[i].z 
//		//	&& screen == 0)
//		//{
//		////load chau trong table
//		//cout << "click dat chau\n";
//		//cout << "vi tri " << i << endl;
//		//pots[i].clickChoosePot = 1;
//		//pots[i].local = i;
//		//glutDisplayFunc(screenNewGame);
//		//glutPostRedisplay();
//		//}
//		
//		//Rct_pot_Type1 = {600,xPot1+600,yPot1 + 612,612}, // chậu bạc
//		if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && x >= 600 && x <= 660 && y >= 606 && y <= 676 
//			&& screen == 0 && pots[i].clickChoosePot == 1 )
//		{
//			pots[i].potType = 0;//Xac nhan loai chau
//			pots[i].clickChoosePot = 2;//Tao dien de dừng 
//			glutDisplayFunc(screenNewGame);
//			glutPostRedisplay();
//		}
//	//Rct_pot_Type2 = {700,xPot2+700,yPot2 + 615,615}, // chậu vàng int xPot2 = 58, yPot2 = 57;
//		if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && x >= 700 && x <= 758 && y >= 615  && y <= 672 
//			&& screen == 0 && pots[i].clickChoosePot == 1)
//		{
//			pots[i].potType = 1;//Xac nhan loai chau 
//			pots[i].clickChoosePot = 2;//Tao dien de dừng 
//			glutDisplayFunc(screenNewGame);
//			glutPostRedisplay();
//		}
//	//Rct_pot_Type3 = {800,xPot3+800,yPot3 + 612,612}, // chậu đỏ int xPot3 = 65, yPot3 = 62;
//		if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && x >= 800 && x <= 865 && y >= 612 && y <=  674  
//			&& screen == 0 && pots[i].clickChoosePot == 1)
//		{
//			pots[i].potType = 2;//Xac nhan loai chau 
//			pots[i].clickChoosePot = 2;//Tao dien de dừng 
//			glutDisplayFunc(screenNewGame);
//			glutPostRedisplay();
//		}
//	}
//}
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
  //load container
  loadContainer();
  // Load mây lock
  loadFilter();
  //back
  btnBack();
  //load btn
  btn_screenNewGame();
  //back to display
  glutMouseFunc(clickBack);
  //Hien thi phan tu
  showElements();
  //Đặt chậu
  //glutMouseFunc(pickPot);
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
void screenMission(){
  glutSetWindowTitle("Mission");
  glClear(GL_COLOR_BUFFER_BIT);
  glLoadIdentity();
  //__Start__
  screen = 2;
  //load bg
  Map_Texture( & img_bg2);
  Draw_Rect( & rct_bg2);
  //Load Filter
  loadFilter();
  //load btn
  btn_screenNewGame();
  Map_Texture( & img_missionScreen);
  Draw_Rect( & rct_missionScreen);
  //back
  glutMouseFunc(clickBack);
  //__End__
  glutSwapBuffers();
}
void screenBag() {
  glutSetWindowTitle("BAG");
  glClear(GL_COLOR_BUFFER_BIT);
  glLoadIdentity();
  //__Start__
  screen = 3;
  Map_Texture( & img_bagScreen);
  Draw_Rect( & rct_bagScreen);
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
  if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && x >= 20 && x <= 70 && y >= 20 && y <= 95 && (screen == 1 || screen == 3)) {
    cout << "Back to NewGame\n";
    glutDisplayFunc(screenNewGame);
  }
  if (screen == 0) {
    //back về display
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && x >= 20 && x <= 70 && y >= 20 && y <= 95) {
      cout << "Back to display\n";
      glutDisplayFunc(display);
    }
    //go to shop
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && x >= 1170 && x <= 81 + 1170 && y >= 100 && y <= 76 + 100) {
      cout << "Qua Shop thanh cong\n";
      glutDisplayFunc(screenShop);
    }
    //go to mission
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && x >= 1170 && x <= 76 + 1170 && y >= 190 && y <= 79 + 190) {
      cout << "show màn mission\n";
      glutDisplayFunc(screenMission);
    }
    //go to bag
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && x >= 1170 && x <= 85 + 1170 && y >= 280 && y <= 73 + 280) {
      cout << "Qua Bag thanh cong\n";
      glutDisplayFunc(screenBag);
    }
  }
  if (screen == 2) {
    // Đóng Mission
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && x >= 850 && x <= 895 && y >= 85 && y <= 138) {
      cout << "close mission\n";
      glutDisplayFunc(screenNewGame);
    }
  }
  //Code xử lý đặt chậu -- TÙNG
  //Vòng lặp để lưu thứ tự chậu được click // trai phai duoi tren
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && x >= locationPot[0].x && x <= locationPot[0].y && y >= locationPot[0].c && y <= locationPot[0].z 
			&& screen == 0 && pots[0].clickChoosePot == 0)
		{
		//load chau trong table
		cout << "click dat chau\n";
		cout << "vi tri " << 0 << endl;
		pots[0].clickChoosePot = 1;
		glutDisplayFunc(screenNewGame);
		glutPostRedisplay();
		}
		if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && x >= locationPot[1].x && x <= locationPot[1].y && y >= locationPot[1].c && y <= locationPot[1].z 
			&& screen == 0 && pots[1].clickChoosePot == 0)
		{
		//load chau trong table
		cout << "click dat chau\n";
		cout << "vi tri " << 1 << endl;
		pots[1].clickChoosePot = 1;
		glutDisplayFunc(screenNewGame);
		glutPostRedisplay();
		}
		if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && x >= locationPot[2].x && x <= locationPot[2].y && y >= locationPot[2].c && y <= locationPot[2].z 
			&& screen == 0 && pots[2].clickChoosePot == 0)
		{
		//load chau trong table
		cout << "click dat chau\n";
		cout << "vi tri " << 2 << endl;
		pots[2].clickChoosePot = 1;
		glutDisplayFunc(screenNewGame);
		glutPostRedisplay();
		}
		if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && x >= locationPot[3].x && x <= locationPot[3].y && y >= locationPot[3].c && y <= locationPot[3].z 
			&& screen == 0 && pots[3].clickChoosePot == 0)
		{
		//load chau trong table
		cout << "click dat chau\n";
		cout << "vi tri " << 3 << endl;
		pots[3].clickChoosePot = 1;
		glutDisplayFunc(screenNewGame);
		glutPostRedisplay();
		}
	for(int i = 0;i < shown;i++)
	{
		//Rct_pot_Type1 = {600,xPot1+600,yPot1 + 612,612}, // chậu bạc
		if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && x >= 600 && x <= 660 && y >= 606 && y <= 676 
			&& screen == 0 && pots[i].clickChoosePot == 1 )
		{
			pots[i].potType = 0;//Xac nhan loai chau
			pots[i].clickChoosePot = 2;//Tao dien de dừng 
			glutDisplayFunc(screenNewGame);
			glutPostRedisplay();
		}
	//Rct_pot_Type2 = {700,xPot2+700,yPot2 + 615,615}, // chậu vàng int xPot2 = 58, yPot2 = 57;
		if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && x >= 700 && x <= 758 && y >= 615  && y <= 672 
			&& screen == 0 && pots[i].clickChoosePot == 1)
		{
			pots[i].potType = 1;//Xac nhan loai chau 
			pots[i].clickChoosePot = 2;//Tao dien de dừng 
			glutDisplayFunc(screenNewGame);
			glutPostRedisplay();
		}
	//Rct_pot_Type3 = {800,xPot3+800,yPot3 + 612,612}, // chậu đỏ int xPot3 = 65, yPot3 = 62;
		if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && x >= 800 && x <= 865 && y >= 612 && y <=  674  
			&& screen == 0 && pots[i].clickChoosePot == 1)
		{
			pots[i].potType = 2;//Xac nhan loai chau 
			pots[i].clickChoosePot = 2;//Tao dien de dừng 
			glutDisplayFunc(screenNewGame);
			glutPostRedisplay();
		}
	}
  glutPostRedisplay();
}
