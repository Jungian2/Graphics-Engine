#pragma once
#include "Vector.h"
#include <Windows.h>
#include <gdiplus.h>
class Polygon3D
{
public:

	// Default constructor
	Polygon3D();

	Polygon3D(int index0, int index1, int index2);

	//Destructor
	~Polygon3D();

	Polygon3D(const Polygon3D& p);

	int GetIndex(int x) const;

	//Accessors and Mutator functions for Culling
	bool IsCulling() const;
	void SetCulling(bool value);

	//Accessors and Mutator functions for the Vector normal
	Vector GetNormalVector() const;
	void SetNormalVector(Vector vector);

	Polygon3D& operator= (const Polygon3D& rhs);

	//Accessors and Mutator functions for getting and setting the Z depth avg
	float GetZAvgDepth() const;
	void SetZAvgDepth(const float avg);



	COLORREF GetPolygon3dColor() const;
	void SetPolygon3dColor(int r, int g, int b);

private:

	COLORREF _polygon3dColor;
	bool _culling = false;
	Vector _normalVector;
	int _indices[3];
	float _avg;
};