#pragma once
//这里是否使用一个绘图机制
#include "c3d.h"
#include "c3dCameara.h"
#include "c3dTexture.h"
class c3dFrame
{
public:
	c3dFrame();
	~c3dFrame();
	int c3dInit();
	void c3dUpdate();
	void c3dDraw();
	void c3dLookAt(mat4x4& m,vec4& eyePos,vec4& at,vec4& up);
	//鼠标键盘机制
	void c3dKeyPressed(int key);
	void perspective(mat4x4& m, float fovy, float aspect, float zn, float zf);
private:
	void c3dDeviceSetTexture( void *bits, long pitch, int w, int h );
	void c3dSetIdentity(mat4x4& m);
	void c3dSetZero(mat4x4& m);
	static LRESULT screen_events(HWND hWnd, UINT msg, 
		WPARAM wParam, LPARAM lParam) ;
	void close();
	void dispatch();
	void apply(vec4& y,vec4& x,mat4x4& m);
private:
	c3dCameara cam;	//相机
	vec2 screen;
	mat4x4	mview;	//模型矩阵
	mat4x4  mworld;	//世界矩阵
	mat4x4 project;	//投影矩阵
	mat4x4 transform;
	HDC sHdc;		//临时
	HBITMAP hbitmap;		//
	HBITMAP screen_ob;		//
	unsigned char *screen_fb;	//framebuffer
	HWND hwnd;
	long screen_pitch;

	unsigned int **texture;          // 纹理：同样是每行索引
	int tex_width;              // 纹理宽度
	int tex_height;             // 纹理高度
	float max_u;
	float max_v;
	int renderState;
	int screenw ;
	int screenh ;
	//---------------------
	c3dTexture tex;
};