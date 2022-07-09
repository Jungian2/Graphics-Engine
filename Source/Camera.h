#pragma once
#include "vertex.h"
#include "matrix.h"
#include <cmath>
class Camera
{
public:

	// Default constructor
	Camera();

	Camera(float xRotation, float yRotation, float zRotation, const Vertex& position);

	//Destructor
	~Camera();

	//Accessors and mutators for X axis rotation

	float GetXRotation() const;
	void SetXRoatation(const float xRotation);

	//Accessors and mutators for Y axis rotation

	float GetYRotation() const;
	void SetYRotation(const float yRotation);

	//Accessors and mutators for Z axis rotation

	float GetZRotation() const;
	void SetZRotation(const float zRotation);

	//Accessors and mutators for Viewing Position

	const Vertex GetViewingPosition();
	void SetViewingPosition(const Vertex& viewingPosition);

	//Returns the matrix object CameraMatrix
	Matrix CreateViewingMatrix();

private:

	float _xRotation;
	float _yRotation;
	float _zRotation;


	float _xTranslation;
	float _yTranslation;
	float _zTranslation;

	float g = 0.1f;
	float result = cos(g);
	float result2 = sin(g);
	float result3 = -sin(g);

	Matrix CameraMatrix;

	Vertex _viewingposition;

	

};