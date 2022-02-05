
class c_loadimage {
   public:
	bool choose;// chậu đã chọn,// true đã chọn loại chậu, false là chưa
    Image Img_Save;
    void Load_Image(char* a) {
		Load_Texture_Swap(&Img_Save, a);
		//Zoom_Image(&Img_Save, 1);
	}
	Rect Rct;
	Image *Img;
	float x, y;
	~c_loadimage(){
	
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
		void Init_LoadImg(float _x, float _y,float w,float h) {
		Img = &Img_Save;
		x = _x;
		y = _y;
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
	// chỉnh vị trí  trong ô xem chậu trước
	void Update_Ghost() {
		Rct.Left = 0;
		Rct.Right = 0;
		Rct.Top = 0 ;
		Rct.Bottom =0;
	}
	void Update() {
		Update_Rect_x();
		Update_Rect_y();
	}
	
};