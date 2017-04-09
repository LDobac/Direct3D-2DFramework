#include "DXUT.h"
#include "Node.h"
#include "Camera.h"

Node::Node()
	: position(0,0), scale(1,1),rotation(0),parent(nullptr),_is_removed_(false),_on_camera_(false)
{
}

void Node::SetParent(Node* pParent)
{
	parent = pParent;
}

Node* Node::GetParent()
{
	return parent;
}

Matrix4 Node::GetTransform() const
{
	Matrix4 matrix;
	D3DXMatrixIdentity(&matrix);

	Vector2 pos = position;
	if (_on_camera_ || parent != nullptr)
	{
		D3DXMatrixTransformation2D(&matrix, nullptr, 0, &scale, nullptr, rotation, &pos);
	}
	else
	{
		D3DXMatrixTransformation2D(&matrix, nullptr, 0, &scale, nullptr, rotation, &(pos - Camera::GetInstance()->position));
	}
	
	if (parent != nullptr)
	{
		matrix *= parent->GetTransform();
	}

	return matrix;
}

void Node::AttachedCamera(bool attach)
{
	_on_camera_ = attach;
}

Vector2 Node::GetParentCoord()
{
	if (parent != nullptr)
	{
		return parent->position + position;
	}
	return Vector2();
}

void Node::Remove()
{
	_is_removed_ = true;
}
