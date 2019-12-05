#pragma once
#include "Object.h"
#include "Geometry.h"

class Sphere:public Object
{
private:
	float _radius;//���a
	Vector3 _pos; //���S���W
public:
	Sphere(Vector3& pos,float r,const Material& m);
	~Sphere();
};

