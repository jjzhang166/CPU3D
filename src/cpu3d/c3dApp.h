#pragma once
#include "c3d.h"
/*
* c3dApp��������࣬����c3dFrame�Ĺ��ܾ�������ȡ������ֻ������ԭʼ�Ĺ��ܣ�����һ��������Ⱦ����������
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