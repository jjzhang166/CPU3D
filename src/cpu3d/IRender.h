#pragma once


class IRender
{
public:
	virtual void DrawPoint(int x,int y) = 0;
	virtual void DrawRect(int x,int y,int w,int h) = 0;
	virtual void DrawLine(int px1,int py1,int px2,int py2) = 0;
};