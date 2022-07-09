#pragma once
#include "Framework.h"
#include "vertex.h"
#include <vector>
#include "matrix.h"
#include "MD2Loader.h"
#include "Model.h"
#include "Camera.h"
#include "Polygon3D.h"
#include "PolygonAmbientLighting.h"
#include "DirectionalLighting.h"

class Rasteriser : public Framework
{
public:

	bool Initialise();

	void Update(const Bitmap& bitmap);
	void Render(const Bitmap& bitmap);
	void Shutdown();

	void DrawSolidFlat(const Bitmap& bitmap);

	//const vector<DirectionalLighting>& DirectionalLighting;


	Vertex vertexArray[4];
	Matrix translateMatrix;

	//generates the perspective matrix
	void GeneratePerspectiveMatrix(float d, float aspectRatio);

	//generates the screen view matrix
	void GenerateViewMatrix(float d, int width, int height);

	//Draws wireframe
	void DrawWireFrame(const Bitmap& bitmap);




private:

	Model _model;
	Matrix _currentModelTransformation; 
	Matrix _perspectiveMatrix;
	Matrix _XrotationMatrix;
	Matrix _YrotationMatrix;
	Matrix _ViewMatrixTransformation;
	Matrix _ScaleMatrix;
	Matrix _DeScaleMatrix;
	Matrix _TranslationMatrix;
	Matrix _DeTranslateMatrix;
	Camera _camera;
	DirectionalLighting _directionalLighting;
	Vector _directionalLightingVector;

	int _height;
	int _width;
	int _frameCounter = 0;
	int _frameCounterBackfaces = 860;
	int _frameCounterDrawSolidFlat = 1000;
};

