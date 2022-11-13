#pragma once

class MeshFactory : public Singleton<MeshFactory>
{
private:
public:
	void OneFaceBlock();
	shared_ptr<Mesh> EditMesh(EditObject& _editObject);
};

