#include "c3dFrame.h"


void c3dFrame::c3dInit()
{

}

void c3dFrame::c3dUpdate()
{

}

void c3dFrame::c3dDraw()
{

}

void c3dFrame::c3dKeyPressed(int key)
{

}

void c3dFrame::c3dSetIdentity(mat4x4& m)
{
	m[0][0] = m[1][1] = m[2][2] = m[3][3] = 1.0f; 
	m[0][1] = m[0][2] = m[0][3] = 0.0f;
	m[1][0] = m[1][2] = m[1][3] = 0.0f;
	m[2][0] = m[2][1] = m[2][3] = 0.0f;
	m[3][0] = m[3][1] = m[3][2] = 0.0f;
}

void c3dFrame::c3dLookAt(mat4x4& m,vec4& eye,vec4& at,vec4& up)
{
	vec3 xaxis, yaxis;
	vec3 zaxis;
	vec4 z = at - eye;
	zaxis = vec3(z);
	normalize(zaxis);
	xaxis = cross(vec3(up),zaxis);
	normalize(xaxis);
	yaxis = cross(zaxis,xaxis);

	//vector_sub(&zaxis, at, eye);
	//vector_normalize(&zaxis);
	//vector_crossproduct(&xaxis, up, &zaxis);
	//vector_normalize(&xaxis);
	//vector_crossproduct(&yaxis, &zaxis, &xaxis);
	//vec3 xaxis3 = cross(up.xyz(),zaxis.xyz());
	m[0][0] = xaxis.x;
	m[1][0] = xaxis.y;
	m[2][0] = xaxis.z;
	m[3][0] = -1 * dot(xaxis,vec3(eye));
	// m[3][0] = -vector_dotproduct(&xaxis, eye);
	m[0][1] = yaxis.x;
	m[1][1] = yaxis.y;
	m[2][1] = yaxis.z;
	m[3][1] = -1 * dot(yaxis,vec3(eye));
	//	 m[3][1] = -vector_dotproduct(&yaxis, eye);
	m[0][2] = zaxis.x;
	m[1][2] = zaxis.y;
	m[2][2] = zaxis.z;
	m[3][2] = dot(zaxis,vec3(eye));
	//	 m[3][2] = -vector_dotproduct(&zaxis, eye);
	m[0][3] =  m[1][3] =  m[2][3] = 0.0f;
	m[3][3] = 1.0f;
}

void c3dFrame::perspective(mat4x4& m, float fovy, float aspect, float zn, float zf)
{
	float fax = 1.0f / (float)tan(fovy * 0.5f);

	c3dSetZero(m);
	m[0][0] = (float)(fax / aspect);
	m[1][1] = (float)(fax);
	m[2][2] = zf / (zf - zn);
	m[3][2] = - zn * zf / (zf - zn);
	m[2][3] = 1;
}

void c3dFrame::c3dSetZero(mat4x4& m)
{
	m[0][0] =  m[0][1] =  m[0][2] =  m[0][3] = 0.0f;
	m[1][0] =  m[1][1] =  m[1][2] =  m[1][3] = 0.0f;
	m[2][0] =  m[2][1] =  m[2][2] =  m[2][3] = 0.0f;
	m[3][0] =  m[3][1] =  m[3][2] =  m[3][3] = 0.0f;
}

