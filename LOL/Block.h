#pragma once


class Block2 : public GameObject
{
	friend GameObject;
private:
	const int sixFaces[6] = { BLOCK_FACE_UP, BLOCK_FACE_DOWN, BLOCK_FACE_RIGHT, BLOCK_FACE_LEFT, BLOCK_FACE_FORWARD, BLOCK_FACE_BEHIND };
	unordered_map<int, shared_ptr<Mesh>> meshList;
public:
	Int3 blockPos;
	int renderFaces;
	Block2();


public:
	virtual void	RenderDetail();
	virtual void	Update();
	virtual void    Render();
};

