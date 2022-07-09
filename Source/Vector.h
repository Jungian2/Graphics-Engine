#pragma once
#include "vertex.h"
class Vector
{
public:

	//Default constructor
	Vector();

	//Destructor
	~Vector();

	//
	Vector(float x, float y, float z);

	static float CreateDotProduct(const Vector& Vector1, const Vector& Vector2);
	static Vector CrossProduct(const Vector& vector1, const Vector& vector2);
	static Vector SubVertex(const Vertex& vertex1, const Vertex& vertex2);

	//Accessors and Mutators for getting and setting the X value that is used to calculate the
	//cross product and SubVertex
	float GetX() const;
	void SetX(const float x);

	//Accessors and Mutators for getting and setting the Y value that is used to calculate the
	//cross product and SubVertex
	float GetY() const;
	void SetY(const float y);

	//Accessors and Mutators for getting and setting the Z value that is used to calculate the
	//cross product and SubVertex
	float GetZ() const;
	void SetZ(const float z);


private:

	float _x;
	float _y;
	float _z;
	float _w;
};

