#pragma once
#include "c3d.h"
class c3dCameara
{
public:
	c3dCameara(void);
	~c3dCameara(void);
	vec3 pos;		//�۾�λ��
	vec3 dir;	//�۾�����	
	vec3 upDir;	//ͷ������

	float ration;	//��߱�
	float fnear;	//���� Զ   ��
	float ffar;
};

