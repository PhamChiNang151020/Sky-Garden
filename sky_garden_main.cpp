#include <stdio.h>
#include <stdlib.h>
#include <gl\glut.h>
#include <gl\GL.h>
#include <gl\GLU.h>
#include <vector>
#include <iostream>
#include <math.h>
#include <windows.h>
#include <fstream>
#include <string.h>
#include "loadimg\loadpng.h"
#include "loadimg\process_image.h"
#include "loadimg\gl_texture.h"
#include <windows.h>
#include "pot.h"
#include "flower.h"
#include "loadimage.h"
#include <ctime>

using namespace std;
//Kích thước màn hình
#define WIDTH 1280
#define HEIGHT 720
// timer
int thoigianhethong = time(0);
//Size của 3 chậu
int xPot1 = 56, yPot1 = 60;
int xPot2 = 58, yPot2 = 57;
int xPot3 = 65, yPot3 = 62;	
// Khai báo tạo độ cho 4 chậu đầu tiên
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
		rct_container={360,675+360,85+600,600},//// container(thanh gỗ) chứa các chậu và hoa
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
///// ==================== Khái báo các biến cho shop hoa
#include "store.h"
//void printtext(int x, int y, string String);
// ô xem trước mặc định
c_Store_Pot Pot_Defaul;
// chậu trên kệ
c_Store_Pot Pot_Store[3];
// chậu ẩn
c_Store_Pot Pot_Store_Ghost[3];
// hoa trên kệ
c_Store_Seed Seed_Store[3];
// hoa ẩn
c_Store_Seed Seed_Store_Ghost[3];

// Tiền lúc vào game
int money = 5000;

// màn hình shop
  
Rect  Rct_btn_Buy={990,205+990,75+605,605}; // Nút buy
		//Rct_Score;
Image Img_Buy;
Image Num :: Img_Num[10]; // khai bao sử dụng ảnh số vi static
Num numSLVPham; // 6 vật vật phẩm
Num numMoney; // khai bao đối tượng sử dụng số
int Class_Pot_Seed = 1; // sử dụng  bấm vào chậu nào, 1 - 3 là chậu, 3 - 6 là hoa

void numSL();
void buyPot();
//===================== Kết thúc Khai báo cho shop
//
//===================== Khai báo chức năng tưới cây và hiệu ứng mây
#include "Rain_Cloud.h"
Image c_Rain :: Img_Save;
c_Rain Rain[2];
Image c_Cloud :: Img_Save;
c_Cloud Cloud[4];
#define INTERVAL 10 // load lại số lần timer

// ==================== kết thúc chức nawg tưới cây và hiệu ứng mây
//============ các vị trí chậu
c_pot pot[12]; // vị trí 12 chậu cho 3 tầng

//Size của 3 chậu
//int xPot1 = 56;int yPot1 = 60;
//int xPot2 = 58;int yPot2 = 57;
//int xPot3 = 65;int yPot3 = 62;
// Khai báo struct chứa vị trí thứ tự của 4 đối tượng
struct location{int x,y,z,c;};
// vị trí của chậu// Trái Phải dưới trên 
location locationPot[12] = {locationPot[0].x = 390                    , locationPot[0].y = 60+locationPot[0].x, locationPot[0].z = 70 + 450,locationPot[0].c = 440,
						   locationPot[1].x = locationPot[0].x + 200 - 60/2, locationPot[1].y = 60+locationPot[1].x , locationPot[1].z = 70 + 450,locationPot[1].c = 440,
						   locationPot[2].x = locationPot[0].x + 400 - 60/2 , locationPot[2].y = 60+ locationPot[2].x, locationPot[2].z = 70 + 450,locationPot[2].c = 440, 
						   locationPot[3].x = locationPot[0].x + 600 - 60/2, locationPot[3].y = 60+locationPot[3].x, locationPot[3].z = 70 + 450,locationPot[3].c = 440,

						   locationPot[4].x = 390                    , locationPot[4].y = 60+locationPot[4].x, locationPot[4].z = 70 + 250, locationPot[4].c = 250,
						   locationPot[5].x = locationPot[0].x + 200 - 60/2, locationPot[5].y = 60+locationPot[5].x , locationPot[5].z = 70 + 250, locationPot[5].c = 250,
						   locationPot[6].x = locationPot[0].x + 400 - 60/2 , locationPot[6].y = 60+ locationPot[6].x, locationPot[6].z = 70 + 250, locationPot[6].c = 250, 
						   locationPot[7].x = locationPot[0].x + 600 - 60/2, locationPot[7].y = 60+locationPot[7].x, locationPot[7].z = 70 + 250, locationPot[7].c = 250,
						
						   locationPot[8].x = 390                    , locationPot[8].y = 60+locationPot[0].x, locationPot[8].z = 70 + 100, locationPot[8].c = 100,
						   locationPot[9].x = locationPot[0].x + 200 - 60/2, locationPot[9].y = 60+locationPot[1].x , locationPot[9].z = 70 + 100, locationPot[9].c = 100,
						   locationPot[10].x = locationPot[0].x + 400 - 60/2 , locationPot[10].y = 60+ locationPot[2].x, locationPot[10].z = 70 + 100, locationPot[10].c = 100, 
						   locationPot[11].x = locationPot[0].x + 600 - 60/2, locationPot[11].y = 60+locationPot[3].x, locationPot[11].z = 70 + 100, locationPot[11].c = 100 };
//============ kết thúc vo 12 vị trí
//=============Khai báo cho thanh gỗ
c_loadimage Container[3];

//============Kết thúc khai báo thanh gỗ
//=============Khai báo cho các giai đoạn phát triển của hoa
c_flower flower[12]; // cho 12 vị trí hoa
int floorSky = 1; // tầng 1 2 3
int soLanTuoiCay = 0;  // 3 lần tưới cây sẽ mở tầng 1
int soLanThuHoach = 0; // 4 lần thu hoạch sẽ mở tầng 3
//============Kết thúc khai báo cho các giai đoạn phát triển của hoa
//Khai báo biến màn hình
int screen;

//Khai báo hàm
void init();
void initStore(); // init shop
void initRain_Cloud();// init Rain Cloud
void initSkyB1(); // init vị trí chậu tầng 1
void initSkyB2(); // init vị trí chậu tầng 2
void initSkyB3(); // init vị trí chậu tầng 3
void initFlowerSkyB1(); // init vị trí hoa tầng 1
void initFlowerSkyB2(); // init vị trí hoa tầng 2
void initFlowerSkyB3(); // init vị trí hoa tầng 3
void initPositiveContainer(); // init thanh gỗ
void display();
void displayStore(); // display shop
void display_RainCloud(); // display Rain_Cloud
void displaySkyB1();// dislpaly chậu vị trí tầng 1
void displaySkyB2();// dislpaly chậu vị trí tầng 2
void displaySkyB3();// dislpaly chậu vị trí tầng 3
void displayFlowerSkyB1();// dislpaly hoa vị trí tầng 1
void displayFlowerSkyB2();// dislpaly hoa vị trí tầng 2
void displayFlowerSkyB3();// dislpaly hoa vị trí tầng 3
void displayPositiveContainer();//display các vị trí ở dưới thanh gỗ
void init_inGame();//hàm load img
void init_menu();
void initPositiveContainerFlower();// itit hoa trên thanh gỗ
void screenNewGame(); // Hàm startGame
void screenContinue(); // Hàm startGame
void screenExit();// Hiển thị màn Exit(Yes/No)
void screenHelp();// Hiển thị màn Help
void screenShop();// Hiển thị màn Shop
void screenMission(); //
void screenBag(); //
void btnBack();   // Tạo btn back ngay góc trái trên
void btn_screenNewGame(); // chứa các button tại màn new game cũng như continue
void clickMain(int button, int state, int x, int y);// dùng để click các phần tử trong màn new game
void clickMenuIntro(int button, int state, int x, int y); // Click các btn ngoài màn newgame
void clickExit(int button, int state, int x, int y);      // Chọn Yes để thoát, No quay về Display
void clickBack(int button, int state, int x, int y); // Dùng để quay lại màn hình display từ các màn khác(Newgame, helpScreen)
void click_btn_right(int button, int state, int x, int y); // Click chuyển sang Shop
void mouseClickInShop(int button , int state, int x, int y); // click trong shop
void clickList(int button, int state, int x, int y); // Dùng để chuyển sang màn List
void Timer_CloudRain(); // Timer cho Cloud_Rain
void Timer(int value);// Hàm timer
void loadContainer();//load thanh gỗ
char* choosePots(int i); // chọn ảnh chậu
char* chooseFlower(int i);//ảnh hoa
void GrowthStage(); // các giai đoạn phát triển của cây
// Mã nguồn code chính
int main(int argc, char ** argv) {
  cout <<"Thoi gian he thong " << thoigianhethong <<endl;
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
  glutTimerFunc(0,Timer,0);
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
  //Load_Texture_Swap( & img_arrow, "Images/Arrow.png");
  Load_Texture_Swap( & img_btn_back, "Images/btn-Back.png");
   // Load ô chứa (thanh gỗ dưới cùng) - container
  Load_Texture_Swap(&img_container,"Images/Container.png");
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
  // Init bên trong shop
  // nút mua
  Load_Texture_Swap(&Img_Buy, "Images/btn-Buy.png");	
  // init vật phẩm trong shop
  initStore();
  //Kết thúc init bên trong shop
  //Init Rain Cloud
  initRain_Cloud();
  //Kết thúc init RainCould
  // Bắt đầu init vị trí chậu
  //initSkyB1
  initSkyB1();
  //initSkyB2
  initSkyB2();
  //initSkyB3
  initSkyB3();
  // kết thúc init vị trí chậu
  // Bắt đầu init vị trí hoa
  initFlowerSkyB1();				
  initFlowerSkyB2();
  initFlowerSkyB3();
  // Kết thúc init vị trí hoa
  //init các vị trí thanh gỗ bên dưới
  initPositiveContainer();
}
//hàm khởi động game
void init_menu() {
  Load_Texture_Swap( & img_continue, "Images/bt-Continue.png");
  Load_Texture_Swap( & img_exit, "Images/bt-Exit.png");
  Load_Texture_Swap( & img_newGame, "Images/bt-NewGame.png");
  Load_Texture_Swap( & img_help, "Images/bt-Help.png");
}
// Hàm Init Rain Cloud
void initRain_Cloud()
{
	c_Cloud :: Load_Image("Images/Cloud4.png"); // khai báo init 
	Cloud[0].Init(370.0f, 0.0f);
	Cloud[1].Init(930.0f, 200.0f);
	Cloud[2].Init(240.0f, 355.0f);

	c_Rain :: Load_Image("Images/rain.png");
	Rain[0].Init(370.0f, 0.0f);
	Rain[1].Init(530.0f, 0.0f);
}
// init chậu hoa, coppy vào hàm init main
void initStore()
{
	// đặt chậu
	Pot_Store[0].Load_Image("Images/Pot1.png");
	Pot_Store[0].Init(250,170);
	Pot_Store[1].Load_Image("Images/Pot2.png");
	Pot_Store[1].Init(450,175);
	Pot_Store[2].Load_Image("Images/Pot3.png");
	Pot_Store[2].Init(650,170);
	// chậu ẩn
	Pot_Store_Ghost[0].Load_Image("Images/Pot1.png");
	Pot_Store_Ghost[0].Init(-200,-200);
	Pot_Store_Ghost[1].Load_Image("Images/Pot2.png");
	Pot_Store_Ghost[1].Init(-200,-200);
	Pot_Store_Ghost[2].Load_Image("Images/Pot3.png");
	Pot_Store_Ghost[2].Init(-200,-200);
	
	// đặt hoa //Seed-A
	Seed_Store[0].Load_Image("Images/Seed-A.png");
	Seed_Store[0].Init(250,350);
	Seed_Store[1].Load_Image("Images/Seed-B.png");
	Seed_Store[1].Init(450,350);
	Seed_Store[2].Load_Image("Images/Seed-C.png");
	Seed_Store[2].Init(650,350);
	// hoa ẩn
	Seed_Store_Ghost[0].Load_Image("Images/Fl-A4.png");
	Seed_Store_Ghost[1].Load_Image("Images/Fl-B4.png");
	Seed_Store_Ghost[2].Load_Image("Images/Fl-C3.png");

	for(int i =0; i<3; i++)
	{
		Seed_Store_Ghost[i].Init(-200,-200);
	}
	// Chậu,hoa xem trước mặc đinh lúc vào shop
	Pot_Defaul.Load_Image("Images/Pot1.png");
	//Pot_Defaul.Zoom(2);
	Pot_Defaul.Init(1080,430); //1080 410
	// số lượng chậu, hoa ban đầu
	for(int i = 0; i < 3 ;i++)
	{
		slPot[i].soLuong = 3;
		slSeed[i].soLuong = 3;
	}

	Num:: Load_Texture_Num("Images/Nums.png");
}
// init vị trị chậu tầng 1
void initSkyB1()
{
	for(int i = 0; i<4;i++)
	{
		pot[i].Load_Image("Images/Arrow.png");
	}
	pot[0].Init_Pot(400.0f, 450.0f);//b2,265
	pot[1].Init_Pot(600.0f, 450.0f); //b1,450
	pot[2].Init_Pot(800.0f, 450.0f); //b3,110
	pot[3].Init_Pot(1000.0f, 450.0f);
}
// init vị trị chậu tầng 2
void initSkyB2()
{
	for(int i = 4; i<8;i++)
	{
		pot[i].Load_Image("Images/Arrow.png");
	}
	pot[4].Init_Pot(400.0f, 265.0f);//b2,265
	pot[5].Init_Pot(600.0f, 265.0f); //b1,450
	pot[6].Init_Pot(800.0f, 265.0f); //b3,110
	pot[7].Init_Pot(1000.0f, 265.0f);
}
// init vị trị chậu tầng 3
void initSkyB3()
{
	for(int i = 8; i<12;i++)
	{
		pot[i].Load_Image("Images/Arrow.png");
	}
	pot[8].Init_Pot(400.0f, 110.0f);//b2,265
	pot[9].Init_Pot(600.0f, 110.0f); //b1,450
	pot[10].Init_Pot(800.0f, 110.0f); //b3,110
	pot[11].Init_Pot(1000.0f, 110.0f);
}
//// ================= init Hoa
// init vị trí hoa tầng 1
void initFlowerSkyB1()
{
	for(int i = 0; i<4;i++)
	{
		flower[i].Load_Image("Images/Arrow.png");
	}
	flower[0].Init_Flower(400.0f, 388.0f,0,0);
	flower[1].Init_Flower(600.0f, 388.0f,0,0); 
	flower[2].Init_Flower(800.0f, 388.0f,0,0); 
	flower[3].Init_Flower(1000.0f, 388.0f,0,0);
}
// init vị trị hoa tầng 2
void initFlowerSkyB2()
{
	for(int i = 4; i<8;i++)
	{
		flower[i].Load_Image("Images/Arrow.png");
	}
	flower[4].Init_Flower(400.0f, 205.0f,0,0);//b2,265
	flower[5].Init_Flower(600.0f, 205.0f,0,0); //b1,450
	flower[6].Init_Flower(800.0f, 205.0f,0,0); //b3,110
	flower[7].Init_Flower(1000.0f, 205.0f,0,0);
}
// init vị trị hoa tầng 3
void initFlowerSkyB3()
{
	for(int i = 8; i<12;i++)
	{
		flower[i].Load_Image("Images/Arrow.png");
	}
	flower[8].Init_Flower(400.0f, 50.0f,0,0);//b2,265
	flower[9].Init_Flower(600.0f, 50.0f,0,0); //b1,450
	flower[10].Init_Flower(800.0f, 50.0f,0,0); //b3,110
	flower[11].Init_Flower(1000.0f, 50.0f,0,0);
}
///////// kết thúc init hoa cho 3 tầng
//// intit chậu vị trí ở phần container
void initPositiveContainerPot()
{
	Container[0].Load_Image("Images/Pot1.png");
	Container[1].Load_Image("Images/Pot2.png");
	Container[2].Load_Image("Images/Pot3.png");
}
// inti trí ở phần container
void initPositiveContainer()
{

	Container[0].Load_Image("Images/Pot1.png");
	Container[1].Load_Image("Images/Pot2.png");
	Container[2].Load_Image("Images/Pot3.png");

	Container[0].Init_LoadImg(600.0f, 610.0f,60,60);
	Container[1].Init_LoadImg(750.0f, 610.0f,60,60);
	Container[2].Init_LoadImg(900.0f, 610.0f,60,60);
}
// intit hoa vị trí ở phần container
void initPositiveContainerFlower()
{

	Container[0].Load_Image("Images/Seed-A.png");
	Container[1].Load_Image("Images/Seed-B.png");
	Container[2].Load_Image("Images/Seed-C.png");
}
///////////display
//display chậu vị trí tầng 1
void displaySkyB1()
{
	for(int i = 0 ; i <4; i++)
	{
		pot[i].Draw();
	}
}
//display chậu vị trí tầng 2
void displaySkyB2()
{
	for(int i = 4 ; i <8; i++)
	{
		pot[i].Draw();
	}
}
//display chậu vị trí tầng 3
void displaySkyB3()
{
	for(int i = 8 ; i <12; i++)
	{
		pot[i].Draw();
	}
}
//
//display hoa vị trí tầng 1
void displayFlowerSkyB1()
{
	for(int i = 0 ; i <4; i++)
	{
		flower[i].Draw();
	}
}
//display hoa vị trí tầng 2
void displayFlowerSkyB2()
{
	for(int i = 4 ; i <8; i++)
	{
		flower[i].Draw();
	}
}
//display hoa vị trí tầng 3
void displayFlowerSkyB3()
{
	for(int i = 8 ; i <12; i++)
	{
		flower[i].Draw();
	}
}
// display vị trí ở phần container
void displayPositiveContainer()
{
	for(int i = 0 ; i <3; i++)
	{
		Container[i].Draw();
	}
}
// display của shop hoa
// display các vật phẩm trong shop // đặt trong hàm display game
void displayStore()
{
	// vẽ chậu kệ
	for(int i =0; i< 3; i++)
		Pot_Store[i].Draw();
	// vẽ hoa kệ
	for(int i =0; i< 3; i++)
		Seed_Store[i].Draw();
	// chậu ẩn
	for(int i =0; i< 3; i++)
		Pot_Store_Ghost[i].Draw();
	//hoa ẩn
	for(int i =0; i< 3; i++)
		Seed_Store_Ghost[i].Draw();
	// xem trước
	Pot_Defaul.Draw();
	// vẽ số x y vị trí đặt số
	numSLVPham.Draw_Num(1050.0f,180.0f);
	numSL(); // gọi hiện số lượng hiện tại
	numMoney.Draw_Num(1080.0f,100.0f);
	numMoney.Update_Num(money);
}
// display Rain Cloud
void display_RainCloud()
{
	// Clound // khai báo display va cai nao ve truoc thi o duoi
	Cloud[0].Draw();
	Cloud[1].Draw();
	Cloud[2].Draw();
	// Rain
	Rain[0].Draw();
	Rain[1].Draw();

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
//loadContainer
void loadContainer(){
  Map_Texture( & img_container);
  Draw_Rect( & rct_container);
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
bool choosePot = false; // hiển thị thanh container
//màn hình newgame
void screenNewGame() {
  glutSetWindowTitle("SKY GRADEN");
  glClear(GL_COLOR_BUFFER_BIT);
  glLoadIdentity();
  //__Start__
  screen = 0;
  Map_Texture( & img_bg2);
  Draw_Rect( & rct_bg2);
  // Load mây lock
  Map_Texture( & img_cloud);
  Draw_Rect( & filter_lock1);
  Draw_Rect( & filter_lock2);
  //back
  btnBack();
  //load btn
  btn_screenNewGame();
  display_RainCloud();
  //load container
  loadContainer();
  //display vị trí chậu tầng 1
  if(floorSky >=1)
  {
	displaySkyB1(); // vị trí chậu
	displayFlowerSkyB1(); // vị trí hoa
  }
  if(floorSky >= 2)
  {
	  //Mây lock tầng 2
	filter_lock2.Bottom = 0;
	filter_lock2.Top = 0;
	filter_lock2.Left = 0;
	filter_lock2.Right = 0;
	displaySkyB2();
	displayFlowerSkyB2(); // vị trí hoa
  }
  if(floorSky >=3 )
  {
	  //May lock tầng 3
	filter_lock1.Bottom = 0;
	filter_lock1.Top = 0;
	filter_lock1.Left = 0;
	filter_lock1.Right = 0;
	displaySkyB3();
	displayFlowerSkyB3(); // vị trí hoa
  }
  //display các vị trí dưới thanh gỗ
  if(choosePot)
  {
	displayPositiveContainer();
  }
  //back to display
  glutMouseFunc(clickMain);

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
  // Display trong shop
  // nut mua
  Map_Texture(&Img_Buy);
  Draw_Rect(&Rct_btn_Buy); 
  // vat pham shop
  displayStore();
  //back
  glutMouseFunc(mouseClickInShop);
  //glutMouseFunc(mouseClick);
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
//click new game game
void clickMain(int button, int state, int x, int y) {
  clickBack(button, state,  x, y);
  // click tưới cây
  if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && x >= 30 && x <= 77+30 && y >= 100  && y <= 71+100 && screen == 0 && Rain[1].x < -140) 
  {
	cout << "Tuoi Cay\n";
	Rain[0].Key_Down();
	Rain[1].Key_Down();
	soLanTuoiCay += 1;
	cout <<"So Lan tuoi cay :" <<soLanTuoiCay << endl;
  }


  // ============= Tầng 1
  //vị trí chậu 1 tầng 1
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && x >= locationPot[0].x && x <= locationPot[0].y && y >= locationPot[0].c && y <= locationPot[0].z )
	{
		cout <<"Click vao vi tri 1 tang 1"<<endl;
		// kiểm soát vị trí được chọn
		pot[0].choose = true;
		for(int i = 1; i < 12 ;++i)
		{
			pot[i].choose = false;
		}
		// kết thúc kiểm soát vị trí được chọn
		// Kiểm tra có chậu chưa
		if(pot[0].already == false)
		{
			choosePot = true;
			initPositiveContainerPot();
		}
		if(pot[0].already == true)
		{
			initPositiveContainerFlower();
			pot[0].chooseSeed = true;

		}
	// kết thúc Kiểm tra có chậu chưa
		glutPostRedisplay();
	}
	//vị trí chậu 2 tầng 1
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && x >= locationPot[1].x && x <= locationPot[1].y && y >= locationPot[1].c && y <= locationPot[1].z )
	{
		cout <<"Click vao vi tri 2 tang 1"<<endl;
		// kiểm soát vị trí được chọn
		for(int i = 0; i < 12 ;++i)
		{
			if(i == 1)
			{
				pot[i].choose = true;
			}
			else
			{
				pot[i].choose = false;
			}	
		}
		// kết thúc kiểm soát vị trí được chọn
		// Kiểm tra có chậu chưa
		if(pot[1].already == false)
		{
			choosePot = true;
			initPositiveContainerPot();
		}
		if(pot[1].already == true)
		{
			// có rồi thì hiện thị hoa
			initPositiveContainerFlower();
			pot[1].chooseSeed = true; 
			// vị trí được chọn
		}
		// kết thúc Kiểm tra có chậu chưa
			glutPostRedisplay();
	}
	//vị trí chậu 3
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && x >= locationPot[2].x && x <= locationPot[2].y && y >= locationPot[2].c && y <= locationPot[2].z )
	{
		cout <<"Click vao vi tri 3 tang 1"<<endl;
		// kiểm soát vị trí được chọn
		for(int i = 0; i < 12 ;++i)
		{
			if(i == 2)
			{
				pot[i].choose = true;
			}
			else
			{
				pot[i].choose = false;
			}
		
		}
		// kết thúc kiểm soát vị trí được chọn
		// Kiểm tra có chậu chưa
		if(pot[2].already == false)
		{
			choosePot = true;
			initPositiveContainerPot();
		}
		else
		{
			// có rồi thì hiện thị hoa
			initPositiveContainerFlower();
			pot[2].chooseSeed = true;
		}
		// kết thúc Kiểm tra có chậu chưa
			glutPostRedisplay();
		}
		//vị trí chậu 4
		if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && x >= locationPot[3].x && x <= locationPot[3].y && y >= locationPot[3].c && y <= locationPot[3].z )
		{
		cout <<"Click vao vi tri 4 tang 1"<<endl;
		// kiểm soát vị trí được chọn
		// kiểm soát vị trí được chọn
		for(int i = 0; i < 12 ;++i)
		{
			if(i == 3)
			{
				pot[i].choose = true;
			}
			else
			{
				pot[i].choose = false;
			}
		
		}
		// kết thúc kiểm soát vị trí được chọn
		// Kiểm tra có chậu chưa
		if(pot[3].already == false)
		{
			choosePot = true;
			initPositiveContainerPot();
		}
		else
		{
			// có rồi thì hiện thị hoa
			initPositiveContainerFlower();
			pot[3].chooseSeed = true;
		}
		// kết thúc Kiểm tra có chậu chưa
		glutPostRedisplay();
	}
	// ==================== Tầng 2 =========
	//vị trí chậu 1 tầng 2
		if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && x >= locationPot[4].x && x <= locationPot[4].y && y >= locationPot[4].c && y <= locationPot[4].z && floorSky >= 2)
	{
		cout <<"Click vao vi tri 1 tang 2"<<endl;
		// kiểm soát vị trí được chọn
		for(int i = 0; i < 12 ;++i)
		{
			if(i == 4)
			{
				pot[i].choose = true;
			}
			else
			{
				pot[i].choose = false;
			}
		
		}
		// kết thúc kiểm soát vị trí được chọn
		// Kiểm tra có chậu chưa
		if(pot[4].already == false)
		{
			choosePot = true;
			initPositiveContainerPot();
		}
		if(pot[4].already == true)
		{
			initPositiveContainerFlower();
			pot[4].chooseSeed = true;
		}
		// kết thúc Kiểm tra có chậu chưa
			glutPostRedisplay();
		}
		//vị trí chậu 2 tầng 2
		if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && x >= locationPot[5].x && x <= locationPot[5].y && y >= locationPot[5].c && y <= locationPot[5].z && floorSky >= 2 )
		{
		cout <<"Click vao vi tri 2 tang 2"<<endl;
		// kiểm soát vị trí được chọn
		for(int i = 0; i < 12 ;++i)
		{
			if(i == 5)
			{
				pot[i].choose = true;
			}
			else
			{
				pot[i].choose = false;
			}
		
		}
		// kết thúc kiểm soát vị trí được chọn
		// Kiểm tra có chậu chưa
		if(pot[5].already == false)
		{
			choosePot = true;
			initPositiveContainerPot();
		}
		if(pot[5].already == true)
		{
			initPositiveContainerFlower();
			pot[5].chooseSeed = true;
		}
		// kết thúc Kiểm tra có chậu chưa
			glutPostRedisplay();
		}
	//vị trí chậu 3
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && x >= locationPot[6].x && x <= locationPot[6].y && y >= locationPot[6].c && y <= locationPot[6].z && floorSky >= 2 )
	{
		cout <<"Click vao vi tri 3 tang 2"<<endl;
		// kiểm soát vị trí được chọn
		for(int i = 0; i < 12 ;++i)
		{
			if(i == 6)
			{
				pot[i].choose = true;
			}
			else
			{
				pot[i].choose = false;
			}
		
		}
		// kết thúc kiểm soát vị trí được chọn
		// Kiểm tra có chậu chưa
		if(pot[6].already == false)
		{
			choosePot = true;
			initPositiveContainerPot();
		}
		if(pot[6].already == true)
		{
			initPositiveContainerFlower();
			pot[6].chooseSeed = true;
		}
		// kết thúc Kiểm tra có chậu chưa
			glutPostRedisplay();
	}
	//vị trí chậu 4
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && x >= locationPot[7].x && x <= locationPot[7].y && y >= locationPot[7].c && y <= locationPot[7].z && floorSky >= 2 )
	{
		cout <<"Click vao vi tri 4 tang 2"<<endl;
		// kiểm soát vị trí được chọn
		for(int i = 0; i < 12 ;++i)
		{
			if(i == 7)
			{
				pot[i].choose = true;
			}
			else
			{
				pot[i].choose = false;
			}		
		}
		// kết thúc kiểm soát vị trí được chọn
		// Kiểm tra có chậu chưa
		if(pot[7].already == false)
		{
			choosePot = true;
			initPositiveContainerPot();
		}
		if(pot[7].already == true)
		{
			initPositiveContainerFlower();
			pot[7].chooseSeed = true;
		}
		// kết thúc Kiểm tra có chậu chưa
		glutPostRedisplay();
	}
	//====================== Tầng 3
	//vị trí chậu 1 tầng 3
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && x >= locationPot[8].x && x <= locationPot[8].y && y >= locationPot[8].c && y <= locationPot[8].z && floorSky >=  3)
	{
		cout <<"Click vao vi tri 1 tang 3"<<endl;
		// kiểm soát vị trí được chọn
		for(int i = 0; i < 12 ;++i)
		{
			if(i == 8)
			{
				pot[i].choose = true;
			}
			else
			{
				pot[i].choose = false;
			}		
		}
		// kết thúc kiểm soát vị trí được chọn
		// Kiểm tra có chậu chưa
		if(pot[8].already == false)
		{
			choosePot = true;
			initPositiveContainerPot();
		}
		if(pot[8].already == true)
		{
			initPositiveContainerFlower();
			pot[8].chooseSeed = true;
		}
	// kết thúc Kiểm tra có chậu chưa
		glutPostRedisplay();
	}
	//vị trí chậu 2 tầng 3
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && x >= locationPot[9].x && x <= locationPot[9].y && y >= locationPot[9].c && y <= locationPot[9].z && floorSky >=  3 )
	{
		cout <<"Click vao vi tri 2 tang 3"<<endl;
		// kiểm soát vị trí được chọn
		for(int i = 0; i < 12 ;++i)
		{
			if(i == 9)
			{
				pot[i].choose = true;
			}
			else
			{
				pot[i].choose = false;
			}
		
		}
		// kết thúc kiểm soát vị trí được chọn
		// Kiểm tra có chậu chưa
		if(pot[9].already == false)
		{
			choosePot = true;
			initPositiveContainerPot();
		}
		if(pot[9].already == true)
		{
			// có rồi thì hiện thị hoa
			initPositiveContainerFlower();
			pot[9].chooseSeed = true;
		}
		// kết thúc Kiểm tra có chậu chưa
		glutPostRedisplay();
	}
	//vị trí chậu 3
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && x >= locationPot[10].x && x <= locationPot[10].y && y >= locationPot[10].c && y <= locationPot[10].z && floorSky >=  3)
	{
		cout <<"Click vao vi tri 3 tang 3"<<endl;
			// kiểm soát vị trí được chọn
		for(int i = 0; i < 12 ;++i)
		{
			if(i == 10)
			{
				pot[i].choose = true;
			}
			else
			{
				pot[i].choose = false;
			}
		
		}
		// kết thúc kiểm soát vị trí được chọn
		// Kiểm tra có chậu chưa
		if(pot[10].already == false)
		{
			choosePot = true;
			initPositiveContainerPot();
		}
		if(pot[10].already == true)
		{
			// có rồi thì hiện thị hoa
			initPositiveContainerFlower();
			pot[10].chooseSeed = true;
		}
		// kết thúc Kiểm tra có chậu chưa
		glutPostRedisplay();
	
	}
	//vị trí chậu 4
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && x >= locationPot[11].x && x <= locationPot[11].y && y >= locationPot[11].c && y <= locationPot[11].z && floorSky >=  3)
	{
		cout <<"Click vao vi tri 4 tang 3"<<endl;
		// kiểm soát vị trí được chọn
		for(int i = 0; i < 12 ;++i)
		{
			if(i == 11)
			{
				pot[i].choose = true;
			}
			else
			{
				pot[i].choose = false;
			}
		
		}
		// kết thúc kiểm soát vị trí được chọn
		// Kiểm tra có chậu chưa
		if(pot[11].already == false)
		{
			choosePot = true;
			initPositiveContainerPot();
		}
		else
		{
			// có rồi thì hiện thị hoa
			initPositiveContainerFlower();
			pot[11].chooseSeed = true;
		}
		// kết thúc Kiểm tra có chậu chưa
		glutPostRedisplay();
	}
	// hiển thị mũi tên chọn hoa
	for(int i = 0; i < 12 ;++i)
	{
		if(pot[i].choose == true && flower[i].stage == 0 && pot[i].already == true)
		{
			flower[i].keyDow_2();
		}
		if(pot[i].choose == false && flower[i].stage == 0)
		{
			flower[i].Update_Ghost();
		}
	}
  //========= chọn loại chậu, loại hoa container
  //vị trí container 1 
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && x >= 580 && x <= 580 + 60 && y >= 610 && y <= 610 + 60 )
	{  
		cout <<"Click vao vi tri container 1 "<<endl;
		// lựa chọn chậu
		for(int i = 0; i < 12 ; ++i)
		{
			if(pot[i].choose == true && pot[i].already == false && slPot[0].soLuong > 0)
			{
				pot[i].Load_Image(choosePots(1));
				pot[i].already = true;
				pot[i].typePot = 1;
				slPot[0].soLuong -=1;
				cout <<"Dat chau loa 1 thanh cong"<<endl;

			}
		}
		if(slPot[0].soLuong <= 0)
		{
			cout <<"So luong chau loai 1 da het"<<endl;
		}
		// Lựa chọn Hoa
		for(int i = 0; i < 12 ; ++i)
		{
			if(pot[i].choose == true && pot[i].already == true && pot[i].chooseSeed == true && flower[i].stage == 0  && slSeed[0].soLuong > 0)
			{
				flower[i].Load_Image(chooseFlower(0));
				flower[i].keyDow_3();
				flower[i].stage = 1;
				flower[i].type = 1;
				flower[i].timeStar = thoigianhethong;
				slSeed[0].soLuong -= 1;
				cout <<"Trong Hoa loai 1 thanh cong"<<endl;
			}
		}
		if(slSeed[0].soLuong <= 0)
		{
			cout <<"So luong hat loai 1 da het"<<endl;
		}
		glutPostRedisplay();
	}
	//vị trí container 2 
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && x >= 730 && x <= 730 + 60 &&  y >= 610 && y <= 610 + 60 )
	{
		cout <<"Click vao vi tri container 2 "<<endl;
		// lựa chọn chậu
		for(int i = 0; i < 12 ; ++i)
		{
			if(pot[i].choose == true && pot[i].already == false && slPot[1].soLuong > 0)
			{
				pot[i].Load_Image(choosePots(2));
				pot[i].already = true;
				pot[i].typePot = 2;
				flower[i].timeStar = thoigianhethong;
				slPot[1].soLuong -= 1;
				cout <<"Dat chau loai 2 thanh cong"<<endl;
			}
		}
		if(slPot[1].soLuong <= 0)
		{
			cout <<"So luong chau loai 2 da het"<<endl;
		}
		// Lựa chọn Hoa 
		for(int i = 0; i < 12 ; ++i)
		{
			if(pot[i].choose == true && pot[i].already == true && pot[i].chooseSeed == true &&flower[i].stage == 0  && slSeed[1].soLuong > 0)
			{
				flower[i].Load_Image(chooseFlower(0));
				flower[i].keyDow_3();
				flower[i].stage = 1;
				flower[i].type = 2;
				flower[i].timeStar = thoigianhethong;
				slSeed[1].soLuong -= 1;
				cout <<"Trong Hoa loai 2 thanh cong"<<endl;
			}
		}
		if(slSeed[1].soLuong <= 0)
		{
			cout <<"So luong hat loai 2 da het"<<endl;
		}
		glutPostRedisplay();
	}
	//vị trí container 3
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && x >= 880 && x <= 880 + 60 &&  y >= 610 && y <= 610 + 60 )
	{
		cout <<"Click vao vi tri container 3 "<<endl;
		// lựa chọn chậu
		for(int i = 0; i < 12 ; ++i)
		{
			if(pot[i].choose == true && pot[i].already == false && slPot[2].soLuong > 0)
			{
				pot[i].Load_Image(choosePots(3));
				pot[i].already = true;
				pot[i].typePot = 3;
				slPot[2].soLuong -=1;
				cout <<"Dat chau loai 3 thanh cong"<<endl;
			}
		}
		if(slPot[2].soLuong <= 0)
		{
			cout <<"So luong chau loai 3 da het"<<endl;
		}
		// Lựa chọn Hoa
		for(int i = 0; i < 12 ; ++i)
		{
			if(pot[i].choose == true && pot[i].already == true && pot[i].chooseSeed == true && flower[i].stage == 0  && slSeed[2].soLuong > 0)
			{
				flower[i].Load_Image(chooseFlower(0));
				flower[i].keyDow_3();
				flower[i].stage = 1;
				flower[i].type = 3;
				flower[i].timeStar = thoigianhethong;
				slSeed[2].soLuong -= 1;
				cout <<"Trong Hoa loai 3 thanh cong"<<endl;
			}
		}
		if(slSeed[2].soLuong <= 0)
		{
			cout <<"So luong hat loai 3 da het"<<endl;
		}
		glutPostRedisplay();
	}
	//============================================== Gỡ chậu or thu hoạch ====================
	/////// ================= gỡ chậu
// ============= Tầng 1
  //vị trí chậu 1 tầng 1
	if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN && x >= locationPot[0].x && x <= locationPot[0].y && y >= locationPot[0].c && y <= locationPot[0].z )
	{
		cout <<"Click RIGHT vao vi tri 1 tang 1"<<endl;
		// gỡ chậu
		if(pot[0].already == true && flower[0].stage == 0)
		{
			pot[0].Load_Image(choosePots(0));
			pot[0].already = false;
			cout <<"Go chau thanh cong"<<endl;
		}
		glutPostRedisplay();
	}
	//vị trí chậu 2 tầng 1
	if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN && x >= locationPot[1].x && x <= locationPot[1].y && y >= locationPot[1].c && y <= locationPot[1].z )
	{
		cout <<"Click RIGHT vao vi tri 2 tang 1"<<endl;
				// gỡ chậu
		if(pot[1].already == true && flower[1].stage == 0)
		{
			pot[1].Load_Image(choosePots(0));
			pot[1].already = false;
			cout <<"Go chau thanh cong"<<endl;
		}
			glutPostRedisplay();
	}
	//vị trí chậu 3
	if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN && x >= locationPot[2].x && x <= locationPot[2].y && y >= locationPot[2].c && y <= locationPot[2].z )
	{
		cout <<"Click RIGHT vao vi tri 3 tang 1"<<endl;
		// gỡ chậu
		if(pot[2].already == true && flower[2].stage == 0)
		{
			pot[2].Load_Image(choosePots(0));
			pot[2].already = false;
			cout <<"Go chau thanh cong"<<endl;
		}
			glutPostRedisplay();
		}
	//vị trí chậu 4
	if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN && x >= locationPot[3].x && x <= locationPot[3].y && y >= locationPot[3].c && y <= locationPot[3].z )
	{
		cout <<"Click RIGHT vao vi tri 4 tang 1"<<endl;
				// gỡ chậu
		if(pot[3].already == true && flower[3].stage == 0)
		{
			pot[3].Load_Image(choosePots(0));
			pot[3].already = false;
			cout <<"Go chau thanh cong"<<endl;
		}
		glutPostRedisplay();
	}
	// ==================== Tầng 2 =========
	//vị trí chậu 1 tầng 2
	if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN && x >= locationPot[4].x && x <= locationPot[4].y && y >= locationPot[4].c && y <= locationPot[4].z && floorSky >= 2)
	{
		cout <<"Click RIGHT vao vi tri 1 tang 2"<<endl;
				// gỡ chậu
		if(pot[4].already == true && flower[4].stage == 0)
		{
			pot[4].Load_Image(choosePots(0));
			pot[4].already = false;
			cout <<"Go chau thanh cong"<<endl;
		}
			glutPostRedisplay();
	}
		//vị trí chậu 2 tầng 2
	if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN && x >= locationPot[5].x && x <= locationPot[5].y && y >= locationPot[5].c && y <= locationPot[5].z && floorSky >= 2 )
	{
		cout <<"Click RIGHT vao vi tri 3 tang 2"<<endl;
		//gỡ chậu
		if(pot[5].already == true && flower[5].stage == 0)
		{
			pot[5].Load_Image(choosePots(0));
			pot[5].already = false;
			cout <<"Go chau thanh cong"<<endl;
		}
			glutPostRedisplay();
	}
	//vị trí chậu 3
	if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN && x >= locationPot[6].x && x <= locationPot[6].y && y >= locationPot[6].c && y <= locationPot[6].z && floorSky >= 2 )
	{
		cout <<"Click RIGHT vao vi tri 3 tang 2"<<endl;
		//gỡ chậu
		if(pot[6].already == true && flower[6].stage == 0)
		{
			pot[6].Load_Image(choosePots(0));
			pot[6].already = false;
			cout <<"Go chau thanh cong"<<endl;
		}
			glutPostRedisplay();
	}
	//vị trí chậu 4
	if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN && x >= locationPot[7].x && x <= locationPot[7].y && y >= locationPot[7].c && y <= locationPot[7].z && floorSky >= 2 )
	{
		cout <<"Click RIGHT vao vi tri 4 tang 2"<<endl;
				// gỡ chậu
		if(pot[7].already == true && flower[7].stage == 0)
		{
			pot[7].Load_Image(choosePots(0));
			pot[7].already = false;
			cout <<"Go chau thanh cong"<<endl;
		}
		glutPostRedisplay();
	}
	//====================== Tầng 3
	//vị trí chậu 1 tầng 3
	if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN && x >= locationPot[8].x && x <= locationPot[8].y && y >= locationPot[8].c && y <= locationPot[8].z && floorSky >=  3)
	{
		cout <<"Click RIGHT vao vi tri 1 tang 3"<<endl;
						// gỡ chậu
		if(pot[8].already == true && flower[8].stage == 0)
		{
			pot[8].Load_Image(choosePots(0));
			pot[8].already = false;
			cout <<"Go chau thanh cong"<<endl;
		}
		glutPostRedisplay();
	}
	//vị trí chậu 2 tầng 3
	if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN && x >= locationPot[9].x && x <= locationPot[9].y && y >= locationPot[9].c && y <= locationPot[9].z && floorSky >=  3 )
	{
		cout <<"Click RIGHT vao vi tri 2 tang 3"<<endl;
						// gỡ chậu
		if(pot[9].already == true && flower[9].stage == 0)
		{
			pot[9].Load_Image(choosePots(0));
			pot[9].already = false;
			cout <<"Go chau thanh cong"<<endl;
		}
		glutPostRedisplay();
	}
	//vị trí chậu 3
	if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN && x >= locationPot[10].x && x <= locationPot[10].y && y >= locationPot[10].c && y <= locationPot[10].z && floorSky >=  3)
	{
		cout <<"Click RIGHT vao vi tri 3 tang 3"<<endl;
						// gỡ chậu
		if(pot[10].already == true && flower[10].stage == 0)
		{
			pot[10].Load_Image(choosePots(0));
			pot[10].already = false;
			cout <<"Go chau thanh cong"<<endl;
		}
		glutPostRedisplay();
	
	}
	//vị trí chậu 4
	if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN && x >= locationPot[11].x && x <= locationPot[11].y && y >= locationPot[11].c && y <= locationPot[11].z && floorSky >=  3)
	{
		cout <<"Click RIGHT vao vi tri 4 tang 3"<<endl;
						// gỡ chậu
		if(pot[11].already == true && flower[11].stage == 0)
		{
			pot[11].Load_Image(choosePots(0));
			pot[11].already = false;
			cout <<"Go chau thanh cong"<<endl;
		}
		glutPostRedisplay();
	}
	// xóa hiển thị mũi tên chọn chậu
	for(int i = 0; i < 12 ;++i)
	{
		if(pot[i].already == false && flower[i].stage == 0)
		{
			flower[i].Update_Ghost();
		}
	}
	/////// ================= kết thúc gỡ chậu
	/////// ================= Thu hoạch
// ============= Tầng 1
  //vị trí chậu 1 tầng 1
	if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN && x >= locationPot[0].x && x <= locationPot[0].y && y >= locationPot[0].c - 30 && y <= locationPot[0].z - 80)
	{
		cout <<"Click RIGHT vao vi tri 1 tang 1 phan thu hoach"<<endl;
		int vitri = 0;
		// thu hoach hoa
		if(pot[vitri].already == true && flower[vitri].stage == 3)
		{
			flower[vitri].Load_Image(choosePots(0));
			flower[vitri].stage = 0;
			if(flower[vitri].type == 1 )
			{
				money += 250; 
			}
			if(flower[vitri].type == 2)
			{
				money += 350;
			}
			if(flower[vitri].type == 3)
			{
				money += 400;
			}
			soLanThuHoach += 1;
			cout <<"Thu hoach thanh cong"<<endl;
		}
		glutPostRedisplay();
	}
	//vị trí chậu 2 tầng 1
	if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN && x >= locationPot[1].x && x <= locationPot[1].y && y >= locationPot[1].c - 30 && y <= locationPot[1].z - 80 )
	{
		cout <<"Click RIGHT vao vi tri thu hoach 2 tang 1"<<endl;
		int vitri = 1;
		// thu hoach hoa
		if(pot[vitri].already == true && flower[vitri].stage == 3)
		{
			flower[vitri].Load_Image(choosePots(0));
			flower[vitri].stage = 0;
			if(flower[vitri].type == 1 )
			{
				money += 250; 
			}
			if(flower[vitri].type == 2)
			{
				money += 350;
			}
			if(flower[vitri].type == 3)
			{
				money += 400;
			}
			soLanThuHoach += 1;
			cout <<"Thu hoach thanh cong"<<endl;
		}
			glutPostRedisplay();
	}
	//vị trí chậu 3
	if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN && x >= locationPot[2].x && x <= locationPot[2].y && y >= locationPot[2].c -30 && y <= locationPot[2].z  - 80)
	{
		cout <<"Click RIGHT vao vi tri thu hoach 3 tang 1"<<endl;
		int vitri = 2;
		// thu hoach hoa
		if(pot[vitri].already == true && flower[vitri].stage == 3)
		{
			flower[vitri].Load_Image(choosePots(0));
			flower[vitri].stage = 0;
			if(flower[vitri].type == 1 )
			{
				money += 250; 
			}
			if(flower[vitri].type == 2)
			{
				money += 350;
			}
			if(flower[vitri].type == 3)
			{
				money += 400;
			}
			soLanThuHoach += 1;
			cout <<"Thu hoach thanh cong"<<endl;
		}
			glutPostRedisplay();
		}
	//vị trí chậu 4
	if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN && x >= locationPot[3].x && x <= locationPot[3].y && y >= locationPot[3].c - 30 && y <= locationPot[3].z - 80 )
	{
		cout <<"Click RIGHT vao vi tri thu hoach 4 tang 1"<<endl;
		int vitri = 3;
		// thu hoach hoa
		if(pot[vitri].already == true && flower[vitri].stage == 3)
		{
			flower[vitri].Load_Image(choosePots(0));
			flower[vitri].stage = 0;
			if(flower[vitri].type == 1 )
			{
				money += 250; 
			}
			if(flower[vitri].type == 2)
			{
				money += 350;
			}
			if(flower[vitri].type == 3)
			{
				money += 400;
			}
			soLanThuHoach += 1;
			cout <<"Thu hoach thanh cong"<<endl;
		}
		glutPostRedisplay();
	}
	// ==================== Tầng 2 =========
	//vị trí chậu 1 tầng 2
	if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN && x >= locationPot[4].x && x <= locationPot[4].y && y >= locationPot[4].c - 30 && y <= locationPot[4].z - 80 && floorSky >= 2)
	{
		cout <<"Click RIGHT vao vi tri thu hoach 1 tang 2"<<endl;
		int vitri = 4;
		// thu hoach hoa
		if(pot[vitri].already == true && flower[vitri].stage == 3)
		{
			flower[vitri].Load_Image(choosePots(0));
			flower[vitri].stage = 0;
			if(flower[vitri].type == 1 )
			{
				money += 250; 
			}
			if(flower[vitri].type == 2)
			{
				money += 350;
			}
			if(flower[vitri].type == 3)
			{
				money += 400;
			}
			soLanThuHoach += 1;
			cout <<"Thu hoach thanh cong"<<endl;
		}
			glutPostRedisplay();
	}
		//vị trí chậu 2 tầng 2
	if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN && x >= locationPot[5].x && x <= locationPot[5].y && y >= locationPot[5].c -30 && y <= locationPot[5].z - 80 && floorSky >= 2 )
	{
		cout <<"Click RIGHT vao vi tri thu hoach 3 tang 2"<<endl;
		int vitri = 5;
		// thu hoach hoa
		if(pot[vitri].already == true && flower[vitri].stage == 3)
		{
			flower[vitri].Load_Image(choosePots(0));
			flower[vitri].stage = 0;
			if(flower[vitri].type == 1 )
			{
				money += 250; 
			}
			if(flower[vitri].type == 2)
			{
				money += 350;
			}
			if(flower[vitri].type == 3)
			{
				money += 400;
			}
			soLanThuHoach += 1;
			cout <<"Thu hoach thanh cong"<<endl;
		}
			glutPostRedisplay();
	}
	//vị trí chậu 3
	if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN && x >= locationPot[6].x && x <= locationPot[6].y && y >= locationPot[6].c -30 && y <= locationPot[6].z- 80  && floorSky >= 2 )
	{
		cout <<"Click RIGHT vao vi tri thu hoach 3 tang 2"<<endl;
		int vitri = 6;
		// thu hoach hoa
		if(pot[vitri].already == true && flower[vitri].stage == 3)
		{
			flower[vitri].Load_Image(choosePots(0));
			flower[vitri].stage = 0;
			if(flower[vitri].type == 1 )
			{
				money += 250; 
			}
			if(flower[vitri].type == 2)
			{
				money += 350;
			}
			if(flower[vitri].type == 3)
			{
				money += 400;
			}
			soLanThuHoach += 1;
			cout <<"Thu hoach thanh cong"<<endl;
		}
			glutPostRedisplay();
	}
	//vị trí chậu 4
	if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN && x >= locationPot[7].x && x <= locationPot[7].y && y >= locationPot[7].c - 30 && y <= locationPot[7].z - 80 && floorSky >= 2 )
	{
		cout <<"Click RIGHT vao vi tri thu hoach 4 tang 2"<<endl;
		int vitri = 7;
		// thu hoach hoa
		if(pot[vitri].already == true && flower[vitri].stage == 3)
		{
			flower[vitri].Load_Image(choosePots(0));
			flower[vitri].stage = 0;
			if(flower[vitri].type == 1 )
			{
				money += 250; 
			}
			if(flower[vitri].type == 2)
			{
				money += 350;
			}
			if(flower[vitri].type == 3)
			{
				money += 400;
			}
			soLanThuHoach += 1;
			cout <<"Thu hoach thanh cong"<<endl;
		}
		glutPostRedisplay();
	}
	//====================== Tầng 3
	//vị trí chậu 1 tầng 3
	if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN && x >= locationPot[8].x && x <= locationPot[8].y && y >= locationPot[8].c - 30 && y <= locationPot[8].z - 80 && floorSky >=  3)
	{
		cout <<"Click RIGHT vao vi tri  thu hoach 1 tang 3"<<endl;
		int vitri = 8;
		// thu hoach hoa
		if(pot[vitri].already == true && flower[vitri].stage == 3)
		{
			flower[vitri].Load_Image(choosePots(0));
			flower[vitri].stage = 0;
			if(flower[vitri].type == 1 )
			{
				money += 250; 
			}
			if(flower[vitri].type == 2)
			{
				money += 350;
			}
			if(flower[vitri].type == 3)
			{
				money += 400;
			}
			cout <<"Thu hoach thanh cong"<<endl;
		}
		glutPostRedisplay();
	}
	//vị trí chậu 2 tầng 3
	if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN && x >= locationPot[9].x && x <= locationPot[9].y && y >= locationPot[9].c - 30 && y <= locationPot[9].z - 80 && floorSky >=  3 )
	{
		cout <<"Click RIGHT vao vi tri thu hoach 2 tang 3"<<endl;
		int vitri = 9;
		// thu hoach hoa
		if(pot[vitri].already == true && flower[vitri].stage == 3)
		{
			flower[vitri].Load_Image(choosePots(0));
			flower[vitri].stage = 0;
			if(flower[vitri].type == 1 )
			{
				money += 250; 
			}
			if(flower[vitri].type == 2)
			{
				money += 350;
			}
			if(flower[vitri].type == 3)
			{
				money += 400;
			}
			cout <<"Thu hoach thanh cong"<<endl;
		}
		glutPostRedisplay();
	}
	//vị trí chậu 3
	if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN && x >= locationPot[10].x && x <= locationPot[10].y && y >= locationPot[10].c - 30 && y <= locationPot[10].z - 80 && floorSky >=  3)
	{
		cout <<"Click RIGHT vao vi tri  thu hoach 3 tang 3"<<endl;
		int vitri = 10;
		// thu hoach hoa
		if(pot[vitri].already == true && flower[vitri].stage == 3)
		{
			flower[vitri].Load_Image(choosePots(0));
			flower[vitri].stage = 0;
			if(flower[vitri].type == 1 )
			{
				money += 250; 
			}
			if(flower[vitri].type == 2)
			{
				money += 350;
			}
			if(flower[vitri].type == 3)
			{
				money += 400;
			}
			cout <<"Thu hoach thanh cong"<<endl;
		}
		glutPostRedisplay();
	
	}
	//vị trí chậu 4
	if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN && x >= locationPot[11].x && x <= locationPot[11].y && y >= locationPot[11].c - 30 && y <= locationPot[11].z - 80 && floorSky >=  3)
	{
		cout <<"Click RIGHT vao vi tri thu hoach 4 tang 3"<<endl;
		int vitri = 11;
		// thu hoach hoa
		if(pot[vitri].already == true && flower[vitri].stage == 3)
		{
			flower[vitri].Load_Image(choosePots(0));
			flower[vitri].stage = 0;
			if(flower[vitri].type == 1 )
			{
				money += 250; 
			}
			if(flower[vitri].type == 2)
			{
				money += 350;
			}
			if(flower[vitri].type == 3)
			{
				money += 400;
			}
			cout <<"Thu hoach thanh cong"<<endl;
		}
		glutPostRedisplay();
	}
	/////// ================= kết thúc Thu hoạch
	if(soLanTuoiCay == 3)
	{
	  floorSky = 2;
	  glutPostRedisplay();
	}
	if(soLanThuHoach >= 4 && soLanTuoiCay >= 3)
	{
		floorSky = 3;
		glutPostRedisplay();
	}
  glutPostRedisplay();
}

/// Các hàm xử lý bên shop
// số lượng vật phẩm
void numSL()
{
	switch(Class_Pot_Seed)
	{
	case 1:
		numSLVPham.Update_Num(slPot[0].soLuong);
		break;
	case 2:
		numSLVPham.Update_Num(slPot[1].soLuong);
		break;
	case 3:
		numSLVPham.Update_Num(slPot[2].soLuong);
		break;
	case 4:
		numSLVPham.Update_Num(slSeed[0].soLuong);
		break;
	case 5:
		numSLVPham.Update_Num(slSeed[1].soLuong);
		break;
	case 6:
		numSLVPham.Update_Num(slSeed[2].soLuong);
		break;


	}
}
// mua chậu
void buyPot()
{
	switch (Class_Pot_Seed)
	{
	case 1:
		if(money >= 200)
		{
			Pot_Store_Ghost[0].BuyPot(0);
			money -= 200;
			
		}
		else
		{
			cout <<"ban khong du tien mua"<< endl;
		}
		break;
	case 2:
		if(money >= 300)
		{
			Pot_Store_Ghost[1].BuyPot(1);
			money -= 300;
		}
		else
		{
			cout <<"ban khong du tien mua"<< endl;
		}
		break;
	case 3:
		if(money >= 400)
		{
			Pot_Store_Ghost[2].BuyPot(2);
			money -= 400;
		}
		else
		{
			cout <<"ban khong du tien mua"<< endl;
		}
		break;
	case 4:
		if(money >= 150)
		{
			Seed_Store_Ghost[0].BuySeed(0);
			money -= 150;
		}
		else
		{
			cout <<"ban khong du tien mua"<< endl;
		}
		break;
	case 5:
		if(money >= 200)
		{
			Seed_Store_Ghost[1].BuySeed(1);
			money -= 200;
		}
		else
		{
			cout <<"ban khong du tien mua"<< endl;
		}
		break;
	case 6:
		if(money >= 250)
		{
			Seed_Store_Ghost[2].BuySeed(2);
			money -= 250;

		}
		else
		{
			cout <<"ban khong du tien mua"<< endl;
		}
		break;
	}

}
// Hàm xử lý sự kiện bên trong shop
void mouseClickInShop(int button , int state, int x, int y)
{
	  //back về screen Newgame
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && x >= 20 && x <= 70 && y >= 20 && y <= 95 && screen == 1) {
		cout << "Back to NewGame\n";
		glutDisplayFunc(screenNewGame);
	  }
	//xem chậu
	// chậu1
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && x >= 210 && x <= 280 && y >= 170  && y <= 220)
	{
		for(int i =0 ; i <3 ; i++)
		{
			Seed_Store_Ghost[i].keyUp();
			Pot_Store_Ghost[i].keyUp();

		}
		
		Pot_Defaul.keyUp();
		//Pot_Defaul.~c_Store_Pot();
		Pot_Store_Ghost[0].keyDow();
		Class_Pot_Seed = 1;
		numSLVPham.Update_Num(slPot[0].soLuong);
		//cout << Class_Pot;		
	}
	// chậu2
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && x >= 410 && x <= 480 && y >= 170  && y <= 240)
	{
		for(int i =0 ; i <3 ; i++)
		{
			Seed_Store_Ghost[i].keyUp();
			Pot_Store_Ghost[i].keyUp();
		}
		Pot_Defaul.keyUp();
		Pot_Store_Ghost[1].keyDow();
		Class_Pot_Seed = 2;
		numSLVPham.Update_Num(slPot[1].soLuong);
		//Pot_Store_Ghost[1].BuyPot(1);
		
	}
	//chậu 3
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && x >= 610 && x <= 680 && y >= 170  && y <= 240)
	{
		for(int i =0 ; i <3 ; i++)
		{
			Seed_Store_Ghost[i].keyUp();
			Pot_Store_Ghost[i].keyUp();
		}
		Pot_Defaul.keyUp();
		Pot_Store_Ghost[2].keyDow();
		numSLVPham.Update_Num(slPot[2].soLuong);
		Class_Pot_Seed = 3;
	}
	// hoa
	// hoa1
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && x >= 210 && x <= 280 && y >= 350  && y <= 440)
	{
		for(int i =0 ; i < 3 ; i++)
		{
			Seed_Store_Ghost[i].keyUp();
			Pot_Store_Ghost[i].keyUp();
		}
		Pot_Defaul.keyUp();
		Seed_Store_Ghost[0].keyDow();
		Class_Pot_Seed = 4;
	}
	// hoa2
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && x >= 410 && x <= 480 && y >= 350  && y <= 420)
	{
		for(int i =0 ; i < 3 ; i++)
		{
			Seed_Store_Ghost[i].keyUp();
			Pot_Store_Ghost[i].keyUp();
		}
		Pot_Defaul.keyUp();
		Seed_Store_Ghost[1].keyDow();
		Class_Pot_Seed = 5;
	}
	//hoa 3
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && x >= 610 && x <= 680 && y >= 350  && y <= 450)
	{
		for(int i =0 ; i < 3 ; i++)
		{
			Seed_Store_Ghost[i].keyUp();
			Pot_Store_Ghost[i].keyUp();
		}

		Pot_Defaul.keyUp();
		Seed_Store_Ghost[2].keyDow();
		Class_Pot_Seed = 6;
	}
	// btn mua vật phẩm
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && x >= 990 && x <= 1180 && y >= 610 && y <= 680)
	{
		buyPot();
		cout <<"============"<<endl;
		cout << "so tien con lai la: "<< money <<endl;
		for(int i =0 ; i < 3 ; i++)
		{
			cout <<" Chau loai "<< i<<":" <<slPot[i].soLuong <<endl;

		}
		cout <<"============"<<endl;
		for(int i =0 ; i < 3 ; i++)
		{
			cout <<" Hoa loai  "<< i<<":" <<slSeed[i].soLuong <<endl;
		}
		numMoney.Update_Num(money); // số tiền	
	}
	glutPostRedisplay();
}

/// Kết thúc phần xử lý trong shop
// TImer 
void Timer_CloudRain()
{
	Rain[0].Update();
	Rain[1].Update();
	for(int i =0; i < 3; i++)
		Cloud[i].Update();
	glutPostRedisplay();
}
// Cho phép gọi đi gọi lại nhiều lần

void Timer(int value)
{
	Timer_CloudRain();
	thoigianhethong = time(0);
	GrowthStage();
	//cout <<"thoi gian: " <<thoigianhethong <<endl;
	glutTimerFunc(INTERVAL,Timer, 0);
}

// Lựa chọn loại chậu
char* choosePots(int i)
{
	char* temp="";
	switch(i)
	{
		case 0:
		{
			temp = "Images/Arrow.png";
			break;
		}
		case 1:
		{
			temp = "Images/Pot1.png";
			break;
		}
		case 2:
		{
			temp = "Images/Pot2.png";
			break;
		}
		case 3:
		{
			temp = "Images/Pot3.png";
			break;
		}
	}
	return temp;
}
// Lựa chọn loại hoa
char* chooseFlower(int i)
{
	char* temp="";
	switch(i)
	{
		case 0:
		{
			temp = "Images/Germ.png"; // giai đoạn nãy mầm
			break;
		}
		case 1:
		{
			temp = "Images/Fl-A3.png"; // giai đoạn 2 của loại hoa 1
			break;
		}
		case 2:
		{
			temp = "Images/Fl-A4.png"; // giai đoạn trưởng thành của loại 1
			break;
		}
		case 3:
		{
			temp = "Images/Fl-B3.png"; // giai đoạn trưởng thành của loại 2
			break;
		}
		case 4:
		{
			temp = "Images/Fl-B4.png"; // giai đoạn trưởng thành của loại 2
			break;
		}
		case 5:
		{
			temp = "Images/Fl-C4.png";// giai đoạn 2 của loại hoa 3
			break;
		}
		case 6:
		{
			temp = "Images/Fl-C3.png";// giai đoạn trưởng thành của loại 3
			break;
		}
	}
	return temp;
}

void GrowthStage()
{
	for(int i = 0 ; i < 12 ;i++)
	{
		if(flower[i].stage == 1 || flower[i].stage == 2)
		{
			switch(flower[i].type)
			{
				case 1: // cây loại 1
				{
					if(thoigianhethong - flower[i].timeStar == 10) // giai doan 2
					{
						flower[i].Load_Image(chooseFlower(1));
						flower[i].Update();
						flower[i].stage = 2;
					}
					if(thoigianhethong - flower[i].timeStar == 15) // giai doan truong thanh
					{
						flower[i].Load_Image(chooseFlower(2));
						flower[i].Update();
						flower[i].stage = 3;
					}
					glutPostRedisplay();
					break;
				}
				case 2: //cây loại 2
				{
					if(thoigianhethong - flower[i].timeStar == 10) // giai doan 2
					{
						flower[i].Load_Image(chooseFlower(3));
						flower[i].Update();
						flower[i].stage = 2;
					}
					if(thoigianhethong - flower[i].timeStar == 15) // giai doan truong thanh
					{
						flower[i].Load_Image(chooseFlower(4));
						flower[i].Update();
						flower[i].stage = 3;
					}
					glutPostRedisplay();
					break;
				}
				case 3: //cây loại 3
				{
					if(thoigianhethong - flower[i].timeStar == 10) // giai doan 2
					{
						flower[i].Load_Image(chooseFlower(5));
						flower[i].Update();
						flower[i].stage = 2;
					}
					if(thoigianhethong - flower[i].timeStar == 15) // giai doan truong thanh
					{
						flower[i].Load_Image(chooseFlower(6));
						flower[i].Update();
						flower[i].stage = 3;
					}
					glutPostRedisplay();
					break;
				}
			}
		}
		
	}
}