#pragma once


class Player
{
private:
	Vector3 prev;
public:
	Actor* body;

	void Init();
	void Update();
	void Release();

	bool RenderHierarchy();
	void Render();


};

