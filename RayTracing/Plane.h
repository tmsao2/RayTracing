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
	const Material& GetMaterial()const;
	bool CheckHit(const RayLine& ray, Vector3& pos, Vector3& normal);
	float DistanceFromStart(const Vector3& pos);
};

