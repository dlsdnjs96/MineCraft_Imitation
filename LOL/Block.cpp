#include "stdafx.h"

Block2::Block2()
{
	for (int i = 0;i < 6;i++)
		meshList[sixFaces[i]]  = RESOURCE->meshes.Load("Block/"+to_string(sixFaces[i])+".mesh");
	shader = RESOURCE->shaders.Load("block.hlsl");
}


void Block2::Update()
{
	GameObject::Update();
}

void Block2::Render()
{
	if (visible)
	{
		for (auto& it : meshList) {
			if ((renderFaces & it.first) and it.second and shader and material)
			{
				Transform::Set();
				shader->Set();
				it.second->Set();
				material->Set();

				D3D->GetDC()->DrawIndexed(it.second->indexCount, 0, 0);
			}
		}
	}

}



void Block2::RenderDetail()
{
}
