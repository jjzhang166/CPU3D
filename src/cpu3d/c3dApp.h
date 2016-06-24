#pragma once
#include "c3d.h"
#include "c3dTexture.h"
/*
* c3dApp��������࣬����c3dFrame�Ĺ��ܾ�������ȡ������ֻ������ԭʼ�Ĺ��ܣ�����һ��������Ⱦ����������
*/
class c3dApp 
{
public:
	c3dApp();
	~c3dApp();
	int setup();
	void update();
	void dispatch();
	void draw();
	void mousePressed(int button,int x,int y);
	void mouseReleased(int button,int x,int y);
	void keyPressed(int key);
	void keyReleased(int key);
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
};