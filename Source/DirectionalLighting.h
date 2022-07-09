#pragma once
#include "Vector.h"
class DirectionalLighting
{
public:

	//Default Constructor
	DirectionalLighting();

	//Destructor
	~DirectionalLighting();

	//Constructor that initialises all RGB elements.
	DirectionalLighting(const int& DirectionalRedValue, const int& DirectionalGreenValue, const int& DirectionalBlueValue, const Vector& lightDirection);

	//Accessors and Mutators for getting and setting the Red value in the directional lightings RGB value
	int GetRedDirectionalValue();
	void SetRedDirectionalValue(const int red);

	//Accessors and Mutators for getting and setting the Green value in the directional lightings RGB value
	int GetGreenDirectionalValue();
	void SetGreenDirectionalValue(const int green);

	//Accessors and Mutators for getting and setting the Blue value in the directional lightings RGB value
	int GetBlueDirectionalValue();
	void SetBlueDirectionalValue(const int blue);

	//Accessors and Mutators for getting and setting the light direction vector
	Vector GetLightDirectionVector();
	void SetLightDirectionVector(const Vector LightDirection);

private:

	int _DirectionalRedValue;
	int _DirectionalGreenValue;
	int _DirectionalBlueValue;
	Vector _lightDirection;

};