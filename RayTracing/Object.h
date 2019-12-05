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
	virtual bool CheckHit() = 0;
	virtual float DistanceFromStart() = 0;

};

