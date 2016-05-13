#include "c3d.h"

class c3dTexture
{
public:
	void Init(int w,int h);
	void DrawLine(vec2& p1,vec2& p2);	//ֱ�ӻ������ػ�����
	void DrawTriangle(vec2& p1,vec2&p2,vec2& p3); //��������
	unsigned char* GetData();
	vec2 GetPos(int p);
	int GetPos(vec2 pos);
	int GetPos(int x,int y);
	int GetSize(){return texw* texh;};
private:
	unsigned char *data;
	int texw,texh;
};