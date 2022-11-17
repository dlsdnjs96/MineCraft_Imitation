#include "framework.h"

EditObject* EditObject::Create(string name)
{
    EditObject* temp = new EditObject();
    temp->name = name;
    temp->type = ObType::Edit;


    temp->shader = RESOURCE->shaders.Load("Block.hlsl");
    return temp;
}

void EditObject::Release()
{
}

void EditObject::Update()
{
	GameObject::Update();
}


void EditObject::RenderDetail()
{
	GameObject::RenderDetail();
    if (ImGui::BeginTabBar("MyTabBar3"))
	{
		if (ImGui::BeginTabItem("EditObject"))
		{
			if (ImGui::Button("Edit Mesh"))
			{
                if (mesh)
                    mesh.reset();
                mesh = EditMesh();

                //filesystem::create_directory("../Contents/Mesh/" + root->name);
                mesh->SaveFile(root->name + "/" + name + ".mesh");
			}
			if (ImGui::Button("Save Mesh"))
			{
                mesh->SaveFile(root->name+"/"+name+".mesh");
			}

			ImGui::NewLine();
			ImGui::InputFloat("imgSize X", &imgSize.x);
			ImGui::InputFloat("imgSize Y", &imgSize.y);

			ImGui::NewLine();
			ImGui::InputFloat("meshFrom X", &meshFrom.x);
			ImGui::InputFloat("meshFrom Y", &meshFrom.y);
			ImGui::InputFloat("meshFrom Z", &meshFrom.z);

			ImGui::NewLine();
			ImGui::InputFloat("meshSize X", &meshSize.x);
			ImGui::InputFloat("meshSize Y", &meshSize.y);
			ImGui::InputFloat("meshSize Z", &meshSize.z);

			ImGui::NewLine();
			ImGui::InputFloat("uvUp from X", &uvUp.first.x);
			ImGui::InputFloat("uvUp from Y", &uvUp.first.y);
			ImGui::InputFloat("uvUp to X", &uvUp.second.x);
			ImGui::InputFloat("uvUp to Y", &uvUp.second.y);

			ImGui::NewLine();
			ImGui::InputFloat("uvDown from X", &uvDown.first.x);
			ImGui::InputFloat("uvDown from Y", &uvDown.first.y);
			ImGui::InputFloat("uvDown to X", &uvDown.second.x);
			ImGui::InputFloat("uvDown to Y", &uvDown.second.y);

			ImGui::NewLine();
			ImGui::InputFloat("uvFront from X", &uvFront.first.x);
			ImGui::InputFloat("uvFront from Y", &uvFront.first.y);
			ImGui::InputFloat("uvFront to X", &uvFront.second.x);
			ImGui::InputFloat("uvFront to Y", &uvFront.second.y);

			ImGui::NewLine();
			ImGui::InputFloat("uvBack from X", &uvBack.first.x);
			ImGui::InputFloat("uvBack from Y", &uvBack.first.y);
			ImGui::InputFloat("uvBack to X", &uvBack.second.x);
			ImGui::InputFloat("uvBack to Y", &uvBack.second.y);

			ImGui::NewLine();
			ImGui::InputFloat("uvRight from X", &uvRight.first.x);
			ImGui::InputFloat("uvRight from Y", &uvRight.first.y);
			ImGui::InputFloat("uvRight to X", &uvRight.second.x);
			ImGui::InputFloat("uvRight to Y", &uvRight.second.y);

			ImGui::NewLine();
			ImGui::InputFloat("uvLeft from X", &uvLeft.first.x);
			ImGui::InputFloat("uvLeft from Y", &uvLeft.first.y);
			ImGui::InputFloat("uvLeft to X", &uvLeft.second.x);
			ImGui::InputFloat("uvLeft to Y", &uvLeft.second.y);
			ImGui::EndTabItem();
		}
		ImGui::EndTabBar();
	}
}

shared_ptr<Mesh> EditObject::EditMesh()
{
    VertexP cubeEdges[8] = {
    {{ -1.f, 1.f,  -1.f }},
    {{ -1.f, 1.f,  1.f }},
    {{ 1.f,  1.f,  1.f }},
    {{ 1.f,  1.f,  -1.f }},
    {{ -1.f, -1.f, -1.f }},
    {{ -1.f, -1.f, 1.f }},
    {{ 1.f,  -1.f, 1.f }},
    {{ 1.f,  -1.f, -1.f }}
    };

    int edgesIndex[6][4] = {
        { 3, 2, 1, 0 },
        { 6, 7, 4, 5 },
        { 6, 2, 3, 7 },
        { 4, 0, 1, 5 },
        { 7, 3, 0, 4 },
        { 5, 1, 2, 6 }
    };
    Vector2 uvs[4] = {
        { 1.f, 1.f },
        { 0.f, 1.f },
        { 0.f, 0.f },
        { 1.f, 0.f }
    };
    Vector3 normals[6] = {
        { 0.f, 1.f, 0.f },
        { 0.f, -1.f, 0.f },
        { 1.f, 0.f, 0.f },
        { -1.f, 0.f, 0.f },
        { 0.f, 0.f, -1.f },
        { 0.f, 0.f, 1.f }
    };

    pair<Vector2, Vector2> uvArr[6] = { uvUp, uvDown, uvRight, uvLeft, uvBack, uvFront };

    VertexPTN* vertices;
    UINT vertexCount = 6 * 4;
    UINT* indices;
    UINT indexCount = 6 * 6;
    VertexType type = VertexType::PTN;

    vertices = new VertexPTN[vertexCount];
    indices = new UINT[indexCount];

    int vIndex = 0, iIndex = 0;

    for (int i = 0; i < 8; i++)
    {
        cubeEdges[i].position.x *= meshSize.x;
        cubeEdges[i].position.y *= meshSize.y;
        cubeEdges[i].position.z *= meshSize.z;

        cubeEdges[i].position.x += meshFrom.x;
        cubeEdges[i].position.y += meshFrom.y;
        cubeEdges[i].position.z += meshFrom.z;
    }


    for (int j = 0; j < 6; j++) {

        for (int i = 0; i < 4; i++) {
            vertices[vIndex].position = cubeEdges[edgesIndex[j][i]].position;
            vertices[vIndex].normal = normals[j];
            //vertices[vIndex].uv = uvs[j];
            vIndex++;
        }
        vertices[vIndex - 4].uv = { uvArr[j].second.x / imgSize.x, uvArr[j].second.y / imgSize.y };
        vertices[vIndex - 3].uv = { uvArr[j].second.x / imgSize.x, uvArr[j].first.y / imgSize.y };
        vertices[vIndex - 2].uv = { uvArr[j].first.x / imgSize.x, uvArr[j].first.y / imgSize.y };
        vertices[vIndex - 1].uv = { uvArr[j].first.x / imgSize.x, uvArr[j].second.y / imgSize.y };


        int arr[6] = { 3, 2, 0, 2, 1, 0 };

        for (int i = 0; i < 6; i++) {
            indices[iIndex] = arr[i] + vIndex - 4;
            iIndex++;
        }
    }


    printf("Edited mesh\r\n");
    return make_shared<Mesh>(vertices, vertexCount, indices, indexCount, type);
}