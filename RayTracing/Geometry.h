#pragma once


//�T�C�Y��\���\����
struct Size {
	float w;//��
	float h;//����
};

//2D���W�E�x�N�g����\���\����
struct Vector2 {
	Vector2():x(0),y(0){}
	Vector2(float inx,float iny):x(inx),y(iny){}
	float x, y;
	///�x�N�g���̑傫����Ԃ��܂�
	float Magnitude()const;
	
	///���K��(�傫�����P��)���܂�
	void Normalize();

	///���K���x�N�g����Ԃ��܂�
	Vector2 Normalized();

	void operator+=(const Vector2& v);
	void operator-=(const Vector2& v);
	void operator*=(float scale);
	Vector2 operator*(float scale);
	Vector2 operator-() {
		return Vector2(-x, -y);
	}
};

Vector2 operator+(const Vector2& va, const Vector2 vb);
Vector2 operator-(const Vector2& va, const Vector2 vb);

///���ς�Ԃ�
float Dot(const Vector2& va, const Vector2& vb);

///�O�ς�Ԃ�
float Cross(const Vector2& va, const Vector2& vb);

///���ω��Z�q
float operator*(const Vector2& va, const Vector2& vb);

///�O�ω��Z�q
float operator%(const Vector2& va, const Vector2& vb);

//�Ƃ肠�����u���W�v���ĈӖ����ƃx�N�^���
//Position�̂ق����悭�ˁH���ė��R�ł��̖��O
typedef Vector2 Position2;


//3D���W�E�x�N�g����\���\����
struct Vector3 {
	Vector3() :x(0), y(0) ,z(0){}
	Vector3(float inx, float iny,float inz) :x(inx), y(iny) ,z(inz){}
	float x, y,z;
	///�x�N�g���̑傫����Ԃ��܂�
	float Magnitude()const;

	///���K��(�傫�����P��)���܂�
	void Normalize();

	///���K���x�N�g����Ԃ��܂�
	const Vector3& Normalized();

	void operator+=(const Vector3& v);
	void operator-=(const Vector3& v);
	void operator*=(float scale);
	Vector3 operator*(float scale)const;
	Vector3 operator-() {
		return Vector3(-x, -y,-z);
	}
};
Vector3 operator+(const Vector3& va, const Vector3 vb);
Vector3 operator-(const Vector3& va, const Vector3 vb);
Vector3 operator+(const Vector3& va, const float scale);
Vector3 operator-(const Vector3& va, const float scale);

///���ς�Ԃ�
float Dot(const Vector3& va, const Vector3& vb);

///�O�ς�Ԃ�
Vector3 Cross(const Vector3& va, const Vector3& vb);

///���ω��Z�q
Vector3 operator*(const Vector3& va, const Vector3& vb);

///�O�ω��Z�q
Vector3 operator%(const Vector3& va, const Vector3& vb);
typedef Vector3 Position3;

///�~��\���\����
struct Circle {
	float radius;//���a
	Position2 pos; //���S���W
	Circle() :radius(0), pos(0, 0) {}
	Circle(float r, Position2& p) :radius(r), pos(p) {}
};

///��`��\���\����
struct Rect {
	Position2 pos; //���S���W
	int w, h;//��,����
	Rect() : pos(0, 0), w(0), h(0) {}
	Rect(float x, float y, int inw, int inh) :
		pos(x, y), w(inw), h(inh) {}
	Rect(Position2& inpos, int inw, int inh) :
		pos(inpos), w(inw), h(inh)
	{}
	void SetCenter(float x, float y) {
		pos.x = x;
		pos.y = y;
	}
	void SetCenter(const Position2& inpos) {
		pos.x = inpos.x;
		pos.y = inpos.y;
	}
	Vector2 Center() {
		return pos;
	}
	float Left() { return pos.x - w / 2; }
	float Top() { return pos.y - h / 2; }
	float Right() { return pos.x + w / 2; }
	float Bottom() { return pos.y + h / 2; }
	void Draw();//�����̋�`��`�悷��
	void Draw(Vector2& offset);//�����̋�`��`�悷��(�I�t�Z�b�g�t��)
};

struct RayLine
{
	Vector3 start;
	Vector3 vector;
	RayLine(const Vector3& s, Vector3& v) :start(s), vector(v.Normalized()){}
	void Init(const Vector3& s, const Vector3& e)
	{
		start = s;
		vector = (e - s).Normalized();
	}
};
