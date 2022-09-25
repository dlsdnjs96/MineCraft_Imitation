#pragma once
namespace Util
{

	void Replace(string* str, string comp, string rep);
	void Replace(wstring* str, wstring comp, wstring rep);

	wstring ToWString(string value);
	string ToString(wstring value);

	float NormalizeAngle(float angle);
	Vector3 NormalizeAngles(Vector3 angles);
	Vector3 QuaternionToYawPtichRoll(Quaternion q1);


	bool RayIntersectTri(IN Ray WRay, IN GameObject* Target, OUT Vector3& HitPoint);

	bool RayIntersectTriNear(IN Ray WRay, IN GameObject* Target, OUT Vector3& HitPoint);

	bool RayIntersectMap(IN Ray WRay, IN GameObject* Terrain, OUT Vector3& HitPoint);


	void NdcToScreen(Vector3& pos);
	void ScreenToNdc(Vector3& pos);
	bool WorldToScreen(Vector3 pos, Vector2& screen, Matrix matrix, int windowWidth, int windowHeight);
	bool IsInScreen(Vector3 pos, Matrix matrix);

	Ray MouseToRay(Vector3 Mouse, Camera* Cam);

	template<typename T>
	//			3     5  
	T Lerp(T from, T to, float value)
	{
		return from + (to - from) * value;
	}
	template<typename T>
	T Quadratic(T p1, T p2, T p3, float value)
	{
		return Lerp(Lerp(p1, p2, value), Lerp(p2, p3, value), value);
	}
	template<typename T>
	T Cubic(T p1, T p2, T p3, T p4, float value)
	{
		return Quadratic(Lerp(p1, p2, value), Lerp(p2, p3, value), 
			Lerp(p3, p4, value), value);
	}
	template <typename T>
	static T Saturate(T& in, T min = 0, T max = 1)
	{
		if (in < min)
		{
			in = min;
			return min;
		}
		else if (in > max)
		{
			in = max;
			return max;
		}
		return in;
	}
}