#include "Polygon3D.h"
#include "Framework.h"


Polygon3D::Polygon3D()
{
	_indices[0] = 0;
	_indices[1] = 0;
	_indices[2] = 0;
	_normalVector = Vector(0, 0, 0);
	_culling = false;
	_avg = 0.0f;

}

Polygon3D::Polygon3D(int index0, int index1, int index2)
{
	_indices[0] = index0;
	_indices[1] = index1;
	_indices[2] = index2;
	_normalVector = Vector(0, 0, 0);
	_culling = false;
	_avg = 0.0f;
}

Polygon3D::~Polygon3D()
{

}

Polygon3D::Polygon3D(const Polygon3D& p)
{
	_indices[0] = p.GetIndex(0);
	_indices[1] = p.GetIndex(1);
	_indices[2] = p.GetIndex(2);
	_polygon3dColor = p.GetPolygon3dColor();
	_culling = p.IsCulling();
	_avg = p.GetZAvgDepth();
}

int Polygon3D::GetIndex(int x) const
{
	return _indices[x];
}

bool Polygon3D::IsCulling() const
{
	return _culling;
}

void Polygon3D::SetCulling(bool value)
{
	_culling = value;
}

Vector Polygon3D::GetNormalVector() const
{
	return _normalVector;
}

void Polygon3D::SetNormalVector(Vector vector)
{
	_normalVector = vector;
}

Polygon3D& Polygon3D::operator=(const Polygon3D& rhs)
{
	// TODO: insert return statement here
	if (this != &rhs)
	{
		_indices[0] = rhs.GetIndex(0);
		_indices[1] = rhs.GetIndex(1);
		_indices[2] = rhs.GetIndex(2);
		_culling = rhs.IsCulling();
		_avg = rhs.GetZAvgDepth();
		_polygon3dColor = rhs.GetPolygon3dColor();
	}
	return *this;
}

float Polygon3D::GetZAvgDepth() const
{
	return _avg;
}

void Polygon3D::SetZAvgDepth(const float avg)
{
	_avg = avg;
}

COLORREF Polygon3D::GetPolygon3dColor() const
{
	return _polygon3dColor;
}

void Polygon3D::SetPolygon3dColor(int r, int g, int b)
{
	_polygon3dColor = COLORREF(RGB(r, g, b));
}


