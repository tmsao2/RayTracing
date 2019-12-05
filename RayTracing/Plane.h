#pragma once
#include "Object.h"
#include "Geometry.h"

class Plane :public Object
{
private:
	Vector3 _normal;//法線ベクトル
	float _offset;//原点からのオフセット
public:
	Plane(Vector3& no, float off, const Material& m);
	~Plane();
	bool CheckHit();
};

