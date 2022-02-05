
class c_pot {
   public:
	bool choose;// vị trí đang được chọn,// true đang chọn , false là chưa
	bool already ; // true: đã có chậu ở vị trí này; false là chưa
	bool chooseSeed; // kiểm soát việc hiển thị hoa
	int typePot; // 1 loại 1, 2 loại 2, 3 loại 3
    Image Img_Save;
    void Load_Image(char* a) {
		Load_Texture_Swap(&Img_Save, a);
		//Zoom_Image(&Img_Save, 1);
	}
	Rect Rct;
	Image *Img;
	float x, y;
	~c_pot(){
	
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
		void Init_Pot(float _x, float _y) {
		Img = &Img_Save;
		x = _x;
		y = _y;
		Rct.Left = x - 56/ 2;
		Rct.Right = Rct.Left + 56;
		Rct.Top =  y ;
		Rct.Bottom = Rct.Top + 60;
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
	// chỉnh vị trí  trong ô xem chậu trước
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