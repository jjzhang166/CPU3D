#pragma once
//�����Ƿ�ʹ��һ����ͼ����
#include "c3d.h"
#include "c3dCameara.h"
class c3dFrame
{
public:
	void c3dInit();
	void c3dUpdate();
	void c3dDraw();
	//�����̻���
	void c3dKeyPressed(int key);
private:
	c3dCameara cam;	//���
	vec2 screen;
	mat4x4	mview;	//ģ�;���
	mat4x4  mworld;	//�������
};