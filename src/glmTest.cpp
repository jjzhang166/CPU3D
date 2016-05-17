#include <iostream>

#include "cpu3d/c3dFrame.h"
using namespace std;
using namespace glm;
int main()
{
	//vec4 v = vec4(0,1,2,3);
	vec3 x (1, 0, 0);
	vec3 y (0, 1, 0);
	vec3 z1 = glm::cross(x,y);
	vec3 z = x * y;
	vec2 xx(1,0);
	vec2 yy(0,1);
	vec2 zz = xx * yy;
	vec2 z2 = vec2(y);
	
	c3dFrame& f = c3dFrame::GetInstance();
	//while (1)	f.dispatch();
	f.dispatch();
	//while (true)
	//{
	//	f.dispatch();
	//	f.c3dUpdate();
	//	f.c3dDraw();
	//	Sleep(1);
	//}
	
	return 0;
}