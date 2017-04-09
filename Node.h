#pragma once

#include <d3dx9.h>
#include <string>
#include <memory>
#include <functional>
#include "Types.h"

class Node
{
private:
	bool _is_removed_;
	bool _on_camera_;
protected:
	Node* parent = nullptr;
public:
	Vector2 position;
	Vector2 scale;
	float rotation;

	int zOrder= 0;

	std::string name;

	void* userPtr;
public:
	Node();
	virtual ~Node() {}

	virtual void Update() {}

	void SetParent(Node* pParent);
	Node* GetParent();

	Matrix4 GetTransform() const;

	virtual void Draw() {}

	void AttachedCamera(bool attach);

	Vector2 GetParentCoord();

	virtual void Remove();
	bool __is_removed__() { return _is_removed_; }
};