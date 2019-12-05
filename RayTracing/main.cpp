#include<dxlib.h>
#include <math.h>
#include <vector>
#include"Geometry.h"
#include "Plane.h"
#include "Sphere.h"
const int screen_width = 640;
const int screen_height = 480;

//ヒントになると思って、色々と関数を用意しておりますが
//別にこの関数を使わなければいけないわけでも、これに沿わなければいけないわけでも
//ありません。レイトレーシングができていれば構いません。

///レイ(光線)と球体の当たり判定
///@param ray (視点からスクリーンピクセルへのベクトル)
///@param sphere 球
///@hint レイは正規化しといたほうが使いやすいだろう
bool IsHitRayAndObject(const Position3& eye,const Vector3& ray,const Sphere& sp,float& t) {
	//レイが正規化済みである前提で…
	//ray=垂線へのベクトル
	//視点から球体中心へのベクトル(視線)を作ります
	auto c = sp.pos - eye;		//中心へのベクトル
	//
	//中心から視線への内積をとります＝＞ベクトル長
	auto dot = Dot(c, ray);
	//視線ベクトルとベクトル長をかけて、中心からの垂線下した点を求めます
	auto vp = ray * dot;

	if ((c-vp).Magnitude()<=sp.radius)
	{
		auto w = sqrt(sp.radius*sp.radius - (c - vp).Magnitude()*(c - vp).Magnitude());
		t=(dot - w);
		return true;
	}
	
	return false;
}

Vector3 RefrectVector(const Vector3& in, const Vector3& normal)
{
	return in - normal * Dot(normal, in) * 2;
}

bool IsHitRayAndObject(const Position3& eye,const Vector3& ray, Plane& pl,float& t)
{
	auto r_ray = ray * -1;
	if (Dot(r_ray, pl.GetNormal().Normalized()) > 0)
	{
		t = (plane.offset - Dot(eye, plane.normal.Normalized())) / Dot(r_ray, plane.normal.Normalized());
		return true;
	}
	return false;
}

void
DrawPixelwithFloat(int x, int y, Vector3 color) {
	DrawPixel(x, y, GetColor(color.x * 0xff, color.y * 0xff, color.z * 0xff));
}

Vector3 Clamp(const Vector3& value,float minVal = 0.0f,float maxVal = 1.0f) {
	return Vector3 ( min(max(value.x , minVal), maxVal),
		min(max(value.y, minVal), maxVal),
		min(max(value.z, minVal), maxVal) );
}

Vector3 CalculateColor(const Vector3& albedo, const float diffuse, const float specular, const float ambient) {
	Vector3 color = Clamp(albedo*(diffuse + ambient) + Vector3(specular, specular, specular));
	return color;
}

Vector3 GetCheckerColor(Position3 pos,float x)
{
	if (x < screen_width/2)
	{
		if (((int)(pos.x / 50) + (int)(pos.z / 50)) % 2)
		{
			return Vector3(1, 1, 0);
		}
		if (!(((int)(pos.x / 50) + (int)(pos.z / 50)) % 2))
		{
			return Vector3(1, 0, 0);
		}
	}
	else
	{
		if (((int)(pos.x / 50) + (int)(pos.z / 50)) % 2)
		{
			return Vector3(1, 0, 0);
		}
		if (!(((int)(pos.x / 50) + (int)(pos.z / 50)) % 2))
		{
			return Vector3(1, 1, 0);
		}
	}
	
}



///レイトレーシング
///@param eye 視点座標
///@param sphere 球オブジェクト(そのうち複数にする)
void RayTracing(Vector3 toLight,const Vector3& eye,std::vector<Object*>& objects) 
{
	toLight.Normalize();

	for (int y = 0; y < screen_height; ++y) 
	{
		for (int x = 0; x < screen_width; ++x) 
		{
			Vector3 ray = Vector3(x - screen_width / 2, screen_height / 2 - y, 0) - eye;
			auto normal = Vector3(0, 0, 0);		//法線ベクトル
			float t;
			Vector3 hitPos;
			Vector3 sPos = Vector3(0, 0, 0);
			Vector3 pPos = Vector3(0, 0, 0);
			//③IsHitRay関数がTrueだったら白く塗りつぶす
			//※塗りつぶしはDrawPixelという関数を使う。
			if (objects[1]->CheckHit(RayLine(hitPos,ray),hitPos,normal))
			{
				if(objects[0]->CheckHit(RayLine(eye, ray), hitPos,normal))
				{
					if (sPos.y >= pPos.y)
					{
						DrawPixelwithFloat(x, y, GetCheckerColor(hitPos, x)*0.3f);
					}
				}
				else
				{
					DrawPixelwithFloat(x, y, GetCheckerColor(hitPos, x));
				}
			}
			if (objects[0]->CheckHit(RayLine(eye,ray), hitPos, normal))
			{
				
				Vector3 albedo = { 1.0f,1.0f,1.0f };
				auto diffuse = Dot(normal, toLight);
				auto mirror = RefrectVector(toLight,normal);
				auto reflect = RefrectVector(ray->vector, normal);
				auto specular = pow(max(Dot(mirror.Normalized(), ray->vector), 0), 20);
				reflect.Normalize();
				if (objects[1]->CheckHit(RayLine(hitPos,ray), hitPos, normal))
				{
					albedo = albedo * GetCheckerColor(hitPos,x);
				}
				if (sPos.z >= pPos.z)
				{
					DrawPixelwithFloat(x, y, CalculateColor(albedo, diffuse, specular, 0));
				}
			}
		}
	}
}

int main() {
	ChangeWindowMode(true);
	SetGraphMode(screen_width, screen_height, 32);
	SetMainWindowText(_T("1701377_高須真樹"));
	DxLib_Init();
	float x = 0, y = 50,z=0;
	std::vector<Object*> objects;
	objects.emplace_back(Sphere(Vector3(0, -100, -100),100,
		Material(Vector3(1.0f, 0.7f, 0.7f), Vector3(1.0f, 1.0f, 1.0f), Vector3(0.1f, 0.1f, 0.1f), 10.0f, 1.0f)));
	objects.emplace_back(Plane(Vector3(0, 1, 0), -200,
		Material(Vector3(1.0f, 0.7f, 0.7f), Vector3(1.0f, 1.0f, 1.0f), Vector3(0.1f, 0.1f, 0.1f), 10.0f, 1.0f)));
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		ClsDrawScreen();
		if (CheckHitKey(KEY_INPUT_UP))
		{
			y+=10;
		}
		if (CheckHitKey(KEY_INPUT_DOWN))
		{
			y-=10;
		}
		if (CheckHitKey(KEY_INPUT_RIGHT))
		{
			x+=10;
		}
		if (CheckHitKey(KEY_INPUT_LEFT))
		{
			x-=10;
		}
		RayTracing(Vector3(-0.5f, 0.5f, 0.5f),Vector3(0, 100, 300),objects);

		ScreenFlip();
	}
	WaitKey();
	DxLib_End();
}