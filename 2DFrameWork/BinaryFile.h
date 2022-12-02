#pragma once

class BinaryWriter
{
public:
	BinaryWriter();
	~BinaryWriter();

	void Open(wstring filePath, UINT openOption = CREATE_ALWAYS);
	void Close();

	void Bool(bool data);
	void Word(WORD data);
	void Int(int data);
	void Int_2(Int2 data);
	void Int_3(Int3 data);
	void Int_4(Int4 data);
	void UInt(UINT data);
	void Float(float data);
	void Double(double data);
	void Char(char data);
	void Uchar(unsigned char data);

	void vector2(const Vector2& data);
	void vector3(const Vector3& data);
	void vector4(const Vector4& data);
	void color3f(const Color& data);
	void color4f(const Color& data);
	void matrix(const  Matrix& data);

	void String(const string& data);
	void Byte(void* data, UINT dataSize);

protected:
	HANDLE fileHandle;
	DWORD size;
};

//////////////////////////////////////////////////////////////////////////

class BinaryReader
{
public:
	BinaryReader();
	~BinaryReader();

	void Open(wstring filePath);
	void Close();

	bool Bool();
	WORD Word();
	int Int();
	Int2 Int_2();
	Int3 Int_3();
	Int4 Int_4();
	UINT UInt();
	float Float();
	double Double();
	char Char();
	unsigned char Uchar();

	Vector2 vector2();
	Vector3 vector3();
	Vector4 vector4();
	Color color3f();
	Color color4f();
	Matrix matrix();

	string String();
	void Byte(void** data, UINT dataSize);

protected:
	HANDLE fileHandle;
	DWORD size;
};