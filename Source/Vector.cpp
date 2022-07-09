#include "Vector.h"


Vector::Vector()
{
	_x = 0.0f;
	_y = 0.0f;
	_z = 0.0f;
	_w = 1;
}

//Destructor
Vector::~Vector()
{
}

Vector::Vector(float x, float y, float z)
{
	_x = x;
	_y = y;
	_z = z;
	_w = 1;
}

//Takes two vectors as operands and returns a real number as a result
float Vector::CreateDotProduct(const Vector& Vector1, const Vector& Vector2)
{
	float dotProduct = 0.0f;
	dotProduct = dotProduct + Vector1.GetX() * Vector2.GetX();
	dotProduct = dotProduct + Vector1.GetY() * Vector2.GetY();
	dotProduct = dotProduct + Vector1.GetZ() * Vector2.GetZ();
	return dotProduct;
}

//Takes two vectors as operands and returns a vector
Vector Vector::CrossProduct(const Vector& vector1, const Vector& vector2)
{
	Vector CrossProductResult;
	CrossProductResult.SetX(vector1.GetY() * vector2.GetZ() - vector1.GetZ() * vector2.GetY());
	CrossProductResult.SetY(vector1.GetZ() * vector2.GetX() - vector1.GetX() * vector2.GetZ());
	CrossProductResult.SetZ(vector1.GetX() * vector2.GetY() - vector1.GetY() * vector2.GetX());

	return CrossProductResult;
}

Vector Vector::SubVertex(const Vertex& vertex1, const Vertex& vertex2)
{
	Vector SubVertexResult;
	SubVertexResult.SetX(vertex1.GetX() - vertex2.GetX());
	SubVertexResult.SetY(vertex1.GetY() - vertex2.GetY());
	SubVertexResult.SetZ(vertex1.GetZ() - vertex2.GetZ());

	return SubVertexResult;
}

float Vector::GetX() const
{
	return _x;
}

void Vector::SetX(const float x)
{
	_x = x;
}

float Vector::GetY() const
{
	return _y;
}

void Vector::SetY(const float y)
{
	_y = y;
}

float Vector::GetZ() const
{
	return _z;
}

void Vector::SetZ(const float z)
{
	_z = z;
}

