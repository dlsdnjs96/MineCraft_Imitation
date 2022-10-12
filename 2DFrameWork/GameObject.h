#pragma once

enum class ObType
{
	GameObject,
	Actor,
	Camera,
	Terrain,
	UI
};

class GameObject : public Transform
{
	friend class Actor;
	//static
private:
	static GameObject*		axis;
	static Material*		defalutMaterial;
public:
	static GameObject* Create(string name = "GameObject");
	static void CreateStaticMember();
	static void DeleteStaticMember();
	//member
protected:
	ObType						type;
public:
	int                         boneIndex = -1;
	string						name;	//key
	bool						visible;
	class Actor*				root;
	map<string, GameObject*>	children;
	shared_ptr<Shader>			shader;
	shared_ptr<Mesh>			mesh;
	shared_ptr<Material>		material;
	Collider*					collider;
	//Method
	GameObject();
protected:
	virtual	~GameObject();
	void	SaveObject(Xml::XMLElement* This, Xml::XMLDocument* doc);
	void	LoadObject(Xml::XMLElement* This);
public:
	void			Release();
	virtual void	Update();
	virtual void	Render();
	void			AddChild(GameObject* child);
	void			AddBone(GameObject* child);
	bool			RenderHierarchy();
	virtual void	RenderDetail();
	ObType			GetObType();

	//Getter Setter
};


class Actor : public GameObject
{
	friend GameObject;
private:
	
public:
	unordered_map<string, GameObject*> obList;
	int             boneIndexCount = 0;
	string			file;
	Skeleton*		skeleton;
	Animations*		anim;
protected:
	Actor();
	virtual	~Actor();
public:
	void			Release();
	void			ReleaseMember();
	static Actor*	Create(string name = "Actor");
	GameObject*		Find(string name);
	bool            DeleteObject(string Name);
	void			SaveFile(string file);
	void			LoadFile(string file);
	virtual void	RenderDetail();
	virtual void	Update();
	virtual void    Render();
};
