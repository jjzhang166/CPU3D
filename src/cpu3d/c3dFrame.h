#pragma once
//这里是否使用一个绘图机制
#include "c3d.h"
#include "c3dCameara.h"
class c3dFrame
{
public:
	void c3dInit();
	void c3dUpdate();
	void c3dDraw();
	//鼠标键盘机制
	void c3dKeyPressed(int key);
private:
	c3dCameara cam;

};