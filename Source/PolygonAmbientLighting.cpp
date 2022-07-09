#include "PolygonAmbientLighting.h"

PolygonAmbientLighting::PolygonAmbientLighting()
{
	_redValue = 0;
	_greenValue = 0;
	_blueValue = 0;
}

PolygonAmbientLighting::PolygonAmbientLighting(const int& RedValue, const int& GreenValue, const int& BlueValue)
{
	_redValue = RedValue;
	_greenValue = GreenValue;
	_blueValue = BlueValue;
}

PolygonAmbientLighting::~PolygonAmbientLighting()
{
}

//accessor for getting the Blue value in PolygonAmbientLighting()
int PolygonAmbientLighting::GetRedValue()
{
	return _redValue;
}

void PolygonAmbientLighting::SetRedValue(const int Red)
{
	_redValue = Red;
}

//accessor for getting the Green value in PolygonAmbientLighting()
int PolygonAmbientLighting::GetGreenValue()
{
	return _greenValue;
}

//Mutator for setting the Green value in PolygonAmbientLighting()
void PolygonAmbientLighting::SetGreenValue(const int Green)
{
	_greenValue = Green;
}

//accessor for getting the Blue value in PolygonAmbientLighting()
int PolygonAmbientLighting::GetBlueValue()
{
	return _blueValue;
}

//Mutator for setting the Blue value in PolygonAmbientLighting()
void PolygonAmbientLighting::SetBlueValue(const int Blue)
{
	_blueValue = Blue;
}
