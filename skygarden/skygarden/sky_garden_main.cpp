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
//int arrowclick = 0;
//thứ tự của chậu trong container
int potclick  = 0;
// thứ tự của hoa trên các chậu
int flclick = 0;
// loại hoa đc chọn trên container
int typeflclick = 0;
// Giai đoạn của hạt
struct Stage{int gd;};
Stage stage[12];
// Khai báo struct có 4 giá trị kiểu int
struct Pot{int x,y,z,c,pla;};
// xác định lần click
//đếm lượt click trong 2 lần click
int cacl1 = 0; // count_arrow_click1
int cacl2 = 0; // count_arrow_click1
//đếm số lần gán hình
int map_pic = -1;
//biến XY hiện 
int XV_plant = 0;
// xác nhận đặt chậu
bool  yes_no = false;
// xác nhận đặt hoa
bool  yes_no_Flower = false;
// xác nhận đang đặt hoa vào chậu đã được đặt
bool planting = false;
 int Xsizex = 59, Xsizey = 62, Vsizex = 58, Vsizey = 61;  
//  vị trí của chậu 1 ở 4 arrow
Pot pot[4] = {pot[0].x = 400           , pot[0].y = xPot1+400, pot[0].z = yPot1 + 450,pot[0].c = 450, pot[0].pla = 0,
			  pot[1].x = pot[0].x + 200, pot[1].y = xPot1+600, pot[1].z = yPot1 + 450,pot[1].c = 450, pot[1].pla = 0,
	          pot[2].x = pot[0].x + 400, pot[2].y = xPot1+800, pot[2].z = yPot1 + 450,pot[2].c = 450, pot[2].pla = 0,
	          pot[3].x = pot[0].x + 600, pot[3].y = xPot1+1000, pot[3].z = yPot1 + 450,pot[3].c = 450, pot[3].pla = 0};
Pot fl[4] = {
				fl[0].x = 400          , fl[0].y = xPot1+400,  fl[0].z =  450 + 15,fl[0].c = 450 - yPot1 + 15, fl[0].pla = 0,
				fl[1].x = fl[0].x + 200, fl[1].y = xPot1+600,  fl[1].z =  450 + 15,fl[1].c = 450 - yPot1 + 15, fl[1].pla = 0,
				fl[2].x = fl[0].x + 400, fl[2].y = xPot1+800,  fl[2].z =  450 + 15,fl[2].c = 450 - yPot1 + 15, fl[2].pla = 0,
				fl[3].x = fl[0].x + 600, fl[3].y = xPot1+1000, fl[3].z =  450 + 15,fl[3].c = 450 - yPot1 + 15, fl[3].pla = 0
			};
//thứ tự click
int arrowclick = -1;

//struct mảng ảnh trung gian
struct PicChange{Image img;}; //số thứ tự là số lần gọi hình trung gian gán cho mũi tên 
PicChange IMG_CHANGE[4];
PicChange IMG_FL_ARROW[4];
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
		//btn mũi tên (Nơi đặt hoa)
		Rct_btn_Fl ={fl[0].x,fl[0].y,fl[0].z,fl[0].c},
		Rct_btn_Fl1={fl[1].x,fl[1].y,fl[1].z,fl[1].c},
		Rct_btn_Fl2={fl[2].x,fl[2].y,fl[2].z,fl[2].c},
		Rct_btn_Fl3={fl[3].x,fl[3].y,fl[3].z,fl[3].c},
		// chau hoa trong container
		Rct_pot_Type1 = {600,xPot1+600,yPot1 + 612,612}, // chậu bạc
		Rct_pot_Type2 = {700,xPot2+700,yPot2 + 615,615}, // chậu vàng
		Rct_pot_Type3 = {800,xPot3+800,yPot3 + 612,612}, // chậu đỏ
	// hoa và hạt
	Rct_seed_A = {600,xPot1+600,yPot1 + 612 - 70,612 - 70}, 
	Rct_seed_B = {700,xPot2+700,yPot2 + 615 - 70,615 - 70},
	Rct_seed_C = {800,xPot3+800,yPot3 + 612 - 70,612 - 70},
		Rct_seed = {}, // hạt
		Rct_germ = {}, // mầm
		Rct_fl_A3 = {}, // hoa A giai đoạn 3 
		Rct_fl_A4 = {}, // hoa A giai đoạn 4
		Rct_fl_B3 = {}, // hoa B giai đoạn 3
		Rct_fl_B4 = {}, // hoa B giai đoạn 4
		Rct_fl_C3 = {}, // hoa C giai đoạn 3
		Rct_fl_C4 = {}, // hoa C giai đoạn 4
	// btn xác nhận đặt chậu
	Rct_btn_X = {630 +180 +180 + 90 ,Xsizex + 630 +180 +180 +90,Xsizey + 617, 617},
	Rct_btn_V = {810 +180 +180 ,Vsizex + 810 +180 +180,Vsizey + 616, 616},
	// btn xác nhận đặt chậu
	Rct_btn_X_Fl = {630 +180 +180 + 90 ,Xsizex + 630 +180 +180 +90,Xsizey + 617 - 70, 617 - 70},
	Rct_btn_V_Fl = {810 +180 +180 ,Vsizex + 810 +180 +180,Vsizey + 616 - 70, 616 - 70}
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
	Img_seed_A,
	Img_seed_B,
	Img_seed_C,
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
		//ảnh của btn xác nhận đặt chậu
		Img_X,Img_V,
		Img_tam,Img_flower,Img_stage;
		
		
// khai báo
void Init_Menu();
void Init_InGame();
void Exit();
void display();
void mouseClick_back(int button , int state, int x, int y);
void mouseClick_back_ScreenGame(int button , int state, int x, int y);
void mouseClick_back_display(int button , int state, int x, int y);
void mouseClick(int button , int state, int x, int y);
void Mission();
void changeImg_ArrowTop();
void changeImgYes();
void changeImgNo();
void load_hard_element(); // Xuất những phần tử cứng
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
//khởi tạo game
void Init_InGame(){
	// 3 loại hạt hoa
	Load_Texture_Swap(&Img_seed_A,"Images/Seed-A.png");
	Load_Texture_Swap(&Img_seed_B,"Images/Seed-B.png");
	Load_Texture_Swap(&Img_seed_C,"Images/Seed-C.png");
	//Load X V xác định đặt chậu
	Load_Texture_Swap(&Img_X,"Images/X.png");
	Load_Texture_Swap(&Img_V,"Images/V.png");
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
// màn hình menu
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
		glutDisplayFunc(screenGame1);
	//Chuyển qua màn hình shop
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && x >= 1170 && x <= 81+1170 && y >= 100 && y <= 76+100 && status == 0)
		glutDisplayFunc(screenShop);
	//click lần 1 dùng struct arrowclick[0].x.y.z.c để lưu giá trị click mới thay vào thứ tự chậu 
	for(int i = 0;i < 4;i++)
	{
		if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && x >= pot[i].x && x <= pot[i].y && y >= pot[i].c && y <= pot[i].z 
			&& status == 0 &&  pot[i].pla == 0 && XV_plant != 1 )
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
		if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && x >= 600 && x <= 660 && y >= 606 && y <= 676 
			&& XV_plant != 1 && planting == false )
		{
				potclick = 1;
				map_pic += 1;
			//hiện x v
			XV_plant = 1;
			yes_no = false;
			
			glutDisplayFunc(screenGame2);
		}
	//Rct_pot_Type2 = {700,xPot2+700,yPot2 + 615,615}, // chậu vàng int xPot2 = 58, yPot2 = 57;
		if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && x >= 700 && x <= 758 && y >= 615  && y <= 672 
			&& XV_plant != 1 && planting == false)
		{
				potclick = 2;
				map_pic += 1;
			//hiện x v
			XV_plant = 1; 
			yes_no = false;
	
			glutDisplayFunc(screenGame2);
		}
	//Rct_pot_Type3 = {800,xPot3+800,yPot3 + 612,612}, // chậu đỏ int xPot3 = 65, yPot3 = 62;
		if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && x >= 800 && x <= 865 && y >= 612 && y <=  674  
			&& XV_plant != 1 && planting == false)
		{
				potclick = 3;
				map_pic += 1;
			//hiện x v
			XV_plant = 1;
			yes_no = false;
			
			glutDisplayFunc(screenGame2);
		}

	//Rct_btn_X = {630 +180 +180 + 90 ,Xsizex + 630 +180 +180 +90,Xsizey + 617, 617},
	
		if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && x >= 630 +180 +180 + 90 
			&& x <= Xsizex + 630 +180 +180 +90 && y >= 617 && y <=  Xsizey + 617  && XV_plant != 0 && planting == false)
		{
			//hiện x v
			XV_plant = 0;
			//đặt chậu
			yes_no = false;
			glutDisplayFunc(screenGame2);
		}
	// _Y Rct_btn_V = {810 +180 +180 ,Vsizex + 810 +180 +180,Vsizey + 616, 616}
		if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && x >= 810 +180 +180 
			&& x <= Vsizex + 810 +180 +180 && y >= 616 && y <=  Vsizey + 616  && XV_plant != 0 && planting == false)
		{
			//hiện x v
			XV_plant = 0;
			//đặt chậu
			yes_no = true;
			glutDisplayFunc(screenGame2);
		}
	//click lần 2 dùng struct arrowclick[1].x.y.z.c để kiểu soát hoa đặt vào chậu thứ tự là x,y,z,c
		// chưa viết
		for(int i = 0;i < 4;i++)
		{
			if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && x >= fl[i].x && x <= fl[i].y && y >= fl[i].c && y <= fl[i].z 
									      && status == 0 &&  pot[i].pla == 1 && XV_plant != 1 && planting == false )
			{
			//load chau trong table
			cout << "click dat hat\n";
			cout << i;
			flclick = i;
			planting = true;
			//gd phat trien -> hàm chạy thời gian
			stage[i].gd = 0;

			glutDisplayFunc(screenGame1);
			glutPostRedisplay();
			}
		}
		//Rct_seed_A = {600,56+600,60 + 612 - 70,612 - 70},
		if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && x >= 600 && x <= 56+600 && y >= 612 - 70 && y <= 60 + 612 - 70 
			&& XV_plant != 1 && planting == true )
		{

				typeflclick = 1;
				//map_pic += 1;
			//hiện x v
			XV_plant = 1;
			yes_no_Flower = false;
			
			glutDisplayFunc(screenGame2);
		}
		//Rct_seed_B = {700,58+700,57 + 615 - 70,615 - 70},
		if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && x >= 700 && x <= 758 && y >= 615 - 70  && y <= 57 + 615 - 70 
			&& XV_plant != 1 && planting == true)
		{
				typeflclick = 2;
				//map_pic += 1;
			//hiện x v
			XV_plant = 1; 
			yes_no_Flower = false;
	
			glutDisplayFunc(screenGame2);
		}
		//Rct_seed_C = {800,65+800,62 + 612 - 70,612 - 70},
		if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && x >= 800 && x <= 865 && y >= 612 - 70 && y <=  62 + 612 - 70
			&& XV_plant != 1 && planting == true)
		{
				typeflclick = 3;
				//map_pic += 1;
			//hiện x v 1 = hiện
			XV_plant = 1;
			yes_no_Flower = false;
			
			glutDisplayFunc(screenGame2);
		}

		//Rct_btn_X = {630 +180 +180 + 90 ,Xsizex + 630 +180 +180 +90,Xsizey + 617, 617},
		if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && x >= 630 +180 +180 + 90 
			&& x <= Xsizex + 630 +180 +180 +90  && y >= 617 -70 && y <=  Xsizey + 617  -70 && XV_plant != 0 && planting == true)
		{
			//hiện x v
			XV_plant = 0;
			//đặt chậu
			yes_no_Flower = false;
			planting = false;
			glutDisplayFunc(screenGame2);
		}
		// _V Rct_btn_V = {810 +180 +180 ,Vsizex + 810 +180 +180,Vsizey + 616, 616}
		if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && x >= 810 +180 +180 
			&& x <= Vsizex + 810 +180 +180 && y >= 616 -70 && y <=  Vsizey + 616 -70  && XV_plant != 0 && planting == true)
		{
			//hiện x v
			XV_plant = 0;
			//đặt chậu
			yes_no_Flower = true;
			planting = false;
			glutDisplayFunc(screenGame2);
		}
	//Load Mission 1170,76+1170,79+190,190
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && x >= 1170 && x <= 76+1170  && y >= 190 && y <=  79+190)
		glutDisplayFunc(Mission);
	glutPostRedisplay();
}
// show label exit
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
		glutDisplayFunc(screenGame1);
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
//sử dụng chuột trong hàm menu (display) newgame continue help exit
void mouseClick(int button , int state, int x, int y)
{
	//NEW GAME
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && x >=150 && x <= 400  && y >= 475 && y <=  550)
	{
		typeflclick = 0;
		potclick  = 0;
		cacl1 = 0;
		cacl2 = 0;
		map_pic = -1;
		XV_plant = 0;
		yes_no = false;
		for(int i = 0;i < 4;i++)
		{
			pot[i].pla = 0;
			fl[i].pla = 0;
		}
		arrowclick = -1;
		planting = false;
		yes_no_Flower = false;
		flclick = 0;
		glutDisplayFunc(screenGame);
	}

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
//bg2 filter btn-back icon-btn(avt-star)  load btn-left(water-harvest-) load btn-right(shop - bag - list)
void load_hard_element() 
{
	//Load bg
	Map_Texture(&Img_Background2);
	Draw_Rect(&Rct_Background2);
	// load lớp phủ
	/*Map_Texture(&Img_filter_lock);
	Draw_Rect(&filter_lock1);
	Draw_Rect(&filter_lock2);*/
	//Load button back
	Map_Texture(&Img_Back);
	Draw_Rect(&Rct_btn_Back);
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

}
// màn hiện mũi tên
void screenGame()
{
	glutSetWindowTitle("SKY GARDEN");
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	status = 0;
	//_____________Start_____________
	//bg2 filter btn-back icon-btn(avt-star)  load btn-left(water-harvest-) load btn-right(shop - bag - list)
	load_hard_element();
	// mũi tên
	Map_Texture(&Img_Arrow);
	Draw_Rect(&Rct_btn_Arrow);
	Draw_Rect(&Rct_btn_Arrow1);
	Draw_Rect(&Rct_btn_Arrow2);
	Draw_Rect(&Rct_btn_Arrow3);
	// chích hoa
	/*Draw_Rect(&Rct_btn_Fl);
	Draw_Rect(&Rct_btn_Fl1);
	Draw_Rect(&Rct_btn_Fl2);
	Draw_Rect(&Rct_btn_Fl3);*/
	//load container
	Map_Texture(&Img_Container);
	Draw_Rect(&Rct_label_Container);
	//Load Mission
	/*Map_Texture(&Img_Mission);
	Draw_Rect(&Mission);*/

	//Chuyển màn sang shop
	glutMouseFunc(mouseClick_back);
	
	
	//_____________End_____________
	glutSwapBuffers();
}
// Gán hình lên mũi tên đươc chọc trên chậu nếu yes_no_Flower = true;
void changeImg_ArrowTop()
{
	Img_flower = Img_seed;
	if(flclick == 0){
			//mũi tên trên chậu
			Map_Texture(&Img_flower);
			Draw_Rect(&Rct_btn_Fl);
			IMG_FL_ARROW[0].img = Img_flower;
			fl[0].pla = 1;
				if( fl[1].pla == 1 )
				{
					//mũi tên trên chậu
			Map_Texture(&IMG_FL_ARROW[1].img);
			Draw_Rect(&Rct_btn_Fl1);
					
				}
				if( fl[2].pla == 1 )
				{
					//mũi tên trên chậu
			Map_Texture(&IMG_FL_ARROW[2].img);
			Draw_Rect(&Rct_btn_Fl2);
					
				}
				if( fl[3].pla == 1 )
				{
					//mũi tên trên chậu
			Map_Texture(&IMG_FL_ARROW[3].img);
			Draw_Rect(&Rct_btn_Fl3);
					
				}
	}
	if(flclick == 1)
	{
				
				//mũi tên trên chậu
			Map_Texture(&Img_flower);
			Draw_Rect(&Rct_btn_Fl1);
				IMG_FL_ARROW[1].img = Img_flower;
				fl[1].pla = 1;
					if( fl[0].pla == 1 )
					{
						//mũi tên trên chậu
			Map_Texture(&IMG_FL_ARROW[0].img);
			Draw_Rect(&Rct_btn_Fl);
						
					}
					if( fl[2].pla == 1 )
					{
						//mũi tên trên chậu
			Map_Texture(&IMG_FL_ARROW[2].img);
			Draw_Rect(&Rct_btn_Fl2);
						
					}
					if( fl[3].pla == 1 )
					{
						//mũi tên trên chậu
			Map_Texture(&IMG_FL_ARROW[3].img);
			Draw_Rect(&Rct_btn_Fl3);
					
					}

	}
	if(flclick == 2)
	{

		//mũi tên trên chậu
			Map_Texture(&Img_flower);
			Draw_Rect(&Rct_btn_Fl2);
		IMG_FL_ARROW[2].img = Img_flower;
		fl[2].pla = 1;
			if( fl[0].pla == 1 )
			{
				//mũi tên trên chậu
			Map_Texture(&IMG_FL_ARROW[0].img);
			Draw_Rect(&Rct_btn_Fl);
			}
			if( fl[1].pla == 1 )
			{
				//mũi tên trên chậu
			Map_Texture(&IMG_FL_ARROW[1].img);
			Draw_Rect(&Rct_btn_Fl1);
				
			}
	
			if( fl[3].pla == 1 )
			{
				//mũi tên trên chậu
			Map_Texture(&IMG_FL_ARROW[3].img);
			Draw_Rect(&Rct_btn_Fl3);
			
			}
		
	}
	if(flclick == 3)
	{
			
			//mũi tên trên chậu
			Map_Texture(&Img_flower);
			Draw_Rect(&Rct_btn_Fl3);
			IMG_FL_ARROW[3].img = Img_seed;
			fl[3].pla = 1;

				if( fl[0].pla == 1 )
				{
					//mũi tên trên chậu
			Map_Texture(&IMG_FL_ARROW[0].img);
			Draw_Rect(&Rct_btn_Fl);
					
				}
				if( fl[1].pla == 1 )
				{
					//mũi tên trên chậu
			Map_Texture(&IMG_FL_ARROW[1].img);
			Draw_Rect(&Rct_btn_Fl1);
				
				}
				if( fl[2].pla == 1 )
				{
					//mũi tên trên chậu
			Map_Texture(&IMG_FL_ARROW[2].img);
			Draw_Rect(&Rct_btn_Fl2);
				}
		}
	//yes_no_Flower = false;
}
//
void changeImgYes()
{
	// Img_flower là biến tạm để đặt arrow trên chậu
	Img_flower = Img_Arrow;
	// Img_stage là biến tạm cho từng giai đoạn 
				if(potclick == 1)
				{
					Img_tam = Img_Pot1;
				}
				else if(potclick == 2)
				{
					Img_tam = Img_Pot2;
				}
				else if(potclick == 3)
				{
					Img_tam = Img_Pot3;
				}	
		
	//Load chau hoa
	if(arrowclick == 0){
			//mũi tên trên chậu
			Map_Texture(&Img_flower);
			Draw_Rect(&Rct_btn_Fl);

			Map_Texture(&Img_tam);
			Draw_Rect(&Rct_btn_Arrow);
	
			Map_Texture(&Img_Arrow);
			Draw_Rect(&Rct_btn_Arrow1);
	
			Map_Texture(&Img_Arrow);
			Draw_Rect(&Rct_btn_Arrow2);
	
			Map_Texture(&Img_Arrow);
			Draw_Rect(&Rct_btn_Arrow3);

			//test
				//	Map_Texture(&Img_Arrow);
				//	Draw_Rect(&Rct_btn_Fl);
			IMG_CHANGE[0].img = Img_tam;
			pot[0].pla = 1;
				if( pot[1].pla == 1 )
				{
					//mũi tên trên chậu
			Map_Texture(&Img_flower);
			Draw_Rect(&Rct_btn_Fl1);
					Map_Texture(&IMG_CHANGE[1].img);
					Draw_Rect(&Rct_btn_Arrow1);
				}
				if( pot[2].pla == 1 )
				{
					//mũi tên trên chậu
			Map_Texture(&Img_flower);
			Draw_Rect(&Rct_btn_Fl2);
					Map_Texture(&IMG_CHANGE[2].img);
					Draw_Rect(&Rct_btn_Arrow2);
				}
				if( pot[3].pla == 1 )
				{
					//mũi tên trên chậu
			Map_Texture(&Img_flower);
			Draw_Rect(&Rct_btn_Fl3);
					Map_Texture(&IMG_CHANGE[3].img);
					Draw_Rect(&Rct_btn_Arrow3);
				}
	}
	if(arrowclick == 1)
	{
				Map_Texture(&Img_Arrow);
				Draw_Rect(&Rct_btn_Arrow);

				//mũi tên trên chậu
			Map_Texture(&Img_flower);
			Draw_Rect(&Rct_btn_Fl1);

				Map_Texture(&Img_tam);
				Draw_Rect(&Rct_btn_Arrow1);

				Map_Texture(&Img_Arrow);
				Draw_Rect(&Rct_btn_Arrow2);

				Map_Texture(&Img_Arrow);
				Draw_Rect(&Rct_btn_Arrow3);
				IMG_CHANGE[1].img = Img_tam;
				pot[1].pla = 1;
					if( pot[0].pla == 1 )
					{
						//mũi tên trên chậu
			Map_Texture(&Img_flower);
			Draw_Rect(&Rct_btn_Fl);
						Map_Texture(&IMG_CHANGE[0].img);
						Draw_Rect(&Rct_btn_Arrow);
					}
					if( pot[2].pla == 1 )
					{
						//mũi tên trên chậu
			Map_Texture(&Img_flower);
			Draw_Rect(&Rct_btn_Fl2);
						Map_Texture(&IMG_CHANGE[2].img);
						Draw_Rect(&Rct_btn_Arrow2);
					}
					if( pot[3].pla == 1 )
					{
						//mũi tên trên chậu
			Map_Texture(&Img_flower);
			Draw_Rect(&Rct_btn_Fl3);
						Map_Texture(&IMG_CHANGE[3].img);
						Draw_Rect(&Rct_btn_Arrow3);
					}

	}
	if(arrowclick == 2)
	{
		Map_Texture(&Img_Arrow);
		Draw_Rect(&Rct_btn_Arrow);

		Map_Texture(&Img_Arrow);
		Draw_Rect(&Rct_btn_Arrow1);

		//mũi tên trên chậu
			Map_Texture(&Img_flower);
			Draw_Rect(&Rct_btn_Fl2);
		Map_Texture(&Img_tam);
		Draw_Rect(&Rct_btn_Arrow2);

		Map_Texture(&Img_Arrow);
		Draw_Rect(&Rct_btn_Arrow3);

		IMG_CHANGE[2].img = Img_tam;
		pot[2].pla = 1;
			if( pot[0].pla == 1 )
			{
				//mũi tên trên chậu
			Map_Texture(&Img_flower);
			Draw_Rect(&Rct_btn_Fl);
				Map_Texture(&IMG_CHANGE[0].img);
				Draw_Rect(&Rct_btn_Arrow);
			}
			if( pot[1].pla == 1 )
			{
				//mũi tên trên chậu
			Map_Texture(&Img_flower);
			Draw_Rect(&Rct_btn_Fl1);
				Map_Texture(&IMG_CHANGE[1].img);
				Draw_Rect(&Rct_btn_Arrow1);
			}
	
			if( pot[3].pla == 1 )
			{
				//mũi tên trên chậu
			Map_Texture(&Img_flower);
			Draw_Rect(&Rct_btn_Fl3);
				Map_Texture(&IMG_CHANGE[3].img);
				Draw_Rect(&Rct_btn_Arrow3);
			}
		
	}
	if(arrowclick == 3)
	{
			Map_Texture(&Img_Arrow);
			Draw_Rect(&Rct_btn_Arrow);

			Map_Texture(&Img_Arrow);
			Draw_Rect(&Rct_btn_Arrow1);

			Map_Texture(&Img_Arrow);
			Draw_Rect(&Rct_btn_Arrow2);
			//mũi tên trên chậu
			Map_Texture(&Img_flower);
			Draw_Rect(&Rct_btn_Fl3);
			Map_Texture(&Img_tam);
			Draw_Rect(&Rct_btn_Arrow3);

			IMG_CHANGE[3].img = Img_tam;
			pot[3].pla = 1;

				if( pot[0].pla == 1 )
				{
					//mũi tên trên chậu
			Map_Texture(&Img_flower);
			Draw_Rect(&Rct_btn_Fl);
					Map_Texture(&IMG_CHANGE[0].img);
					Draw_Rect(&Rct_btn_Arrow);
				}
				if( pot[1].pla == 1 )
				{
					//mũi tên trên chậu
			Map_Texture(&Img_flower);
			Draw_Rect(&Rct_btn_Fl1);
					Map_Texture(&IMG_CHANGE[1].img);
					Draw_Rect(&Rct_btn_Arrow1);
				}
				if( pot[2].pla == 1 )
				{
					//mũi tên trên chậu
			Map_Texture(&Img_flower);
			Draw_Rect(&Rct_btn_Fl2);
					Map_Texture(&IMG_CHANGE[2].img);
					Draw_Rect(&Rct_btn_Arrow2);
				}
		}
	//yes_no = false;
}
//
void changeImgNo()
{ 
	map_pic -= 1;	

		Img_tam = Img_Arrow;
		
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
				if( pot[1].pla == 1 )
				{
					Map_Texture(&IMG_CHANGE[1].img);
					Draw_Rect(&Rct_btn_Arrow1);
				}
				if( pot[2].pla == 1 )
				{
					Map_Texture(&IMG_CHANGE[2].img);
					Draw_Rect(&Rct_btn_Arrow2);
				}
				if( pot[3].pla == 1 )
				{
					Map_Texture(&IMG_CHANGE[3].img);
					Draw_Rect(&Rct_btn_Arrow3);
				}
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
					if( pot[0].pla == 1 )
					{
						Map_Texture(&IMG_CHANGE[0].img);
						Draw_Rect(&Rct_btn_Arrow);
					}
					if( pot[2].pla == 1 )
					{
						Map_Texture(&IMG_CHANGE[2].img);
						Draw_Rect(&Rct_btn_Arrow2);
					}
					if( pot[3].pla == 1 )
					{
						Map_Texture(&IMG_CHANGE[3].img);
						Draw_Rect(&Rct_btn_Arrow3);
					}

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

			if( pot[0].pla == 1 )
			{
				Map_Texture(&IMG_CHANGE[0].img);
				Draw_Rect(&Rct_btn_Arrow);
			}
			if( pot[1].pla == 1 )
			{
				Map_Texture(&IMG_CHANGE[1].img);
				Draw_Rect(&Rct_btn_Arrow1);
			}
	
			if( pot[3].pla == 1 )
			{
				Map_Texture(&IMG_CHANGE[3].img);
				Draw_Rect(&Rct_btn_Arrow3);
			}
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

				if( pot[0].pla == 1 )
				{
					Map_Texture(&IMG_CHANGE[0].img);
					Draw_Rect(&Rct_btn_Arrow);
				}
				if( pot[1].pla == 1 )
				{
					Map_Texture(&IMG_CHANGE[1].img);
					Draw_Rect(&Rct_btn_Arrow1);
				}
				if( pot[2].pla == 1 )
				{
					Map_Texture(&IMG_CHANGE[2].img);
					Draw_Rect(&Rct_btn_Arrow2);
				}
		}
}
// màn hiện container
void screenGame1()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	status = 0;
	cout << arrowclick;
	//_____________Start_____________
	//bg2 filter btn-back icon-btn(avt-star)  load btn-left(water-harvest-) load btn-right(shop - bag - list)
	load_hard_element();
	// load container
	Map_Texture(&Img_Container);
	Draw_Rect(&Rct_label_Container);
	//Load mũi tên
	Map_Texture(&Img_Arrow);
	Draw_Rect(&Rct_btn_Arrow);

	Map_Texture(&Img_Arrow);
	Draw_Rect(&Rct_btn_Arrow1);

	Map_Texture(&Img_Arrow);
	Draw_Rect(&Rct_btn_Arrow2);

	Map_Texture(&Img_Arrow);
	Draw_Rect(&Rct_btn_Arrow3);

	//mũi tên trên chậu
	/*Map_Texture(&Img_Arrow);
	Draw_Rect(&Rct_btn_Fl);
	Map_Texture(&Img_Arrow);
	Draw_Rect(&Rct_btn_Fl1);
	Map_Texture(&Img_Arrow);
	Draw_Rect(&Rct_btn_Fl2);
	Map_Texture(&Img_Arrow);
	Draw_Rect(&Rct_btn_Fl3);*/
	//Tùngu
				if( pot[0].pla == 1 )
				{
					Map_Texture(&IMG_CHANGE[0].img);
					Draw_Rect(&Rct_btn_Arrow);
				}
				if( pot[1].pla == 1 )
				{
					Map_Texture(&IMG_CHANGE[1].img);
					Draw_Rect(&Rct_btn_Arrow1);
				}
				if( pot[2].pla == 1 )
				{
				
					Map_Texture(&IMG_CHANGE[2].img);
					Draw_Rect(&Rct_btn_Arrow2);
				}
				if( pot[3].pla == 1 )
				{
			
					Map_Texture(&IMG_CHANGE[3].img);
					Draw_Rect(&Rct_btn_Arrow3);
				}
	// Tùngu2
				if( fl[0].pla == 1 )
				{
					//mũi tên trên chậu
					Map_Texture(&IMG_FL_ARROW[0].img);
					Draw_Rect(&Rct_btn_Fl);
					
				}
				if( fl[1].pla == 1 )
				{
						//mũi tên trên chậu
					Map_Texture(&IMG_FL_ARROW[1].img);
					Draw_Rect(&Rct_btn_Fl1);
					
				}
				if( fl[2].pla == 1 )
				{
						//mũi tên trên chậu
					Map_Texture(&IMG_FL_ARROW[2].img);
					Draw_Rect(&Rct_btn_Fl2);
					
				}
				if( fl[3].pla == 1 )
				{
						//mũi tên trên chậu
					Map_Texture(&IMG_FL_ARROW[3].img);
					Draw_Rect(&Rct_btn_Fl3);
				}
	
	
	if(planting)
	{
		//ve hạt
		Map_Texture(&Img_seed_A);
		Draw_Rect(&Rct_seed_A);
		Map_Texture(&Img_seed_B);
		Draw_Rect(&Rct_seed_B);
		Map_Texture(&Img_seed_C);
		Draw_Rect(&Rct_seed_C);
	}
	else 
	{
		//Load loại chậu
		Map_Texture(&Img_Pot1);
		Draw_Rect(&Rct_pot_Type1);
		Map_Texture(&Img_Pot2);
		Draw_Rect(&Rct_pot_Type2);
		Map_Texture(&Img_Pot3);
		Draw_Rect(&Rct_pot_Type3);
	}
	

	
	
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
	//bg2 filter btn-back icon-btn(avt-star)  load btn-left(water-harvest-) load btn-right(shop - bag - list)
	load_hard_element();
	
	//gan hinh
	if(yes_no)
	{
		changeImgYes();	
	}	
	else 
	{ 
		changeImgNo();
	}
	if(yes_no_Flower)
	{
		changeImg_ArrowTop();
	}
	else
	{
		
	}
	//Load container
	if (XV_plant == 0)
	{
		Map_Texture(&Img_Container);
		Draw_Rect(&Rct_label_Container);
		Map_Texture(&Img_Pot1);
		Draw_Rect(&Rct_pot_Type1);
		Map_Texture(&Img_Pot2);
		Draw_Rect(&Rct_pot_Type2);
		Map_Texture(&Img_Pot3);
		Draw_Rect(&Rct_pot_Type3);
	}
	else if(XV_plant == 1 && planting == false)
	{
		//Load X V đặt chậu
		Map_Texture(&Img_X);
		Draw_Rect(&Rct_btn_X);
		Map_Texture(&Img_V);
		Draw_Rect(&Rct_btn_V);
	}
	else if (XV_plant == 1 && planting == true)
	{
		screenGame1();
		// load X V đặt hoa
		Map_Texture(&Img_X);
		Draw_Rect(&Rct_btn_X_Fl);
		Map_Texture(&Img_V);
		Draw_Rect(&Rct_btn_V_Fl);
	}
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