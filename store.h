
int SCALE = 1;
struct sLPot_Store{
	int soLuong;
};
struct sLSeed_Store{
	int soLuong;
};
sLPot_Store slPot[3];
sLPot_Store slSeed[3];

class c_Store_Pot {
  public:
    Image Img_Save;
    void Load_Image(char* a) {
		Load_Texture_Swap(&Img_Save, a);
		//Zoom_Image(&Img_Save, 1);
	}
	Rect Rct;
	Image *Img;
	float x, y;
	~c_Store_Pot(){
	
		cout <<"Doi tuong da duoc huy";
	}
	void Init(float _x, float _y) {
		Img = &Img_Save;
		x = _x;
		y = _y;
		Update_Rect_x();
		Update_Rect_y();
		//Rct.Top =  y ;
		//Rct.Bottom = Rct.Top + Img ->h;
	}
	void Draw() {
		Map_Texture(Img);
		Draw_Rect(&Rct);
	}
	void Zoom(int heSoZoom)
	{
		Zoom_Image(&Img_Save, heSoZoom);
	}
	void keyDow()
	{
		Update();
	}
	void keyUp()
	{
		x = -200;
		y = -200;
		Update_Rect_x();
		Update_Rect_y();
		//Delete_Image(&Img_Save);
	}
	void Update_Rect_x() {
		Rct.Left = x - Img->w / 2;
		Rct.Right = Rct.Left + Img->w;
	}
	void Update_Rect_y()
	{
		Rct.Top =  y ;
		Rct.Bottom = Rct.Top + Img ->h;
	}
	// chỉnh vị trí  trong ô xem chậu trước
	void Update() {
		x = 1080;
		y = 430;
		Update_Rect_x();
		Update_Rect_y();
	}
	
	void BuyPot(int i)
	{
		slPot[i].soLuong += 1;
		cout <<" Mua thanh cong chau loai "<< i <<" , so luong dang co la: " <<slPot[i].soLuong << endl;
	}

};
class c_Store_Seed {
  public:
    Image Img_Save;
    void Load_Image(char* a) {
		Load_Texture_Swap(&Img_Save, a);
		//Zoom_Image(&Img_Save, 1);
	}
	Rect Rct;
	Image *Img;
	float x, y;
	void Init(float _x, float _y) {
		Img = &Img_Save;
		x = _x;
		y = _y;
		Update_Rect_x();
		Update_Rect_y();
		//Rct.Top =  y;
		//Rct.Bottom = Rct.Top + Img->h ;

	}
	void Draw() {
		Map_Texture(Img);
		Draw_Rect(&Rct);
	}
	void keyDow()
	{
		Update();
	}
	void keyUp()
	{
		x = -200;
		y = -200;
		Update_Rect_x();
		Update_Rect_y();
	}
	void Update_Rect_x() {
		Rct.Left = x - Img->w / 2;
		Rct.Right = Rct.Left + Img->w;
	}
	void Update_Rect_y() {
		Rct.Top =  y;
		Rct.Bottom = Rct.Top + Img->h ;
	}
	void Update() {
		x = 1080;
		y = 430;
		Update_Rect_x();
		Update_Rect_y();
	}
	void BuySeed(int i)
	{
		slSeed[i].soLuong += 1;
		cout <<" Mua thanh cong hoa loai "<< i <<" : "<<slSeed[i].soLuong << endl;
	}
};
int Score, Score_Add, Score_Array[10], Score_Length;
class Num
{
public :
    static Image Img_Num[10];
	void static Load_Texture_Num(char *file) {
		int Pos[][4] = {
			{0, 0, 20, 46},
			{20, 0, 16, 46},//{20, 0, 14, 46}
			{34, 0, 21, 46},
			{55, 0, 19, 46},
			{74, 0, 22, 46},
			{96, 0, 19, 46},
			{115, 0, 22, 46},
			{137, 0, 16, 46},
			{153, 0, 23, 46},
			{176, 0, 22, 46}};
		int *Ptr_Pos;
		Image Img, Img_Tmp;
		Load_Png(&Img.img, &Img.w, &Img.h, file);
		int i;
		for (i = 0; i < 10; i++) {
			Ptr_Pos = &Pos[i][0];
			Crop_Image(&Img, &Img_Tmp, *Ptr_Pos, *(Ptr_Pos + 1), *(Ptr_Pos + 2), *(Ptr_Pos + 3));
			Swap_Image(Img_Tmp.img, Img_Tmp.w, Img_Tmp.h);
			Img_Num[i] = Img_Tmp;
		}
		free(Img.img); 
	}
	Rect Rct_Score;
	float x,y;
	void Draw_Num(float _x,float _y) {
		int i;
		x = _x;
		y = _y;
		Rct_Score.Top = y;
		Rct_Score.Bottom = Rct_Score.Top + Img_Num[0].h;	
		Rct_Score.Right = x;
		for (i = Score_Length - 1; i >= 0; i--) {
			Rct_Score.Left = Rct_Score.Right;
			Rct_Score.Right = Rct_Score.Left + Img_Num[Score_Array[i]].w;
			Map_Texture(&Img_Num[Score_Array[i]]);
			Draw_Rect(&Rct_Score);
		}
		//cout << "ve thanh cong" << endl;
	}
	void Update_Num(int s) {
		int x = s;
		Score_Length = 0;
		int Size = 0, Size_s;
		do {
			Score_Array[Score_Length] = x % 10;
			Size += Img_Num[Score_Array[Score_Length]].w;
			x /= 10;
			Score_Length++;
		} while (x > 0);
	}

};