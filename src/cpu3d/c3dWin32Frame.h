#pragma once
#include "c3d.h"
#include "c3dTexture.h"
/*
* c3dApp��������࣬����c3dFrame�Ĺ��ܾ�������ȡ������ֻ������ԭʼ�Ĺ��ܣ�����һ��������Ⱦ����������
*/
class c3dWin32Frame
{
public:
	c3dWin32Frame();
	~c3dWin32Frame();
	int setup();
	void update();
	void draw();
	void drawFrameBuffer(unsigned char *,unsigned int);
	void run();
	static LRESULT screen_events(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
protected:
	HDC sHdc;		//��ʱ
	HBITMAP hbitmap;		//
	HBITMAP screen_ob;		//
	unsigned char *screen_fb;	//framebuffer
	HWND hwnd;
	long screen_pitch;
	int screenw ;
	int screenh ;
	c3dTexture tex;
public:
	static c3dWin32Frame * pThis;
};