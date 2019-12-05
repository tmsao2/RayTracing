#pragma once
#include "Geometry.h"

class Material
{
private:
	Vector3 diffuse;
	Vector3 specular;
	Vector3 ambient;
	float specularity;
	float reflectance;
public:
	Material();
	Material(Vector3& diff, Vector3& spec, Vector3& amb, float power, float reflect);
	~Material();
};

