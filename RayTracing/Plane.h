#pragma once
#include "Geometry.h"

class Plane
{
private:
	Vector3 normal;//法線ベクトル
	float offset;//原点からのオフセット
public:
	Plane(Vector3& no, float off);
	~Plane();
};

