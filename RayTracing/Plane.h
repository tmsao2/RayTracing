#pragma once
#include "Object.h"
#include "Geometry.h"

class Plane :public Object
{
private:
	Vector3 _normal;//�@���x�N�g��
	float _offset;//���_����̃I�t�Z�b�g
public:
	Plane(Vector3& no, float off, const Material& m);
	~Plane();
	bool CheckHit();
};

