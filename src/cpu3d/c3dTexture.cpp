#include "c3dTexture.h"

void c3dTexture::Init(int w,int h)
{
	if ( w <= 0 || h <= 0)
	{
		return;
	}
	//const int cw = w;
	//const int ch = h;
	//data = new char[cw][ch];
	//*data = new  char[];
	texw = w;
	texh = h;
	data = new unsigned char[w * h * 4];
	memset(data,0,w*h*4);
}

void c3dTexture::DrawLine(vec2& p1,vec2& p2)
{
	//	glm::min(p1,p2);
	int minX = p1.x < p2.x ? p1.x : p2.x;
	int maxX = p1.x > p2.x ? p1.x : p2.x;
	vec2 k = p2 - p1; 
	int x = 0;
	int y = 0;
	if (k.x > 0)
	{
		for (int i = p1.x; i < p2.x; ++ k.x)
		{
			x = i;
			y = p1.y + k.y;
			int spos = GetPos(x,y);
			data[spos] = 0xFF;	//ÑÕÉ«´ý¶¨
		}
	}else
	{
		for (int i = p1.x; i > p2.x; ++ k.x)
		{
			x = i;
			y = p1.y + k.y;
		}
	}

}

void c3dTexture::DrawTriangle()
{

}

unsigned char* c3dTexture::GetData()
{
	return data;
}

vec2 c3dTexture::GetPos(int p)
{
	int y = p / texw;
	int x = p % texw;
	return vec2(x,y);
}

int c3dTexture::GetPos(vec2 pos)
{
	if (pos.y < 1)
	{
		return pos.x;
	}
	int m = (pos.y - 1) *texw + pos.x;
	return m;
}

int c3dTexture::GetPos(int x,int y)
{
	if (y < 1)
	{
		return x;
	}
	int m = (y - 1) *texw + x;
	return m;
}
