#pragma once
#include <DirectXMath.h>

using namespace DirectX;


/// <summary>
/// éZèpópÇÃ2éüå≥êî(DirectX::XMFLOAT2åpè≥)
/// </summary>
struct Vector2 : XMFLOAT2
{

#pragma region constractor
	using XMFLOAT2::XMFLOAT2;
	Vector2() : XMFLOAT2::XMFLOAT2() {}
	using XMFLOAT2::operator=;
	Vector2(const float _x, const float _y) { x = _x; y = _y; }
#pragma endregion

#pragma region operator
	Vector2& operator =(const XMFLOAT3& _vec) { x = _vec.x; y = _vec.y; return *this; }
	Vector2& operator =(const XMFLOAT4& _vec) { x = _vec.x; y = _vec.y; return *this; }

	Vector2& operator *=(const float& _value) { x *= _value; y *= _value; return *this; }
	Vector2& operator /=(const float _value) { x /= _value; y /= _value; return *this; }
	Vector2& operator +=(const XMFLOAT2& _vec) { x += _vec.x; y += _vec.y; return *this; }
	Vector2& operator -=(const XMFLOAT2& _vec) { x -= _vec.x; y -= _vec.y; return *this; }
	Vector2& operator *=(const XMFLOAT2& _vec) { x *= _vec.x; y *= _vec.y; return *this; }
	Vector2& operator /=(const XMFLOAT2& _vec) { x /= _vec.x; y /= _vec.y; return *this; }
	Vector2& operator +=(const XMFLOAT3& _vec) { x += _vec.x; y += _vec.y; return *this; }
	Vector2& operator -=(const XMFLOAT3& _vec) { x -= _vec.x; y -= _vec.y; return *this; }
	Vector2& operator *=(const XMFLOAT3& _vec) { x *= _vec.x; y *= _vec.y; return *this; }
	Vector2& operator /=(const XMFLOAT3& _vec) { x /= _vec.x; y /= _vec.y; return *this; }
	Vector2& operator +=(const XMFLOAT4& _vec) { x += _vec.x; y += _vec.y; return *this; }
	Vector2& operator -=(const XMFLOAT4& _vec) { x -= _vec.x; y -= _vec.y; return *this; }
	Vector2& operator *=(const XMFLOAT4& _vec) { x *= _vec.x; y *= _vec.y; return *this; }
	Vector2& operator /=(const XMFLOAT4& _vec) { x /= _vec.x; y /= _vec.y; return *this; }

	const Vector2 operator *(const float _value) const { return Vector2(x * _value, y * _value); }
	const Vector2 operator /(const float _value) const { return Vector2(x / _value, y / _value); }
	const Vector2 operator +(const XMFLOAT2& _vec)const { return  Vector2(x + _vec.x, y + _vec.y); }
	const Vector2 operator -(const XMFLOAT2& _vec)const { return  Vector2(x - _vec.x, y - _vec.y); }
	const Vector2 operator *(const XMFLOAT2& _vec)const { return  Vector2(x * _vec.x, y * _vec.y); }
	const Vector2 operator /(const XMFLOAT2& _vec)const { return  Vector2(x / _vec.x, y / _vec.y); }
	const Vector2 operator +(const XMFLOAT3& _vec)const { return  Vector2(x + _vec.x, y + _vec.y); }
	const Vector2 operator -(const XMFLOAT3& _vec)const { return  Vector2(x - _vec.x, y - _vec.y); }
	const Vector2 operator *(const XMFLOAT3& _vec)const { return  Vector2(x * _vec.x, y * _vec.y); }
	const Vector2 operator /(const XMFLOAT3& _vec)const { return  Vector2(x / _vec.x, y / _vec.y); }
	const Vector2 operator +(const XMFLOAT4& _vec)const { return  Vector2(x + _vec.x, y + _vec.y); }
	const Vector2 operator -(const XMFLOAT4& _vec)const { return  Vector2(x - _vec.x, y - _vec.y); }
	const Vector2 operator *(const XMFLOAT4& _vec)const { return  Vector2(x * _vec.x, y * _vec.y); }
	const Vector2 operator /(const XMFLOAT4& _vec)const { return  Vector2(x / _vec.x, y / _vec.y); }

	const float& operator [](const int _index)const { return *((&x) + _index); }
	float& operator [](const int _index) { return *((&x) + _index); }
#pragma endregion

#pragma region function
	float Length() { return sqrtf(x * x + y * y); }

	static float Dot(const Vector2& _vec1, const Vector2& _vec2)
	{
		float _ans;
		DirectX::XMStoreFloat(&_ans, DirectX::XMVector2Dot(DirectX::XMVector2Normalize(DirectX::XMLoadFloat2(&_vec1)), DirectX::XMVector2Normalize(DirectX::XMLoadFloat2(&_vec2))));
		return _ans;
	}
	static Vector2 Cross(const Vector2& _vec1, const Vector2& _vec2)
	{
		Vector2 _ans;
		DirectX::XMStoreFloat2(&_ans, DirectX::XMVector2Cross(DirectX::XMVector2Normalize(DirectX::XMLoadFloat2(&_vec1)), DirectX::XMVector2Normalize(DirectX::XMLoadFloat2(&_vec2))));
		return _ans;
	}
#pragma endregion
};

/// <summary>
/// éZèpópÇÃ3éüå≥êî(DirectX::XMFLOAT3åpè≥)
/// </summary>
struct Vector3 : XMFLOAT3
{

#pragma region constractor
	using XMFLOAT3::XMFLOAT3;
	Vector3() : XMFLOAT3::XMFLOAT3() {}
	Vector3(const float _x, const float _y, const float _z) { x = _x; y = _y; z = _z; }
#pragma endregion

#pragma region operator
	using XMFLOAT3::operator=;
	Vector3& operator =(const XMFLOAT2& _vec) { x = _vec.x; y = _vec.y; return *this; }
	Vector3& operator =(const XMFLOAT4& _vec) { x = _vec.x; y = _vec.y; z = _vec.z; return *this; }

	Vector3& operator *=(const float& _value) { x *= _value; y *= _value; z *= _value; return *this; }
	Vector3& operator /=(const float _value) { x /= _value; y /= _value; z /= _value; return *this; }
	Vector3& operator +=(const XMFLOAT2& _vec) { x += _vec.x; y += _vec.y; return *this; }
	Vector3& operator -=(const XMFLOAT2& _vec) { x -= _vec.x; y -= _vec.y; return *this; }
	Vector3& operator *=(const XMFLOAT2& _vec) { x *= _vec.x; y *= _vec.y; return *this; }
	Vector3& operator /=(const XMFLOAT2& _vec) { x /= _vec.x; y /= _vec.y; return *this; }
	Vector3& operator +=(const XMFLOAT3& _vec) { x += _vec.x; y += _vec.y; z += _vec.z; return *this; }
	Vector3& operator -=(const XMFLOAT3& _vec) { x -= _vec.x; y -= _vec.y; z -= _vec.z; return *this; }
	Vector3& operator *=(const XMFLOAT3& _vec) { x *= _vec.x; y *= _vec.y; z *= _vec.z; return *this; }
	Vector3& operator /=(const XMFLOAT3& _vec) { x /= _vec.x; y /= _vec.y; z /= _vec.z; return *this; }
	Vector3& operator +=(const XMFLOAT4& _vec) { x += _vec.x; y += _vec.y; z += _vec.z; return *this; }
	Vector3& operator -=(const XMFLOAT4& _vec) { x -= _vec.x; y -= _vec.y; z -= _vec.z; return *this; }
	Vector3& operator *=(const XMFLOAT4& _vec) { x *= _vec.x; y *= _vec.y; z *= _vec.z; return *this; }
	Vector3& operator /=(const XMFLOAT4& _vec) { x /= _vec.x; y /= _vec.y; z /= _vec.z; return *this; }

	const Vector3 operator *(const float _value) const { return Vector3(x * _value, y * _value, z * _value); }
	const Vector3 operator /(const float _value) const { return Vector3(x / _value, y / _value, z / _value); }
	const Vector3 operator +(const XMFLOAT2& _vec)const { return  Vector3(x + _vec.x, y + _vec.y, z); }
	const Vector3 operator -(const XMFLOAT2& _vec)const { return  Vector3(x - _vec.x, y - _vec.y, z); }
	const Vector3 operator *(const XMFLOAT2& _vec)const { return  Vector3(x * _vec.x, y * _vec.y, z); }
	const Vector3 operator /(const XMFLOAT2& _vec)const { return  Vector3(x / _vec.x, y / _vec.y, z); }
	const Vector3 operator +(const XMFLOAT3& _vec)const { return  Vector3(x + _vec.x, y + _vec.y, z + _vec.z); }
	const Vector3 operator -(const XMFLOAT3& _vec)const { return  Vector3(x - _vec.x, y - _vec.y, z - _vec.z); }
	const Vector3 operator *(const XMFLOAT3& _vec)const { return  Vector3(x * _vec.x, y * _vec.y, z * _vec.z); }
	const Vector3 operator /(const XMFLOAT3& _vec)const { return  Vector3(x / _vec.x, y / _vec.y, z / _vec.z); }
	const Vector3 operator +(const XMFLOAT4& _vec)const { return  Vector3(x + _vec.x, y + _vec.y, z + _vec.z); }
	const Vector3 operator -(const XMFLOAT4& _vec)const { return  Vector3(x - _vec.x, y - _vec.y, z - _vec.z); }
	const Vector3 operator *(const XMFLOAT4& _vec)const { return  Vector3(x * _vec.x, y * _vec.y, z * _vec.z); }
	const Vector3 operator /(const XMFLOAT4& _vec)const { return  Vector3(x / _vec.x, y / _vec.y, z / _vec.z); }

	const float& operator [](const int _index)const { return *((&x) + _index); }
	float& operator [](const int _index) { return *((&x) + _index); }
#pragma endregion

#pragma region function
	float Length() { return sqrtf(x * x + y * y + z * z); }

	static float Dot(const Vector3& _vec1, const Vector3& _vec2)
	{
		float _ans;
		DirectX::XMStoreFloat(&_ans, DirectX::XMVector3Dot(DirectX::XMVector3Normalize(DirectX::XMLoadFloat3(&_vec1)), DirectX::XMVector3Normalize(DirectX::XMLoadFloat3(&_vec2))));
		return _ans;
	}
	static Vector3 Cross(const Vector3& _vec1, const Vector3& _vec2)
	{
		Vector3 _ans;
		DirectX::XMStoreFloat3(&_ans, DirectX::XMVector2Cross(DirectX::XMVector3Normalize(DirectX::XMLoadFloat3(&_vec1)), DirectX::XMVector3Normalize(DirectX::XMLoadFloat3(&_vec2))));
		return _ans;
	}
#pragma endregion
};

/// <summary>
/// éZèpópÇÃ4éüå≥êî(DirectX::XMFLOAT4åpè≥)
/// </summary>
struct Vector4 : XMFLOAT4
{

#pragma region constractor
	using XMFLOAT4::XMFLOAT4;
	Vector4() : XMFLOAT4::XMFLOAT4() {}
	Vector4(const float _x, const float _y, const float _z, const float _w) { x = _x; y = _y; z = _z; w = _w; }
#pragma endregion

#pragma region operator
	using XMFLOAT4::operator=;
	Vector4& operator =(const XMFLOAT2& _vec) { x = _vec.x; y = _vec.y; return *this; }
	Vector4& operator =(const XMFLOAT3& _vec) { x = _vec.x; y = _vec.y; z = _vec.z; return *this; }

	Vector4& operator *=(const float& _value) { x *= _value; y *= _value; z *= _value; w *= _value; return *this; }
	Vector4& operator /=(const float _value) { x /= _value; y /= _value; z /= _value; w /= _value; return *this; }
	Vector4& operator +=(const XMFLOAT2& _vec) { x += _vec.x; y += _vec.y; return *this; }
	Vector4& operator -=(const XMFLOAT2& _vec) { x -= _vec.x; y -= _vec.y; return *this; }
	Vector4& operator *=(const XMFLOAT2& _vec) { x *= _vec.x; y *= _vec.y; return *this; };
	Vector4& operator /=(const XMFLOAT2& _vec) { x /= _vec.x; y /= _vec.y; return *this; }
	Vector4& operator +=(const XMFLOAT3& _vec) { x += _vec.x; y += _vec.y; z += _vec.z; return *this; }
	Vector4& operator -=(const XMFLOAT3& _vec) { x -= _vec.x; y -= _vec.y; z -= _vec.z; return *this; }
	Vector4& operator *=(const XMFLOAT3& _vec) { x *= _vec.x; y *= _vec.y; z *= _vec.z; return *this; };
	Vector4& operator /=(const XMFLOAT3& _vec) { x /= _vec.x; y /= _vec.y; z /= _vec.z; return *this; }
	Vector4& operator +=(const XMFLOAT4& _vec) { x += _vec.x; y += _vec.y; z += _vec.z; w += _vec.w; return *this; };
	Vector4& operator -=(const XMFLOAT4& _vec) { x -= _vec.x; y -= _vec.y; z -= _vec.z; w -= _vec.w; return *this; };
	Vector4& operator *=(const XMFLOAT4& _vec) { x *= _vec.x; y *= _vec.y; z *= _vec.z; w *= _vec.w; return *this; };
	Vector4& operator /=(const XMFLOAT4& _vec) { x /= _vec.x; y /= _vec.y; z /= _vec.z; w /= _vec.w; return *this; }

	const Vector4 operator *(const float _value) const { return Vector4(x * _value, y * _value, z * _value, w * _value); }
	const Vector4 operator /(const float _value) const { return Vector4(x / _value, y / _value, z / _value, w / _value); }
	const Vector4 operator +(const XMFLOAT2& _vec)const { return  Vector4(x + _vec.x, y + _vec.y, z, w); }
	const Vector4 operator -(const XMFLOAT2& _vec)const { return  Vector4(x - _vec.x, y - _vec.y, z, w); }
	const Vector4 operator *(const XMFLOAT2& _vec)const { return  Vector4(x * _vec.x, y * _vec.y, z, w); }
	const Vector4 operator /(const XMFLOAT2& _vec)const { return  Vector4(x / _vec.x, y / _vec.y, z, w); }
	const Vector4 operator +(const XMFLOAT3& _vec)const { return  Vector4(x + _vec.x, y + _vec.y, z + _vec.z, w); }
	const Vector4 operator -(const XMFLOAT3& _vec)const { return  Vector4(x - _vec.x, y - _vec.y, z - _vec.z, w); }
	const Vector4 operator *(const XMFLOAT3& _vec)const { return  Vector4(x * _vec.x, y * _vec.y, z * _vec.z, w); }
	const Vector4 operator /(const XMFLOAT3& _vec)const { return  Vector4(x / _vec.x, y / _vec.y, z / _vec.z, w); }
	const Vector4 operator +(const XMFLOAT4& _vec)const { return  Vector4(x + _vec.x, y + _vec.y, z + _vec.z, w + _vec.w); }
	const Vector4 operator -(const XMFLOAT4& _vec)const { return  Vector4(x - _vec.x, y - _vec.y, z - _vec.z, w - _vec.w); }
	const Vector4 operator *(const XMFLOAT4& _vec)const { return  Vector4(x * _vec.x, y * _vec.y, z * _vec.z, w * _vec.w); }
	const Vector4 operator /(const XMFLOAT4& _vec)const { return  Vector4(x / _vec.x, y / _vec.y, z / _vec.z, w / _vec.w); }

	const float& operator [](const int _index)const { return *((&x) + _index); }
	float& operator [](const int _index) { return *((&x) + _index); }
#pragma endregion

#pragma region function
	float Length() { return sqrtf(x * x + y * y + z * z); }

	static float Dot(const Vector4& _vec1, const Vector4& _vec2)
	{
		float _ans;
		DirectX::XMStoreFloat(&_ans, DirectX::XMVector4Dot(DirectX::XMVector4Normalize(DirectX::XMLoadFloat4(&_vec1)), DirectX::XMVector4Normalize(DirectX::XMLoadFloat4(&_vec2))));
		return _ans;
	}
	static Vector4 Cross(const Vector4& _vec1, const Vector4& _vec2)
	{
		Vector4 _ans;
		DirectX::XMStoreFloat4(&_ans, DirectX::XMVector2Cross(DirectX::XMVector4Normalize(DirectX::XMLoadFloat4(&_vec1)), DirectX::XMVector4Normalize(DirectX::XMLoadFloat4(&_vec2))));
		return _ans;
	}
#pragma endregion
};
