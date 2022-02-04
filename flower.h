class c_flower
{
public:	
	public:
	bool choose;// vị trí đang được chọn,// true đang chọn , false là chưa
	int type; // loại hoa 1 hoa vàng gia ban 250 , 2 hoa đỏ gia ban 350 , 3 hoa tím gia ban 400
	bool lackWater; // thiếu nước là true, false không thiếu nước
	int stage; // các giai đoạn của bông hoa 1 mầm, 2 đang trưởng thành , 3 thu hoặc, 0 chưa có hoa
	int timeStar;
    Image Img_Save;
    void Load_Image(char* a) {
		Load_Texture_Swap(&Img_Save, a);
		//Zoom_Image(&Img_Save, 1);
	}
	Rect Rct;
	Image *Img;
	float x, y;
	~c_flower(){
	
		//cout <<"Doi tuong da duoc huy";
	}
	void Init(float _x, float _y) {
		Img = &Img_Save;
		x = _x;
		y = _y;
		Update_Rect_x();
		Update_Rect_y();
		Rct.Top =  y ;
		Rct.Bottom = Rct.Top + Img ->h;
	}
	void Init_Flower(float _x, float _y,float w,float h) {
		Img = &Img_Save;
		x = _x;
		y = _y;
		Update_Rect_x();
		Update_Rect_y();
		Rct.Left = x - w/ 2;
		Rct.Right = Rct.Left + w;
		Rct.Top =  y ;
		Rct.Bottom = Rct.Top + h;
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
	// mũi tên
	void keyDow_2()
	{
		Update_2();
	}
	// mầm cây
	void keyDow_3()
	{
		Rct.Left = x - Img->w / 2;
		Rct.Right = Rct.Left + Img->w;
		Rct.Top =  y + 45 ;
		Rct.Bottom = Rct.Top + Img ->h;
	}
	void keyUp()
	{
		
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
	void Update() {
		Update_Rect_x();
		Update_Rect_y();
	}
	void Update_2() { // cho mũi tên
		Rct.Left = x - 56 / 2;
		Rct.Right = Rct.Left + 56;
		Rct.Top =  y +12  ;
		Rct.Bottom = Rct.Top +60;
	}
	void Update_Ghost() {
		Rct.Left = 0;
		Rct.Right = 0;
		Rct.Top = 0 ;
		Rct.Bottom =0;
	}
};
