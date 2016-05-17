#include "c3dTexture.h"

void c3dTexture::Init(int w,int h)
{
	if ( w <= 0 || h <= 0)
	{
		return;
	}
	texw = w;
	texh = h;
	data = new unsigned char[w * h * 4];
	memset(data,0,w*h*4 * sizeof(unsigned char));
}

void c3dTexture::DrawLine(vec2& p1,vec2& p2)
{
	//这里先判断颜色坐标是否在区域内
	if (p1.x >= texw || p2.x >= texw || p2.x >= texh || p2.y >= texh)
	{
		return;
	}

	//颜色待定

	vec2 k = p2 - p1; 
	float x = 0;
	float y = 0;
	if (k.x == 0)
	{
		if (k.y == 0)
		{
			int spos = GetPos(p1.x,p1.y) * 4;
			data[spos] = 0xFF;
			data[spos+1] = 0xFF;	//g
			data[spos+2] = 0xFF;	//b
			data[spos+3] = 0xFF;	//a
			return;
		}
		//p1.y p2.y
		if (p1.y < p2.y)
		{
			for (int i = p1.y; i < p2.y; ++i)
			{
				int spos = GetPos(p1.x, i) * 4;
				data[spos] = 0xFF;
				data[spos+1] = 0xFF;	//g
				data[spos+2] = 0xFF;	//b
				data[spos+3] = 0xFF;	//a
			}
		}
		if (p1.y > p2.y)
		{
			for (int i = p2.y; i < p1.y; ++i)
			{
				int spos = GetPos(p1.x, i) * 4;
				data[spos] = 0xFF;
				data[spos+1] = 0xFF;	//g
				data[spos+2] = 0xFF;	//b
				data[spos+3] = 0xFF;	//a
			}
		}
		
	}
	if (k.x > 0)
	{
		y = p1.y;
		for (int i = p1.x; i < p2.x; /*i += k.x*/ ++i)
		{
			x = i;
			y += k.y / k.x;
			int spos = GetPos(x,y) * 4;
			data[spos] = 0xFF;	//r
			data[spos+1] = 0xFF;	//g
			data[spos+2] = 0xFF;	//b
			data[spos+3] = 0xFF;	//a
		}
	}else
	{
		y = p1.y;
		for (int i = p1.x; i > p2.x;/* i += k.x*/--i)
		{
			x = i;
			y += -1 * k.y / k.x;
			int spos = GetPos(x,y) * 4;
			data[spos] = 0xFF;	//r
			data[spos+1] = 0xFF;	//g
			data[spos+2] = 0xFF;	//b
			data[spos+3] = 0xFF;	//a
		}
	}

}

void c3dTexture::DrawTriangle(vec2& p1,vec2&p2,vec2& p3)
{
	//smoothstep(p1,p2,p3);
	//目前按照点线的方式吧
	DrawLine(p1, p2);
	DrawLine(p2, p3);
	DrawLine(p1, p3);
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

void c3dTexture::DrawDebug(vec2& p1,vec2&p2)
{
#ifdef _DEBUG
	for (int i = 0; i < texw * texh*4; ++i)
	{
		//data[i] = i % 255 ;
	}
#endif // _DEBUG


}
