#pragma once
class UI : public Actor
{
public:
	static UI* Create(string name = "UI");
	static UI* CreateChild(string name);
	virtual void	Update() override;
	bool			Press = false;
	bool			Over = false;
	function<void()> mouseOver = nullptr; //���콺�� ���������ҋ�
	function<void()> mouseDown = nullptr; // ������ �������� �ѹ�
	function<void()> mousePress = nullptr; // ������ ������
	function<void()> mouseUp = nullptr; //������ ��������
};

