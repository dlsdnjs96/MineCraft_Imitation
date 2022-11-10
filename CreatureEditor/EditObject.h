#pragma once

class EditObject : public GameObject
{
private:
	Vector3 meshFrom;
	Vector3 meshSize;

	pair<Vector2, Vector2> uvUp;
	pair<Vector2, Vector2> uvDown;
	pair<Vector2, Vector2> uvFront;
	pair<Vector2, Vector2> uvBack;
	pair<Vector2, Vector2> uvRight;
	pair<Vector2, Vector2> uvLeft;
public:
	virtual void	Release() override;
	virtual void	Update() override;
	virtual void	Render(class Shader* otherShader = nullptr) override;
	virtual void	RenderDetail() override;

};

