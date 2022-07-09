#include "DirectionalLighting.h"

DirectionalLighting::DirectionalLighting()
{
	_DirectionalRedValue = 0;
	_DirectionalGreenValue = 0;
	_DirectionalBlueValue = 0;
}

DirectionalLighting::~DirectionalLighting()
{
}

DirectionalLighting::DirectionalLighting(const int& DirectionalRedValue, const int& DirectionalGreenValue, const int& DirectionalBlueValue, const Vector& lightDirection)
{
	_DirectionalRedValue = (int)DirectionalRedValue;
	_DirectionalGreenValue = (int)DirectionalGreenValue;
	_DirectionalBlueValue = (int)DirectionalBlueValue;
	_lightDirection = lightDirection;
}

int DirectionalLighting::GetRedDirectionalValue()
{
	return _DirectionalRedValue;
}

void DirectionalLighting::SetRedDirectionalValue(const int red)
{
	_DirectionalRedValue = red;
}

int DirectionalLighting::GetGreenDirectionalValue()
{
	return _DirectionalGreenValue;
}

void DirectionalLighting::SetGreenDirectionalValue(const int green)
{
	_DirectionalRedValue = green;
}

int DirectionalLighting::GetBlueDirectionalValue()
{
	return _DirectionalBlueValue;
}

void DirectionalLighting::SetBlueDirectionalValue(const int blue)
{
	_DirectionalRedValue = blue;
}

Vector DirectionalLighting::GetLightDirectionVector()
{
	return _lightDirection;
}

void DirectionalLighting::SetLightDirectionVector(const Vector LightDirection)
{
	_lightDirection = LightDirection;
}


