#include "Polygon3D.h"
#include <Windows.h>

class PolygonAmbientLighting
{
public:

	//Default Constructor
	PolygonAmbientLighting();

	PolygonAmbientLighting(const int& RedValue, const int& GreenValue, const int& BlueValue);

	//Destructor
	~PolygonAmbientLighting();

	//Acessors and mutators for getting and setting the Red value in RGB for the Ambient lighting
	int GetRedValue();
	void SetRedValue(const int Red);

	//Acessors and mutators for getting and setting the Green value in RGB for the Ambient lighting
	int GetGreenValue();
	void SetGreenValue(const int Green);

	//Acessors and mutators for getting and setting the Blue value in RGB for the Ambient lighting
	int GetBlueValue();
	void SetBlueValue(const int Blue);

private:

	int _redValue;
	int _greenValue;
	int _blueValue;
	
};
