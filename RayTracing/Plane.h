#pragma once
#include "Geometry.h"

class Plane
{
private:
	Vector3 normal;//�@���x�N�g��
	float offset;//���_����̃I�t�Z�b�g
public:
	Plane(Vector3& no, float off);
	~Plane();
};

