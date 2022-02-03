class c_flower
{
public:	
	public:
	bool choose;// vị trí đang được chọn,// true đang chọn , false là chưa
	bool already ; // true: đã có hoa; false là chưa
	int type; // loại hoa
	bool lackWater; // thiếu nước là truem false không thiếu nước
	int stage; // các giai đoạn của bông hoa
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
		//x = -200;
		//y = -200;
		//Update_Rect_x();
		//Update_Rect_y();
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
		//x = 1080;
		//y = 430;
		//Update_Rect_x();
		//Update_Rect_y();
	}
	void Update_Ghost() {
		Rct.Left = 0;
		Rct.Right = 0;
		Rct.Top = 0 ;
		Rct.Bottom =0;
	}
};
