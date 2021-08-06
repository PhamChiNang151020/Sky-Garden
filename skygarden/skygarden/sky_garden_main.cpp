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
#include <gl\gl_texture.h>

//#include "../Lib/loadpng.h"
//#include "../Lib/process_image.h"
//#include "../Lib/gl_texture.h"

using namespace std;


#define WIDTH 1280	
#define HEIGHT 720
// Dùng để gọi lại
#define INTERVAL 15

#define CLOUD_COUNT 3
int xPot = 64, yPot = 58;
int status;
int chau = 0;

// Khai báo struct lưu giá trị của chậu
struct Pot{int x,y,z,c;};
Pot pot[4] = {pot[0].x = 400, pot[0].y = xPot+400, pot[0].z = yPot + 450,pot[0].c = 450,
	pot[1].x = pot[0].x + 200, pot[1].y = xPot+600, pot[1].z = yPot + 450,pot[1].c = 450,
	pot[2].x = pot[0].x + 400, pot[2].y = xPot+800, pot[2].z = yPot + 450,pot[2].c = 450,
	pot[3].x = pot[0].x + 600, pot[3].y = xPot+1000, pot[3].z = yPot + 450,pot[3].c = 450};


// Trái Phải dưới trên
Rect	Rct_Background = {0, 1280, 720,0},
		Rct_Background2 = {0, 1280, 720,0},
		Rct_HelpScreen = {0, 1280, 720,0},
		Rct_ShopScreen = {0, 1280, 720,0},
		Rct_Ground = {200 , 300+200, 50+200 ,200},
		//Exit display
		Exit_YN={292,705+292,430+135,135},
		bt1 = {200,300+200,50+400,400};

Rect	// bt screen 1
		BT_1={150,250+150,75+475,475}, //250x75
		BT_2={150,250+150,75+575,575},
		BT_3={880,250+880,75+475,475},
		BT_4={880,250+880,75+575,575},
		// bt back, buy
		BT_Buy={990,205+990,75+605,605},
		BT_back ={20,50+20,75+20,20},
		// filter lock
		filter_lock1={270,810+270,180,0},
		filter_lock2={270,810+270,180+180,180},
		//button-Right
		BT_Store={1170,81+1170,76+100,100},
		BT_List={1170,76+1170,79+190,190},
		BT_Bag={1170,85+1170,73+280,280},
		//button-Left
		BT_Water_bottle={30,77+30,71+100,100},
		BT_Harvest={45,64+45,67+195,195},
		BT_Xeng={45,62+45,63+290,290},
		//Load Container
		Container={360,675+360,85+600,600},
		// Load Mission
		Mission = {400,506+400,604 +67,67};
Rect    //icon
		icon_avt={400,54+400,35+640,640},
		icon_star={400,30+400,29+608,608},
		Bt_icon_arrow={pot[0].x,pot[0].y,pot[0].z,pot[0].c},
		Bt_icon_arrow1={pot[1].x,pot[1].y,pot[1].z,pot[1].c},
		Bt_icon_arrow2={pot[2].x,pot[2].y,pot[2].z,pot[2].c},
		Bt_icon_arrow3={pot[3].x,pot[3].y,pot[3].z,pot[3].c},
		// chau hoa trong table
		Pot_Tb1 = {600,xPot+600,yPot + 612,612};

Image	Img_Background, Img_Background2, Img_HelpScreen, Img_ShopScreen,
		Img_Ground,
		Img_filter_lock,
		Img_Bt1, Img_Bt2, Img_Bt3, Img_Bt4,
		//Exit display
		Img_Exit_YN,
		//bt back, buy
		Img_Bt_buy,
		Img_Bt_back,
		//img-button-right
		Img_Bt_Store,
		Img_Bt_List,
		Img_Bt_Bag,
		//img-button-right
		Img_Water_bottle, Img_Harvest, Img_Xeng,
		//img-button-bottom
		Img_Pot1,Img_Pot2,Img_Pot3,
		//img-container
		Img_Container,
		//Pot
		Img_icon_arrow,
		Img_pot_in_taskbar1,
		//Img mission
		Img_Mission;

Image	Img_icon_star, Img_icon_avt;


// khai báo
void Init_Menu();
void Init_InGame();
void Init_Exit();
void display();
void mouseClick_back(int button , int state, int x, int y);
void mouseClick_back_ScreenGame(int button , int state, int x, int y);
void mouseClick_back_display(int button , int state, int x, int y);
void mouseClick(int button , int state, int x, int y);
void container_buttonLRB();
void screenGame();
void screenGame1();
void screenGame2();
void screenHelp();
void screenShop();

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

	//gọi icon
	//glutSetIconTitle("ic_skygarden.ico");

	
	init();
	glutDisplayFunc(display);
	glutMouseFunc(mouseClick);
	glutTimerFunc(0,Timer,0);


	glutMainLoop();
	return 0;
}
//InGame
void Init_InGame(){
	//Load bg2
	Load_Texture_Swap(&Img_Background2,"Images/bg2.png");
	//Exit display
	Load_Texture_Swap(&Img_Exit_YN,"Images/Exit_YN.png");
	//Load screenHelp
	Load_Texture_Swap(&Img_HelpScreen,"Images/bg3-help.png");
	//Load screenStore
	Load_Texture_Swap(&Img_ShopScreen,"Images/bg4-Shop.png");
	//Load Bt back
	Load_Texture_Swap(&Img_Bt_back,"Images/bt-back.png");
	//load lớp phủ
	Load_Texture_Swap(&Img_filter_lock,"Images/lopphu.png");
	//Load button Right
	Load_Texture_Swap(&Img_Bt_Store,"Images/bt-store.png");
	Load_Texture_Swap(&Img_Bt_List,"Images/bt-list.png");
	Load_Texture_Swap(&Img_Bt_Bag,"Images/bt-Tui.png");
	//Load button Left
	Load_Texture_Swap(&Img_Water_bottle,"Images/bt-water-bottle.png");
	Load_Texture_Swap(&Img_Harvest,"Images/bt-Thuhoach.png");
	Load_Texture_Swap(&Img_Xeng,"Images/bt-Xeng.png");
	//Load button Bottom
	Load_Texture_Swap(&Img_Pot1,"Images/Pot1.png");
	Load_Texture_Swap(&Img_Pot2,"Images/Pot1.png");
	Load_Texture_Swap(&Img_Pot3,"Images/Pot1.png");
	// Load ô chứa - container
	Load_Texture_Swap(&Img_Container,"Images/Container.png");
	//Load icon
	Load_Texture_Swap(&Img_icon_avt,"Images/icon_avt.png");
	Load_Texture_Swap(&Img_icon_star,"Images/icon_star.png");
	//Load_Texture_Swap(&Img_pot_in_taskbar1,"Images/Pot1.png");
	Load_Texture_Swap(&Img_icon_arrow,"Images/muiten.png");
	//Load button buy
	Load_Texture_Swap(&Img_Bt_buy,"Images/bt-Buy.png");
	// Load Mission
	Load_Texture_Swap(&Img_Mission,"Images/Mission.png");
}
// Mỗi lần thêm hình thì vẽ khung cho nó
void Init_Menu()
{
	Load_Texture_Swap(&Img_Background,"Images/bg1.png");
	Load_Texture_Swap(&Img_Bt1,"Images/bt-NewGame.png");
	Load_Texture_Swap(&Img_Bt2,"Images/bt-Continue.png");
	Load_Texture_Swap(&Img_Bt3,"Images/bt-Help.png");
	Load_Texture_Swap(&Img_Bt4,"Images/bt-Exit.png");
}

void mouseClick_back(int button , int state, int x, int y)
{
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && x >= 20 && x <= 70 && y >= 20  && y <= 95 && status == 0 )
    {
        glutDisplayFunc(display);
    }
	//Trả về màn hình game
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN &&x >= 20 && x <= 70 && y >= 20  && y <= 95 && status == 1 )
		glutDisplayFunc(screenGame);
	//Chuyển qua màn hình shop
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && x >= 1170 && x <= 81+1170 && y >= 100 && y <= 76+100 && status == 0)
		glutDisplayFunc(screenShop);
	//
	for(int i = 0; i < 4;i++)
	{
		if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && x >= pot[i].x && x <= pot[i].y && y >= pot[i].c && y <= pot[i].z && status == 0 )
		{
		//load chau trong table
		cout << "click dat chau";
		cout << i;
		chau = i;
		glutDisplayFunc(screenGame1);
		glutPostRedisplay();
		}
	}
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && x >= 600 && x <= 660 && y >= 606 && y <= 676 )
	{
		glutDisplayFunc(screenGame2);
	}
	glutPostRedisplay();
}
// click newgame
void display()
{
	glutSetWindowTitle("SKY GARDEN");
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	//_____________Start___________
	glutMouseFunc(mouseClick);
	Map_Texture(&Img_Background);
	Draw_Rect(&Rct_Background); 
	Map_Texture(&Img_Bt1);
	Draw_Rect(&BT_1);
	Map_Texture(&Img_Bt2);
	Draw_Rect(&BT_2);
	Map_Texture(&Img_Bt3);
	Draw_Rect(&BT_3);
	Map_Texture(&Img_Bt4);
	Draw_Rect(&BT_4);
	//_____________End_____________
	glutSwapBuffers();
}
void mouseClick_back_display(int button , int state, int x, int y)
{
	//yes
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && x >= 495 && x <= 495+110  && y >= 380 && y <=  380+110)
		exit(true);
		
	//no
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && x >=687 && x <= 687+110  && y >= 380 && y <=  380+110)
		glutDisplayFunc(display);
}
void Init_Exit()
{
	glutSetWindowTitle("EXIT");
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	//_____________Start___________
	//Load Display
	Map_Texture(&Img_Background);
	Draw_Rect(&Rct_Background); 
	Map_Texture(&Img_Bt1);
	Draw_Rect(&BT_1);
	Map_Texture(&Img_Bt2);
	Draw_Rect(&BT_2);
	Map_Texture(&Img_Bt3);
	Draw_Rect(&BT_3);
	Map_Texture(&Img_Bt4);
	Draw_Rect(&BT_4);
	//Exit
	Map_Texture(&Img_Exit_YN);
	Draw_Rect(&Exit_YN); 

	glutMouseFunc(mouseClick_back_display);

	//_____________End_____________
	glutSwapBuffers();
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
		glutDisplayFunc(screenHelp);

	// exit
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && x >= 880 && x <= 1130 && y >= 575 && y <= 650)
		//exit(true);
		glutDisplayFunc(Init_Exit);

	//_____________End_____________
	glutPostRedisplay();
}
//sử dụng button cho screen
void container_buttonLRB()
{
	//load container
	Map_Texture(&Img_Container);
	Draw_Rect(&Container);
	//Load icon botton
	Map_Texture(&Img_icon_avt);
	Draw_Rect(&icon_avt);
	Map_Texture(&Img_icon_star);
	Draw_Rect(&icon_star);
	//Load button Right
	Map_Texture(&Img_Bt_Store);
	Draw_Rect(&BT_Store);
	Map_Texture(&Img_Bt_List);
	Draw_Rect(&BT_List);
	Map_Texture(&Img_Bt_Bag);
	Draw_Rect(&BT_Bag);
	//Load button Left
	Map_Texture(&Img_Water_bottle);
	Draw_Rect(&BT_Water_bottle);
	Map_Texture(&Img_Harvest);
	Draw_Rect(&BT_Harvest);
	Map_Texture(&Img_Xeng);
	Draw_Rect(&BT_Xeng);
}
void screenGame()
{
	glutSetWindowTitle("SKY GARDEN");
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	status = 0;
	//_____________Start_____________
	//Load bg
	Map_Texture(&Img_Background2);
	Draw_Rect(&Rct_Background2); 
	// load filter
	Map_Texture(&Img_filter_lock);
	Draw_Rect(&filter_lock1); // lock tầng 1
	Draw_Rect(&filter_lock2); // lock tầng 2
	//Load button back
	Map_Texture(&Img_Bt_back);
	Draw_Rect(&BT_back);
	container_buttonLRB();
	Map_Texture(&Img_icon_arrow);
	Draw_Rect(&Bt_icon_arrow);
	Draw_Rect(&Bt_icon_arrow1);
	Draw_Rect(&Bt_icon_arrow2);
	Draw_Rect(&Bt_icon_arrow3);

	//Load Mission
	/*Map_Texture(&Img_Mission);
	Draw_Rect(&Mission);*/

	//Chuyển màn sang shop
	glutMouseFunc(mouseClick_back);
	
	
	//_____________End_____________
	glutSwapBuffers();
}
void screenGame1()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	status = 0;
	cout << chau;
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
	
	Map_Texture(&Img_Container);
	Draw_Rect(&Container);
	//Load chau hoa
	Map_Texture(&Img_icon_arrow);
	Draw_Rect(&Bt_icon_arrow);
	Map_Texture(&Img_icon_arrow);
	Draw_Rect(&Bt_icon_arrow1);
	Map_Texture(&Img_icon_arrow);
	Draw_Rect(&Bt_icon_arrow2);
	Map_Texture(&Img_icon_arrow);
	Draw_Rect(&Bt_icon_arrow3);

	//Load icon botton
	Map_Texture(&Img_icon_avt);
	Draw_Rect(&icon_avt);
	Map_Texture(&Img_icon_star);
	Draw_Rect(&icon_star);
	//Load button Left
	Map_Texture(&Img_Water_bottle);
	Draw_Rect(&BT_Water_bottle);
	Map_Texture(&Img_Harvest);
	Draw_Rect(&BT_Harvest);
	Map_Texture(&Img_Xeng);
	Draw_Rect(&BT_Xeng);
	// store
	Map_Texture(&Img_Bt_Store);
	Draw_Rect(&BT_Store);
	//Load bag
	Map_Texture(&Img_Bt_Bag);
	Draw_Rect(&BT_Bag);
	//Load quest
	Map_Texture(&Img_Bt_List);
	Draw_Rect(&BT_List);

	//Load table
	
	Map_Texture(&Img_Pot1);
	Draw_Rect(&Pot_Tb1);
	
	
	glutMouseFunc(mouseClick_back);
	glutTimerFunc(0,Timer,0);
	//_____________End_____________
	glutSwapBuffers();
}
void screenGame2()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	//_____________Start_____________
	cout << chau;
	//Load bg
	Load_Texture_Swap(&Img_Background2,"Images/bg2.png");
	Map_Texture(&Img_Background2);
	Draw_Rect(&Rct_Background2);
	
	// load lớp phủ
	Map_Texture(&Img_filter_lock);
	Draw_Rect(&filter_lock1);
	Draw_Rect(&filter_lock2);

	//Load icon botton
	Map_Texture(&Img_icon_avt);
	Draw_Rect(&icon_avt);
	Map_Texture(&Img_icon_star);
	Draw_Rect(&icon_star);

	//Load button Left
	Map_Texture(&Img_Water_bottle);
	Draw_Rect(&BT_Water_bottle);
	Map_Texture(&Img_Harvest);
	Draw_Rect(&BT_Harvest);
	Map_Texture(&Img_Xeng);
	Draw_Rect(&BT_Xeng);

	//Load button back
	Map_Texture(&Img_Bt_back);
	Draw_Rect(&BT_back);
	//goi bt back
	
	//Load chau hoa
	if(chau == 0 ){

	Map_Texture(&Img_Pot1);
	Draw_Rect(&Bt_icon_arrow);
	
	Map_Texture(&Img_icon_arrow);
	Draw_Rect(&Bt_icon_arrow1);
	
	Map_Texture(&Img_icon_arrow);
	Draw_Rect(&Bt_icon_arrow2);
	
	Map_Texture(&Img_icon_arrow);
	Draw_Rect(&Bt_icon_arrow3);

	}
	if(chau == 1)
	{
		Map_Texture(&Img_icon_arrow);
		Draw_Rect(&Bt_icon_arrow);

		Map_Texture(&Img_Pot1);
		Draw_Rect(&Bt_icon_arrow1);

		Map_Texture(&Img_icon_arrow);
		Draw_Rect(&Bt_icon_arrow2);

		Map_Texture(&Img_icon_arrow);
		Draw_Rect(&Bt_icon_arrow3);
	}
	if(chau == 2)
	{
		Map_Texture(&Img_icon_arrow);
		Draw_Rect(&Bt_icon_arrow);

		Map_Texture(&Img_icon_arrow);
		Draw_Rect(&Bt_icon_arrow1);

		Map_Texture(&Img_Pot1);
		Draw_Rect(&Bt_icon_arrow2);

		Map_Texture(&Img_icon_arrow);
		Draw_Rect(&Bt_icon_arrow3);
	}
	if(chau == 3)
	{
		Map_Texture(&Img_icon_arrow);
		Draw_Rect(&Bt_icon_arrow);

		Map_Texture(&Img_icon_arrow);
		Draw_Rect(&Bt_icon_arrow1);

		Map_Texture(&Img_icon_arrow);
		Draw_Rect(&Bt_icon_arrow2);

		Map_Texture(&Img_Pot1);
		Draw_Rect(&Bt_icon_arrow3);
	}
	
	//Load table
	Map_Texture(&Img_Container);
	Draw_Rect(&Container);
	Map_Texture(&Img_Pot1);
	Draw_Rect(&Pot_Tb1);
	// store
	Map_Texture(&Img_Bt_Store);
	Draw_Rect(&BT_Store);
	//Load bag
	Map_Texture(&Img_Bt_Bag);
	Draw_Rect(&BT_Bag);
	//Load quest
	Map_Texture(&Img_Bt_List);
	Draw_Rect(&BT_List);
	//Load store
	glutMouseFunc(mouseClick_back);
	glutTimerFunc(0,Timer,0);
	//_____________End_____________
	glutSwapBuffers();
}
void screenHelp()
{
	glutSetWindowTitle("HELP");
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	//_____________Start___________
	Map_Texture(&Img_HelpScreen);
	Draw_Rect(&Rct_HelpScreen);
	glutMouseFunc(mouseClick_back);
	//Load button back

	Map_Texture(&Img_Bt_back);
	Draw_Rect(&BT_back);
	//_____________End_____________
	glutSwapBuffers();
}
void screenShop()
{
	glutSetWindowTitle("SHOP");
	status = 1;
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	//_____________Start___________
	Map_Texture(&Img_ShopScreen);
	glutSetIconTitle("");
	Draw_Rect(&Rct_ShopScreen); 
	glutMouseFunc(mouseClick_back);
	//Load button buy
	Map_Texture(&Img_Bt_buy);
	Draw_Rect(&BT_Buy); 

	//_____________End_____________
	glutSwapBuffers();
}