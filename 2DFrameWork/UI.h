#pragma once
class UI : public Actor
{
public:
	static UI* Create(string name = "UI");
	virtual void	Update() override;
	bool			Press = false;
	bool			prevOver = false;
	bool			over = false;
	function<void()> mouseOver = nullptr; //마우스가 위에존재할떄
	function<void()> mouseNotOver = nullptr; //마우스가 위에존재할떄
	function<void()> mouseDown = nullptr; // 위에서 눌렀을때 한번
	function<void()> mouseDownR = nullptr; // 위에서 눌렀을때 한번
	function<void()> mousePress = nullptr; // 누르고 있을때
	function<void()> mouseUp = nullptr; //누르고 떼었을때

	bool MouseOver();
};

