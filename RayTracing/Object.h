#pragma once
#include "Geometry.h"
#include "Material.h"

class Object
{
protected:
	Material material;
public:
	Object(const Material& m);
	~Object();
	virtual const Material& GetMaterial()const = 0;
	virtual bool CheckHit(const RayLine& ray, Vector3& pos, Vector3& normal) = 0;
	virtual float DistanceFromStart(const Vector3& pos) = 0;

};

