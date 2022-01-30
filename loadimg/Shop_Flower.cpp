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
#include "loadpng.h"
#include "process_image.h"
#include "gl_texture.h"
#include <windows.h>
using namespace std;
// khai báo toàn cục
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
int money = 50000;
// màn hình shop
Rect	Rct_ShopScreen = {0, 1280, 720,0}, //Màn hình shop
		//Cửa sổ exit
		Rct_btn_Buy={990,205+990,75+605,605};
		//Rct_Score;

Image Img_ShopScreen;
Image Img_Buy;
Image Num :: Img_Num[10]; // khai bao sử dụng ảnh số vi static
Num numSLVPham; // 6 vật vật phẩm
Num numMoney; // khai bao đối tượng sử dụng số
int Class_Pot_Seed = 1; // sử dụng  bấm vào chậu nào, 1 - 3 là chậu, 3 - 6 là hoa
#define WIDTH 1280
#define HEIGHT 720
#define INTERVAL 10 
void numSL();
void buyPot();
// init chậu hoa, coppy vào hàm init găm
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
// display các vật phẩm trong sho // đặt trong hàm display game
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
	Load_Texture_Swap(&Img_ShopScreen, "Images/bg4-Shop.png");
	// nút mua
	Load_Texture_Swap(&Img_Buy, "Images/btn-Buy.png");	
	// init vật phẩm trong shop
	initStore();
	// khai báo load ảnh các con số
	 

	

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
	// nut mua
	Map_Texture(&Img_Buy);
	Draw_Rect(&Rct_btn_Buy); 
	 // vat pham shop
	displayStore();
   
	glutSwapBuffers();
}
// Cho phép gọi đi gọi lại nhiều lần
void Timer(int value)
{
	
	glutPostRedisplay();
	glutTimerFunc(INTERVAL,Timer, 0);
}

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

void mouseClick(int button , int state, int x, int y)
{
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
	glutCreateWindow("SKY");

	
	init();
	glutDisplayFunc(display);
	glutMouseFunc(mouseClick);

	glutTimerFunc(0,Timer,0);


	glutMainLoop();
	return 0;
}