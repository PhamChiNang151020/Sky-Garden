
int SCALEs = 1;

class c_Rain {
  public:
	static Image Img_Save;
	static void Load_Image(char* a) {
		Load_Texture_Swap(&Img_Save, a);
		Zoom_Image(&Img_Save, SCALEs);
	}
	Rect Rct;
	Image *Img;
	float x, y;
	void Init(float _x, float _y) {
		Img = &Img_Save;
		x = _x;
		y = _y;
		Update_Rect();
		Rct.Bottom =  Rct.Bottom + Img->h;
		Rct.Top = y;

	}
	void Draw() {
		Map_Texture(Img);
		Draw_Rect(&Rct);
	}
	void Update_Rect() {
		Rct.Left = x - Img->w / 2;
		Rct.Right = Rct.Left + Img->w;
	}
	bool ismua;
	void Key_Down() {
		ismua = true;
		x = 1280;
		//Update();
	}
	void Key_Up() {
		ismua = false;
	}
	void Update() {
		x -= 3.0f;
		Update_Rect();
	}
};
class c_Cloud {
  public:
	static Image Img_Save;
	static void Load_Image(char* a) {
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
		Update_Rect();
		Rct.Bottom =  y;
		Rct.Top = Rct.Bottom + Img->h;

	}
	void Draw() {
		Map_Texture(Img);
		Draw_Rect(&Rct);
	}
	void Update_Rect() {
		Rct.Left = x - Img->w / 2;
		Rct.Right = Rct.Left + Img->w;
	}
	void Update() {
		x -= 0.8f;
		if (x < -130.0f)
			x += 1880.0f;
		Update_Rect();
	}
};


