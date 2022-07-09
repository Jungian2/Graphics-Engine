#include "Rasteriser.h"
#include <cmath>

Rasteriser app;

bool Rasteriser::Initialise()
{
	Vertex position = Vertex(0, 0, -50);
	_camera = Camera(0.0f, 0.0f, 0.0f, position);

	vector<DirectionalLighting> _directionalLighting;
	_directionalLighting.push_back(DirectionalLighting(0, 0, 255, (Vector(-1, 0, -1))));


	if (!MD2Loader::LoadModel("MD2\\cartman.md2", _model, &Model::AddPolygon, &Model::AddVertex))
	{
		return false;
	}
	

	float g = 0.01f;

	//Rotate by X-axis
	_XrotationMatrix = Matrix{ 1, 0, 0, 0,
							  0, cos(g), -sin(g), 0,
								0, sin(g), cos(g), 0,
								0, 0, 0, 1 };

	//Rotate by Y-axis
	_YrotationMatrix = Matrix{ cos(g), 0, sin(g), 0,
									0, 1, 0, 0,
								-sin(g), 0, cos(g), 0,
									0, 0, 0, 1 };
	
	//Transformation Matrix
	_currentModelTransformation = Matrix{ 1, 0, 0, 0,
											0, 1, 0, 0,
											0, 0, 1, 0,
											0, 0, 0, 1 };

	//Scale Matrix
	_ScaleMatrix = Matrix{ 1.005f, 0, 0, 0,
						   0, 1.005f, 0, 0,
						   0, 0, 1.005f, 0,
						   0, 0, 0, 1 };

	//DeScale Matrix
	_DeScaleMatrix = Matrix{ 0.995f, 0, 0, 0,
							0, 0.995f, 0, 0,
							0, 0, 0.995f, 0,
							0, 0, 0, 1 };

	//Translation Matrix
	_TranslationMatrix = Matrix{1, 0, 0, 0.2f,
								0, 1, 0, 0,
								0, 0, 1, 0,
								0, 0, 0, 1};

	//DeTranslate Matrix
	_DeTranslateMatrix = Matrix{ 1, 0, 0, -0.2f,
								0, 1, 0, 0,
								0, 0, 1, 0,
								0, 0, 0, 1 };

	return true;
}

void Rasteriser::Update(const Bitmap& bitmap)
{
	//Initialise Frame counter
	_frameCounter = _frameCounter + 1;

	if (_frameCounter < 100)
	{
		_currentModelTransformation = _currentModelTransformation * _ScaleMatrix;
	}
	else if (_frameCounter > 100 && _frameCounter < 200)
	{
		_currentModelTransformation = _currentModelTransformation * _DeScaleMatrix;
	}

	else if (_frameCounter > 200 && _frameCounter < 830)
	{
		_currentModelTransformation = _currentModelTransformation * _XrotationMatrix;
	}

	else if (_frameCounter > 840 && _frameCounter < 1000)
	{
		_currentModelTransformation = _currentModelTransformation * _YrotationMatrix;
	}

	else if (_frameCounter > 1000 && _frameCounter < 1200)
	{
		_currentModelTransformation = _currentModelTransformation * _ScaleMatrix;
	}

	_height = bitmap.GetHeight();
	_width = bitmap.GetWidth();
	float aspectRatio = _width / float(_height);
	float d = 1;
	GeneratePerspectiveMatrix(d, aspectRatio);
	GenerateViewMatrix(d, _width, _height);


}

void Rasteriser::Render(const Bitmap& bitmap)
{
	

	if (_frameCounter < _frameCounterBackfaces)
	{

		bitmap.Clear(RGB(255, 255, 255));
		_model.ApplyTransformToLocalVertices(_currentModelTransformation);
		_model.ApplyTransformToTransformedVertices(_camera.CreateViewingMatrix());
		_model.Sort();
		_model.ApplyTransformToTransformedVertices(_perspectiveMatrix);
		_model.dehomogenize();
		_model.ApplyTransformToTransformedVertices(_ViewMatrixTransformation);

		DrawWireFrame(bitmap);
	}

	if (_frameCounter > _frameCounterBackfaces)
	{
		bitmap.Clear(RGB(255, 255, 255));
		_model.ApplyTransformToLocalVertices(_currentModelTransformation);
		_model.CalculateBackFaces(_camera);
		_model.ApplyTransformToTransformedVertices(_camera.CreateViewingMatrix());
		_model.Sort();
		_model.ApplyTransformToTransformedVertices(_perspectiveMatrix);
		_model.dehomogenize();
		_model.ApplyTransformToTransformedVertices(_ViewMatrixTransformation);

		DrawWireFrame(bitmap);

	}

	if (_frameCounter > _frameCounterDrawSolidFlat)
	{
		bitmap.Clear(RGB(255, 255, 255));
		_model.ApplyTransformToLocalVertices(_currentModelTransformation);
		_model.CalculateBackFaces(_camera);
		_model.CalculateLightingDirectional(_directionalLighting, _model);
		_model.ApplyTransformToTransformedVertices(_camera.CreateViewingMatrix());
		_model.Sort();
		_model.ApplyTransformToTransformedVertices(_perspectiveMatrix);
		_model.dehomogenize();
		_model.ApplyTransformToTransformedVertices(_ViewMatrixTransformation);

		DrawSolidFlat(bitmap);
	}
}

void Rasteriser::Shutdown()
{

}

void Rasteriser::DrawSolidFlat(const Bitmap& bitmap)
{

	//COLORREF color = RGB(93, 63, 211);
	//HPEN hpen = CreatePen(PS_SOLID, 1, color);
	//HBRUSH brush = CreateSolidBrush(color);

	HDC hdc = bitmap.GetDC();

	
	if (_frameCounter > _frameCounterBackfaces)
	{
		//Text Drawing methods
		HDC hdc = bitmap.GetDC();
		SetBkMode(hdc, TRANSPARENT);
		RECT rect = { 40, 40, 200, 200 };
		SetTextColor(hdc, RGB(0, 0, 0));
		SetBkMode(hdc, TRANSPARENT);
		DrawText(hdc, L"Solidflat", -1, &rect, DT_LEFT);
	}

	//SelectObject(hdc, brush);
	//SelectObject(hdc, hpen);

	const vector<Polygon3D>& localPolygonList = _model.GetPolygons();
	const vector<Vertex>& localVerticesCollection = _model.GetTransVertices();

	for (int i = 0; i < localPolygonList.size(); i++)
	{

		if (localPolygonList[i].IsCulling() == false)
		{
			COLORREF localColor = localPolygonList[i].GetPolygon3dColor();
			HPEN hpen = CreatePen(PS_SOLID, 1, localColor);
			HBRUSH brush = CreateSolidBrush(localColor);
			SelectObject(hdc, brush);
			SelectObject(hdc, hpen);
			POINT polygonPoints[3];



			int i0 = localPolygonList[i].GetIndex(0);
			int i1 = localPolygonList[i].GetIndex(1);
			int i2 = localPolygonList[i].GetIndex(2);

			

			Vertex vertex1 = localVerticesCollection[i0];
			Vertex vertex2 = localVerticesCollection[i1];
			Vertex vertex3 = localVerticesCollection[i2];

			vector<Vertex> localPolygonVertexCollection;

			

			localPolygonVertexCollection.push_back(vertex1);
			localPolygonVertexCollection.push_back(vertex2);
			localPolygonVertexCollection.push_back(vertex3);


			polygonPoints[0].x = (LONG)vertex1.GetX();
			polygonPoints[0].y = (LONG)vertex1.GetY();
			polygonPoints[1].x = (LONG)vertex2.GetX();
			polygonPoints[1].y = (LONG)vertex2.GetY();
			polygonPoints[2].x = (LONG)vertex3.GetX();
			polygonPoints[2].y = (LONG)vertex3.GetY();

			Polygon(hdc, polygonPoints, 3);
		}


	}

}


void Rasteriser::GeneratePerspectiveMatrix(float d, float aspectRatio)
{
	
	_perspectiveMatrix = Matrix{ d / aspectRatio, 0, 0, 0,
											0, d, 0, 0,
											0, 0, d, 0,
											0, 0, 1, 0};


	

}

void Rasteriser::GenerateViewMatrix(float d, int width, int height)
{
	_ViewMatrixTransformation = Matrix{ width / 2.0f, 0, 0, width / 2.0f,
										0, -height/2.0f, 0, height/2.0f,
										0, 0, d/2.0f, d/2.0f,
										0, 0, 0, 1};
}

void Rasteriser::DrawWireFrame(const Bitmap& bitmap)
{

	if (_frameCounter < _frameCounterBackfaces)
	{
		//Text Drawing methods
		HDC hdc = bitmap.GetDC();
		SetBkMode(hdc, TRANSPARENT);
		RECT rect = { 40, 40, 200, 200 };
		SetTextColor(hdc, RGB(0, 0, 0));
		SetBkMode(hdc, TRANSPARENT);
		DrawText(hdc, L"Wireframe", -1, &rect, DT_LEFT);
	}

	if (_frameCounter > _frameCounterBackfaces)
	{
		//Text Drawing methods
		HDC hdc = bitmap.GetDC();
		SetBkMode(hdc, TRANSPARENT);
		RECT rect = { 40, 40, 200, 200 };
		SetTextColor(hdc, RGB(0, 0, 0));
		SetBkMode(hdc, TRANSPARENT);
		DrawText(hdc, L"Backface Culling", -1, &rect, DT_LEFT);
	}



	const vector<Polygon3D>& localPolygonList = _model.GetPolygons();
	const vector<Vertex>& localVerticesCollection = _model.GetTransVertices();

	for (int i = 0; i < localPolygonList.size(); i++)
	{
		if (localPolygonList[i].IsCulling() == false)
		{
			int i0 = localPolygonList[i].GetIndex(0);
			int i1 = localPolygonList[i].GetIndex(1);
			int i2 = localPolygonList[i].GetIndex(2);

			Vertex vertex1 = localVerticesCollection[i0];
			Vertex vertex2 = localVerticesCollection[i1];
			Vertex vertex3 = localVerticesCollection[i2];

			vector<Vertex> localPolygonVertexCollection;

			localPolygonVertexCollection.push_back(vertex1);
			localPolygonVertexCollection.push_back(vertex2);
			localPolygonVertexCollection.push_back(vertex3);

			HDC hdc = bitmap.GetDC();

			for (int j = 0; j <= 2; j++)
			{
				if (j == 0)
				{
					MoveToEx(hdc, (int)localPolygonVertexCollection[j].GetX(), (int)localPolygonVertexCollection[j].GetY(), NULL);
				}
				else
				{
					LineTo(hdc, (int)localPolygonVertexCollection[j].GetX(), (int)localPolygonVertexCollection[j].GetY());
				}

			}
			LineTo(hdc, (int)localPolygonVertexCollection[0].GetX(), (int)localPolygonVertexCollection[0].GetY());
		}
		

	}

}

