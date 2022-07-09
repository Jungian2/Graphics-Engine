#include "Model.h"
#include <algorithm>

//Default Constructor
Model::Model()
{
	_KDred = 1.0f;
	_KDgreen = 1.0f;
	_KDblue = 1.0f;

}

//Destructor
Model::~Model()
{
}

void Model::CalculateBackFaces(Camera camera)
{
	for (int i = 0; i < GetPolygonCount(); i++)
	{
		int index0 = _polygons[i].GetIndex(0);
		int index1 = _polygons[i].GetIndex(1);
		int index2 = _polygons[i].GetIndex(2);

		const Vertex vertex0 = _transformedVertices[index0];
		const Vertex vertex1 = _transformedVertices[index1];
		const Vertex vertex2 = _transformedVertices[index2];

		Vector vectorA = Vector::SubVertex(vertex0, vertex1);
		Vector vectorB = Vector::SubVertex(vertex0, vertex2);
		Vector vectorNormal = Vector::CrossProduct(vectorB, vectorA);

		Vector eyeVector = Vector::SubVertex(vertex0, camera.GetViewingPosition());
		Vector GetDotProduct;
		float dotProduct = Vector::CreateDotProduct(vectorNormal, eyeVector);

		if (dotProduct < 0)
		{
			_polygons[i].SetCulling(true);
		}
		else
		{
			_polygons[i].SetCulling(false);
		}
		_polygons[i].SetNormalVector(vectorNormal);
	}
}

bool Predicate(Polygon3D polygon1, Polygon3D polygon2)
{
	if (polygon1.GetZAvgDepth() > polygon2.GetZAvgDepth())
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Model::Sort(void)
{
	for (int i = 0; i < GetPolygonCount(); i++)
	{
		int index0 = _polygons[i].GetIndex(0);
		int index1 = _polygons[i].GetIndex(1);
		int index2 = _polygons[i].GetIndex(2);

		const Vertex vertex0 = _transformedVertices[index0];
		const Vertex vertex1 = _transformedVertices[index1];
		const Vertex vertex2 = _transformedVertices[index2];

		float zDepthAvg = ((vertex0.GetZ() + vertex1.GetZ() + vertex2.GetZ()) / 3);
		_polygons[i].SetZAvgDepth(zDepthAvg);
	}
	sort(_polygons.begin(), _polygons.end(), Predicate);
}

const vector<Polygon3D>& Model::GetPolygons()
{
	// TODO: insert return statement here
	return _polygons;
}

const vector<Vertex>& Model::GetVertices()
{
	// TODO: insert return statement here
	return _vertices;

}

size_t Model::GetPolygonCount() const
{
	return _polygons.size();
}

size_t Model::GetVertexCount() const
{
	return _vertices.size();
}

void Model::AddVertex(float x, float y, float z)
{
	_vertices.push_back(Vertex(x, y, z));
}

void Model::AddPolygon(int i0, int i1, int i2)
{
	_polygons.push_back(Polygon3D(i0, i1, i2));
}

const vector<Vertex>& Model::GetTransVertices()
{
	// TODO: insert return statement here
	return _transformedVertices;
}

void Model::ApplyTransformToLocalVertices(const Matrix& transfrom)
{

	_transformedVertices.clear();

	for (int i = 0; i < _vertices.size(); i++ )
	{
		_transformedVertices.push_back(transfrom * _vertices[i]);
		
	}
}

void Model::ApplyTransformToTransformedVertices(const Matrix& transform)
{
	for (int i = 0; i < _vertices.size(); i++)
	{
		_transformedVertices[i] = transform * _transformedVertices[i];

	}
}

void Model::dehomogenize()
{
	for (int i = 0; i < _vertices.size(); i++)
	{
		_transformedVertices[i].Dehomogenzied();
	}
}

float Model::GetKD_Red() const
{
	return _KDred;
}

void Model::SetKD_Red(const float KD_Red)
{
	_KDred = KD_Red;
}

float Model::GetKD_Green() const
{
	return _KDgreen;
}

void Model::SetKD_Green(const float KD_Green)
{
	_KDgreen = KD_Green;
}

float Model::GetKD_Blue() const
{
	return _KDblue;
}

void Model::SetKD_Blue(const float KD_Blue)
{
	_KDblue = KD_Blue;
}


void Model::CalculateLightingDirectional(const DirectionalLighting& light, int numLights, const Vector& camera)
{
	float total_R;
	float total_G;
	float total_B;

	for (int i = 0; i < GetPolygonCount(); i++)
	{
		total_R = 0;
		total_G = 0;
		total_B = 0;
		
	}

}

