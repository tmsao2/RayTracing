#pragma once
#include "Geometry.h"
class Sphere
{
private:
	float radius;//���a
	Vector3 pos; //���S���W
	
public:
	Sphere(Vector3& pos,float r);
	~Sphere();
};

