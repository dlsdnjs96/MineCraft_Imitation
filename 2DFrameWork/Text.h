#pragma once

class Text : public Actor
{
private:
public:
	bool fromLeft;
	string text;
	static Text* Create(string name = "Text");
	void Update();
	void RenderDetail();

	void ChangeText(string _text);
};

