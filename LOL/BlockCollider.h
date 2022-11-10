#pragma once

class BlockCollider : public Transform
{
private:
	shared_ptr<Mesh> colliders[3][3][3];
public:
	void Update();
};

