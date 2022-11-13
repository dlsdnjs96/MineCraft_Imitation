#pragma once

class EditObject : public GameObject
{
private:
public:
	Vector3 meshFrom = { 0.f, 0.f, 0.f };
	Vector3 meshSize = { 1.f, 1.f, 1.f };

	pair<Vector2, Vector2> uvUp = { { 0.f, 0.f }, { 1.f, 1.f } };
	pair<Vector2, Vector2> uvDown = { { 0.f, 0.f }, { 1.f, 1.f } };
	pair<Vector2, Vector2> uvFront = { { 0.f, 0.f }, { 1.f, 1.f } };
	pair<Vector2, Vector2> uvBack = { { 0.f, 0.f }, { 1.f, 1.f } };
	pair<Vector2, Vector2> uvRight = { { 0.f, 0.f }, { 1.f, 1.f } };
	pair<Vector2, Vector2> uvLeft = { { 0.f, 0.f }, { 1.f, 1.f } };

	static EditObject* Create(string name);
	virtual void	Release() override;
	virtual void	Update() override;
	virtual void	RenderDetail() override;
	shared_ptr<Mesh> EditMesh();
};

