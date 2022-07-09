#pragma once
#include <vector>
#include "Polygon3D.h"
#include "vertex.h"
#include "matrix.h"
#include "Camera.h"
#include "Vector.h"
#include "DirectionalLighting.h"
#include <gdiplus.h>

using namespace std;

class Model
{
public:

	//Default Constructor
	Model();

	//Destructor
	~Model();

	//Method to calculate the backfaces using the camera object
	void CalculateBackFaces(Camera camera);

	//Sort method to order the polygons in the collection
	void Sort(void);

	const vector<Polygon3D>& GetPolygons();
	const vector<Vertex>& GetVertices();
	size_t GetPolygonCount() const;
	size_t GetVertexCount() const;
	void AddVertex(float x, float y, float z);
	void AddPolygon(int i0, int i1, int i2);

	size_t GetDirectionalLightCount() const;

	const vector<Vertex>& GetTransVertices();

	//ApplyTransformToLocalVertices multiplies the transformation matrix to each vertex
	void ApplyTransformToLocalVertices(const Matrix& transfrom);

	//applies the transformation matrix to each vertex in the transformed vertices collection
	void ApplyTransformToTransformedVertices(const Matrix& transform);

	//To dehomogenize each vertex in the transformed vertices collection.
	void dehomogenize();



	float GetKD_Red() const;
	void SetKD_Red(const float KD_Red);

	float GetKD_Green() const;
	void SetKD_Green(const float KD_Green);

	float GetKD_Blue() const;
	void SetKD_Blue(const float KD_Blue);

	void CalculateLightingDirectional(DirectionalLighting light, Model model);

private:

	Matrix transformationMatrix = Matrix{ 1, 0, 0, 0,
								          0, 1, 0, 0,
								          0, 0, 1, 0,
										  0, 0, 0, 1};

	vector<Polygon3D> _polygons;
	vector<Vertex> _vertices;
	vector<Vertex> _transformedVertices;
	vector<DirectionalLighting> _DirectionalLighting;

	float _KDred, _KDgreen, _KDblue;



	
};