#include "Camera.h"

Camera::Camera(): Camera(0, 0, 0, Vertex(0, 0, 0)) 
{

}

Camera::Camera(float xRotation, float yRotation, float zRotation, const Vertex& position) 
{
	//The xRotation, yRotation and zRotation parameters specify the initial rotation of the camera
	_xRotation = xRotation;
	_yRotation = yRotation;
	_zRotation = zRotation;
	_viewingposition = position;

	//Setting the X, Y & Z equal to the viewing position
	_xTranslation = _viewingposition.GetX();
	_yTranslation = _viewingposition.GetY();
	_zTranslation = _viewingposition.GetZ();

	//Camera Matrix
	CameraMatrix = Matrix{ 1, 0, 0, -_xTranslation,
						   0, 1, 0, -_yTranslation,
						   0, 0, 1, -_zTranslation,
						   0, 0, 0, 1 };

	//
	Matrix _matrix1 = { 1, 0, 0, 0,
							  0, cos(_xRotation), sin(_xRotation), 0,
							  0, -sin(_xRotation), cos(_xRotation), 0,
							  0, 0, 0, 1 };

	Matrix _matrix2 = { cos(_yRotation), 0, -sin(_yRotation), 0,
							  0, 1, 0, 0,
							  sin(_yRotation), 0, cos(_yRotation), 0,
							  0, 0, 0, 1 };

	Matrix _matrix3 = { cos(_zRotation), sin(_zRotation), 0, 0,
							  -sin(_zRotation), cos(_zRotation), 0, 0,
							  0, 0, 1, 0,
							  0, 0, 0, 1 };

	//Setting the camera matrix to be equal to itself and the 3 other matrices
	CameraMatrix = _matrix1 * _matrix2 * _matrix3 * CameraMatrix;
}

//Destructor 
Camera::~Camera()
{
}

float Camera::GetXRotation() const
{
	return _xRotation;
}

void Camera::SetXRoatation(const float xRotation)
{
	_xRotation = xRotation;
}

float Camera::GetYRotation() const
{
	return _yRotation;
}

void Camera::SetYRotation(const float yRotation)
{
	_yRotation = yRotation;
}

float Camera::GetZRotation() const
{
	return _zRotation;
}

void Camera::SetZRotation(const float zRotation)
{
	_zRotation = zRotation;
}

const Vertex Camera::GetViewingPosition()
{
	return _viewingposition;
}

void Camera::SetViewingPosition(const Vertex& viewingPosition)
{
	_viewingposition = viewingPosition;
}

Matrix Camera::CreateViewingMatrix()
{
	return CameraMatrix;
}
