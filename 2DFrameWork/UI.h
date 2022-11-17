#pragma once
class UI : public Actor
{
public:
	static UI* Create(string name = "UI");
	virtual void	Update() override;
	bool			Press = false;
	bool			prevOver = false;
	bool			over = false;
	function<void()> mouseOver = nullptr; //���콺�� ���������ҋ�
	function<void()> mouseNotOver = nullptr; //���콺�� ���������ҋ�
	function<void()> mouseDown = nullptr; // ������ �������� �ѹ�
	function<void()> mouseDownR = nullptr; // ������ �������� �ѹ�
	function<void()> mousePress = nullptr; // ������ ������
	function<void()> mouseUp = nullptr; //������ ��������

	bool MouseOver();
};

