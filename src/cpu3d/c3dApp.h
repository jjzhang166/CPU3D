#pragma once
#include "c3d.h"
/*
* c3dApp用作入口类，其中c3dFrame的功能尽量都抽取出来，只保留最原始的功能，即把一张纹理渲染到窗口上面
*/
class c3dApp
{
public:
	c3dApp();
	~c3dApp();
	void setup();
	void update();
	void draw();
	void mousepressed(int button,int x,int y);
	void mouseReleased(int button,int x,int y);
	void keyPressed(int key);
	void keyReleased(int key);
};