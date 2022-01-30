#ifndef POT_H
#define POT_H
class pot
{
public:	
	//int x,y,b,t; // Trái x, Phải y, Dưới b(bottom), Trên t(top)
	int clickChoosePot; // Số lần click
	int clickChooseFlower;
	int potType; // Loại chậu 
	bool planted; // Ktra đã trồng
	int flowerType;
	int stage;
};
#endif