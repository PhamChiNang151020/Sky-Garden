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

//Tùng

using namespace std;
//Kích thước màn hình
#define WIDTH 1280	
#define HEIGHT 720
//Màn load lại sao 15ms
#define INTERVAL 15
// ?? Phong viết cô ơi
#define CLOUD_COUNT 3
//Size của 3 chậu
int xPot1 = 56, yPot1 = 60;
int xPot2 = 58, yPot2 = 57;
int xPot3 = 65, yPot3 = 62;
//Biến vị trí màn hình
int status;
//Biến chậu
int arrowclick = 0;
int potclick  = 0;

// Khai báo struct lưu giá trị của chậu
struct Pot{int x,y,z,c;};
//  vị trí của chậu 1 ở 4 arrow
Pot pot[4] = {pot[0].x = 400           , pot[0].y = xPot1+400, pot[0].z = yPot1 + 450,pot[0].c = 450, 
			  pot[1].x = pot[0].x + 200, pot[1].y = xPot1+600, pot[1].z = yPot1 + 450,pot[1].c = 450,
	          pot[2].x = pot[0].x + 400, pot[2].y = xPot1+800, pot[2].z = yPot1 + 450,pot[2].c = 450,
	          pot[3].x = pot[0].x + 600, pot[3].y = xPot1+1000, pot[3].z = yPot1 + 450,pot[3].c = 450};


					// Trái Phải dưới trên 
Rect	Rct_Background = {0, 1280, 720,0}, //Màn hình menu
		Rct_Background2 = {0, 1280, 720,0}, //Màn hình ingame(chính)
		Rct_HelpScreen = {0, 1280, 720,0}, // Màn hình help
		Rct_ShopScreen = {0, 1280, 720,0}, //Màn hình shop
		//Cửa sổ exit
		Rct_Exit_YesNo={292,705+292,430+135,135};

Rect	// button trong màn hình login
		Rct_btn_NewGame={150,250+150,75+475,475}, //250x75
		Rct_btn_Continue={150,250+150,75+575,575},
		Rct_btn_Help={880,250+880,75+475,475},
		Rct_btn_Exit={880,250+880,75+575,575},
		// btn trở về, mua
		Rct_btn_Buy={990,205+990,75+605,605},
		Rct_btn_Back ={20,50+20,75+20,20},
		//cloud filter 
		filter_lock1={270,810+270,180,0}, //Mây lock
		filter_lock2={270,810+270,180+180,180}, // Mây lock
		//btn bên phải
		Rct_btn_Shop={1170,81+1170,76+100,100},
		Rct_btn_List={1170,76+1170,79+190,190},
		Rct_btn_Bag={1170,85+1170,73+280,280},
		//btn bên trái
		Rct_btn_Water_Bottle={30,77+30,71+100,100}, // Btn Bồn Nước
		Rct_btn_Harvest={45,64+45,67+195,195}, // Btn Thu Hoạch
		Rct_btn_Shovel={45,62+45,63+290,290}, // Btn Xẻng
		// Khung chứa chậu, hoa, trang trí
		Rct_label_Container={360,675+360,85+600,600},
		// khung chứa nhiệm vụ
		Rct_label_Mission = {400,506+400,604 +67,67};
Rect    //icon
		icon_avt={400,54+400,35+640,640},
		icon_star={400,30+400,29+608,608},
		//btn mũi tên (Nơi đặt chậu hoa)
		Rct_btn_Arrow ={pot[0].x,pot[0].y,pot[0].z,pot[0].c},
		Rct_btn_Arrow1={pot[1].x,pot[1].y,pot[1].z,pot[1].c},
		Rct_btn_Arrow2={pot[2].x,pot[2].y,pot[2].z,pot[2].c},
		Rct_btn_Arrow3={pot[3].x,pot[3].y,pot[3].z,pot[3].c},
		// chau hoa trong container
		Rct_pot_Type1 = {600,xPot1+600,yPot1 + 612,612}, // chậu bạc
		Rct_pot_Type2 = {700,xPot2+700,yPot2 + 615,615}, // chậu vàng
		Rct_pot_Type3 = {800,xPot3+800,yPot3 + 612,612}, // chậu đỏ
	// hoa và hạt
		Rct_seed = {}, // hạt
		Rct_germ = {}, // mầm
		Rct_fl_A3 = {}, // hoa A giai đoạn 3 
		Rct_fl_A4 = {}, // hoa A giai đoạn 4
		Rct_fl_B3 = {}, // hoa B giai đoạn 3
		Rct_fl_B4 = {}, // hoa B giai đoạn 4
		Rct_fl_C3 = {}, // hoa C giai đoạn 3
		Rct_fl_C4 = {} // hoa C giai đoạn 4
		;

Image	Img_Background, Img_Background2, Img_HelpScreen, Img_ShopScreen, // nền
		Img_filter_lock, //cloud filter lock img
		Img_NewGame, Img_Continue, Img_Help, Img_Exit, // bg btn img
		Img_Exit_YesNo, //Cửa sổ exit
		Img_Buy, Img_Back, //bt back, buy
		Img_Shop, Img_List,Img_Bag, //ảnh btn phải
		Img_Water_bottle, Img_Harvest, Img_Shovel, //ảnh btn trái
		Img_Pot1,Img_Pot2,Img_Pot3, //ảnh của 3 loại chậu
		//Pot1 = chậu bạc = type1
		//Pot2 = chậu vàng = type2
		//Pot3 = chậu đỏ = type3
	Img_seed , // ảnh hạt
	Img_germ , // ảnh mầm
	Img_fl_A3 , // ảnh hoa A giai đoạn 3 
	Img_fl_A4 , // ảnh hoa A giai đoạn 4
	Img_fl_B3 , // ảnh hoa B giai đoạn 3
	Img_fl_B4 , // ảnh hoa B giai đoạn 4
	Img_fl_C3 , // ảnh hoa C giai đoạn 3
	Img_fl_C4, // ảnh hoa C giai đoạn 4
		Img_Container, //ảnh của label chứa chậu, hoa, trang trí
		Img_Arrow, //ảnh mũi tên
		Img_Mission; // ảnh nhiệm vụ
		//icon avt
Image	Img_icon_star, Img_icon_avt,
		Img_tam;


// khai báo
void Init_Menu();
void Init_InGame();
void Exit();
void display();
void mouseClick_back(int button , int state, int x, int y);
void mouseClick_back_ScreenGame(int button , int state, int x, int y);
void mouseClick_back_display(int button , int state, int x, int y);
void mouseClick(int button , int state, int x, int y);
void container_buttonLRB();
void Mission();
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
	Load_Texture_Swap(&Img_Exit_YesNo,"Images/Exit_YN.png");
	//Load screenHelp
	Load_Texture_Swap(&Img_HelpScreen,"Images/bg3-Help.png");
	//Load screenStore
	Load_Texture_Swap(&Img_ShopScreen,"Images/bg4-Shop.png");
	//Load Bt back
	Load_Texture_Swap(&Img_Back,"Images/btn-Back.png");
	//load lớp phủ
	Load_Texture_Swap(&Img_filter_lock,"Images/filter-lock.png");
	//Load button Right
	Load_Texture_Swap(&Img_Shop,"Images/btn-Shop.png");
	Load_Texture_Swap(&Img_List,"Images/btn-List.png");
	Load_Texture_Swap(&Img_Bag,"Images/btn-Bag.png");
	//Load button Left
	Load_Texture_Swap(&Img_Water_bottle,"Images/btn-Water-Bottle.png");
	Load_Texture_Swap(&Img_Harvest,"Images/btn-Harvest.png");
	Load_Texture_Swap(&Img_Shovel,"Images/btn-Shovel.png");
	//Load chậu trong container
	Load_Texture_Swap(&Img_Pot1,"Images/Pot1.png");
	Load_Texture_Swap(&Img_Pot2,"Images/Pot2.png");
	Load_Texture_Swap(&Img_Pot3,"Images/Pot3.png");
	//load hạt giống
	Load_Texture_Swap(&Img_seed,"Images/Seed.png");
	//load mầm
	Load_Texture_Swap(&Img_germ,"Images/Germ.png");
	//load hoa
	Load_Texture_Swap(&Img_fl_A3,"Images/Fl-A3.png");
	Load_Texture_Swap(&Img_fl_A4,"Images/Fl-A4.png");
	Load_Texture_Swap(&Img_fl_B3,"Images/Fl-B3.png");
	Load_Texture_Swap(&Img_fl_B4,"Images/Fl-B4.png");
	Load_Texture_Swap(&Img_fl_C3,"Images/Fl-C3.png");
	Load_Texture_Swap(&Img_fl_C4,"Images/Fl-C4.png");
	// Load ô chứa - container
	Load_Texture_Swap(&Img_Container,"Images/Container.png");
	//Load icon
	Load_Texture_Swap(&Img_icon_avt,"Images/icon_avt.png");
	Load_Texture_Swap(&Img_icon_star,"Images/icon_star.png");
	//Load_Texture_Swap(&Img_pot_in_taskbar1,"Images/Pot1.png");
	Load_Texture_Swap(&Img_Arrow,"Images/Arrow.png");
	//Load button buy
	Load_Texture_Swap(&Img_Buy,"Images/btn-Buy.png");
	// Load Mission
	Load_Texture_Swap(&Img_Mission,"Images/Mission.png");
}
// Mỗi lần thêm hình thì vẽ khung cho nó
void Init_Menu()
{
	Load_Texture_Swap(&Img_Background,"Images/bg1.png");
	Load_Texture_Swap(&Img_NewGame,"Images/bt-NewGame.png");
	Load_Texture_Swap(&Img_Continue,"Images/bt-Continue.png");
	Load_Texture_Swap(&Img_Help,"Images/bt-Help.png");
	Load_Texture_Swap(&Img_Exit,"Images/bt-Exit.png");
}
void display()
{
	glutSetWindowTitle("SKY GARDEN");
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	//_____________Start___________
	glutMouseFunc(mouseClick);
	Map_Texture(&Img_Background);
	Draw_Rect(&Rct_Background); 
	Map_Texture(&Img_NewGame);
	Draw_Rect(&Rct_btn_NewGame);
	Map_Texture(&Img_Continue);
	Draw_Rect(&Rct_btn_Continue);
	Map_Texture(&Img_Help);
	Draw_Rect(&Rct_btn_Help);
	Map_Texture(&Img_Exit);
	Draw_Rect(&Rct_btn_Exit);
	//_____________End_____________
	glutSwapBuffers();
}
// khi chọn no trong cửa sổ exit
// back xanh lá - chuyển màn hình shop - xử lí click đặt chậu - click mission
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
		cout << "click dat chau\n";
		cout << i;
		arrowclick = i;
		glutDisplayFunc(screenGame1);
		glutPostRedisplay();
		}
	}

	//Rct_pot_Type1 = {600,xPot1+600,yPot1 + 612,612}, // chậu bạc
		if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && x >= 600 && x <= 660 && y >= 606 && y <= 676 )
		{
			potclick = 1;
			glutDisplayFunc(screenGame2);
		}
	//Rct_pot_Type2 = {700,xPot2+700,yPot2 + 615,615}, // chậu vàng int xPot2 = 58, yPot2 = 57;
		if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && x >= 700 && x <= 758 && y >= 615  && y <= 672 )
		{
			potclick = 2;
			glutDisplayFunc(screenGame2);
		}
	//Rct_pot_Type3 = {800,xPot3+800,yPot3 + 612,612}, // chậu đỏ int xPot3 = 65, yPot3 = 62;
		if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && x >= 800 && x <= 865 && y >= 612 && y <=  674 )
		{
			potclick = 3;
			glutDisplayFunc(screenGame2);
		}
	
	
	//Load Mission 1170,76+1170,79+190,190
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && x >= 1170 && x <= 76+1170  && y >= 190 && y <=  79+190)
		glutDisplayFunc(Mission);
	glutPostRedisplay();
}
// click newgame
void mouseClick_back_display(int button , int state, int x, int y)
{
	//yes
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && x >= 495 && x <= 495+110  && y >= 380 && y <=  380+110)
		exit(true);
		
	//no
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && x >=687 && x <= 687+110  && y >= 380 && y <=  380+110)
		glutDisplayFunc(display);
}
// back về screen Game(Chính)
void mouseClick_back_ScreenGame(int button , int state, int x, int y)
{	
	//tọa độ nút x trong m
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && x >=850 && x <= 895  && y >= 85 && y <=  138)
		glutDisplayFunc(screenGame);
}
// Hàm mission
void Mission()
{
	glutSetWindowTitle("MISSION");
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	//_____________Start___________
	//Load lại screen game trước để đè mission lên
	Map_Texture(&Img_Background2);
	Draw_Rect(&Rct_Background2); 
	//container_buttonLRB();
	//load container
	Map_Texture(&Img_Container);
	Draw_Rect(&Rct_label_Container);
	//Load icon botton
	Map_Texture(&Img_icon_avt);
	Draw_Rect(&icon_avt);
	Map_Texture(&Img_icon_star);
	Draw_Rect(&icon_star);
	//Load button Right
	Map_Texture(&Img_Shop);
	Draw_Rect(&Rct_btn_Shop);
	Map_Texture(&Img_List);
	Draw_Rect(&Rct_btn_List);
	Map_Texture(&Img_Bag);
	Draw_Rect(&Rct_btn_Bag);
	//Load button Left
	Map_Texture(&Img_Water_bottle);
	Draw_Rect(&Rct_btn_Water_Bottle);
	Map_Texture(&Img_Harvest);
	Draw_Rect(&Rct_btn_Harvest);
	Map_Texture(&Img_Shovel);
	Draw_Rect(&Rct_btn_Shovel);
	//
	// load filter
	Map_Texture(&Img_filter_lock);
	Draw_Rect(&filter_lock1); // lock tầng 1
	Draw_Rect(&filter_lock2); // lock tầng 2
	// cửa sổ nhiệm vụ
	Map_Texture(&Img_Mission);
	Draw_Rect(&Rct_label_Mission);
	
	
	glutMouseFunc(mouseClick_back_ScreenGame);
	//_____________End_____________
	glutSwapBuffers();
}
//exitgame
void Exit()
{
	glutSetWindowTitle("EXIT");
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	//_____________Start___________
	//Load Display
	Map_Texture(&Img_Background);
	Draw_Rect(&Rct_Background); 
	Map_Texture(&Img_NewGame);
	Draw_Rect(&Rct_btn_NewGame);
	Map_Texture(&Img_Continue);
	Draw_Rect(&Rct_btn_Continue);
	Map_Texture(&Img_Help);
	Draw_Rect(&Rct_btn_Help);
	Map_Texture(&Img_Exit);
	Draw_Rect(&Rct_btn_Exit);
	//Exit
	Map_Texture(&Img_Exit_YesNo);
	Draw_Rect(&Rct_Exit_YesNo); 

	glutMouseFunc(mouseClick_back_display);

	//_____________End_____________
	glutSwapBuffers();
}
//sử dụng chuột trong hàm menu (display)
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
		glutDisplayFunc(Exit);

	//_____________End_____________
	glutPostRedisplay();
}
//sử dụng button cho screen
void container_buttonLRB()
{
	//load container
	Map_Texture(&Img_Container);
	Draw_Rect(&Rct_label_Container);
	//Load icon botton
	Map_Texture(&Img_icon_avt);
	Draw_Rect(&icon_avt);
	Map_Texture(&Img_icon_star);
	Draw_Rect(&icon_star);
	//Load button Right
	Map_Texture(&Img_Shop);
	Draw_Rect(&Rct_btn_Shop);
	Map_Texture(&Img_List);
	Draw_Rect(&Rct_btn_List);
	Map_Texture(&Img_Bag);
	Draw_Rect(&Rct_btn_Bag);
	//Load button Left
	Map_Texture(&Img_Water_bottle);
	Draw_Rect(&Rct_btn_Water_Bottle);
	Map_Texture(&Img_Harvest);
	Draw_Rect(&Rct_btn_Harvest);
	Map_Texture(&Img_Shovel);
	Draw_Rect(&Rct_btn_Shovel);
}
// màn hiện mũi tên
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
	Map_Texture(&Img_Back);
	Draw_Rect(&Rct_btn_Back);

	//container_buttonLRB();
	//load container
	Map_Texture(&Img_Container);
	Draw_Rect(&Rct_label_Container);
	//Load icon botton
	Map_Texture(&Img_icon_avt);
	Draw_Rect(&icon_avt);
	Map_Texture(&Img_icon_star);
	Draw_Rect(&icon_star);
	//Load button Right
	Map_Texture(&Img_Shop);
	Draw_Rect(&Rct_btn_Shop);
	Map_Texture(&Img_List);
	Draw_Rect(&Rct_btn_List);
	Map_Texture(&Img_Bag);
	Draw_Rect(&Rct_btn_Bag);
	//Load button Left
	Map_Texture(&Img_Water_bottle);
	Draw_Rect(&Rct_btn_Water_Bottle);
	Map_Texture(&Img_Harvest);
	Draw_Rect(&Rct_btn_Harvest);
	Map_Texture(&Img_Shovel);
	Draw_Rect(&Rct_btn_Shovel);
	//
	Map_Texture(&Img_Arrow);
	Draw_Rect(&Rct_btn_Arrow);
	Draw_Rect(&Rct_btn_Arrow1);
	Draw_Rect(&Rct_btn_Arrow2);
	Draw_Rect(&Rct_btn_Arrow3);

	//Load Mission
	/*Map_Texture(&Img_Mission);
	Draw_Rect(&Mission);*/

	//Chuyển màn sang shop
	glutMouseFunc(mouseClick_back);
	
	
	//_____________End_____________
	glutSwapBuffers();
}
// màn hiện container
void screenGame1()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	status = 0;
	cout << arrowclick;
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
	Map_Texture(&Img_Back);
	Draw_Rect(&Rct_btn_Back);
	
	Map_Texture(&Img_Container);
	Draw_Rect(&Rct_label_Container);
	//Load chau hoa
	Map_Texture(&Img_Arrow);
	Draw_Rect(&Rct_btn_Arrow);
	Map_Texture(&Img_Arrow);
	Draw_Rect(&Rct_btn_Arrow1);
	Map_Texture(&Img_Arrow);
	Draw_Rect(&Rct_btn_Arrow2);
	Map_Texture(&Img_Arrow);
	Draw_Rect(&Rct_btn_Arrow3);

	//Load icon botton
	Map_Texture(&Img_icon_avt);
	Draw_Rect(&icon_avt);
	Map_Texture(&Img_icon_star);
	Draw_Rect(&icon_star);
	// load btn-left(water-harvest-)
	Map_Texture(&Img_Water_bottle);
	Draw_Rect(&Rct_btn_Water_Bottle);
	Map_Texture(&Img_Harvest);
	Draw_Rect(&Rct_btn_Harvest);
	Map_Texture(&Img_Shovel);
	Draw_Rect(&Rct_btn_Shovel);
	// load btn-right(shop - bag - list)
	Map_Texture(&Img_Shop);
	Draw_Rect(&Rct_btn_Shop);
	Map_Texture(&Img_Bag);
	Draw_Rect(&Rct_btn_Bag);
	Map_Texture(&Img_List);
	Draw_Rect(&Rct_btn_List);

	//Load loại chậu
	
	Map_Texture(&Img_Pot1);
	Draw_Rect(&Rct_pot_Type1);
	Map_Texture(&Img_Pot2);
	Draw_Rect(&Rct_pot_Type2);
	Map_Texture(&Img_Pot3);
	Draw_Rect(&Rct_pot_Type3);

	
	
	glutMouseFunc(mouseClick_back);
	glutTimerFunc(0,Timer,0);
	//_____________End_____________
	glutSwapBuffers();
}
// màn thay chậu vào mũi tên
void screenGame2()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	//_____________Start_____________
	cout << arrowclick << endl;
	//Load bg
	//Load_Texture_Swap(&Img_Background2,"Images/bg2.png");
	Map_Texture(&Img_Background2);
	Draw_Rect(&Rct_Background2);
	
	// load lớp phủ
	Map_Texture(&Img_filter_lock);
	Draw_Rect(&filter_lock1);
	Draw_Rect(&filter_lock2);

	//Load button Left
	Map_Texture(&Img_Water_bottle);
	Draw_Rect(&Rct_btn_Water_Bottle);
	Map_Texture(&Img_Harvest);
	Draw_Rect(&Rct_btn_Harvest);
	Map_Texture(&Img_Shovel);
	Draw_Rect(&Rct_btn_Shovel);

	//Load button back
	Map_Texture(&Img_Back);
	Draw_Rect(&Rct_btn_Back);
	//goi bt back
	if(potclick == 1)
	{
		Img_tam = Img_Pot1;
	}
	else if(potclick == 2)
	{
		Img_tam = Img_Pot2;
	}
	else 
	{
		Img_tam = Img_Pot3;
	}
	//Load chau hoa
	if(arrowclick == 0 ){

	Map_Texture(&Img_tam);
	Draw_Rect(&Rct_btn_Arrow);
	
	Map_Texture(&Img_Arrow);
	Draw_Rect(&Rct_btn_Arrow1);
	
	Map_Texture(&Img_Arrow);
	Draw_Rect(&Rct_btn_Arrow2);
	
	Map_Texture(&Img_Arrow);
	Draw_Rect(&Rct_btn_Arrow3);

	}
	if(arrowclick == 1)
	{
		Map_Texture(&Img_Arrow);
		Draw_Rect(&Rct_btn_Arrow);

		Map_Texture(&Img_tam);
		Draw_Rect(&Rct_btn_Arrow1);

		Map_Texture(&Img_Arrow);
		Draw_Rect(&Rct_btn_Arrow2);

		Map_Texture(&Img_Arrow);
		Draw_Rect(&Rct_btn_Arrow3);
	}
	if(arrowclick == 2)
	{
		Map_Texture(&Img_Arrow);
		Draw_Rect(&Rct_btn_Arrow);

		Map_Texture(&Img_Arrow);
		Draw_Rect(&Rct_btn_Arrow1);

		Map_Texture(&Img_tam);
		Draw_Rect(&Rct_btn_Arrow2);

		Map_Texture(&Img_Arrow);
		Draw_Rect(&Rct_btn_Arrow3);
	}
	if(arrowclick == 3)
	{
		Map_Texture(&Img_Arrow);
		Draw_Rect(&Rct_btn_Arrow);

		Map_Texture(&Img_Arrow);
		Draw_Rect(&Rct_btn_Arrow1);

		Map_Texture(&Img_Arrow);
		Draw_Rect(&Rct_btn_Arrow2);

		Map_Texture(&Img_tam);
		Draw_Rect(&Rct_btn_Arrow3);
	}
	
	//Load container
	Map_Texture(&Img_Container);
	Draw_Rect(&Rct_label_Container);
	Map_Texture(&Img_Pot1);
	Draw_Rect(&Rct_pot_Type1);
	Map_Texture(&Img_Pot2);
	Draw_Rect(&Rct_pot_Type2);
	Map_Texture(&Img_Pot3);
	Draw_Rect(&Rct_pot_Type3);
	// store
	Map_Texture(&Img_Shop);
	Draw_Rect(&Rct_btn_Shop);
	//Load bag
	Map_Texture(&Img_Bag);
	Draw_Rect(&Rct_btn_Bag);
	//Load quest
	Map_Texture(&Img_List);
	Draw_Rect(&Rct_btn_List);
	//
	//Load icon botton
	Map_Texture(&Img_icon_avt);
	Draw_Rect(&icon_avt);
	Map_Texture(&Img_icon_star);
	Draw_Rect(&icon_star);
	//Load store
	glutMouseFunc(mouseClick_back);
	glutTimerFunc(0,Timer,0);
	//_____________End_____________
	glutSwapBuffers();
}
// màn gì nhìn tên là biết
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

	Map_Texture(&Img_Back);
	Draw_Rect(&Rct_btn_Back);
	//_____________End_____________
	glutSwapBuffers();
}
// chú thích giống màn screenhelp
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
	Map_Texture(&Img_Buy);
	Draw_Rect(&Rct_btn_Buy); 

	//_____________End_____________
	glutSwapBuffers();
}