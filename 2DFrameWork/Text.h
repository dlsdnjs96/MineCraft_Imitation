#pragma once

class Text : public Actor
{
private:
public:
	string text;
	static Text* Create(string name = "Text");

	void ChangeText(string _text);
};

