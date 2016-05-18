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
//��ʱ��ɫΪ��ɫ������Ჹ��
void c3dTexture::DrawLine(vec2& p1,vec2& p2)
{
	//��bug�ж������� ���ߵķ�ʽ���� x������������yֵ�仯�Ƚϴ��ʱ��
	//���»��߲���������������Ӹ���X�������߸���y������Ҫ�жϵ�
	vec2 k = p2 - p1;		
	vec2 kAbs = glm::abs(k);
	bool bLoopedByY = false;
	kAbs.y > kAbs.x ? bLoopedByY = true : bLoopedByY =  false;
	//�ж����������Ƿ�ͷ�����ʵ���� ��ʱû�뵽���õĽ���취��
	//��Ϊ�ü� Ӧ������׶�ü�
	/*if (p1.x >= texw || p2.x >= texw || p1.y >= texh || p2.y >= texh)
	{
		return;
	}*/
	if ( p1.x > texw ) p1.x = texw;
	if ( p1.y > texh ) p1.y = texh;
	if ( p2.x > texw ) p2.x = texw;
	if ( p2.y > texh ) p2.y = texh;

	if ( p1.x < 0 ) p1.x = 0;
	if ( p1.y < 0 ) p1.y = 0;
	if ( p2.x < 0 ) p2.x = 0;
	if ( p2.y < 0 ) p2.y = 0;



	//����Ӧ�ø��� �Ƿ�����Y���껭�������� ����Ҫ��������
	vec2 srcPoint,dstPoint;
	float stepX = 0;
	float stepY = 0;
	if (bLoopedByY)
	{
		if( p1.y < p2.y )
		{
			srcPoint = p1;
			dstPoint = p2;
		}
		else{
			srcPoint = p2;
			dstPoint = p1;
		}
		float step = k.x / k.y;	//����Ҫע�⣬Ϊÿ��һ��Y��x���ߵľ��� xҪת��Ϊ����
		stepX = srcPoint.x;
		for (int y = srcPoint.y; y < dstPoint.y; ++y)
		{
			stepX += step;
			stepY = y;
			int spos = GetPos(stepX, stepY) * 4;
			data[ spos ] = 0xFF;
			data[ spos + 1 ] = 0xFF;	//g
			data[ spos + 2 ] = 0xFF;	//b
			data[ spos + 3 ] = 0xFF;	//a
		}
	}else{
		//����������x���껭��
		if( p1.x < p2.x )
		{
			srcPoint = p1;
			dstPoint = p2;
		}
		else{
			srcPoint = p2;
			dstPoint = p1;
		}
		float step = k.y / k.x;	//����Ҫע�⣬Ϊÿ��һ��Y��x���ߵľ��� xҪת��Ϊ����
		stepY = srcPoint.y;
		for (int x = srcPoint.x; x < dstPoint.x; ++x)
		{
			stepY += step;
			stepX = x;
			int spos = GetPos(stepX, stepY) * 4;
			data[ spos ] = 0xFF;
			data[ spos + 1 ] = 0xFF;	//g
			data[ spos + 2 ] = 0xFF;	//b
			data[ spos + 3 ] = 0xFF;	//a
		}

	}
}

void c3dTexture::DrawTriangle(vec2& p1,vec2&p2,vec2& p3)
{
	//smoothstep(p1,p2,p3);
	//Ŀǰ���յ��ߵķ�ʽ��
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
