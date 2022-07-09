#include "Model.h"
#include <algorithm>
#include "DirectionalLighting.h"
//Default Constructor
Model::Model()
{
	_KDred = 1.0f;
	_KDgreen = 0.2f;
	_KDblue = 1.0f;

}

//Destructor
Model::~Model()
{
}

//Calculate Backfaces Method
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

size_t Model::GetDirectionalLightCount() const
{
	return _DirectionalLighting.size();
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


void Model::CalculateLightingDirectional(DirectionalLighting light, Model model)
{

	COLORREF TotalRGB;
	int TempRed = 1;
	int TempGreen = 1;
	int TempBlue = 1;


	for (int i = 0; i < GetPolygonCount(); i++)
	{
		TotalRGB = RGB(0, 0, 0);

		for (int j = 0; j < GetDirectionalLightCount(); j++)
		{

			//TempRed = (int)light.SetRedDirectionalValue();
			//TempGreen = (int)light.SetGreenDirectionalValue();
			//TempBlue = (int)light.SetBlueDirectionalValue();
			light.SetRedDirectionalValue(TempRed);
			light.SetGreenDirectionalValue(TempGreen);
			light.SetBlueDirectionalValue(TempBlue);


			TempRed = TempRed * (int)model.GetKD_Red();
			TempGreen = TempGreen * (int)model.GetKD_Green();
			TempBlue = TempBlue * (int)model.GetKD_Blue();

			float Vector01 = Vector::CreateDotProduct(light.GetLightDirectionVector(), _polygons[i].GetNormalVector());

			
			int TempRGBMultiply = (TempRed + TempGreen + TempBlue);

			float ResultOfMultiply = TempRGBMultiply * Vector01;

			TotalRGB = RGB((int)TempRed, (int)TempGreen, (int)TempBlue);

			if (TempRed > 255)
			{
				TempRed = 255;
			}
			if (TempRed < 0)
			{
				TempRed = 0;
			}

			if (TempGreen > 255)
			{
				TempGreen = 255;
			}
			if (TempGreen < 0)
			{
				TempGreen = 0;
			}

			if (TempBlue > 255)
			{
				TempBlue = 255;
			}
			if (TempBlue < 0)
			{
				TempBlue = 0;
			}

			_polygons[i].SetPolygon3dColor(TempRed, TempGreen, TempBlue);
			
			
		}

	}
}

