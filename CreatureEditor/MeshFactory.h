#pragma once

class MeshFactory : public Singleton<MeshFactory>
{
private:
public:
	void OneFaceBlock();
	shared_ptr<Mesh> EditMesh(EditObject& _editObject);
	shared_ptr<Mesh> CrossMesh();
	shared_ptr<Mesh> SharpMesh();
	shared_ptr<Mesh> ItemMesh();
};

